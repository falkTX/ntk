//
// "$Id: Fl_Double_Window.cxx 8383 2011-02-06 12:20:16Z AlbrechtS $"
//
// Double-buffered window code for the Fast Light Tool Kit (FLTK).
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
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Printer.H>
#include <FL/x.H>
#include <FL/fl_draw.H>

#include <FL/Fl_Cairo.H>

//#define DEBUG_EXPOSE

// On systems that support double buffering "naturally" the base
// Fl_Window class will probably do double-buffer and this subclass
// does nothing.

void Fl_Double_Window::show() {
  Fl_Window::show();
}

static void fl_copy_offscreen_to_display(int x, int y, int w, int h, Fl_Offscreen pixmap, int srcx, int srcy);

/** \addtogroup fl_drawings
 @{
 */
/** Copy a rectangular area of the given offscreen buffer into the current drawing destination.
 \param x,y	position where to draw the copied rectangle
 \param w,h	size of the copied rectangle
 \param pixmap  offscreen buffer containing the rectangle to copy
 \param srcx,srcy origin in offscreen buffer of rectangle to copy
 */
void fl_copy_offscreen(int x, int y, int w, int h, Fl_Offscreen pixmap, int srcx, int srcy) {
  if (fl_graphics_driver == Fl_Display_Device::display_device()->driver()) {
    fl_copy_offscreen_to_display(x, y, w, h, pixmap, srcx, srcy);
  }
  else { // when copy is not to the display
    fl_begin_offscreen(pixmap);
    uchar *img = fl_read_image(NULL, srcx, srcy, w, h, 0);
    fl_end_offscreen();
    fl_draw_image(img, x, y, w, h, 3, 0);
    delete[] img;
  }
}
/** @} */

#if defined(USE_X11)

static void fl_copy_offscreen_to_display(int x, int y, int w, int h, Fl_Offscreen pixmap, int srcx, int srcy) {
  XCopyArea(fl_display, pixmap, fl_window, fl_gc, srcx, srcy, w, h, x, y);
}


// maybe someone feels inclined to implement alpha blending on X11?
char fl_can_do_alpha_blending() {
  return 0;
}
#elif defined(WIN32)

// Code used to switch output to an off-screen window.  See macros in
// win32.H which save the old state in local variables.

typedef struct { BYTE a; BYTE b; BYTE c; BYTE d; } FL_BLENDFUNCTION;
typedef BOOL (WINAPI* fl_alpha_blend_func)
    (HDC,int,int,int,int,HDC,int,int,int,int,FL_BLENDFUNCTION);
static fl_alpha_blend_func fl_alpha_blend = NULL;
static FL_BLENDFUNCTION blendfunc = { 0, 0, 255, 1};

/*
 * This function checks if the version of MSWindows that we
 * curently run on supports alpha blending for bitmap transfers
 * and finds the required function if so.
 */
char fl_can_do_alpha_blending() {
  static char been_here = 0;
  static char can_do = 0;
  // do this test only once
  if (been_here) return can_do;
  been_here = 1;
  // load the library that implements alpha blending
  HMODULE hMod = LoadLibrary("MSIMG32.DLL");
  // give up if that doesn't exist (Win95?)
  if (!hMod) return 0;
  // now find the blending function inside that dll
  fl_alpha_blend = (fl_alpha_blend_func)GetProcAddress(hMod, "AlphaBlend");
  // give up if we can't find it (Win95)
  if (!fl_alpha_blend) return 0;
  // we have the call, but does our display support alpha blending?
  // get the desktop's device context
  HDC dc = GetDC(0L);
  if (!dc) return 0;
  // check the device capabilities flags. However GetDeviceCaps
  // does not return anything useful, so we have to do it manually:

  HBITMAP bm = CreateCompatibleBitmap(dc, 1, 1);
  HDC new_gc = CreateCompatibleDC(dc);
  int save = SaveDC(new_gc);
  SelectObject(new_gc, bm);
  /*COLORREF set = */ SetPixel(new_gc, 0, 0, 0x01010101);
  BOOL alpha_ok = fl_alpha_blend(dc, 0, 0, 1, 1, new_gc, 0, 0, 1, 1, blendfunc);
  RestoreDC(new_gc, save);
  DeleteDC(new_gc);
  DeleteObject(bm);
  ReleaseDC(0L, dc);

  if (alpha_ok) can_do = 1;
  return can_do;
}

