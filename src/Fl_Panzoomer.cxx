
/*******************************************************************************/
/* Copyright (C) 2012 Jonathan Moore Liles                                     */
/*                                                                             */
/* This program is free software; you can redistribute it and/or modify it     */
/* under the terms of the GNU General Public License as published by the       */
/* Free Software Foundation; either version 2 of the License, or (at your      */
/* option) any later version.                                                  */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but WITHOUT */
/* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       */
/* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for   */
/* more details.                                                               */
/*                                                                             */
/* You should have received a copy of the GNU General Public License along     */
/* with This program; see the file COPYING.  If not,write to the Free Software */
/* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
/*******************************************************************************/

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Panzoomer.H>

Fl_Panzoomer::Fl_Panzoomer ( int X, int Y, int W, int H, const char *L ) :
    Fl_Valuator( X,Y,W,H,L )
{
    _zoom = 1;
    _zoom_min = 0;
    _zoom_max = 4;
    _zoom_changed = false;

    _ymin = _ymax = _xmin = _xmax = _ysize = _xsize =
    _xpos = _ypos = 0;

    step( 1 );
}

int
Fl_Panzoomer::x_value ( int pos, int size, int first, int total )
{
    if ( pos + size > first + total )
        total = pos+size-first;
            
    if ( (int)_xmin == first &&
         (int)_xmax == total &&
         (int)_xpos == pos &&
         (int)_xsize == size )
        return pos;

    damage( FL_DAMAGE_USER1 );

    _xmin = first;
    _xmax = total;
    _xpos = pos;
    _xsize = size;

    return pos;
}

int
Fl_Panzoomer::y_value ( int pos, int size, int first, int total )
{
    if ( pos + size > first + total )
        total = pos+size-first;

    if ( (int)_ymin == first &&
         (int)_ymax == total &&
         (int)_ypos == pos &&
         (int)_ysize == size )
        return pos;

    damage( FL_DAMAGE_USER1 );
    
    _ymin = first;
    _ymax = total;
    _ypos = pos;
    _ysize = size;
    
    return pos;
}

void
Fl_Panzoomer::x_value ( double v ) 
{ 
    if ( _xpos == v )
        return;

    _xpos = v;
    if ( _xpos < _xmin )
        _xpos = _xmin;
    else if ( _xpos > _xmax - _xsize)
        _xpos = _xmax - _xsize;
    
    damage( FL_DAMAGE_USER1 );
}

void
Fl_Panzoomer::y_value ( double v )
{
    if ( _ypos == v )
        return;

    _ypos = v; 
        
    if ( _ypos < _ymin )
        _ypos = _ymin;
    else if ( _ypos > _ymax - _ysize )
        _ypos = _ymax - _ysize;

    damage( FL_DAMAGE_USER1 );
}

void
Fl_Panzoomer::zoom ( int v )
{
        int z = _zoom;

        _zoom = v;

        if ( _zoom > _zoom_max )
            _zoom = _zoom_max;
        else
            if ( _zoom < _zoom_min )
                _zoom = _zoom_min;

        if ( z != _zoom )
        {
            _zoom_changed = true;
            do_callback();
            _zoom_changed = false;
        }
}

void
Fl_Panzoomer::draw ( void )
{
    draw(x(),y(),w(),h());
}

void
Fl_Panzoomer::draw ( int X, int Y, int W, int H )
{
    fl_draw_box( box(), X,Y,W,H,color());

    X += Fl::box_dx( box() );
    Y += Fl::box_dy( box() );
    W -= Fl::box_dw( box() );
    H -= Fl::box_dh( box() );

    fl_push_clip( X,Y,W,H );

    draw_background( X,Y,W,H );
    draw_cursor( X,Y,W,H );
    
    fl_pop_clip();

    draw_label();
}

void
Fl_Panzoomer::draw_background ( int X, int Y, int W, int H )
{
}

void
Fl_Panzoomer::draw_cursor ( int X, int Y, int W, int H )
{
    int cx,cy,cw,ch;

    cx = X; cy = Y; cw = W; ch = H;

    cursor_bounds( cx,cy,cw,ch );

    fl_rectf( cx,cy,cw,ch,
              fl_color_add_alpha( FL_WHITE, 40 ));

    fl_rect( cx,cy,cw,ch,
              fl_color_add_alpha( FL_WHITE, 200 ));
}

