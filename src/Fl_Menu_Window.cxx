//
// "$Id: Fl_Menu_Window.cxx 8198 2011-01-06 10:24:58Z manolo $"
//
// Menu window code for the Fast Light Tool Kit (FLTK).
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

// This is the window type used by Fl_Menu to make the pop-ups.
// It draws in the overlay planes if possible.

// Also here is the implementation of the mouse & keyboard grab,
// which are used so that clicks outside the program's windows
// can be used to dismiss the menus.

#include <config.h>
#include <FL/Fl.H>
#include <FL/x.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Menu_Window.H>

#include <stdio.h>

void Fl_Menu_Window::show() {
    Fl_Single_Window::show();
}

void Fl_Menu_Window::flush() {
  Fl_Single_Window::flush();
}

// Fix the colormap flashing on Maximum Impact Graphics by erasing the
// menu before unmapping it:
void Fl_Menu_Window::hide() {
//  erase();
  Fl_Single_Window::hide();
}

/**  Destroys the window and all of its children.*/
Fl_Menu_Window::~Fl_Menu_Window() {
  hide();
}

//
// End of "$Id: Fl_Menu_Window.cxx 8198 2011-01-06 10:24:58Z manolo $".
//
