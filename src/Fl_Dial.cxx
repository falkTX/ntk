
/*******************************************************************************/
/* Copyright (C) 2008 Jonathan Moore Liles                                     */
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

#include <FL/Fl_Dial.H>

#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>

#include <FL/Fl_Shared_Image.H>

class image_node {
    
public:
    
    Fl_Image *original;                                     /* originl image */
    
    Fl_Image *scaled;                                        /* downscaled image */
    
    class image_node *next;
};

static image_node *_first = 0;

int Fl_Dial::_default_style = Fl_Dial::PLASTIC_DIAL;
Fl_Image *Fl_Dial::_default_image = 0;

/** This simple box is suitable for use with knob-type widgets. It
 * comprises a border with shadow, and a cap with glare-lines akin
 * to those seen on burnished aluminum knobs. */
static void
burnished_oval_box ( int x, int y, int w, int h, Fl_Color c )
{
    /* draw background */
    fl_color( fl_darker( c ) );
    fl_pie( x, y, w, h, 0, 360 );
    fl_color( fl_darker( fl_darker( c ) ) );
    fl_pie( x, y, w, h, 180 + 215, 180 + 45 );

    /* shrink */
    x += 4;
    y += 4;
    w -= 7;
    h -= 7;

    /* draw cap */
    fl_color( c );
    fl_pie( x, y, w, h, 0, 360 );

    /* draw glare */

    const int a1 = 10;
    const int a2 = 90;

    fl_color( fl_color_average( FL_WHITE, c, 0.15f ) );
    fl_pie( x, y, w, h, a1, a2 );
    fl_pie( x, y, w, h, 180 + a1, 180 + a2 );
    fl_color( fl_color_average( FL_WHITE, c, 0.25f ) );

    const int d = (a2 - a1) / 2;
    fl_pie( x, y, w, h, a1 + (d / 2), a2 - (d / 2) );
    fl_pie( x, y, w, h, 180 + a1 + (d / 2), 180 + a2 - (d / 2) );
}




void
Fl_Dial::draw_box ( void )
{
}

static Fl_Widget *_mouse_inside = NULL;

int
Fl_Dial::handle ( int m )
{
    /* Fl_Dial and friends should really handle mousewheel, but they don't in FTLK1 */

    switch ( m )
    {
        case FL_ENTER:
            _mouse_inside = this;
            redraw();
            return Fl_Dial_Base::handle(m) || 1;
        case FL_LEAVE:
            _mouse_inside = NULL;
            redraw();
            return Fl_Dial_Base::handle(m) || 1;
        case FL_MOUSEWHEEL:
        {
            if ( this != Fl::belowmouse() )
                return 0;
            if (Fl::e_dy==0)
                return 0;
            
            const int steps = Fl::event_ctrl() ? 128 : 16;
            
            const float step = fabs( maximum() - minimum() ) / (float)steps;
            
            int dy = Fl::e_dy;
            
            /* slider is in 'upside down' configuration, invert meaning of mousewheel */
            if ( maximum() > minimum() )
                dy = 0 - dy;
            
            handle_drag(clamp(value() + step * dy));
            return 1;
        }
    }

    int X, Y, S;

    get_knob_dimensions ( &X, &Y, &S );

    return Fl_Dial_Base::handle( m, X, Y, S, S );
}

