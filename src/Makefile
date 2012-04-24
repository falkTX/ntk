#
# "$Id: Makefile 8389 2011-02-06 14:08:08Z manolo $"
#
# Library makefile for the Fast Light Tool Kit (FLTK).
#
# Copyright 1998-2010 by Bill Spitzak and others.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
# USA.
#
# Please report all bugs and problems on the following page:
#
#      http://www.ntk.org/str.php
#

CPPFILES = \
	Fl_Cairo_Graphics_Driver.cxx \
	Fl.cxx \
	Fl_Adjuster.cxx \
	Fl_Bitmap.cxx \
	Fl_Browser.cxx \
	Fl_Browser_.cxx \
	Fl_Browser_load.cxx \
	Fl_Box.cxx \
	Fl_Button.cxx \
	Fl_Chart.cxx \
	Fl_Check_Browser.cxx \
	Fl_Check_Button.cxx \
	Fl_Choice.cxx \
	Fl_Color_Chooser.cxx \
	Fl_Counter.cxx \
	Fl_Dial.cxx \
	Fl_Dial_Base.cxx \
	Fl_Device.cxx \
	Fl_Double_Window.cxx \
	Fl_File_Browser.cxx \
	Fl_File_Chooser.cxx \
	Fl_File_Chooser2.cxx \
	Fl_File_Icon.cxx \
	Fl_File_Input.cxx \
	Fl_Group.cxx \
	Fl_Help_View.cxx \
	Fl_Image.cxx \
	Fl_Input.cxx \
	Fl_Input_.cxx \
	Fl_Light_Button.cxx \
	Fl_Menu.cxx \
	Fl_Menu_.cxx \
	Fl_Menu_Bar.cxx \
	Fl_Sys_Menu_Bar.cxx \
	Fl_Menu_Button.cxx \
	Fl_Menu_Window.cxx \
	Fl_Menu_add.cxx \
	Fl_Menu_global.cxx \
	Fl_Multi_Label.cxx \
	Fl_Native_File_Chooser.cxx \
	Fl_Overlay_Window.cxx \
	Fl_Pack.cxx \
	Fl_Paged_Device.cxx \
	Fl_Pixmap.cxx \
	Fl_Positioner.cxx \
	Fl_Preferences.cxx \
	Fl_Printer.cxx \
	Fl_Progress.cxx \
	Fl_Repeat_Button.cxx \
	Fl_Return_Button.cxx \
	Fl_Roller.cxx \
	Fl_Round_Button.cxx \
	Fl_Scroll.cxx \
	Fl_Scrollbar.cxx \
	Fl_Shared_Image.cxx \
	Fl_Single_Window.cxx \
	Fl_Slider.cxx \
	Fl_Table.cxx \
	Fl_Table_Row.cxx \
	Fl_Tabs.cxx \
	Fl_Text_Buffer.cxx \
	Fl_Text_Display.cxx \
	Fl_Text_Editor.cxx \
	Fl_Tile.cxx \
	Fl_Tiled_Image.cxx \
	Fl_Tree.cxx \
	Fl_Tree_Item.cxx \
	Fl_Tree_Item_Array.cxx \
	Fl_Tree_Prefs.cxx \
	Fl_Tooltip.cxx \
	Fl_Valuator.cxx \
	Fl_Value_Input.cxx \
	Fl_Value_Output.cxx \
	Fl_Value_Slider.cxx \
	Fl_Widget.cxx \
	Fl_Window.cxx \
	Fl_Window_fullscreen.cxx \
	Fl_Window_hotspot.cxx \
	Fl_Window_iconize.cxx \
	Fl_Wizard.cxx \
	Fl_XBM_Image.cxx \
	Fl_XPM_Image.cxx \
	Fl_abort.cxx \
	Fl_add_idle.cxx \
	Fl_arg.cxx \
	Fl_compose.cxx \
	Fl_display.cxx \
	Fl_get_key.cxx \
	Fl_get_system_colors.cxx \
	Fl_grab.cxx \
	Fl_lock.cxx \
	Fl_own_colormap.cxx \
	Fl_visual.cxx \
	Fl_x.cxx \
	filename_absolute.cxx \
	filename_expand.cxx \
	filename_ext.cxx \
	filename_isdir.cxx \
	filename_list.cxx \
	filename_match.cxx \
	filename_setext.cxx \
	fl_arc.cxx \
	fl_arci.cxx \
	fl_ask.cxx \
	fl_boxtype.cxx \
	fl_color.cxx \
	fl_cursor.cxx \
	fl_curve.cxx \
	fl_diamond_box.cxx \
	fl_dnd.cxx \
	fl_draw.cxx \
	Fl_Cairo.cxx \
	fl_draw_image.cxx \
	fl_draw_pixmap.cxx \
	fl_encoding_latin1.cxx \
	fl_encoding_mac_roman.cxx \
	fl_engraved_label.cxx \
	fl_file_dir.cxx \
	fl_font.cxx \
	fl_labeltype.cxx \
	fl_line_style.cxx \
	fl_open_uri.cxx \
	fl_oval_box.cxx \
	fl_overlay.cxx \
	fl_read_image.cxx \
	fl_rect.cxx \
	fl_round_box.cxx \
	fl_rounded_box.cxx \
	fl_set_font.cxx \
	fl_set_fonts.cxx \
	fl_scroll_area.cxx \
	fl_shadow_box.cxx \
	fl_shortcut.cxx \
	fl_show_colormap.cxx \
	fl_symbols.cxx \
	fl_vertex.cxx \
	screen_xywh.cxx \
	fl_utf8.cxx \
	Fl_Theme.cxx \
	Fl_Theme_Chooser.cxx \
	Cairo_Theme.cxx \
	Gleam_Theme.cxx \
	Clean_Theme.cxx \
	Crystal_Theme.cxx \
	themes.cxx \
	ps_image.cxx
	
