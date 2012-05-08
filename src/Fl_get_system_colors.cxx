//
// "$Id: Fl_get_system_colors.cxx 7903 2010-11-28 21:06:39Z matt $"
//
// System color support for the Fast Light Tool Kit (FLTK).
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

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/x.H>
#include <FL/math.h>
#include <FL/fl_utf8.h>
#include "flstring.h"
#include <stdio.h>
#include <stdlib.h>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Tiled_Image.H>
#include "tile.xpm"

#if defined(WIN32) && !defined(__CYGWIN__) && !defined(__WATCOMC__)
// Visual C++ 2005 incorrectly displays a warning about the use of POSIX APIs
// on Windows, which is supposed to be POSIX compliant...
#  define putenv _putenv
#endif // WIN32 && !__CYGWIN__

static char	fl_bg_set = 0;
static char	fl_bg2_set = 0;
static char	fl_fg_set = 0;

/**
    Changes fl_color(FL_BACKGROUND_COLOR) to the given color, 
    and changes the gray ramp from 32 to 56 to black to white.  These are 
    the colors used as backgrounds by almost all widgets and used to draw 
    the edges of all the boxtypes.
*/
void Fl::background(uchar r, uchar g, uchar b) {
  fl_bg_set = 1;

  // replace the gray ramp so that FL_GRAY is this color
  if (!r) r = 1; else if (r==255) r = 254;
  double powr = log(r/255.0)/log((FL_GRAY-FL_GRAY_RAMP)/(FL_NUM_GRAY-1.0));
  if (!g) g = 1; else if (g==255) g = 254;
  double powg = log(g/255.0)/log((FL_GRAY-FL_GRAY_RAMP)/(FL_NUM_GRAY-1.0));
  if (!b) b = 1; else if (b==255) b = 254;
  double powb = log(b/255.0)/log((FL_GRAY-FL_GRAY_RAMP)/(FL_NUM_GRAY-1.0));
  for (int i = 0; i < FL_NUM_GRAY; i++) {
    double gray = i/(FL_NUM_GRAY-1.0);
    Fl::set_color(fl_gray_ramp(i),
		  uchar(pow(gray,powr)*255+.5),
		  uchar(pow(gray,powg)*255+.5),
		  uchar(pow(gray,powb)*255+.5));
  }
}
/** Changes fl_color(FL_FOREGROUND_COLOR). */
void Fl::foreground(uchar r, uchar g, uchar b) {
  fl_fg_set = 1;

  Fl::set_color(FL_FOREGROUND_COLOR,r,g,b);
}

/**
    Changes the alternative background color. This color is used as a 
    background by Fl_Input and other text widgets.
    <P>This call may change fl_color(FL_FOREGROUND_COLOR) if it 
    does not provide sufficient contrast to FL_BACKGROUND2_COLOR.
*/
void Fl::background2(uchar r, uchar g, uchar b) {
  fl_bg2_set = 1;

  Fl::set_color(FL_BACKGROUND2_COLOR,r,g,b);
  Fl::set_color(FL_FOREGROUND_COLOR,
                get_color(fl_contrast(FL_FOREGROUND_COLOR,FL_BACKGROUND2_COLOR)));
}

// these are set by Fl::args() and override any system colors:
const char *fl_fg = NULL;
const char *fl_bg = NULL;
const char *fl_bg2 = NULL;

static void set_selection_color(uchar r, uchar g, uchar b) {
  Fl::set_color(FL_SELECTION_COLOR,r,g,b);
}

#if defined(WIN32) || defined(__APPLE__)

