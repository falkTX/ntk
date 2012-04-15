#
# "$Id: Makefile 8427 2011-02-15 15:29:03Z mike $"
#
# Top-level makefile for the Fast Light Tool Kit (FLTK).
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

include makeinclude

DIRS = $(IMAGEDIRS) src fluid documentation

all: makeinclude ntk-config
	for dir in $(DIRS); do\
		echo "=== making $$dir ===";\
		(cd $$dir; $(MAKE) $(MFLAGS)) || exit 1;\
	done

install: makeinclude
	-mkdir -p $(DESTDIR)$(bindir)
	$(RM) $(DESTDIR)$(bindir)/ntk-config
	$(INSTALL_SCRIPT) ntk-config $(DESTDIR)$(bindir)
	for dir in FL $(DIRS); do\
		echo "=== installing $$dir ===";\
		(cd $$dir; $(MAKE) $(MFLAGS) install) || exit 1;\
	done

install-desktop: makeinclude
	cd documentation; $(MAKE) $(MFLAGS) $(INSTALL_DESKTOP)
	cd fluid; $(MAKE) $(MFLAGS) $(INSTALL_DESKTOP)
	cd test; $(MAKE) $(MFLAGS) $(INSTALL_DESKTOP)

uninstall: makeinclude
	$(RM) $(DESTDIR)$(bindir)/ntk-config
	for dir in FL $(DIRS); do\
		echo "=== uninstalling $$dir ===";\
		(cd $$dir; $(MAKE) $(MFLAGS) uninstall) || exit 1;\
	done

uninstall-desktop: makeinclude
	cd documentation; $(MAKE) $(MFLAGS) $(UNINSTALL_DESKTOP)
	cd fluid; $(MAKE) $(MFLAGS) $(UNINSTALL_DESKTOP)
	cd test; $(MAKE) $(MFLAGS) $(UNINSTALL_DESKTOP)

depend: makeinclude
	for dir in $(DIRS); do\
		echo "=== making dependencies in $$dir ===";\
		(cd $$dir; $(MAKE) $(MFLAGS) depend) || exit 1;\
	done

clean:
	-$(RM) core *.o
	for dir in $(DIRS); do\
		echo "=== cleaning $$dir ===";\
		(cd $$dir; $(MAKE) $(MFLAGS) clean) || exit 1;\
	done

distclean: clean
	$(RM) config.*
	$(RM) ntk-config ntk.list makeinclude
	$(RM) ntk.spec
	$(RM) FL/Makefile
	$(RM) documentation/*.$(CAT1EXT)
	$(RM) documentation/*.$(CAT3EXT)
	$(RM) documentation/*.$(CAT6EXT)
	$(RM) documentation/ntk.ps
	$(RM) -r documentation/ntk.d
	for file in test/*.fl; do\
		$(RM) test/`basename $$file .fl`.cxx; \
		$(RM) test/`basename $$file .fl`.h; \
	done

ntk-config: configure configh.in ntk-config.in
	if test -f config.status; then \
		./config.status --recheck; \
		./config.status; \
	else \
		./configure; \
	fi
	touch config.h
	chmod +x ntk-config

makeinclude: configure configh.in makeinclude.in
	if test -f config.status; then \
		./config.status --recheck; \
		./config.status; \
	else \
		./configure; \
	fi
	touch config.h
	chmod +x ntk-config

configure: configure.in
	autoconf

portable-dist:
	epm -v -s ntk.xpm ntk

native-dist:
	epm -v -f native ntk

etags:
	etags FL/*.H FL/*.h src/*.cxx src/*.c src/*.h src/xutf8/*.h src/xutf8/*.c cairo/*.cxx fluid/*.h fluid/*.cxx test/*.h test/*.cxx

#
# Run the clang.llvm.org static code analysis tool on the C sources.
# (at least checker-231 is required for scan-build to work this way)
#

.PHONY: clang clang-changes
clang:
	$(RM) -r clang
	scan-build -V -k -o `pwd`/clang $(MAKE) $(MFLAGS) clean all
clang-changes:
	scan-build -V -k -o `pwd`/clang $(MAKE) $(MFLAGS) all


#
# End of "$Id: Makefile 8427 2011-02-15 15:29:03Z mike $".
#