OBJCPPFILES = \
    Fl_cocoa.mm \
    Fl_Quartz_Printer.mm \
    Fl_Native_File_Chooser_MAC.mm
	
GLCPPFILES = \
	Fl_Gl_Choice.cxx \
	Fl_Gl_Overlay.cxx \
	Fl_Gl_Device_Plugin.cxx \
	Fl_Gl_Window.cxx \
	freeglut_geometry.cxx \
	freeglut_stroke_mono_roman.cxx \
	freeglut_stroke_roman.cxx \
	freeglut_teapot.cxx \
	gl_draw.cxx \
	gl_start.cxx \
	glut_compatability.cxx \
	glut_font.cxx

IMGCPPFILES = \
	fl_images_core.cxx \
	Fl_BMP_Image.cxx \
	Fl_File_Icon2.cxx \
	Fl_GIF_Image.cxx \
	Fl_Help_Dialog.cxx \
	Fl_JPEG_Image.cxx \
	Fl_PNG_Image.cxx \
	Fl_PNM_Image.cxx


CFILES = fl_call_main.c flstring.c scandir.c numericsort.c vsnprintf.c fl_utf.c

UTF8CFILES = \
	xutf8/case.c \
	xutf8/is_right2left.c \
	xutf8/is_spacing.c \
	xutf8/keysym2Ucs.c \
	xutf8/utf8Input.c \
	xutf8/utf8Utils.c \
	xutf8/utf8Wrap.c

################################################################
FLTKFLAGS = -DFL_LIBRARY
include ../makeinclude

MMFILES = $(shell if test $(USEMMFILES) = Yes; then echo $(OBJCPPFILES); fi)

OBJECTS =  $(MMFILES:.mm=.o) $(CPPFILES:.cxx=.o) $(CFILES:.c=.o) $(UTF8CFILES:.c=.o)
GLOBJECTS = $(GLCPPFILES:.cxx=.o)
FLOBJECTS = $(FLCPPFILES:.cxx=.o)
IMGOBJECTS = $(IMGCPPFILES:.cxx=.o)

all:	$(LIBNAME) $(DSONAME) \
	$(FLLIBNAME) $(FLDSONAME) \
	$(GLLIBNAME) $(GLDSONAME) \
	$(IMGLIBNAME) $(IMGDSONAME) 

$(LIBNAME): $(OBJECTS)
	echo $(LIBCOMMAND) $@ ...
	$(RM) $@
	$(LIBCOMMAND) $@ $(OBJECTS)
	$(RANLIB) $@

libntk.so.1.3: $(OBJECTS)
	echo $(DSOCOMMAND) $@ ...
	$(DSOCOMMAND) $@ $(OBJECTS)
	$(RM) libntk.so
	$(LN) libntk.so.1.3 libntk.so

libntk.sl.1.3: $(OBJECTS)
	echo $(DSOCOMMAND) $@ ...
	$(DSOCOMMAND) $@ $(OBJECTS)
	$(RM) libntk.sl
	$(LN) libntk.sl.1.3 libntk.sl

libntk.1.3.dylib: $(OBJECTS)
	echo $(DSOCOMMAND) $@ ...
	$(DSOCOMMAND) $@ \
		-install_name $(libdir)/$@ \
		-current_version 1.3.0 \
		-compatibility_version 1.3.0 \
		$(OBJECTS) $(LDLIBS)
	$(RM) libntk.dylib
	$(LN) libntk.1.3.dylib libntk.dylib