void
Fl_Panzoomer::cursor_bounds ( int &cx, int &cy, int &cw, int &ch ) const
{
    const int minh = 12;
    const int minw = 12;

    int X,Y,W,H;
    
    X = cx;
    Y = cy;
    W = cw;
    H = ch;

    double hval;
    if ( _xmin == _xmax )
        hval = 0.5;
    else 
    {
        hval = (_xpos-_xmin)/(_xmax-_xmin);

        if (hval > 1.0) hval = 1.0;
        else if (hval < 0.0) hval = 0.0;
    }

    double vval;
    if ( _ymin == _ymax )
        vval = 0.5;
    else 
    {
        vval = (_ypos-_ymin)/(_ymax-_ymin);

        if (vval > 1.0) vval = 1.0;
        else if (vval < 0.0) vval = 0.0;
    }

    cx = X + (hval) * W + .5;
    cy = _ymax ? Y + (vval) * H + .5 : Y;
    cw = W * (_xsize/_xmax);
    ch = _ymax ? H * (_ysize/_ymax) : H;

    cw = cw < minw ? minw : cw;
    ch = ch < minh ? minh : ch;
}

int
Fl_Panzoomer::handle ( int m )
{
    return handle( m, x(),y(),w(),h());
}

int
Fl_Panzoomer::handle ( int m, int X, int Y, int W, int H )
{
    static int xoffset;
    static int yoffset;
    static bool drag;

    X += Fl::box_dx( box() );
    Y += Fl::box_dy( box() );
    W -= Fl::box_dw( box() );
    H -= Fl::box_dh( box() );

    switch ( m )
    {
        case FL_ENTER:
        case FL_LEAVE:
            return 1;
        case FL_PUSH:
        {
            int cx,cy,cw,ch;

            cx = X; cy = Y; cw = W; ch = H;
            
            cursor_bounds( cx,cy,cw,ch );

            if ( Fl::event_inside( cx,cy,cw,ch ) )
            {
                xoffset = Fl::event_x() - cx;
                yoffset = Fl::event_y() - cy;
            }
            else
            {
                xoffset = cw / 2;
                yoffset = ch / 2;
            }

            if (// Fl::event_inside( cx,cy,cw,ch ) &&
                 Fl::event_button1() )
                drag = true;

            /* fallthrough */
//            return 1;
        }
        case FL_DRAG:
        {
            int cx,cy,cw,ch;

            cx = X; cy = Y; cw = W; ch = H;
            
            cursor_bounds( cx,cy,cw,ch );
            
            if ( drag )
            {
                x_value((((double)Fl::event_x() - X - xoffset) / W) * _xmax);
                y_value( (((double)Fl::event_y() - Y - yoffset) / H) * _ymax );
                
                if ( when() & FL_WHEN_CHANGED )
                    do_callback();
            }

            damage( FL_DAMAGE_USER1 );

            return 1;
            break;
        }
        case FL_MOUSEWHEEL:
        {
            const int dy = Fl::event_dy();
            const int dx = Fl::event_dx();

            if ( dy && Fl::event_ctrl() )
            {                
                zoom( _zoom + dy );
                
                damage( FL_DAMAGE_USER1 );

                return 1;
            }

            if ( !Fl::event_alt() && !Fl::event_shift())
            {
                if ( dy )
                    y_value( _ypos + ( (double)dy*5 / H ) * _ymax );

                if ( dx )
                    x_value( _xpos + ( (double)dx*5 / W ) * _xmax );
                
                if ( when() & FL_WHEN_CHANGED )
                    do_callback();
                
                damage( FL_DAMAGE_USER1 );
                
                return 1;
            }

            return 0;
            break;
        }
        case FL_RELEASE:
        {
            if ( drag )
            {
                drag = false;

                if ( when() & FL_WHEN_RELEASE )
                    do_callback();
            }
            
            return 1;
        }
        case FL_KEYBOARD: 
        {
            if ( Fl::event_shift() || Fl::event_ctrl() || Fl::event_alt() )
                return 0;

            double xv = _xpos;
            double yv = _ypos;

            /* FIXME: hack */
            int xls = _xsize / 50;
            int yls = _ysize / 50;

            switch ( Fl::event_key() )
            {
                case FL_Up:
                    yv -= yls;
                    break;
                case FL_Down:
                    yv += yls;
                    break;
                case FL_Left:
                    xv -= xls;
                    break;
                case FL_Right:
                    xv += xls;
                    break;
                default:
                    return 0;
            }
            
            x_value( xv );
            y_value( yv );

            do_callback();

            redraw();

            return 1;

            break;
        }
    }

    return 0;
}

