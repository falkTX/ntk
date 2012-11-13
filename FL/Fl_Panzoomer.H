
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

#ifndef Fl_Panzoomer_H
#define Fl_Panzoomer_H

#include <FL/Fl_Valuator.H>

class FL_EXPORT Fl_Panzoomer : public Fl_Valuator
{
protected:

    int _zoom;
    bool _zoom_changed;
    int _zoom_min;
    int _zoom_max;

    double _ymin, _ymax, _xmin, _xmax;
    double _xpos, _ypos;

    /* size of the window vertically and horizontally as a value
     * between 0-1. */
    double _ysize, _xsize;

protected:

    virtual void draw_cursor ( int X, int Y, int W, int H );
    /* override this method to draw a thumbnail background... */
    virtual void draw_background ( int X, int Y, int W, int H );
    virtual void draw ( int X, int Y, int W, int H );
    virtual int handle ( int m, int X, int Y, int W, int H );
    void cursor_bounds ( int &cx, int &cy, int &cw, int &ch ) const;

public:

    virtual void draw ( void );
    virtual int handle ( int m );

    Fl_Panzoomer ( int X, int Y, int W, int H, const char *L=0 );
    virtual ~Fl_Panzoomer ( ) { }


    /* these behave like Fl_Scrollbar::value() */
    /* first and total are the bounds, size is the size of the window,
     * and pos is the leftmost edge. */
    int x_value ( int pos, int size, int first, int total )
        {
            if ( pos + size > first + total )
                total = pos+size-first;

            _xmin = first;
            _xmax = total;
            _xpos = pos;
            _xsize = size;

            damage( FL_DAMAGE_USER1 );

            return pos;
        }

    int y_value ( int pos, int size, int first, int total )
        {
            if ( pos + size > first + total )
                total = pos+size-first;

            _ymin = first;
            _ymax = total;
            _ypos = pos;
            _ysize = size;

            damage( FL_DAMAGE_USER1 );

            return pos;
        }

    double x_value ( void ) const { return _xpos; }
    double y_value ( void ) const { return _ypos; }
    void x_value ( double v );
    void y_value ( double v );


    bool zoom_changed ( void ) const { return _zoom_changed; }
    double zoom ( void ) const { return _zoom; }
    void zoom ( int v );

    void zoom_range ( int zmin, int zmax ) { _zoom_min = zmin; _zoom_max = zmax; }

    void zoom_in ( void ) { int z = _zoom; zoom( _zoom - 1 ); if ( z != _zoom ) do_callback(); }
    void zoom_out ( void ) { int z = _zoom; zoom( _zoom + 1 ); if ( z != _zoom ) do_callback(); }
};

#endif