libntk_s.a: $(OBJECTS)
	echo $(DSOCOMMAND) libntk_s.o ...
	$(DSOCOMMAND) libntk_s.o $(OBJECTS) $(IMAGELIBS)
	echo $(LIBCOMMAND) libntk_s.a libntk_s.o
	$(RM) $@
	$(LIBCOMMAND) libntk_s.a libntk_s.o
	$(CHMOD) +x libntk_s.a

$(FLLIBNAME): $(FLOBJECTS)
	echo $(LIBCOMMAND) $@ ...
	$(RM) $@
	$(LIBCOMMAND) $@ $(FLOBJECTS)
	$(RANLIB) $@

$(GLLIBNAME): $(GLOBJECTS)
	echo $(LIBCOMMAND) $@ ...
	$(RM) $@
	$(LIBCOMMAND) $@ $(GLOBJECTS)
	$(RANLIB) $@

libntk_gl.so.1.3: $(GLOBJECTS) libntk.so.1.3
	echo $(DSOCOMMAND) $@ ...
	$(DSOCOMMAND) $@ $(GLOBJECTS) -L. -lntk
	$(RM) libntk_gl.so
	$(LN) libntk_gl.so.1.3 libntk_gl.so

libntk_gl.sl.1.3: $(GLOBJECTS) libntk.sl.1.3
	echo $(DSOCOMMAND) $@ ...
	$(DSOCOMMAND) $@ $(GLOBJECTS) -L. -lntk
	$(RM) libntk_gl.sl
	$(LN) libntk_gl.sl.1.3 libntk_gl.sl

libntk_gl.1.3.dylib: $(GLOBJECTS) libntk.1.3.dylib
	echo $(DSOCOMMAND) $@ ...
	$(DSOCOMMAND) $@ \
		-install_name $(libdir)/$@ \
		-current_version 1.3.0 \
		-compatibility_version 1.3.0 \
		$(GLOBJECTS) -L. $(GLDLIBS) -lntk
	$(RM) libntk_gl.dylib
	$(LN) libntk_gl.1.3.dylib libntk_gl.dylib

libntk_gl_s.a: $(GLOBJECTS)
	echo $(DSOCOMMAND) libntk_gl_s.o ...
	$(DSOCOMMAND) libntk_gl_s.o $(GLOBJECTS)
	echo $(LIBCOMMAND) libntk_gl_s.a libntk_gl_s.o
	$(RM) $@
	$(LIBCOMMAND) libntk_gl_s.a libntk_gl_s.o
	$(CHMOD) +x libntk_gl_s.a

$(IMGLIBNAME): $(IMGOBJECTS)
	echo $(LIBCOMMAND) $@ ...
	$(RM) $@
	$(LIBCOMMAND) $@ $(IMGOBJECTS)
	$(RANLIB) $@

libntk_images.so.1.3: $(IMGOBJECTS) libntk.so.1.3
	echo $(DSOCOMMAND) $@ ...
	$(DSOCOMMAND) $@ $(IMGOBJECTS) -L. $(IMAGELIBS) -lntk
	$(RM) libntk_images.so
	$(LN) libntk_images.so.1.3 libntk_images.so

libntk_images.sl.1.3: $(IMGOBJECTS) libntk.sl.1.3
	echo $(DSOCOMMAND) $@ ...
	$(DSOCOMMAND) $@ $(IMGOBJECTS) -L. $(IMAGELIBS) -lntk
	$(RM) libntk_images.sl
	$(LN) libntk_images.sl.1.3 libntk_images.sl

libntk_images.1.3.dylib: $(IMGOBJECTS) libntk.1.3.dylib
	echo $(DSOCOMMAND) $@ ...
	$(DSOCOMMAND) $@ \
		-install_name $(libdir)/$@ \
		-current_version 1.3.0 \
		-compatibility_version 1.3.0 \
		$(IMGOBJECTS)  -L. $(LDLIBS) $(IMAGELIBS) -lntk
	$(RM) libntk_images.dylib
	$(LN) libntk_images.1.3.dylib libntk_images.dylib

libntk_images_s.a: $(IMGOBJECTS)
	echo $(DSOCOMMAND) libntk_images_s.o ...
	$(DSOCOMMAND) libntk_images_s.o $(IMGOBJECTS)
	echo $(LIBCOMMAND) libntk_images_s.a libntk_images_s.o
	$(RM) $@
	$(LIBCOMMAND) libntk_images_s.a libntk_images_s.o
	$(CHMOD) +x libntk_images_s.a

#-----------------------------------------------------------------
# - the import libraries libntk*.dll.a and the .dll files
#   are created from the libntk*.a files. They are built
#   into the src dir.
# - The _images, _gl, _forms and dlls must be linked
#   against the import libraries in the src dir.
#-----------------------------------------------------------------