HDC fl_makeDC(HBITMAP bitmap) {
  HDC new_gc = CreateCompatibleDC(fl_gc);
  SetTextAlign(new_gc, TA_BASELINE|TA_LEFT);
  SetBkMode(new_gc, TRANSPARENT);
#if USE_COLORMAP
  if (fl_palette) SelectPalette(new_gc, fl_palette, FALSE);
#endif
  SelectObject(new_gc, bitmap);
  return new_gc;
}

static void fl_copy_offscreen_to_display(int x,int y,int w,int h,HBITMAP bitmap,int srcx,int srcy) {
  HDC new_gc = CreateCompatibleDC(fl_gc);
  int save = SaveDC(new_gc);
  SelectObject(new_gc, bitmap);
  BitBlt(fl_gc, x, y, w, h, new_gc, srcx, srcy, SRCCOPY);
  RestoreDC(new_gc, save);
  DeleteDC(new_gc);
}

void fl_copy_offscreen_with_alpha(int x,int y,int w,int h,HBITMAP bitmap,int srcx,int srcy) {
  HDC new_gc = CreateCompatibleDC(fl_gc);
  int save = SaveDC(new_gc);
  SelectObject(new_gc, bitmap);
  BOOL alpha_ok = 0;
  // first try to alpha blend
  // if to printer, always try alpha_blend
  int to_display = Fl_Surface_Device::surface()->class_name() == Fl_Display_Device::class_id; // true iff display output
  if ( (to_display && fl_can_do_alpha_blending()) || Fl_Surface_Device::surface()->class_name() == Fl_Printer::class_id) {
    alpha_ok = fl_alpha_blend(fl_gc, x, y, w, h, new_gc, srcx, srcy, w, h, blendfunc);
  }
  // if that failed (it shouldn't), still copy the bitmap over, but now alpha is 1
  if (!alpha_ok) {
    BitBlt(fl_gc, x, y, w, h, new_gc, srcx, srcy, SRCCOPY);
  }
  RestoreDC(new_gc, save);
  DeleteDC(new_gc);
}

extern void fl_restore_clip();

#elif defined(__APPLE_QUARTZ__) || defined(FL_DOXYGEN)

char fl_can_do_alpha_blending() {
  return 1;
}

Fl_Offscreen fl_create_offscreen_with_alpha(int w, int h) {
  void *data = calloc(w*h,4);
  CGColorSpaceRef lut = CGColorSpaceCreateDeviceRGB();
  CGContextRef ctx = CGBitmapContextCreate(
    data, w, h, 8, w*4, lut, kCGImageAlphaPremultipliedLast);
  CGColorSpaceRelease(lut);
  return (Fl_Offscreen)ctx;
}

/** \addtogroup fl_drawings
 @{
 */

/** 
  Creation of an offscreen graphics buffer.
 \param w,h     width and height in pixels of the buffer.
 \return    the created graphics buffer.
 */
Fl_Offscreen fl_create_offscreen(int w, int h) {
  void *data = calloc(w*h,4);
  CGColorSpaceRef lut = CGColorSpaceCreateDeviceRGB();
  CGContextRef ctx = CGBitmapContextCreate(
    data, w, h, 8, w*4, lut, kCGImageAlphaNoneSkipLast);
  CGColorSpaceRelease(lut);
  return (Fl_Offscreen)ctx;
}

static void bmProviderRelease (void *src, const void *data, size_t size) {
  CFIndex count = CFGetRetainCount(src);
  CFRelease(src);
  if(count == 1) free((void*)data);
}

