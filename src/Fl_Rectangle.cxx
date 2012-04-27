// "$Id: Fl_Rectangle.h 8500 2011-03-03 09:20:46Z bgbnbigben $"
//
// Copyright 1998-2006 by Bill Spitzak and others.
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
//    http://www.fltk.org/str.php

#include <FL/Fl_Rectangle.H>
#include <FL/fl_draw.H>

/*! \class Fl_Rectangle
  Describes an integer-sized rectangle. This is the base class of
  Widget, and also used a lot to pass rectangular areas to drawing
  functions. Almost all the functions are inline.

  Negative w() or h() is supposed to mean an empty and thus
  invisible rectangle, but some code will treat the rectangle as
  reflected about x or y. Set the size to zero to make sure you
  have an empty one.
*/

/*! \fn Rectangle::Rectangle()
  The default constructor does not put anything into the fields!
  You can either call set() or just modify the x_, y_, w_, and h_
  variables directly.
*/

/** Initialize to the size w,h. The rectangle is placed inside the
    source rectangle \a r either centered or against an edge depending
    on the FL_ALIGN values in \a flags. For centered alignment if the
    difference in sizes is odd, it always rounds up and left.
    Default value for \a flags is to center in both directions.
 */
void Fl_Rectangle::set(const Fl_Rectangle& r, int w, int h, int flags) {
  if (flags & FL_ALIGN_LEFT) {
    if (flags & FL_ALIGN_RIGHT &&  w > r.w()) x_ = r.r()-w;
    else x_ = r.x();
  } else if (flags & FL_ALIGN_RIGHT) {
    x_ = r.r()-w;
  } else {
    x_ = r.x()+((r.w()-w)>>1);
    // fabien: shouldn't it  consider the case r is smaller to avoid negative values ?
    // WAS: no, it is supposed to center at all times. The right-shift
    // instead of divide-by-2 is to avoid shifting as it goes negative.
    // fabien : well while debugging i observed the shift doesn't avoid
    //    to get negative value at least on Win32
    // WAS: no, it is *supposed* to return a negative value! I want the
    // rectangle "centered" even if it is *bigger*.
    // if (x_<0) x_=0;
  }
  if (flags & FL_ALIGN_TOP) {
    if (flags & FL_ALIGN_BOTTOM && h > r.h()) y_ = r.b()-h;
    else y_ = r.y();
  } else if (flags & FL_ALIGN_BOTTOM) {
    y_ = r.b()-h;
  } else {
    y_ = r.y()+((r.h()-h)>>1);
    // see above
    // if (y_<0) y_=0;
  }
  w_ = w;
  h_ = h;
}

/**
  Replace the value with the union of this rectangle and \a R
  (ie the rectangle that surrounds both of these rectangles).
  If one rectangle is empty(), the other is returned unchanged
  (ie it does not union in the degenerate point of that rectangle).
*/
void Fl_Rectangle::merge(const Fl_Rectangle& R) {
  if (R.empty()) return;
  if (empty()) {*this = R; return;}
  if (R.x() < x()) set_x(R.x());
  if (R.r() > r()) set_r(R.r());
  if (R.y() < y()) set_y(R.y());
  if (R.b() > b()) set_b(R.b());
}

/**
  Replace the value with the intersection of this rectangle and \a R.
  If the rectangles do not intersect, the result may have negative
  width and/or height, this means empty() will return true, but some
  code may still draw this rectangle.
*/
void Fl_Rectangle::intersect(const Fl_Rectangle& R) {
  if (R.x() > x()) set_x(R.x());
  if (R.r() < r()) set_r(R.r());
  if (R.y() > y()) set_y(R.y());
  if (R.b() < b()) set_b(R.b());
}