#-----------------------------------------------------------------
# cygwin GDI shared libraries
#-----------------------------------------------------------------

cygntknox-1.3.dll: $(LIBNAME)
	echo $(DSOCOMMAND) $(LIBNAME) ...
	$(DSOCOMMAND) $(LIBNAME) -Wl,--no-whole-archive \
		-Wl,--out-implib=libntk.dll.a $(LDLIBS)

cygntknox_gl-1.3.dll: $(GLLIBNAME) cygntknox-1.3.dll
	echo $(DSOCOMMAND) $(GLLIBNAME) ...
	$(DSOCOMMAND) $(GLLIBNAME) -Wl,--no-whole-archive \
		-Wl,--out-implib=libntk_gl.dll.a \
		-L. -lntk $(GLDLIBS)

cygntknox_images-1.3.dll: $(IMGLIBNAME) cygntknox-1.3.dll
	echo $(DSOCOMMAND) $(IMGLIBNAME) ...
	$(DSOCOMMAND) $(IMGLIBNAME) -Wl,--no-whole-archive \
		-Wl,--out-implib=libntk_images.dll.a \
		-L. -lntk -Wl,--exclude-libs -Wl,libntk_png.a \
			$(IMAGELIBS) $(LDLIBS)

#-----------------------------------------------------------------
# cygwin X11 shared libraries
#-----------------------------------------------------------------

cygntk-1.3.dll: $(LIBNAME)
	echo $(DSOCOMMAND) $(LIBNAME) ...
	$(DSOCOMMAND) $(LIBNAME) -Wl,--no-whole-archive \
		-Wl,--out-implib=libntk.dll.a $(LDLIBS)

cygntk_gl-1.3.dll: $(GLLIBNAME) cygntk-1.3.dll
	echo $(DSOCOMMAND) $(GLLIBNAME) ...
	$(DSOCOMMAND) $(GLLIBNAME) -Wl,--no-whole-archive \
		-Wl,--out-implib=libntk_gl.dll.a \
		-L. -lntk $(GLDLIBS)

cygntk_images-1.3.dll: $(IMGLIBNAME) cygntk-1.3.dll
	echo $(DSOCOMMAND) $(IMGLIBNAME) ...
	$(DSOCOMMAND) $(IMGLIBNAME) -Wl,--no-whole-archive \
		-Wl,--out-implib=libntk_images.dll.a \
		-L. -lntk -Wl,--exclude-libs -Wl,libntk_png.a \
			$(IMAGELIBS) $(LDLIBS)

mgwntknox-1.3.dll: $(LIBNAME)
	echo $(DSOCOMMAND) $(LIBNAME) ...
	$(DSOCOMMAND) $(LIBNAME) -Wl,--no-whole-archive \
		-Wl,--out-implib=libntk.dll.a $(LDLIBS)

mgwntknox_gl-1.3.dll: $(GLLIBNAME) mgwntknox-1.3.dll
	echo $(DSOCOMMAND) $(GLLIBNAME) ...
	$(DSOCOMMAND) $(GLLIBNAME) -Wl,--no-whole-archive \
		-Wl,--out-implib=libntk_gl.dll.a \
		-L. -lntk $(GLDLIBS)

#-----------------------------------------------------
# See STR #1585 for --exclude-libs
#-----------------------------------------------------

mgwntknox_images-1.3.dll: $(IMGLIBNAME) mgwntknox-1.3.dll
	echo $(DSOCOMMAND) $(IMGLIBNAME) ...
	$(DSOCOMMAND) $(IMGLIBNAME) -Wl,--no-whole-archive \
		-Wl,--out-implib=libntk_images.dll.a \
		-L. -lntk -Wl,--exclude-libs -Wl,libntk_png.a \
			$(IMAGELIBS) $(LDLIBS)

