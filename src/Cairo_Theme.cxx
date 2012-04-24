
/*******************************************************************************/
/* Copyright (C) 2012 Jonathan Moore Liles                                     */
/* Copyright (C) 2001-2005 by Colin Jones                                      */
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

#include <cairo/cairo.h>

#define USE_X11 1
#define FLTK_HAVE_CAIRO 1
#define FLTK_USE_CAIRO 1

#include <FL/Fl.H>
#include <FL/Fl_Cairo.H>
#include <FL/x.H>
#include <FL/fl_draw.H>

#include "FL/Fl_Theme.H"
#include <math.h>

float fl_box_saturation = 0.6f;
bool fl_boxes_use_gradients = true;
bool fl_debug_boxes = false;

static const int DX = 1;

static void cairo_color(Fl_Color c)
{
    cairo_t *cr = Fl::cairo_cc();

    uchar r,g,b;
    
    c = fl_color_average( c, FL_GRAY, fl_box_saturation ); 

    Fl_Color bc = Fl::draw_box_active() ? c : fl_inactive( c );
    
    fl_color( bc );
    
    Fl::get_color( bc, r, g, b );

    cairo_set_source_rgb( cr, r / 255.0, g / 255.0, b / 255.0 );
}

static void rect_path ( int x, int y, int w, int h, double radius )
{
    cairo_t *cr = Fl::cairo_cc();

    double degrees = M_PI / 180.0;
    
//    x += 2;  y += 2; w -= 4; h -= 4;

    x += DX;  y += DX; w -= DX*2; h -= DX*2;

    cairo_new_sub_path (cr);
    cairo_arc (cr, x + w - radius, y + radius, radius, -90 * degrees, 0 * degrees);
    cairo_arc (cr, x + w - radius, y + h - radius, radius, 0 * degrees, 90 * degrees);
    cairo_arc (cr, x + radius, y + h - radius, radius, 90 * degrees, 180 * degrees);
    cairo_arc (cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
    cairo_close_path (cr);
}

static void draw_rect(int x, int y, int w, int h, Fl_Color bc, double radius = 2 )
{
    cairo_t *cr = Fl::cairo_cc();

    rect_path( x, y, w, h, radius );
    
//    uchar r,g,b;
       
    cairo_color( bc );

    cairo_set_line_width (cr, 1);
    cairo_stroke_preserve (cr);
    cairo_set_source_rgba (cr, 0, 0, 0, 0.1);
    cairo_set_line_width (cr, DX);
    cairo_stroke (cr);
    cairo_set_line_width (cr, 1);

    /* cairo_set_source_rgb( cr, 1, 0, 0 ); */
    /* cairo_rectangle( cr, x, y, w, h ); */
    /* cairo_stroke( cr ); */
}

static void draw_rectf(int x, int y, int w, int h, Fl_Color bc, double radius = 2 )
{
    /* // Draw the outline around the perimeter of the box */
    /* fl_color(fl_color_average(FL_BLACK, FL_BACKGROUND_COLOR, .1)); */

    cairo_t *cr = Fl::cairo_cc();

    rect_path( x, y, w, h, radius );
           
    uchar r,g,b;
    
    cairo_color( bc );

    Fl::get_color( fl_color(), r, g, b );

    float rf = r / 255.0;
    float gf = g / 255.0;
    float bf = b / 255.0;

    cairo_pattern_t *grad = 0;

    if ( fl_boxes_use_gradients )
    {

        grad = cairo_pattern_create_linear( x, y, x, y + h );//,  350.0, 350.0);
    
        cairo_pattern_add_color_stop_rgb( grad, 0.0, rf, gf, bf );
        cairo_pattern_add_color_stop_rgb( grad, 0.4, rf, gf, bf );
        cairo_pattern_add_color_stop_rgb( grad, 1.0, rf + 0.1, gf + 0.1, bf + 0.1 );

        cairo_set_source( cr, grad );
    }
    else
    {
        cairo_set_source_rgb (cr, rf, gf, bf );
    }

    cairo_fill_preserve (cr);
    cairo_set_source_rgba (cr, 0, 0, 0, 0.3 );
    cairo_set_line_width (cr, DX + 0.5 );
    cairo_stroke (cr);

    if ( grad )
        cairo_pattern_destroy( grad );

    cairo_set_line_width (cr, 1);

    /* cairo_set_source_rgb( cr, 1, 0, 0 ); */
    /* cairo_rectangle( cr, x + 0.5, y + 0.5, w + 1, h + 1 ); */
    /* cairo_stroke( cr ); */

}

static void shade_rect_up(int x, int y, int w, int h, Fl_Color bc)
{
    draw_rectf( x, y, w, h, bc );
}

static void frame_rect_up(int x, int y, int w, int h, Fl_Color bc)
{
    draw_rect( x,y,w,h, bc );
}

static void frame_rect_down(int x, int y, int w, int h, Fl_Color bc)
{
    draw_rect( x,y,w,h, bc );
}

static void shade_rect_down(int x, int y, int w, int h, Fl_Color bc)
{
    draw_rectf( x, y, w, h, bc );
}

static void up_frame(int x, int y, int w, int h, Fl_Color c)
{
    frame_rect_up(x, y, w - 1, h - 1, fl_darker(c));
}

static void thin_up_box(int x, int y, int w, int h, Fl_Color c)
{
    shade_rect_up(x + 1, y, w - 2, h - 1, c);
    draw_rect(x + 1, y + 1, w - 3, h - 3, fl_color_average(c, FL_WHITE, .25f));
    frame_rect_up(x, y, w - 1, h - 1, fl_darker(c));

}

static void up_box(int x, int y, int w, int h, Fl_Color c)
{
//    shade_rect_up(x + 1, y, w - 2, h - 1, c);
    shade_rect_up(x, y, w, h, c);

//    frame_rect_up(x, y, w - 1, h - 1, fl_darker(c));
    //draw the inner rect.
    draw_rect(x + 1, y + 1, w - 3, h - 3, fl_color_average(c, FL_WHITE, .25f));

    if ( fl_debug_boxes )
        fl_rect( x, y, w, h, FL_RED );
}

static void down_frame(int x, int y, int w, int h, Fl_Color c)
{
    frame_rect_down(x, y, w - 1, h - 1, fl_darker(c));
}

static void down_box(int x, int y, int w, int h, Fl_Color c)
{
    shade_rect_down(x + 1, y, w - 2, h, c);
    down_frame(x, y, w, h, fl_darker(c));
    //draw the inner rect.
    //frame_rect(x + 1, y + 1, w - 3, h - 3, fl_color_average(c, FL_BLACK, .65));
}

static void thin_down_box(int x, int y, int w, int h, Fl_Color c)
{
    down_box(x, y, w, h, c);
}

static void round_box(int x, int y, int w, int h, Fl_Color c)
{
    cairo_t *cr = Fl::cairo_cc();

    if ( w > 20 && h > 20 )
        draw_rectf( x, y, w, h, c, 20.0 );
    if ( w > 10 && h > 10 )
        draw_rectf( x, y, w, h, c, 10.0 );
    else
    {
        cairo_save( cr );
        cairo_translate( cr, x + w / 2, y + w / 2 );
        cairo_scale( cr, w, h );
        cairo_arc( cr, 0, 0, 0.5, 0, M_PI * 2 );
       
        cairo_restore( cr );

        cairo_color( c );
        cairo_fill_preserve( cr );
        cairo_set_source_rgb( cr, 0, 0, 0 );
        cairo_set_line_width( cr, 1 );
        cairo_stroke( cr );
    }
}

static void round_shadow_box(int x, int y, int w, int h, Fl_Color c)
{
    cairo_t *cr = Fl::cairo_cc();

    rect_path( x + 5, y + 5, w, h, 10.0 );

    cairo_set_source_rgba( cr, 0, 0, 0, 0.5 );
   
    cairo_fill( cr );
   
    draw_rectf( x, y, w, h, c, 10.0 );
}


static void
init_theme ( void )
{
    Fl::set_boxtype(  _FL_RSHADOW_BOX,         round_shadow_box,           5,5,10,10 );
    Fl::set_boxtype(  _FL_ROUNDED_BOX,         round_box,           4,4, 8,8 );
    Fl::set_boxtype(  FL_UP_BOX,         up_box,           DX,DX,DX*2,DX*2 );
    Fl::set_boxtype(  FL_DOWN_BOX,       down_box,         DX,DX,DX*2,DX*2 );
    Fl::set_boxtype(  FL_THIN_UP_BOX,         up_box,      DX,DX,DX*2,DX*2  );
    Fl::set_boxtype(  FL_THIN_DOWN_BOX,       down_box,    DX,DX,DX*2,DX*2  );
    Fl::set_boxtype(  FL_UP_FRAME,       up_frame,         DX,DX,DX*2,DX*2  );
    Fl::set_boxtype(  FL_DOWN_FRAME,     down_frame,       DX,DX,DX*2,DX*2  );
    /* Fl::set_boxtype(  FL_THIN_UP_BOX,    thin_up_box,      1,1,1,1 ); */
    /* Fl::set_boxtype(  FL_THIN_DOWN_BOX,  thin_down_box,    1,1,1,1 ); */
    Fl::set_boxtype(  FL_ROUND_UP_BOX,   up_box,           DX,DX,DX*2,DX*2 );
    Fl::set_boxtype(  FL_ROUND_DOWN_BOX, down_box,         DX,DX,DX*2,DX*2 );
}

void
init_cairo_theme ( void )
{
    Fl_Theme *t = new Fl_Theme( "Cairo", "Pure Cairo Theme", "Jonathan Moore Liles", init_theme );

    Fl_Theme::add( t );
}

