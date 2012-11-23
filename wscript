#!/usr/bin/env python
import subprocess
import waflib.Options as Options
from waflib.Configure import conf
import string
import os
import sys

# Version of this package (even if built as a child)

FL_MAJOR_VERSION='1'
FL_MINOR_VERSION='3'
FL_PATCH_VERSION='0'

PACKAGE_VERSION = FL_MAJOR_VERSION + '.' + FL_MINOR_VERSION + '.' + FL_PATCH_VERSION

API_VERSION = FL_MAJOR_VERSION + '.' + FL_MINOR_VERSION

# Variables for 'waf dist'
APPNAME = 'ntk'
VERSION = PACKAGE_VERSION

# Mandatory variables
top = '.'
out = 'build'

children = [ 'fluid', 'test' ]
#children = []

CFLAGS = [ '-D_LARGEFILE_SOURCE', '-D_LARGEFILE64_SOURCE', '-D_THREAD_SAFE', '-D_REENTRANT' ]

@conf
def makelib(bld,*k,**kw):
    kw['includes'] = ['.', 'src', 'src/xutf8/headers' ]
    kw['cflags'] = [ '-fPIC' ]
    kw['cxxflags'] = [ '-fPIC' ]
    kw['defines'] = [ 'FL_LIBRARY=1', 'FL_INTERNALS=1' ]
    kw['vnum'] = API_VERSION
    kw['install_path'] = '${LIBDIR}'
    kw['features' ] = 'c cxx cxxshlib'
    bld.stlib(*k,**kw)
    kw['features' ] = 'c cxx cxxstlib'
    bld.shlib(*k,**kw)
    
def options(opt):
    opt.load('compiler_c')
    opt.load('compiler_cxx')
    opt.load('gnu_dirs')

    opt.add_option('--enable-debug', action='store_true', default=False, dest='debug',
                   help='Build for debugging')
    opt.add_option('--enable-gl', action='store_true', default=False, dest='USE_GL',
                   help='Build with OpenGL extension library')
    opt.add_option('--enable-test', action='store_true', default=False, dest='ENABLE_TEST',
                   help='Build test programs')

def configure(conf):
    conf.load('compiler_c')
    conf.load('compiler_cxx')
    conf.load('gnu_dirs')
    # conf.load('ntk_fluid')
    conf.line_just = 52
    conf.env.append_value('CFLAGS', CFLAGS + ['-Wall'])
#    conf.env.append_value('CXXFLAGS',['-Wall','-fno-exceptions', '-fno-rtti'])
    conf.env.append_value('CXXFLAGS',CFLAGS + ['-Wall'])

    conf.check_cfg(package='x11', uselib_store='X11', args="--cflags --libs",
                   mandatory=True)

    conf.check_cfg(package='xft', uselib_store='XFT', args="--cflags --libs",
                   mandatory=True)

    conf.check_cfg(package='cairo', uselib_store='CAIRO', args="--cflags --libs",
                   atleast_version='1.9.0', mandatory=True)


    conf.check(header_name='unistd.h', define_name='HAVE_UNISTD_H', mandatory=False)
    conf.check(header_name='pthread.h', define_name='HAVE_PTHREAD_H', mandatory=False)
    conf.check(header_name='dirent.h', define_name='HAVE_DIRENT_H', mandatory=False)
    conf.check(header_name='string.h', define_name='HAVE_STRINGS_H', mandatory=False)
    conf.check(header_name='locale.h', define_name='HAVE_LOCALE_H', mandatory=False)
    conf.check(header_name='sys/select.h', define_name='HAVE_SYS_SELECT_H', mandatory=False)
    conf.check(header_name='dlfcn.h', define_name='HAVE_DLFCN_H', mandatory=False)
    conf.check(header_name='sys/stdtypes.h', define_name='HAVE_SYS_STDTYPES_H', mandatory=False)
    conf.check(header_name='pthread.h', define_name='HAVE_PTHREAD', mandatory=True)
    conf.check(header_name='png.h', define_name='HAVE_PNG_H', mandatory=False)

    conf.check(features='c cprogram', 
               fragment='#include <pthread.h>\nint main ( int argc, const char **argv ) { return PTHREAD_MUTEX_RECURSIVE; }\n',
               execute = False,
               define_name='HAVE_PTHREAD_MUTEX_RECURSIVE', mandatory=False,
               msg='Checking for PTHREAD_MUTEX_RECURSIVE')
