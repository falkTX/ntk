//
// "$Id: Fl_Cairo.H 8198 2011-01-06 10:24:58Z manolo $"
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

/* \file
    Handling transparently platform dependent cairo include files 
*/

#ifndef FL_CAIRO_H
# define FL_CAIRO_H
# ifdef FLTK_HAVE_CAIRO

// Cairo is currently supported for the following platforms:
// Win32, Apple Quartz, X11

# include <FL/Fl_Export.H>

# if defined(USE_X11) // X11
#  include <cairo/cairo-xlib.h>
# elif defined(WIN32)
#  include <cairo/cairo-win32.h>
# elif defined(__APPLE_QUARTZ__)
#  include <cairo/cairo-quartz.h>
# else
#  error Cairo is not supported on that platform.
# endif

FL_EXPORT extern cairo_surface_t *fl_cairo_surface;
FL_EXPORT extern cairo_t *fl_cairo_context;

cairo_surface_t * cairo_create_surface(void * gc, int W, int H);

# endif // FLTK_HAVE_CAIRO


#endif // FL_CAIRO_H

//
// End of "$Id: Fl_Cairo.H 8198 2011-01-06 10:24:58Z manolo $" .
//