#  include <stdio.h>
// simulation of XParseColor:
int fl_parse_color(const char* p, uchar& r, uchar& g, uchar& b) {
  if (*p == '#') p++;
  int n = strlen(p);
  int m = n/3;
  const char *pattern = 0;
  switch(m) {
  case 1: pattern = "%1x%1x%1x"; break;
  case 2: pattern = "%2x%2x%2x"; break;
  case 3: pattern = "%3x%3x%3x"; break;
  case 4: pattern = "%4x%4x%4x"; break;
  default: return 0;
  }
  int R,G,B; if (sscanf(p,pattern,&R,&G,&B) != 3) return 0;
  switch(m) {
  case 1: R *= 0x11; G *= 0x11; B *= 0x11; break;
  case 3: R >>= 4; G >>= 4; B >>= 4; break;
  case 4: R >>= 8; G >>= 8; B >>= 8; break;
  }
  r = (uchar)R; g = (uchar)G; b = (uchar)B;
  return 1;
}
#else
// Wrapper around XParseColor...
int fl_parse_color(const char* p, uchar& r, uchar& g, uchar& b) {
  XColor x;
  if (!fl_display) fl_open_display();
  if (XParseColor(fl_display, fl_colormap, p, &x)) {
    r = (uchar)(x.red>>8);
    g = (uchar)(x.green>>8);
    b = (uchar)(x.blue>>8);
    return 1;
  } else return 0;
}
#endif // WIN32 || __APPLE__
/** \fn Fl::get_system_colors()
    Read the user preference colors from the system and use them to call
    Fl::foreground(), Fl::background(), and 
    Fl::background2().  This is done by
    Fl_Window::show(argc,argv) before applying the -fg and -bg
    switches.
    
    <P>On X this reads some common values from the Xdefaults database.
    KDE users can set these values by running the "krdb" program, and
    newer versions of KDE set this automatically if you check the "apply
    style to other X programs" switch in their control panel.
*/
#if defined(WIN32)
static void
getsyscolor(int what, const char* arg, void (*func)(uchar,uchar,uchar))
{
  if (arg) {
    uchar r,g,b;
    if (!fl_parse_color(arg, r,g,b))
      Fl::error("Unknown color: %s", arg);
    else
      func(r,g,b);
  } else {
    DWORD x = GetSysColor(what);
    func(uchar(x&255), uchar(x>>8), uchar(x>>16));
  }
}

void Fl::get_system_colors() {
  if (!fl_bg2_set) getsyscolor(COLOR_WINDOW,	fl_bg2,Fl::background2);
  if (!fl_fg_set) getsyscolor(COLOR_WINDOWTEXT,	fl_fg, Fl::foreground);
  if (!fl_bg_set) getsyscolor(COLOR_BTNFACE,	fl_bg, Fl::background);
  getsyscolor(COLOR_HIGHLIGHT,	0,     set_selection_color);
}

#elif defined(__APPLE__)
// MacOS X currently supports two color schemes - Blue and Graphite.
// Since we aren't emulating the Aqua interface (even if Apple would
// let us), we use some defaults that are similar to both.  The
// Fl::scheme("plastic") color/box scheme provides a usable Aqua-like
// look-n-feel...
void Fl::get_system_colors()
{
  fl_open_display();

  if (!fl_bg2_set) background2(0xff, 0xff, 0xff);
  if (!fl_fg_set) foreground(0, 0, 0);
  if (!fl_bg_set) background(0xd8, 0xd8, 0xd8);
  
#if 0 
  // this would be the correct code, but it does not run on all versions
  // of OS X. Also, setting a bright selection color would require 
  // some updates in Fl_Adjuster and Fl_Help_Browser
  OSStatus err;
  RGBColor c;
  err = GetThemeBrushAsColor(kThemeBrushPrimaryHighlightColor, 24, true, &c);
  if (err)
    set_selection_color(0x00, 0x00, 0x80);
  else
    set_selection_color(c.red, c.green, c.blue);
#else
  set_selection_color(0x00, 0x00, 0x80);
#endif
}
#else

// Read colors that KDE writes to the xrdb database.

// XGetDefault does not do the expected thing: it does not like
// periods in either word. Therefore it cannot match class.Text.background.
// However *.Text.background is matched by pretending the program is "Text".
// But this will also match *.background if there is no *.Text.background
// entry, requiring users to put in both (unless they want the text fields
// the same color as the windows).

static void
getsyscolor(const char *key1, const char* key2, const char *arg, const char *defarg, void (*func)(uchar,uchar,uchar))
{
  if (!arg) {
    arg = XGetDefault(fl_display, key1, key2);
    if (!arg) arg = defarg;
  }
  XColor x;
  if (!XParseColor(fl_display, fl_colormap, arg, &x))
    Fl::error("Unknown color: %s", arg);
  else
    func(x.red>>8, x.green>>8, x.blue>>8);
}

