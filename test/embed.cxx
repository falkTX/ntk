
/*******************************************************************************/
/* Copyright (C) 2013 Jonathan Moore Liles                                     */
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

#include <FL/x.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl.H>                                           
#include <FL/Fl_Box.H>
#include <FL/Fl_Socket_Window.H>
#include <stdlib.h>

int main ( int argc, char **argv )
{
    Window into = 0;
    int wait_for_client = 0;

    if ( argc > 1 )
    {
        if ( !strcmp( argv[1], "--wait" ) )
            wait_for_client = 1;
        else
            sscanf( argv[1], "%lx", &into );
    }

    fl_open_display();

    Fl_Double_Window *plug = NULL;

    if (  ! wait_for_client )
    {
        { Fl_Double_Window *o = plug = new Fl_Double_Window( 300,300, "Plug");
            o->color( FL_GRAY );
            { 
                Fl_Box *o = new Fl_Box( 0, 0, 300, 300, 
                                        "You should see a gray box in the upper left hand corner on green field if embedding worked.");

                o->align( FL_ALIGN_WRAP );
                o->box(FL_UP_BOX);
                Fl_Group::current()->resizable(o);
            }
          
            o->end();
          
            /* NOTE: window to be embedded is never show()'n */
        }
    }

    Fl_Socket_Window *socket = NULL;

    if ( ! into )
    {
        { Fl_Double_Window *o = new Fl_Double_Window( 500, 600, "Top-Level" );
            { Fl_Box *o = new Fl_Box( 0, 0, 500, 100, "This is the top-level window, the window for embedding should be nested below" );
                o->align( FL_ALIGN_WRAP );
                o->box( FL_BORDER_BOX );
            }
            { Fl_Socket_Window *o = socket = new Fl_Socket_Window( 0, 100, 500,500, "Socket");
                o->color(FL_GREEN);
                o->end();
                o->show();
            }
            o->end();

            o->show();
        }
    }
    if ( ! wait_for_client )
    {
        if ( ! into )
        {
            fl_embed( plug, fl_xid( socket ));
        }
        else
        {
            fl_embed( plug, into );
        }
    }
    else
    {
        printf( "Waiting for client... win_id = 0x%lx %ld\n", fl_xid( socket ), fl_xid( socket ) );
    }

    Fl::run();

    return 0;
}