#    conf.check(function_name='jpeg_CreateCompress', header_name='jpeglib.h', use='jpeg', define_name='HAVE_LIBJPEG', mandatory=False)

    if Options.options.ENABLE_TEST:
        conf.env.ENABLE_TEST = True

    conf.env.BUNDLED = []    

    conf.env['LIB_PTHREAD'] = ['pthread']
    conf.env['LIB_DL'] = ['dl']
    conf.env['LIB_M'] = ['m']

    conf.env.BUNDLED = []    

    conf.check(function_name='strtoll', header_name="stdlib.h", define_name='HAVE_STRTOLL', mandatory=False)
    conf.check(function_name='scandir', header_name="dirent.h", define_name='HAVE_SCANDIR', mandatory=False)

    conf.check(lib='jpeg', uselib_store='LIBJPEG', mandatory=True )
    conf.check_cfg(package='libpng', uselib_store='LIBPNG', args="--cflags --libs",
                          mandatory=True)
    conf.check_cfg(package='zlib', uselib_store='LIBZ', args="--cflags --libs",
                          mandatory=True)

    
    if Options.options.USE_GL:
        conf.env.append_value( 'USE_GL', '1' )
        conf.check_cfg(package='gl', uselib_store='GL', args="--cflags --libs",
                   mandatory=True)

    # FIXME: HAVE_LONG_LONG

    optimization_flags = [
        "-O3",
        "-fomit-frame-pointer",
        "-ffast-math",
        #            "-fstrength-reduce",
        "-pipe"
        ]

    debug_flags = [
        '-g',
        '-O0' ]

    if Options.options.debug:
        print 'Building for debugging'
        conf.env.append_value('CFLAGS', debug_flags )
        conf.env.append_value('CXXFLAGS', debug_flags )
    else:
        print 'Building for performance'
        conf.env.append_value('CFLAGS', optimization_flags )
        conf.env.append_value('CXXFLAGS', optimization_flags )
        conf.define( 'NDEBUG', 1 )

    if sys.platform == 'darwin':
        conf.define( '__APPLE__', 1 )
    if sys.platform == 'win32':
        conf.define( 'WIN32', 1 )
    else:
        conf.define( 'HAVE_X11', 1 )
        conf.define( 'USE_X11', 1 )

    conf.define( 'USE_POLL', 1 )
    conf.define( 'USE_XFT', 1 )
    conf.define( 'BORDER_WIDTH', 1 )

    conf.define( 'HAVE_SCANDIR_POSIX', 1 )
    conf.define( 'HAVE_STRCASECMP', 1 )
    conf.define( 'HAVE_VSNPRINTF', 1 )
    conf.define( 'HAVE_SNPRINTF', 1 )
    conf.define( 'HAVE_STRTOLL', 1 )

    conf.define( 'HAVE_DLSYM', 1 )
    
#    print conf.env
# FIXME: use tests for these

    conf.define( 'U16', 'unsigned short', quote=False )
    conf.define( 'U32', 'unsined', quote=False )
    conf.define( 'U64', 'unsigned long', quote=False )

    conf.define( 'WORDS_BIGENDIAN', 0 )

    conf.define('VERSION', PACKAGE_VERSION)
    conf.define('FLTK_DOCDIR', conf.env.DOCDIR );
    # conf.define('SYSTEM_PATH', string.join( [ conf.env.DATADIR, APPNAME ], '/' ) )
    # conf.define('DOCUMENT_PATH', conf.env.DOCDIR )
    # conf.define('PIXMAP_PATH', string.join( [ conf.env.DATADIR, APPNAME ], '/' ) )

    conf.write_config_header('config.h', remove=False)
    
    for i in conf.env.BUNDLED:
        conf.recurse(i)

    for i in children:
        conf.recurse(i)


    print('')

