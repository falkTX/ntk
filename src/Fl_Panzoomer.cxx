
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

void
Fl_Panzoomer::x_value ( double v ) { 
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
Fl_Panzoomer::y_value ( double v ) {
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
    type( FL_HORIZONTAL );

    fl_draw_box( box(), x(),y(),w(),h(), color());
//    fl_rectf( x(),y(),w(),h(), color() );

    fl_push_clip( x(), y(), w(), h());

    int X,Y,W,H;
    
    X = x() + Fl::box_dx( box() );
    Y = y() + Fl::box_dy( box() );
    W = w() - Fl::box_dw( box() );
    H = h() - Fl::box_dh( box() );
    
    if ( _draw_thumbnail_view_callback )
        _draw_thumbnail_view_callback( X,Y,W,H, _draw_thumbnail_view_userdata );

    int cx,cy,cw,ch;

    cursor_bounds( cx,cy,cw,ch );

    fl_rectf( cx,cy,cw,ch,
              fl_color_add_alpha( FL_WHITE, 50 ));

    fl_rect( cx,cy,cw,ch,
              fl_color_add_alpha( FL_WHITE, 80 ));
    
    fl_pop_clip();

    draw_label();
}

void
Fl_Panzoomer::cursor_bounds ( int &cx, int &cy, int &cw, int &ch ) const
{
    int X,Y,W,H;
    
    X = x() + Fl::box_dx( box() );
    Y = y() + Fl::box_dy( box() );
    W = w() - Fl::box_dw( box() );
    H = h() - Fl::box_dh( box() );

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
}

int
Fl_Panzoomer::handle ( int m )
{
    static int xoffset;
    static int yoffset;
    static bool drag;

    switch ( m )
    {
        case FL_ENTER:
        case FL_LEAVE:
            return 1;
        case FL_PUSH:
        {
            int cx,cy,cw,ch;

            cursor_bounds( cx,cy,cw,ch );

            xoffset = Fl::event_x() - cx;
            yoffset = Fl::event_y() - cy;

            if ( Fl::event_inside( cx,cy,cw,ch ) &&
                 Fl::event_button1() )
                drag = true;

            return 1;
        }
        case FL_DRAG:
        {
            int cx,cy,cw,ch;
            
            cursor_bounds( cx,cy,cw,ch );
            
            if ( drag )
            {
                x_value((((double)Fl::event_x() - x() - xoffset) / w()) * _xmax);
                y_value( (((double)Fl::event_y() - y() - yoffset) / h()) * _ymax );
                
                if ( when() & FL_WHEN_CHANGED )
                    do_callback();
            }
            
            return 1;
            break;
        }
        case FL_MOUSEWHEEL:
        {
            int d = Fl::event_dy();

            if ( Fl::event_ctrl() )
            {                
                zoom( _zoom + d );
                
                return 1;
            }
            else if (!Fl::event_alt() && !Fl::event_shift())
            {
                y_value( _ypos + ( (double)d*5 / h() ) * _ymax );
                
                if ( when() & FL_WHEN_CHANGED )
                    do_callback();

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
    }

    return 0;
}