void Fl::get_system_colors()
{
  fl_open_display();
  const char* key1 = 0;
  if (Fl::first_window()) key1 = Fl::first_window()->xclass();
  if (!key1) key1 = "fltk";
  if (!fl_bg2_set) getsyscolor("Text","background",	fl_bg2,	"#ffffff", Fl::background2);
  if (!fl_fg_set) getsyscolor(key1,  "foreground",	fl_fg,	"#000000", Fl::foreground);
  if (!fl_bg_set) getsyscolor(key1,  "background",	fl_bg,	"#c0c0c0", Fl::background);
  getsyscolor("Text", "selectBackground", 0, "#000080", set_selection_color);
}

#endif


//// Simple implementation of 2.0 Fl::scheme() interface...
#define D1 BORDER_WIDTH
#define D2 (BORDER_WIDTH+BORDER_WIDTH)

extern void	fl_up_box(int, int, int, int, Fl_Color);
extern void	fl_down_box(int, int, int, int, Fl_Color);
extern void	fl_thin_up_box(int, int, int, int, Fl_Color);
extern void	fl_thin_down_box(int, int, int, int, Fl_Color);
extern void	fl_round_up_box(int, int, int, int, Fl_Color);
extern void	fl_round_down_box(int, int, int, int, Fl_Color);

extern void	fl_up_frame(int, int, int, int, Fl_Color);
extern void	fl_down_frame(int, int, int, int, Fl_Color);
extern void	fl_thin_up_frame(int, int, int, int, Fl_Color);
extern void	fl_thin_down_frame(int, int, int, int, Fl_Color);

#ifndef FL_DOXYGEN
const char	*Fl::scheme_ = (const char *)0;	    // current scheme 
Fl_Image	*Fl::scheme_bg_ = (Fl_Image *)0;    // current background image for the scheme
#endif

static Fl_Pixmap	tile(tile_xpm);

int Fl::scheme(const char *s) {

    printf( "Setting Fl::scheme() is obsolete" );
  // Load the scheme...
  return reload_scheme();
}

int Fl::reload_scheme() {
    Fl_Window *win;

    set_boxtype(FL_UP_FRAME,        fl_up_frame, D1, D1, D2, D2);
    set_boxtype(FL_DOWN_FRAME,      fl_down_frame, D1, D1, D2, D2);
    set_boxtype(FL_THIN_UP_FRAME,   fl_thin_up_frame, 1, 1, 2, 2);
    set_boxtype(FL_THIN_DOWN_FRAME, fl_thin_down_frame, 1, 1, 2, 2);
  
    set_boxtype(FL_UP_BOX,          fl_up_box, D1, D1, D2, D2);
    set_boxtype(FL_DOWN_BOX,        fl_down_box, D1, D1, D2, D2);
    set_boxtype(FL_THIN_UP_BOX,     fl_thin_up_box, 1, 1, 2, 2);
    set_boxtype(FL_THIN_DOWN_BOX,   fl_thin_down_box, 1, 1, 2, 2);
    set_boxtype(_FL_ROUND_UP_BOX,   fl_round_up_box, 3, 3, 6, 6);
    set_boxtype(_FL_ROUND_DOWN_BOX, fl_round_down_box, 3, 3, 6, 6);
  
    // Use standard size scrollbars...
    Fl::scrollbar_size(16);

// Set (or clear) the background tile for all windows...
    for (win = first_window(); win; win = next_window(win)) {
//        win->labeltype(scheme_bg_ ? FL_NORMAL_LABEL : FL_NO_LABEL);
//        win->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE | FL_ALIGN_CLIP | FL_ALIGN_IMAGE_BACKDROP );
        win->align( FL_ALIGN_IMAGE_BACKDROP );
        win->image(scheme_bg_);
        win->redraw();
    }

    return 1;
}


//
// End of "$Id: Fl_get_system_colors.cxx 7903 2010-11-28 21:06:39Z matt $".
//