static void fl_copy_offscreen_to_display(int x,int y,int w,int h,Fl_Offscreen osrc,int srcx,int srcy) {
  CGContextRef src = (CGContextRef)osrc;
  void *data = CGBitmapContextGetData(src);
  int sw = CGBitmapContextGetWidth(src);
  int sh = CGBitmapContextGetHeight(src);
  CGImageAlphaInfo alpha = CGBitmapContextGetAlphaInfo(src);
  CGColorSpaceRef lut = CGColorSpaceCreateDeviceRGB();
  // when output goes to a Quartz printercontext, release of the bitmap must be
  // delayed after the end of the print page
  CFRetain(src);
  CGDataProviderRef src_bytes = CGDataProviderCreateWithData( src, data, sw*sh*4, bmProviderRelease);
  CGImageRef img = CGImageCreate( sw, sh, 8, 4*8, 4*sw, lut, alpha,
    src_bytes, 0L, false, kCGRenderingIntentDefault);
  // fl_push_clip();
  CGRect rect = { { x, y }, { w, h } };
  Fl_X::q_begin_image(rect, srcx, srcy, sw, sh);
  CGContextDrawImage(fl_gc, rect, img);
  Fl_X::q_end_image();
  CGImageRelease(img);
  CGColorSpaceRelease(lut);
  CGDataProviderRelease(src_bytes);
}

/**  Deletion of an offscreen graphics buffer.
 \param ctx     the buffer to be deleted.
 */
void fl_delete_offscreen(Fl_Offscreen ctx) {
  if (!ctx) return;
  void *data = CGBitmapContextGetData((CGContextRef)ctx);
  CFIndex count = CFGetRetainCount(ctx);
  CGContextRelease((CGContextRef)ctx);
  if(count == 1) free(data);
}

const int stack_max = 16;
static int stack_ix = 0;
static CGContextRef stack_gc[stack_max];
static Window stack_window[stack_max];
static Fl_Surface_Device *_ss;

/**  Send all subsequent drawing commands to this offscreen buffer.
 \param ctx     the offscreen buffer.
 */
void fl_begin_offscreen(Fl_Offscreen ctx) {
  _ss = Fl_Surface_Device::surface(); 
  Fl_Display_Device::display_device()->set_current();
  if (stack_ix<stack_max) {
    stack_gc[stack_ix] = fl_gc;
    stack_window[stack_ix] = fl_window;
  } else 
    fprintf(stderr, "FLTK CGContext Stack overflow error\n");
  stack_ix++;

  fl_gc = (CGContextRef)ctx;
  fl_window = 0;
  CGContextSaveGState(fl_gc);
  fl_push_no_clip();
}

/** Quit sending drawing commands to the current offscreen buffer.
 */
void fl_end_offscreen() {
  Fl_X::q_release_context();
  fl_pop_clip();
  if (stack_ix>0)
    stack_ix--;
  else
    fprintf(stderr, "FLTK CGContext Stack underflow error\n");
  if (stack_ix<stack_max) {
    fl_gc = stack_gc[stack_ix];
    fl_window = stack_window[stack_ix];
  }
  _ss->set_current();
}

/** @} */

extern void fl_restore_clip();

#else
# error unsupported platform
#endif

/**
  Forces the window to be redrawn.
*/
void Fl_Double_Window::flush() {flush(0);}