clean:
	-$(RM) *.o xutf8/*.o *.dll.a core.* *~ *.bak *.bck
	-$(RM) $(DSONAME) $(FLDSONAME) $(GLDSONAME) $(IMGDSONAME) \
		$(LIBNAME) $(FLLIBNAME) $(GLLIBNAME) \
		$(IMGLIBNAME) \
		libntk.so libntk_gl.so libntk_images.so \
		libntk.sl libntk_gl.sl libntk_images.sl \
		libntk.dylib \
		libntk_gl.dylib libntk_images.dylib \
		cmap core

depend:	$(CPPFILES) $(MMFILES) $(FLCPPFILES) $(GLCPPFILES) $(IMGCPPFILES) $(CFILES) $(UTF8CFILES)
	makedepend -Y -I.. -f makedepend $(CPPFILES) $(MMFILES) $(FLCPPFILES) \
		$(GLCPPFILES) $(IMGCPPFILES) $(CFILES) $(UTF8CFILES)

# Automatically generated dependencies... generated on a Linux/Unix host !
include makedepend

# These dependencies aren't part of the makedepend file since
# they are part of the WIN32 and MacOS code base...
# Please add only non-Linux/Unix files or such that are optional
# (like "*xft*") here:
Fl_get_key.o:	Fl_get_key_mac.cxx Fl_get_key_win32.cxx
Fl_Native_File_Chooser.o : Fl_Native_File_Chooser_WIN32.cxx
Fl_Theme_Chooser.o : Fl_Theme_Chooser.cxx
Fl_Native_File_Chooser_MAC.o:	Fl_Native_File_Chooser_MAC.mm
Fl.o:		Fl_win32.cxx
Fl_cocoa.o:	Fl_cocoa.mm
fl_color.o:	fl_color_mac.cxx fl_color_win32.cxx
fl_dnd.o:	fl_dnd_win32.cxx fl_dnd_x.cxx
fl_draw_image.o: fl_draw_image_mac.cxx fl_draw_image_win32.cxx
fl_font.o:	fl_font_mac.cxx fl_font_x.cxx fl_font_xft.cxx fl_font_win32.cxx
fl_read_image.o: fl_read_image_mac.cxx fl_read_image_win32.cxx
fl_set_fonts.o:	fl_set_fonts_mac.cxx fl_set_fonts_x.cxx \
		fl_set_fonts_xft.cxx fl_set_fonts_win32.cxx
Fl_Printer.o: Fl_GDI_Printer.cxx Fl_PostScript.cxx
Fl_Quartz_Printer.o:	Fl_Quartz_Printer.mm
fl_arci.o:	../FL/mac.H ../FL/win32.H
Fl_arg.o:	../FL/mac.H ../FL/win32.H
fl_ask.o:	../FL/mac.H ../FL/win32.H
Fl_Bitmap.o:	../FL/mac.H ../FL/win32.H
fl_color.o:	../FL/mac.H ../FL/win32.H
fl_cursor.o:	../FL/mac.H ../FL/win32.H
fl_dnd.o:	../FL/mac.H ../FL/win32.H
Fl.o:	../FL/mac.H ../FL/win32.H
Fl_Double_Window.o:	../FL/mac.H ../FL/win32.H
fl_draw_image.o:	../FL/mac.H ../FL/win32.H
fl_draw_image_mac.o:	../FL/mac.H ../FL/win32.H
fl_draw_image_win32.o:	../FL/mac.H ../FL/win32.H
fl_draw_pixmap.o:	../FL/mac.H ../FL/win32.H
fl_encoding_latin1.o:	../FL/mac.H ../FL/win32.H
fl_encoding_mac_roman.o:   ../FL/mac.H ../FL/win32.H
Fl_File_Chooser2.o:	../FL/mac.H ../FL/win32.H
fl_font.o:	../FL/mac.H ../FL/win32.H
Fl_get_key.o:	../FL/mac.H ../FL/win32.H
Fl_get_system_colors.o:	../FL/mac.H ../FL/win32.H
Fl_Gl_Choice.o:	../FL/mac.H ../FL/win32.H
Fl_Gl_Overlay.o:	../FL/mac.H ../FL/win32.H
Fl_Gl_Window.o:	../FL/mac.H ../FL/win32.H
Fl_grab.o:	../FL/mac.H ../FL/win32.H
Fl_Image.o:	../FL/mac.H ../FL/win32.H
fl_line_style.o:	../FL/mac.H ../FL/win32.H
Fl_Menu_Window.o:	../FL/mac.H ../FL/win32.H
fl_overlay.o:	../FL/mac.H ../FL/win32.H
Fl_Overlay_Window.o:	../FL/mac.H ../FL/win32.H
Fl_own_colormap.o:	../FL/mac.H ../FL/win32.H
Fl_Pixmap.o:	../FL/mac.H ../FL/win32.H
Fl_Printer.o:  ../FL/mac.H ../FL/win32.H
fl_read_image.o:	../FL/mac.H ../FL/win32.H
fl_read_image_mac.o:	../FL/mac.H ../FL/win32.H
fl_read_image_win32.o:	../FL/mac.H ../FL/win32.H
fl_rect.o:	../FL/mac.H ../FL/win32.H
fl_scroll_area.o:	../FL/mac.H ../FL/win32.H
fl_set_font.o:	../FL/mac.H ../FL/win32.H
fl_set_fonts.o:	../FL/mac.H ../FL/win32.H
fl_shortcut.o:	../FL/mac.H ../FL/win32.H
fl_vertex.o:	../FL/mac.H ../FL/win32.H
Fl_visual.o:	../FL/mac.H ../FL/win32.H
Fl_Window_fullscreen.o:	../FL/mac.H ../FL/win32.H
Fl_Window_iconize.o:	../FL/mac.H ../FL/win32.H
Fl_x.o:	../FL/mac.H ../FL/win32.H
gl_draw.o:	../FL/mac.H ../FL/win32.H
gl_start.o:	../FL/mac.H ../FL/win32.H

################################################################

install: $(LIBNAME) $(DSONAME) \
	$(FLLIBNAME) $(FLDSONAME) \
	$(GLLIBNAME) $(GLDSONAME) \
	$(IMGLIBNAME) $(IMGDSONAME) 
	echo "Installing libraries in $(DESTDIR)$(libdir)..."
	-$(INSTALL_DIR) $(DESTDIR)$(libdir)
	-$(INSTALL_DIR) $(DESTDIR)$(bindir)
	$(RM) $(DESTDIR)$(libdir)/$(LIBBASENAME)
	$(INSTALL_LIB) $(LIBNAME) $(DESTDIR)$(libdir)
	$(INSTALL_LIB) $(FLLIBNAME) $(DESTDIR)$(libdir)
	$(INSTALL_LIB) $(IMGLIBNAME) $(DESTDIR)$(libdir)
	$(RANLIB) $(DESTDIR)$(libdir)/$(LIBBASENAME)
	$(RANLIB) $(DESTDIR)$(libdir)/$(FLLIBBASENAME)
	if test x$(GLLIBNAME) != x; then \
		$(INSTALL_LIB) $(GLLIBNAME) $(DESTDIR)$(libdir); \
		$(RANLIB) $(DESTDIR)$(libdir)/$(GLLIBBASENAME); \
	fi
	$(RANLIB) $(DESTDIR)$(libdir)/$(IMGLIBBASENAME)
	if test x$(DSONAME) = xlibntk.so.1.3; then\
		$(RM) $(DESTDIR)$(libdir)/libntk.so*;\
		$(INSTALL_LIB) libntk.so.1.3 $(DESTDIR)$(libdir); \
		$(LN) libntk.so.1.3 $(DESTDIR)$(libdir)/libntk.so;\
	fi
	if test x$(DSONAME) = xlibntk.sl.1.3; then\
		$(RM) $(DESTDIR)$(libdir)/libntk.sl*;\
		$(INSTALL_LIB) libntk.sl.1.3 $(DESTDIR)$(libdir); \
		$(LN) libntk.sl.1.3 $(DESTDIR)$(libdir)/libntk.sl;\
	fi
	if test x$(DSONAME) = xlibntk.1.3.dylib; then\
		$(RM) $(DESTDIR)$(libdir)/libntk.*dylib;\
		$(INSTALL_LIB) libntk.1.3.dylib $(DESTDIR)$(libdir); \
		$(LN) libntk.1.3.dylib $(DESTDIR)$(libdir)/libntk.dylib;\
	fi
	if test x$(DSONAME) = xlibntk_s.a; then\
		$(RM) $(DESTDIR)$(libdir)/libntk_s.a;\
		$(INSTALL_LIB) libntk_s.a $(DESTDIR)$(libdir); \
	fi
	if test x$(DSONAME) = xcygntknox-1.3.dll; then\
		$(RM) $(DESTDIR)$(bindir)/$(DSONAME);\
		$(INSTALL_LIB) $(DSONAME) $(DESTDIR)$(bindir); \
		$(RM) $(DESTDIR)$(libdir)/libntk.dll.a;\
		$(INSTALL_LIB) libntk.dll.a $(DESTDIR)$(libdir); \
	fi
	if test x$(DSONAME) = xmgwntknox-1.3.dll; then\
		$(RM) $(DESTDIR)$(bindir)/$(DSONAME);\
		$(INSTALL_LIB) $(DSONAME) $(DESTDIR)$(bindir); \
		$(RM) $(DESTDIR)$(libdir)/libntk.dll.a;\
		$(INSTALL_LIB) libntk.dll.a $(DESTDIR)$(libdir); \
	fi
	if test x$(GLDSONAME) = xlibntk_gl.so.1.3; then\
		$(RM) $(DESTDIR)$(libdir)/libntk_gl.so*;\
		$(INSTALL_LIB) libntk_gl.so.1.3 $(DESTDIR)$(libdir); \
		$(LN) libntk_gl.so.1.3 $(DESTDIR)$(libdir)/libntk_gl.so;\
	fi
	if test x$(GLDSONAME) = xlibntk_gl.sl.1.3; then\
		$(RM) $(DESTDIR)$(libdir)/libntk_gl.sl*;\
		$(INSTALL_LIB) libntk_gl.sl.1.3 $(DESTDIR)$(libdir); \
		$(LN) libntk_gl.sl.1.3 $(DESTDIR)$(libdir)/libntk_gl.sl;\
	fi
	if test x$(GLDSONAME) = xlibntk_gl.1.3.dylib; then\
		$(RM) $(DESTDIR)$(libdir)/libntk_gl.*dylib;\
		$(INSTALL_LIB) libntk_gl.1.3.dylib $(DESTDIR)$(libdir); \
		$(LN) libntk_gl.1.3.dylib $(DESTDIR)$(libdir)/libntk_gl.dylib;\
	fi
	if test x$(GLDSONAME) = xlibntk_gl_s.a; then\
		$(RM) $(DESTDIR)$(libdir)/libntk_gl_s.a;\
		$(INSTALL_LIB) libntk_gl_s.a $(DESTDIR)$(libdir); \
	fi
	if test x$(GLDSONAME) = xcygntknox_gl-1.3.dll; then\
		$(RM) $(DESTDIR)$(bindir)/$(GLDSONAME);\
		$(INSTALL_LIB) $(GLDSONAME) $(DESTDIR)$(bindir); \
		$(RM) $(DESTDIR)$(libdir)/libntk_gl.dll.a;\
		$(INSTALL_LIB) libntk_gl.dll.a $(DESTDIR)$(libdir); \
	fi
	if test x$(GLDSONAME) = xmgwntknox_gl-1.3.dll; then\
		$(RM) $(DESTDIR)$(bindir)/$(GLDSONAME);\
		$(INSTALL_LIB) $(GLDSONAME) $(DESTDIR)$(bindir); \
		$(RM) $(DESTDIR)$(libdir)/libntk_gl.dll.a;\
		$(INSTALL_LIB) libntk_gl.dll.a $(DESTDIR)$(libdir); \
	fi
	if test x$(IMGDSONAME) = xlibntk_images.so.1.3; then\
		$(RM) $(DESTDIR)$(libdir)/libntk_images.so*;\
		$(INSTALL_LIB) libntk_images.so.1.3 $(DESTDIR)$(libdir); \
		$(LN) libntk_images.so.1.3 $(DESTDIR)$(libdir)/libntk_images.so;\
	fi
	if test x$(IMGDSONAME) = xlibntk_images.sl.1.3; then\
		$(RM) $(DESTDIR)$(libdir)/libntk_images.sl*;\
		$(INSTALL_LIB) libntk_images.sl.1.3 $(DESTDIR)$(libdir); \
		$(LN) libntk_images.sl.1.3 $(DESTDIR)$(libdir)/libntk_images.sl;\
	fi
	if test x$(IMGDSONAME) = xlibntk_images.1.3.dylib; then\
		$(RM) $(DESTDIR)$(libdir)/libntk_images.*dylib;\
		$(INSTALL_LIB) libntk_images.1.3.dylib $(DESTDIR)$(libdir); \
		$(LN) libntk_images.1.3.dylib $(DESTDIR)$(libdir)/libntk_images.dylib;\
	fi
	if test x$(IMGDSONAME) = xlibntk_images_s.a; then\
		$(RM) $(DESTDIR)$(libdir)/libntk_images_s.a;\
		$(INSTALL_LIB) libntk_images_s.a $(DESTDIR)$(libdir); \
	fi
	if test x$(IMGDSONAME) = xcygntknox_images-1.3.dll; then\
		$(RM) $(DESTDIR)$(bindir)/$(IMGDSONAME); \
		$(INSTALL_LIB) $(IMGDSONAME) $(DESTDIR)$(bindir); \
		$(RM) $(DESTDIR)$(libdir)/libntk_images.dll.a;\
		$(INSTALL_LIB) libntk_images.dll.a $(DESTDIR)$(libdir); \
	fi
	if test x$(IMGDSONAME) = xmgwntknox_images-1.3.dll; then\
		$(RM) $(DESTDIR)$(bindir)/$(IMGDSONAME); \
		$(INSTALL_LIB) $(IMGDSONAME) $(DESTDIR)$(bindir); \
		$(RM) $(DESTDIR)$(libdir)/libntk_images.dll.a;\
		$(INSTALL_LIB) libntk_images.dll.a $(DESTDIR)$(libdir); \
	fi


uninstall:
	echo "Uninstalling libraries..."
	$(RM) $(DESTDIR)$(libdir)/$(LIBBASENAME)
	if test x$(DSONAME) = xlibntk.so.1.3; then\
		$(RM) $(DESTDIR)$(libdir)/libntk.so*;\
	fi
	if test x$(DSONAME) = xlibntk.sl.1.3; then\
		$(RM) $(DESTDIR)$(libdir)/libntk.sl*;\
	fi
	if test x$(DSONAME) = xlibntk.1.3.dylib; then\
		$(RM) $(DESTDIR)$(libdir)/libntk.*dylib;\
	fi
	if test x$(DSONAME) = xlibntk_s.a; then\
		$(RM) $(DESTDIR)$(libdir)/libntk_s.a;\
	fi
	if test x$(DSONAME) = xcygntknox-1.3.dll; then\
		$(RM) $(DESTDIR)$(bindir)/$(DSONAME); \
		$(RM) $(DESTDIR)$(libdir)/libntk.dll.a;\
	fi
	if test x$(DSONAME) = xcygntk-1.3.dll; then\
		$(RM) $(DESTDIR)$(bindir)/$(DSONAME); \
		$(RM) $(DESTDIR)$(libdir)/libntk.dll.a;\
	fi
	if test x$(DSONAME) = xmgwntknox-1.3.dll; then\
		$(RM) $(DESTDIR)$(bindir)/$(DSONAME); \
		$(RM) $(DESTDIR)$(libdir)/libntk.dll.a;\
	fi
	$(RM) $(DESTDIR)$(libdir)/$(FLLIBBASENAME);
	if test x$(GLLIBNAME) != x; then\
		$(RM) $(DESTDIR)$(libdir)/$(GLLIBBASENAME);\
	fi
	if test x$(GLDSONAME) = xlibntk_gl.so.1.3; then\
		$(RM) $(DESTDIR)$(libdir)/libntk_gl.so*;\
	fi
	if test x$(GLDSONAME) = xlibntk_gl.sl.1.3; then\
		$(RM) $(DESTDIR)$(libdir)/libntk_gl.sl*;\
	fi
	if test x$(GLDSONAME) = xlibntk_gl.1.3.dylib; then\
		$(RM) $(DESTDIR)$(libdir)/libntk_gl.*dylib;\
	fi
	if test x$(GLDSONAME) = xlibntk_gl_s.a; then\
		$(RM) $(DESTDIR)$(libdir)/libntk_gl_s.a;\
	fi
	if test x$(GLDSONAME) = xcygntknox_gl-1.3.dll; then\
		$(RM) $(DESTDIR)$(bindir)/$(GLDSONAME); \
		$(RM) $(DESTDIR)$(libdir)/libntk_gl.dll.a;\
	fi
	if test x$(GLDSONAME) = xcygntk_gl-1.3.dll; then\
		$(RM) $(DESTDIR)$(bindir)/$(GLDSONAME); \
		$(RM) $(DESTDIR)$(libdir)/libntk_gl.dll.a;\
	fi
	if test x$(GLDSONAME) = xmgwntknox_gl-1.3.dll; then\
		$(RM) $(DESTDIR)$(bindir)/$(GLDSONAME); \
		$(RM) $(DESTDIR)$(libdir)/libntk_gl.dll.a;\
	fi
	if test x$(IMGLIBNAME) != x; then\
		$(RM) $(DESTDIR)$(libdir)/$(IMGLIBBASENAME);\
	fi
	if test x$(IMGDSONAME) = xlibntk_images.so.1.3; then\
		$(RM) $(DESTDIR)$(libdir)/libntk_images.so*;\
	fi
	if test x$(IMGDSONAME) = xlibntk_images.sl.1.3; then\
		$(RM) $(DESTDIR)$(libdir)/libntk_images.sl*;\
	fi
	if test x$(IMGDSONAME) = xlibntk_images.1.3.dylib; then\
		$(RM) $(DESTDIR)$(libdir)/libntk_images.*dylib;\
	fi
	if test x$(IMGDSONAME) = xlibntk_images_s.a; then\
		$(RM) $(DESTDIR)$(libdir)/libntk_images_s.a;\
	fi
	if test x$(IMGDSONAME) = xcygntknox_images-1.3.dll; then\
		$(RM) $(DESTDIR)$(bindir)/$(IMGDSONAME); \
		$(RM) $(DESTDIR)$(libdir)/libntk_images.dll.a;\
	fi
	if test x$(IMGDSONAME) = xcygntk_images-1.3.dll; then\
		$(RM) $(DESTDIR)$(bindir)/$(IMGDSONAME); \
		$(RM) $(DESTDIR)$(libdir)/libntk_images.dll.a;\
	fi
	if test x$(IMGDSONAME) = xmgwntknox_images-1.3.dll; then\
		$(RM) $(DESTDIR)$(bindir)/$(IMGDSONAME); \
		$(RM) $(DESTDIR)$(libdir)/libntk_images.dll.a;\
	fi

#
# End of "$Id: Makefile 8389 2011-02-06 14:08:08Z manolo $".
#