void
Fl_Dial::draw ( void )
{
    int X, Y, S;

    get_knob_dimensions ( &X, &Y, &S);

    draw_box();
    draw_label();

    double angle = ( angle2() - angle1() ) * ( value() - minimum()) / ( maximum() - minimum() ) + angle1();

    int t = type();

    if ( t == PIXMAP_DIAL )
    {
        Fl_Image *im = pixmap();
        
        if ( !im )
            im = Fl_Dial::_default_image;
               
        if ( im )
        {
            fl_push_clip( x(), y(), w(), h() );
      
            int knob_width = im->h();
            const int frames = im->w() / im->h();

            const int index = (int)( ( frames - 1 ) * ( value() - minimum()) / ( maximum() - minimum() ));

            /* if ( ( damage() == FL_DAMAGE_ALL ) || */
            /*      ( ( damage() & FL_DAMAGE_EXPOSE ) && */
            /*        index != _last_pixmap_index ) ) */
            {

                /* FIXME: Why doesn't this work? */
                /* if ( ! active_r() ) */
                /* { */
                /*     im->inactive(); */
                /* } */

                if ( w() >= knob_width )
                {
                    im->draw( x() + ( w() / 2 ) - ( knob_width / 2 ),
                              y() + ( h() / 2 ) - ( knob_width / 2 ),
                              knob_width,
                              knob_width,
                              knob_width * index,
                              0 );
                }
                else
                {
//                    while ( knob_width > w() )
                    knob_width = w();

                    image_node *i;

                    Fl_Image *scaled = 0;

                    for ( i = _first; i; i = i->next )
                    {
                        if ( i->original == im &&
                             i->scaled && i->scaled->h() == knob_width )
                        {
                            scaled = i->scaled;
                            break;
                        }
                    }

                    if ( ! scaled )
                    {
                        scaled = im->copy( knob_width * frames, knob_width );

                        i = new image_node();

                        i->original = im;
                        i->scaled = scaled;
                        i->next = _first;
                        _first = i;
                    }
                  
                    scaled->draw( x() + ( w() / 2 ) - ( knob_width / 2 ),
                                  y() + ( h() / 2 ) - ( knob_width / 2 ),
                                  knob_width,
                                  knob_width,
                                  knob_width * index,
                                  0 );
                }
                
                _last_pixmap_index = index;
            }

            fl_pop_clip();

            goto done;
        }
        else
            /* draw as plastic dial instead when image is missing */
            t = PLASTIC_DIAL;
    }

    if ( t == ARC_DIAL )
    {
        /* fl_line_style( FL_SOLID, 0 ); */
        if ( type() == ARC_DIAL )
            fl_draw_box( box(), X, Y, S, S, color() );

        /* shrink a bit */
        X += S / 16.0;
        Y += S / 16.0;
        S -= S / 8;

        fl_line_style( FL_SOLID, S / 6 );

        /* background arc */
        fl_color( fl_darker( color() ) );
        fl_arc( X, Y, S, S, 270 - angle1(), 270 - angle2() );

        /* foreground arc */
        fl_color( selection_color() );
        fl_arc( X, Y, S, S, 270 - angle1(), 270 - angle  );

        fl_line_style( FL_SOLID, 0 );

        fl_color( fl_contrast( labelcolor(), color() ) );
    }
    else if ( t == PLASTIC_DIAL || t == BURNISHED_DIAL )
    {
        draw_knob(t);
        
        draw_cursor( X, Y, S);
    }

done:

    if ( _mouse_inside == this )
    {
        /* TODO: Make this optional */
        char s[128];
    
        fl_font( FL_HELVETICA, 10 );
    
        char buf[128];
        format(buf);
        
        snprintf( s, sizeof( s ), buf, value()  );
        
        fl_color( FL_FOREGROUND_COLOR );
        fl_draw( s, X, Y, S, S, FL_ALIGN_CENTER );
    }
}

void
Fl_Dial::get_knob_dimensions ( int *X, int *Y, int *S )
{
    int ox, oy, ww, hh, side;
    ox = x();
    oy = y();
    ww = w();
    hh = h();
    
    if (ww > hh)
    {
        side = hh;
        ox = ox + (ww - side) / 2;
    }
    else
    {
        side = ww;
        oy = oy + (hh - side) / 2;
    }
    side = w() > h() ? hh : ww;

    *X = ox;
    *Y = oy;
    *S = side;
}