def build(bld):
    #     libs = 'LILV SUIL JACK SERD SRATOM LV2'


    libs = '' 

    lib_source = '''
src/Fl_Cairo_Graphics_Driver.cxx
src/Fl.cxx
src/Fl_Adjuster.cxx
src/Fl_Bitmap.cxx
src/Fl_Browser.cxx
src/Fl_Browser_.cxx
src/Fl_Browser_load.cxx
src/Fl_Box.cxx
src/Fl_Button.cxx
src/Fl_Chart.cxx
src/Fl_Check_Browser.cxx
src/Fl_Check_Button.cxx
src/Fl_Choice.cxx
src/Fl_Color_Chooser.cxx
src/Fl_Counter.cxx
src/Fl_Dial.cxx
src/Fl_Dial_Base.cxx
src/Fl_Device.cxx
src/Fl_Double_Window.cxx
src/Fl_File_Browser.cxx
src/Fl_File_Chooser.cxx
src/Fl_File_Chooser2.cxx
src/Fl_File_Icon.cxx
src/Fl_File_Input.cxx
src/Fl_Group.cxx
src/Fl_Help_View.cxx
src/Fl_Image.cxx
src/Fl_Input.cxx
src/Fl_Input_.cxx
src/Fl_Light_Button.cxx
src/Fl_Menu.cxx
src/Fl_Menu_.cxx
src/Fl_Menu_Bar.cxx
src/Fl_Sys_Menu_Bar.cxx
src/Fl_Menu_Button.cxx
src/Fl_Menu_Window.cxx
src/Fl_Menu_add.cxx
src/Fl_Menu_global.cxx
src/Fl_Multi_Label.cxx
src/Fl_Native_File_Chooser.cxx
src/Fl_Overlay_Window.cxx
src/Fl_Pack.cxx
src/Fl_Paged_Device.cxx
src/Fl_Panzoomer.cxx
src/Fl_Pixmap.cxx
src/Fl_Positioner.cxx
src/Fl_Preferences.cxx
src/Fl_Printer.cxx
src/Fl_Progress.cxx
src/Fl_Repeat_Button.cxx
src/Fl_Return_Button.cxx
src/Fl_Round_Button.cxx
src/Fl_Scroll.cxx
src/Fl_Scrollbar.cxx
src/Fl_Shared_Image.cxx
src/Fl_Single_Window.cxx
src/Fl_Slider.cxx
src/Fl_Table.cxx
src/Fl_Table_Row.cxx
src/Fl_Tabs.cxx
src/Fl_Text_Buffer.cxx
src/Fl_Text_Display.cxx
src/Fl_Text_Editor.cxx
src/Fl_Tile.cxx
src/Fl_Tiled_Image.cxx
src/Fl_Tree.cxx
src/Fl_Tree_Item.cxx
src/Fl_Tree_Item_Array.cxx
src/Fl_Tree_Prefs.cxx
src/Fl_Tooltip.cxx
src/Fl_Valuator.cxx
src/Fl_Value_Input.cxx
src/Fl_Value_Output.cxx
src/Fl_Value_Slider.cxx
src/Fl_Widget.cxx
src/Fl_Window.cxx
src/Fl_Window_fullscreen.cxx
src/Fl_Window_hotspot.cxx
src/Fl_Window_iconize.cxx
src/Fl_Wizard.cxx
src/Fl_XBM_Image.cxx
src/Fl_XPM_Image.cxx
src/Fl_abort.cxx
src/Fl_add_idle.cxx
src/Fl_arg.cxx
src/Fl_compose.cxx
src/Fl_display.cxx
src/Fl_get_key.cxx
src/Fl_get_system_colors.cxx
src/Fl_grab.cxx
src/Fl_lock.cxx
src/Fl_own_colormap.cxx
src/Fl_visual.cxx
src/Fl_x.cxx
src/filename_absolute.cxx
src/filename_expand.cxx
src/filename_ext.cxx
src/filename_isdir.cxx
src/filename_list.cxx
src/filename_match.cxx
src/filename_setext.cxx
src/fl_arc.cxx
src/fl_arci.cxx
src/fl_ask.cxx
src/fl_boxtype.cxx
src/fl_color.cxx
src/fl_cursor.cxx
src/fl_curve.cxx
src/fl_diamond_box.cxx
src/fl_dnd.cxx
src/fl_draw.cxx
src/Fl_Cairo.cxx
src/fl_draw_image.cxx
src/fl_draw_pixmap.cxx
src/fl_encoding_latin1.cxx
src/fl_encoding_mac_roman.cxx
src/fl_engraved_label.cxx
src/fl_file_dir.cxx
src/fl_font.cxx
src/fl_labeltype.cxx
src/fl_line_style.cxx
src/fl_open_uri.cxx
src/fl_oval_box.cxx
src/fl_overlay.cxx
src/fl_read_image.cxx
src/fl_rect.cxx
src/fl_round_box.cxx
src/fl_rounded_box.cxx
src/fl_set_font.cxx
src/fl_set_fonts.cxx
src/fl_scroll_area.cxx
src/fl_shadow_box.cxx
src/fl_shortcut.cxx
src/fl_show_colormap.cxx
src/fl_symbols.cxx
src/fl_vertex.cxx
src/screen_xywh.cxx
src/fl_utf8.cxx
src/Fl_Theme.cxx
src/Fl_Theme_Chooser.cxx
src/Cairo_Theme.cxx
src/Gleam_Theme.cxx
src/Clean_Theme.cxx
src/Crystal_Theme.cxx
src/Vector_Theme.cxx
src/themes.cxx
src/ps_image.cxx
src/fl_utf.c
src/vsnprintf.c
src/xutf8/case.c
src/xutf8/is_right2left.c
src/xutf8/is_spacing.c
src/xutf8/keysym2Ucs.c
src/xutf8/utf8Input.c
src/xutf8/utf8Utils.c
src/xutf8/utf8Wrap.c
src/numericsort.c
src/flstring.c
'''

    # conf.define( 'FL_LIBRARY', 1 )
    # conf.define( 'FL_INTERNALS', 1 )

    bld.makelib(   source = lib_source,
                   target       = 'ntk',
                   uselib = [ 'X11', 'XFT', 'CAIRO', 'DL', 'M', 'PTHREAD' ] )
    
    lib_images_source = '''
src/fl_images_core.cxx
src/Fl_BMP_Image.cxx
src/Fl_File_Icon2.cxx
src/Fl_GIF_Image.cxx
src/Fl_Help_Dialog.cxx
src/Fl_JPEG_Image.cxx
src/Fl_PNG_Image.cxx
src/Fl_PNM_Image.cxx
'''

    bld.makelib(    source = lib_images_source,
                    target       = 'ntk_images',
                    uselib = [ 'LIBJPEG', 'LIBPNG', 'LIBZ', 'DL', 'M', 'PTHREAD', 'XFT' ] )

    lib_gl_source = '''
src/Fl_Gl_Choice.cxx
src/Fl_Gl_Device_Plugin.cxx
src/Fl_Gl_Overlay.cxx
src/Fl_Gl_Window.cxx
'''
    
    if bld.env.USE_GL:
        print 'Using GL'
        bld.makelib( 
            source = lib_gl_source,
            target       = 'ntk_gl',
            uselib = [ 'X11', 'DL', 'M', 'PTHREAD', 'GL' ] )

    bld( features = 'subst',
         source = 'ntk.pc.in',
         target = 'ntk.pc',
         encoding = 'utf8',
         install_path = '${LIBDIR}/pkgconfig',
         CFLAGS = ' '.join( CFLAGS ),
         VERSION = VERSION,
         PREFIX = bld.env.PREFIX )

    bld( features = 'subst',
         source = 'ntk_images.pc.in',
         target = 'ntk_images.pc',
         encoding = 'utf8',
         install_path = '${LIBDIR}/pkgconfig',
         CFLAGS = ' '.join( CFLAGS ),
         VERSION = VERSION,
         PREFIX = bld.env.PREFIX )

    bld( features = 'subst',
         source = 'ntk_gl.pc.in',
         target = 'ntk_gl.pc',
         encoding = 'utf8',
         install_path = '${LIBDIR}/pkgconfig',
         CFLAGS = ' '.join( CFLAGS ),
         VERSION = VERSION,
         PREFIX = bld.env.PREFIX )

    bld( features = 'subst',
         source = 'ntk-uninstalled.pc.in',
         target = 'ntk-uninstalled.pc',
         encoding = 'utf8',
         CFLAGS = ' '.join( CFLAGS ),
         VERSION = VERSION,
         BUILD = os.getcwd() + '/' + out )

    bld( features = 'subst',
         source = 'ntk_images.pc.in',
         target = 'ntk_images-uninstalled.pc',
         encoding = 'utf8',
         VERSION = VERSION,
         CFLAGS = ' '.join( CFLAGS ),
         BUILD = os.getcwd() + '/' + out )


    bld( features = 'subst',
         source = 'ntk_gl.pc.in',
         target = 'ntk_gl-uninstalled.pc',
         encoding = 'utf8',
         VERSION = VERSION,
         CFLAGS = ' '.join( CFLAGS ),
         BUILD = os.getcwd() + '/' + out )


    bld.program(
	source = 'src/ntk-chtheme.cxx',
	target = 'ntk-chtheme',
        # force dynamic linkage to ntk
        after = [ 'ntk' ],
        lib = [ 'ntk'] ,
        linkflags = '-L.',
        # # 
        uselib = [ 'CAIRO', 'XFT', 'X11' ],
        includes = [ '.' ], 
	install_path = "${BINDIR}" )

    # bld( features = 'subst',
    #      source = 'ntk-config.in',
    #      target = '../ntk-config',
    #      mode = 0777,
    #      encoding = 'utf8',
    #      # VERSION = VERSION,
    #      FL_MAJOR_VERSION = FL_MAJOR_VERSION,
    #      FL_MINOR_VERSION = FL_MINOR_VERSION,
    #      FL_PATCH_VERSION = FL_PATCH_VERSION,
    #      preifx = bld.env.PREFIX,
    #      exec_prefix = bld.env.EXECPREFIX,
    #      bindir = bld.env.BINDIR,
    #      includedir = bld.env.INCLUDEDIR,
    #      libdir = bld.env.LIBDIR,
    #      srcdir = os.getcwd() + '/' + out,
    #      CC = bld.env.CC[0],
    #      CXX = bld.env.CXX[0],
    #      CFLAGS = string.join( bld.env.CFLAGS, ' ' ),
    #      CXXFLAGS = string.join( bld.env.CXXFLAGS, ' ' ),
    #      LDFLAGS = bld.env.LDFLAGS,
    #      CAIROLIBS = '-lcairo',
         
    #      install_path = '${BINDIR}' )

    for i in bld.env.BUNDLED:
        bld.recurse(i)

    for i in children:
        bld.recurse(i)

        # 'PREFIX': bld.env.PREFIX,
        #                 'EXEC_PREFIX' : bld.env.EXEC_PREFIX,
        #                 'BINDIR' : bld.env.BINDIR,
        #                 'INCLUDEDIR' : bld.env.INCLUDEDIR,
        #                 'LIBDIR' : bld.env.LIBDIR,
        #                 'SRCDIR' : bld.env.SRCDIR } )


    start_dir = bld.path.find_dir( 'FL' )

    bld.install_files( bld.env.INCLUDEDIR + '/ntk/FL', start_dir.ant_glob('*.H *.h'),
                       cwd=start_dir, relative_trick=True)

    #  bld.install_files( string.join( [ '${DATADIR}/doc', APPNAME ], '/' ), bld.path.ant_glob( 'doc/*.html doc/*.png' ) )
    
