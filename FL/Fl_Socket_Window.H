/*******************************************************************************/
/* Copyright (C) 2013 Jonathan Moore Liles                                     */
/*                                                                             */
/* This program is free software; you can redistribute it and/or modify it     */
/* under the terms of the GNU Library General Public License as published      */
/* by the Free Software Foundation; either version 2 of the License, or (at    */
/* your option) any later version.                                             */
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

#ifndef FL_SOCKET_WINDOW_H
#define FL_SOCKET_WINDOW_H

#include <FL/Fl_Window.H>
#include <FL/x.H>

class Fl_Socket_Window : public Fl_Window
{
    static const char * class_name ( void ) { return "Fl_Socket_Window"; } 

    Window _plug_xid;
    
    
public:

    Fl_Socket_Window ( int X, int Y, int W, int H, const char *L=0 ) : Fl_Window(X,Y,W,H,L)
        {
            user_data( (void*)class_name() );
        }

    ~Fl_Socket_Window ( )
        {
        }
    
    static bool is_socket ( Fl_Window *w ) { return class_name() == w->user_data(); }
    
    virtual Window plug_xid ( void ) const { return _plug_xid; }

    virtual void plug_xid ( Window w ) { _plug_xid = w; }
}; 

#endif