void 
Fl_Dial::draw_cursor ( int ox, int oy, int side )
{
    double angle;

//    fl_color(fl_color_average(FL_BACKGROUND_COLOR, FL_BLACK, .7f));

    angle = ( angle2() - angle1() ) * ( value() - minimum()) / ( maximum() - minimum() ) + angle1();

    fl_color( fl_contrast( selection_color(), FL_BACKGROUND_COLOR ) );
    
    fl_line_style( FL_SOLID, side / 8 );
    
    const int d = 6;
    
    /* account for edge conditions */
    angle = angle < angle1() + d ? angle1() + d : angle;
    angle = angle > angle2() - d ? angle2() - d : angle;
    
    ox += side * 0.15;
    oy += side * 0.15;
    side -= side * 0.15 * 2;
    
    fl_arc( ox, oy, side, side, 270 - (angle - d), 270 - (angle + d) );
//    fl_arc( ox, oy, side, side, 270 - (angle + d), 270 - (angle - d) );
    
    fl_line_style( FL_SOLID, 0 );
}

void
Fl_Dial::draw_knob ( int type )
{
    int ox, oy, ww, hh, side;

    get_knob_dimensions ( &ox, &oy, &side );

    ww = w();
    hh = h();
    draw_label();
    fl_clip(ox, oy, ww, hh);

    int o = side * 0.15;

    // background
    /* fl_color(FL_BACKGROUND_COLOR); */
    /* fl_rectf(ox, oy, side, side); */
        
    /* scale color */
    if ( damage() & FL_DAMAGE_ALL )
    {
        fl_color(fl_color_average(color(), FL_BACKGROUND2_COLOR, .6));
        
        fl_pie(ox + 1, oy + 3, side - 2, side - 12, 0, 360);

        // scale
        
        draw_scale(ox, oy, side);
    }

    Fl_Color c = active_r() ? fl_color_average(FL_BACKGROUND_COLOR, FL_WHITE, .7) : FL_INACTIVE_COLOR;

    if ( type == BURNISHED_DIAL )
    {
        burnished_oval_box( ox + o, oy + o, side - (o*2), side - (o*2), c );
    }
    else
    {
            
        fl_color(FL_BACKGROUND_COLOR);

        fl_pie(ox + o, oy + o, side - (o*2), side - (o*2), 0, 360);

        // shadow

        fl_color(fl_color_average(FL_BACKGROUND_COLOR, FL_BLACK, .8f));
        fl_pie(ox + o + 2, oy + o + 3, side - o*2, side - o*2, 0, 360);
        /* fl_color(fl_color_average(FL_BACKGROUND_COLOR, FL_BLACK, .2f)); */
        /* fl_pie(ox + o + 4, oy + o + 5, side - o*2, side - o*2, 0, 360); */

        // knob edge
        fl_color( c);

        fl_arc(ox + o, oy + o, side - o*2, side - o*2, 0, 360);

        fl_color(fl_color_average(FL_BACKGROUND_COLOR, FL_WHITE, .6));

        fl_pie(ox + o, oy + o, side - o*2, side - o*2, 0, 360);
        
    }
    fl_pop_clip();
}


void
Fl_Dial::draw_scale ( int ox, int oy, int side )
{
    float x1, y1, x2, y2, rds, cx, cy, ca, sa;
    rds = side / 2;
    cx = ox + side / 2;
    cy = oy + side / 2;
    if (_scaleticks == 0)
        return;
    double a_step = (10.0 * 3.14159 / 6.0) / _scaleticks;
    double a_orig = -(3.14159 / 3.0);
    for (int a = 0; a <= _scaleticks; a++)
    {
        double na = a_orig + a * a_step;
        ca = cos(na);
        sa = sin(na);
        x1 = cx + (rds) * ca;
        y1 = cy - (rds) * sa;
        x2 = cx + (rds - 6) * ca;
        y2 = cy - (rds - 6) * sa;
        fl_color(FL_BACKGROUND_COLOR);
        fl_line(x1, y1, x2, y2);
    }
}

void 
Fl_Dial::scaleticks ( int tck )
{
    _scaleticks = tck;
    if (_scaleticks < 0)
        _scaleticks = 0;
    if (_scaleticks > 31)
        _scaleticks = 31;
    if (visible())
        damage(FL_DAMAGE_ALL);
}
