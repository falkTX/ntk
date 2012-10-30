#
# "$Id: Makefile 8086 2010-12-20 20:33:24Z matt $"
#
# FLUID makefile for the Fast Light Tool Kit (FLTK).
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
#      http://www.fltk.org/str.php
#

CPPFILES = \
	CodeEditor.cxx \
	Fl_Function_Type.cxx \
	Fl_Group_Type.cxx \
	Fl_Menu_Type.cxx \
	Fl_Type.cxx \
	Fl_Widget_Type.cxx \
	Fl_Window_Type.cxx \
	Fluid_Image.cxx \
	about_panel.cxx \
	align_widget.cxx \
	alignment_panel.cxx \
	code.cxx \
	factory.cxx \
	file.cxx \
	fluid.cxx \
	function_panel.cxx \
	template_panel.cxx \
	undo.cxx \
	widget_panel.cxx

################################################################

OBJECTS = $(CPPFILES:.cxx=.o)

include ../makeinclude

all:	$(FLUID) ntk-fluid$(EXEEXT)

ntk-fluid$(EXEEXT):		$(OBJECTS) $(LIBNAME) $(FLLIBNAME) \
			$(IMGLIBNAME)
	echo Linking $@...
	$(CXX) $(ARCHFLAGS) $(LDFLAGS) -o $@ $(OBJECTS) $(LINKFLTKFORMS) $(LINKFLTKIMG) $(LDLIBS)
	$(OSX_ONLY) $(INSTALL_BIN) ntk-fluid ntk-fluid.app/Contents/MacOS

ntk-fluid-shared$(EXEEXT):	$(OBJECTS) ../src/$(DSONAME) ../src/$(FLDSONAME) \
			../src/$(IMGDSONAME)
	echo Linking $@...
	$(CXX) $(ARCHFLAGS) $(LDFLAGS) -o $@ $(OBJECTS) $(LINKSHARED) $(LDLIBS)

clean:
	-$(RM) *.o core.* *~ *.bck *.bck
	-$(RM) core ntk-fluid$(EXEEXT) ntk-fluid-shared$(EXEEXT)
	-$(RM) ntk-fluid.app/Contents/MacOS/ntk-fluid$(EXEEXT)

depend:	$(CPPFILES)
	makedepend -Y -I.. -f makedepend $(CPPFILES)

# Automatically generated dependencies...
include makedepend

install: all
	echo "Installing FLUID in $(DESTDIR)$(bindir)..."
	-$(INSTALL_DIR) $(DESTDIR)$(bindir)
	$(INSTALL_BIN) $(FLUID) $(DESTDIR)$(bindir)/ntk-fluid$(EXEEXT)

install-linux:
	-$(INSTALL_DIR) $(DESTDIR)/usr/share/applications
	$(INSTALL_DATA) ntk-fluid.desktop  $(DESTDIR)/usr/share/applications
	for size in 16 32 48 64 128; do \
		if test ! -d $(DESTDIR)/usr/share/icons/hicolor/$${size}x$${size}/apps; then \
			$(INSTALL_DIR) $(DESTDIR)/usr/share/icons/hicolor/$${size}x$${size}/apps; \
		fi; \
		$(INSTALL_DATA) icons/ntk-fluid-$$size.png $(DESTDIR)/usr/share/icons/hicolor/$${size}x$${size}/apps/ntk-fluid.png; \
	done
	-$(INSTALL_DIR) $(DESTDIR)/usr/share/mimelnk/application
	$(INSTALL_DATA) x-ntk-fluid.desktop  $(DESTDIR)/usr/share/mimelnk/application

install-osx:
	echo Installing Fluid in $(DESTDIR)/Applications...
	-$(INSTALL_DIR) $(DESTDIR)/Applications/ntk-fluid.app
	-$(INSTALL_DIR) $(DESTDIR)/Applications/ntk-fluid.app/Contents
	$(INSTALL_DATA) ntk-fluid.app/Contents/Info.plist $(DESTDIR)/Applications/ntk-fluid.app/Contents/Info.plist
	$(INSTALL_DATA) ntk-fluid.app/Contents/PkgInfo $(DESTDIR)/Applications/ntk-fluid.app/Contents/PkgInfo
	-$(INSTALL_DIR) $(DESTDIR)/Applications/ntk-fluid.app/Contents/MacOS
	$(RM) $(DESTDIR)/Applications/ntk-fluid.app/Contents/MacOS/ntk-fluid
	$(LN) $(bindir)/ntk-fluid $(DESTDIR)/Applications/ntk-fluid.app/Contents/MacOS/ntk-fluid
	-$(INSTALL_DIR) $(DESTDIR)/Applications/ntk-fluid.app/Contents/Resources
	$(INSTALL_DATA) ntk-fluid.app/Contents/Resources/ntk-fluid.icns $(DESTDIR)/Applications/ntk-fluid.app/Contents/Resources

uninstall:
	$(RM) $(DESTDIR)$(bindir)/ntk-fluid$(EXEEXT)

uninstall-linux:
	$(RM) $(DESTDIR)/usr/share/applications/ntk-fluid.desktop
	$(RM) $(DESTDIR)/usr/share/icons/hicolor/*/ntk-fluid.png
	$(RM) $(DESTDIR)/usr/share/mimelnk/application/x-ntk-fluid.desktop

uninstall-osx:
	$(RM) -r $(DESTDIR)/Applications/ntk-fluid.app


#
# Note: The rebuild target can only be used if you have the original .fl
#       files.  This is normally only used by the FLTK maintainers...
#

rebuild:
	./ntk-fluid -c about_panel.fl
	./ntk-fluid -c alignment_panel.fl
	./ntk-fluid -c function_panel.fl
	./ntk-fluid -c print_panel.fl
	./ntk-fluid -c template_panel.fl
	./ntk-fluid -c widget_panel.fl

#
# End of "$Id: Makefile 8086 2010-12-20 20:33:24Z matt $".
#
