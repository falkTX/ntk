//
// "$Id: Fl_Overlay_Window.cxx 8198 2011-01-06 10:24:58Z manolo $"
//
// Overlay window code for the Fast Light Tool Kit (FLTK).
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

/** \fn virtual void Fl_Overlay_Window::draw_overlay() = 0
  You must subclass Fl_Overlay_Window and provide this method.
  It is just like a draw() method, except it draws the overlay.
  The overlay will have already been "cleared" when this is called.  You
  can use any of the routines described in &lt;FL/fl_draw.H&gt;.
*/

// A window using double-buffering and able to draw an overlay
// on top of that.  Uses the hardware to draw the overlay if
// possible, otherwise it just draws in the front buffer.

#include <config.h>
#include <FL/Fl.H>
#include <FL/Fl_Overlay_Window.H>
#include <FL/fl_draw.H>
#include <FL/x.H>

void Fl_Overlay_Window::flush() {
#ifdef BOXX_BUGS
  if (overlay_ && overlay_ != this && overlay_->shown()) {
    // all drawing to windows hidden by overlay windows is ignored, fix this
    XUnmapWindow(fl_display, fl_xid(overlay_));
    Fl_Double_Window::flush(0);
    XMapWindow(fl_display, fl_xid(overlay_));
    return;
  }
#endif
  int erase_overlay = (damage()&FL_DAMAGE_OVERLAY);
  clear_damage((uchar)(damage()&~FL_DAMAGE_OVERLAY));
  Fl_Double_Window::flush(erase_overlay);
  Fl_X* myi = Fl_X::i(this);
#if FLTK_HAVE_CAIRO
      Fl::cairo_make_current( this, myi->xid );
#endif
      draw_overlay();
#if FLTK_HAVE_CAIRO
      Fl::cairo_make_current( this, myi->other_xid );
#endif
}

/**
  Destroys the window and all child widgets.
*/
Fl_Overlay_Window::~Fl_Overlay_Window() {
  hide();
//  delete overlay; this is done by ~Fl_Group
}

int Fl_Overlay_Window::can_do_overlay() {return 0;}

/**
  Call this to indicate that the overlay data has changed and needs to
  be redrawn.  The overlay will be clear until the first time this is
  called, so if you want an initial display you must call this after
  calling show().
*/
void Fl_Overlay_Window::redraw_overlay() {
  clear_damage((uchar)(damage()|FL_DAMAGE_OVERLAY));
  Fl::damage(FL_DAMAGE_CHILD);
}


//
// End of "$Id: Fl_Overlay_Window.cxx 8198 2011-01-06 10:24:58Z manolo $".
//
