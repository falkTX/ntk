
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

#include "FL/Fl_Theme.H"

#include "FL/Cairo_Theme.H"
#include "FL/Crystal_Theme.H"
#include "FL/Gleam_Theme.H"
#include "FL/Clean_Theme.H"
#include "FL/Vector_Theme.H"

static bool themes_registered = 0;

void fl_register_themes ( void )
{
    if ( themes_registered )
        return;

    themes_registered = 1;

    init_cairo_theme();
    init_clean_theme();
    init_crystal_theme();
    init_gleam_theme();
    init_vector_theme();

    {
        Fl_Color_Scheme *o = new Fl_Color_Scheme( "Black",
                                                  fl_rgb_color( 4, 4, 4 ),
                                                  fl_rgb_color( 20, 20, 20 ),
                                                  fl_rgb_color( 240, 240, 240 ),
                                                  FL_YELLOW );
        Fl_Color_Scheme::add( o );
    }
    {
        Fl_Color_Scheme *o = new Fl_Color_Scheme( "Darker",
                                                  fl_rgb_color( 20, 20, 20 ),
                                                  fl_rgb_color( 100, 100, 100 ),
                                                  fl_rgb_color( 240, 240, 240 ),
                                                  FL_YELLOW );
        Fl_Color_Scheme::add( o );
    }
    {
        Fl_Color_Scheme *o = new Fl_Color_Scheme( "Dark",
                                                  fl_rgb_color( 50, 50, 50 ),
                                                  fl_rgb_color( 100, 100, 100 ),
                                                  fl_rgb_color( 255, 255, 255 ),
                                                  FL_YELLOW );
        Fl_Color_Scheme::add( o );
    }    
    {
        Fl_Color_Scheme *o = new Fl_Color_Scheme( "Gray",
                                                  fl_rgb_color( 100, 100, 100 ),
                                                  fl_rgb_color( 127, 127, 127 ),
                                                  fl_rgb_color( 255, 255, 255 ),
                                                  FL_YELLOW );
        Fl_Color_Scheme::add( o );
    }

	
    {
        Fl_Color_Scheme *o = new Fl_Color_Scheme( "Washed out",
                                                  fl_rgb_color( 135, 135, 135 ),
                                                  fl_rgb_color( 203, 203, 203 ),
                                                  fl_rgb_color( 1, 1, 1 ),
						  fl_rgb_color( 0xf0,0xad,0x3f ) );
        Fl_Color_Scheme::add( o );
    }
    
    {
        Fl_Color_Scheme *o = new Fl_Color_Scheme( "Beige",
                                                  fl_rgb_color( 0xb7,0xb5,0x9e ),
//						  fl_rgb_color( 0x28, 0x27, 0x23 ),
						  fl_rgb_color( 0x91, 0x8f, 0x7c ),
						  /* fl_rgb_color( 0x28, 0x27, 0x23 ), */
						  fl_rgb_color( 0x18, 0x17, 0x13 ),
                                                  /* fl_rgb_color( 1, 1, 1 ), */
						  fl_rgb_color( 0xeb,0x7b,0x19 ) );
        Fl_Color_Scheme::add( o );
    }
    {
        Fl_Color_Scheme *o = new Fl_Color_Scheme( "Muted",
                                                  fl_rgb_color( 195, 195, 195 ),
                                                  fl_rgb_color( 220, 220, 220 ),
                                                  fl_rgb_color( 1,1,1 ),
						  fl_rgb_color( 0xf0,0xad,0x3f ) );
        Fl_Color_Scheme::add( o );
    }
    {
        Fl_Color_Scheme *o = new Fl_Color_Scheme( "Light",
                                                  fl_rgb_color( 220, 220, 220 ),
                                                  fl_rgb_color( 192, 192, 192 ),
                                                  fl_rgb_color( 1,1,1 ),
                                                  FL_BLUE );
        Fl_Color_Scheme::add( o );
    }
    {
        Fl::get_system_colors();

        Fl_Color_Scheme *o = new Fl_Color_Scheme( "System",
                                                  (Fl_Color)Fl::get_color( FL_BACKGROUND_COLOR ),
                                                  (Fl_Color)Fl::get_color( FL_BACKGROUND2_COLOR  ),
                                                  (Fl_Color)Fl::get_color( FL_FOREGROUND_COLOR  ),
                                                  (Fl_Color)Fl::get_color( FL_SELECTION_COLOR  ));
        Fl_Color_Scheme::add( o );
    }
}