/**
  Forces the window to be redrawn.
  \param[in] eraseoverlay non-zero to erase overlay, zero to ignore

  Fl_Overlay_Window relies on flush(1) copying the back buffer to the
  front everywhere, even if damage() == 0, thus erasing the overlay,
  and leaving the clip region set to the entire window.
*/
void Fl_Double_Window::flush(int eraseoverlay) {
  Fl_X *myi = Fl_X::i(this);

  if (!myi->other_xid) {

#if defined(USE_X11) || defined(WIN32)
    myi->other_xid = fl_create_offscreen(w(), h());
    clear_damage(FL_DAMAGE_ALL);
#elif defined(__APPLE_QUARTZ__)
    if (force_doublebuffering_) {
      myi->other_xid = fl_create_offscreen(w(), h());
      clear_damage(FL_DAMAGE_ALL);
    }

#else
# error unsupported platform
#endif
    myi->other_cs = Fl::cairo_create_surface( myi->other_xid, w(), h() );
    myi->other_cc = cairo_create( myi->other_cs );

  }
  
  fl_clip_region(myi->region);

  if (damage() & ~FL_DAMAGE_EXPOSE) {

  Fl::cairo_make_current( myi->other_cs, myi->other_cc );
  
#ifdef WIN32
    HDC _sgc = fl_gc;
    fl_gc = fl_makeDC(myi->other_xid);
    int save = SaveDC(fl_gc);
    fl_restore_clip(); // duplicate region into new gc
    draw();
    RestoreDC(fl_gc, save);
    DeleteDC(fl_gc);
    fl_gc = _sgc;
#elif defined(__APPLE__)
    if ( myi->other_xid ) {
      fl_begin_offscreen( myi->other_xid );
      fl_clip_region( 0 );   
      draw();

      fl_end_offscreen();
    } else {
      draw();
    }
#else // X:
    fl_window = myi->other_xid;
    
//    fl_restore_clip();
    fl_clip_region(myi->region);

    draw();

#if FLTK_HAVE_CAIRO
    cairo_surface_flush( myi->other_cs );
#endif

    fl_window = myi->xid;

#if FLTK_HAVE_CAIRO
    Fl::cairo_make_current( myi->cs, myi->cc );
#endif

//    fl_restore_clip();
    fl_clip_region(myi->region);

#endif
  }

  if (eraseoverlay)
  {
      fl_clip_region(0);
  }

  // on Irix (at least) it is faster to reduce the area copied to
  // the current clip region:

#if 1 // FLTK_USE_CAIRO
  cairo_set_source_surface( myi->cc, myi->other_cs, 0, 0 );
  cairo_set_operator( myi->cc, CAIRO_OPERATOR_SOURCE );
  /* cairo_rectangle( myi->cc, 0, 0, w(), h() ); */
  /* cairo_fill( myi->cc ); */
  cairo_paint( myi->cc );
  cairo_set_operator( myi->cc, CAIRO_OPERATOR_OVER );
#else
  int X,Y,W,H; fl_clip_box(0,0,w(),h(),X,Y,W,H);
  if (myi->other_xid) fl_copy_offscreen(X, Y, W, H, myi->other_xid, X, Y);
#endif

  #ifdef DEBUG_EXPOSE 
if ( damage() & FL_DAMAGE_EXPOSE )
  {
      #if FLTK_HAVE_CAIRO
      fl_rectf( 0,0, w(), h(), fl_color_add_alpha( FL_RED, 50 ));
      #endif
  }
  #endif 
}

void Fl_Double_Window::resize(int X,int Y,int W,int H) {
  int ow = w();
  int oh = h();
  Fl_Window::resize(X,Y,W,H);
  Fl_X* myi = Fl_X::i(this);
  if (myi && myi->other_xid && (ow != w() || oh != h())) {
#if FLTK_HAVE_CAIRO
      if ( myi->other_cs )
      {
          cairo_destroy( myi->other_cc ); myi->other_cc = 0;
          cairo_surface_destroy( myi->other_cs ); myi->other_cs = 0;
      }
#endif
    fl_delete_offscreen(myi->other_xid);
    myi->other_xid = 0;
  }
}

void Fl_Double_Window::hide() {
  Fl_X* myi = Fl_X::i(this);
  if (myi && myi->other_xid) {
#if FLTK_HAVE_CAIRO
      if ( myi->other_cs )
      {
          cairo_destroy( myi->other_cc ); myi->other_cc = 0;
          cairo_surface_destroy( myi->other_cs ); myi->other_cs = 0;
      }
#endif
      fl_delete_offscreen(myi->other_xid);
      myi->other_xid = 0;
  }
  Fl_Window::hide();
}

/**
  The destructor <I>also deletes all the children</I>. This allows a
  whole tree to be deleted at once, without having to keep a pointer to
  all the children in the user code.
*/
Fl_Double_Window::~Fl_Double_Window() {
  hide();
}

//
// End of "$Id: Fl_Double_Window.cxx 8383 2011-02-06 12:20:16Z AlbrechtS $".
//
