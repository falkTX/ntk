//
// "$Id: Fl_Cairo.cxx 8198 2011-01-06 10:24:58Z manolo $"
//
// Main header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

#include <config.h>

#ifdef FLTK_HAVE_CAIRO
#include <FL/Fl.H>
#include <FL/x.H>
#include <FL/Fl_Window.H>
#ifdef __APPLE__
#include <Carbon/Carbon.h>
#endif

/* 
    Creates transparently a cairo_surface_t object.
    gc is an HDC context in  WIN32, a CGContext* in Quartz, a display on X11
 */
cairo_surface_t * cairo_create_surface(void * gc, int W, int H) {
# if defined(USE_X11)
    return cairo_xlib_surface_create(fl_display, fl_window, fl_visual->visual, W, H);
# elif   defined(WIN32)
    return cairo_win32_surface_create((HDC) gc);
# elif defined(__APPLE_QUARTZ__)
    return cairo_quartz_surface_create_for_cg_context((CGContext*) gc, W, H);
# else
#  error Cairo is not supported under this platform.
# endif
}

cairo_surface_t *fl_cairo_surface;
cairo_t *fl_cairo_context;

cairo_t * 
Fl::cairo_make_current(Fl_Window* wi) {
    if (!wi) return NULL; // Precondition

    if ( ! wi->i->cc )
    {
        /* set this window's context to be the current one */
        wi->i->cs = cairo_create_surface(fl_gc, wi->w(), wi->h());
        wi->i->cc = cairo_create( wi->i->cs );
//        cairo_surface_destroy( s );
    }

    fl_cairo_surface = wi->i->cs;
    fl_cairo_context = wi->i->cc;

    return wi->i->cc;
}

void
Fl::cairo_set_drawable ( Fl_Window *wi )
{
    cairo_xlib_surface_set_drawable( wi->i->cs, fl_window, wi->w(), wi->h() );
}

#endif // FLTK_HAVE_CAIRO

//
// End of "$Id: Fl_Cairo.cxx 8198 2011-01-06 10:24:58Z manolo $" .
//
