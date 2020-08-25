NULL =
lib_LTLIBRARIES = libcafekbd.la libcafekbdui.la

common_CFLAGS =					\
	-I$(top_srcdir)				\
	$(GDK_CFLAGS)				\
	$(GIO_CFLAGS)				\
	$(LIBXKLAVIER_CFLAGS)			\
	$(XLIB_CFLAGS)				\
	-I$(top_srcdir)/intl			\
	-DG_LOG_DOMAIN=\"MateKbdIndicator\"	\
	-DDATADIR=\"$(datadir)\"		\
	-DSYSCONFDIR=\"$(sysconfdir)\"		\
	-DLIBDIR=\"$(libdir)\"			\
	$(NULL)

common_LDFLAGS = -version-info @VERSION_INFO@ -no-undefined

common_LIBADD =					\
	$(GDK_LIBS)				\
	$(GIO_LIBS)				\
	$(LIBXKLAVIER_LIBS)			\
	$(XLIB_LIBS)				\
	$(NULL)

libcafekbd_la_SOURCES =				\
	cafekbd-desktop-config.c		\
	cafekbd-keyboard-config.c		\
	cafekbd-util.c				\
	$(NULL)
libcafekbd_la_CFLAGS =				\
	$(common_CFLAGS)			\
	$(NULL)
libcafekbd_la_LDFLAGS =				\
	$(common_LDFLAGS)			\
	$(NULL)
libcafekbd_la_LIBADD =				\
	$(common_LIBADD)			\
	$(NULL)

libcafekbdui_la_SOURCES =			\
	cafekbd-indicator-config.c		\
	cafekbd-indicator.c			\
	cafekbd-status.c			\
	cafekbd-indicator-marshal.c		\
	cafekbd-keyboard-drawing-marshal.c	\
	cafekbd-keyboard-drawing-resources.c	\
	cafekbd-keyboard-drawing.c		\
	$(NULL)
libcafekbdui_la_CFLAGS =			\
	$(common_CFLAGS)			\
	$(GTK_CFLAGS)				\
	$(NULL)
libcafekbdui_la_LDFLAGS =			\
	$(common_LDFLAGS)			\
	$(NULL)
libcafekbdui_la_LIBADD = 			\
	libcafekbd.la				\
	$(common_LIBADD)			\
	$(GLIB_LIBS)				\
	$(GMODULE_LIBS)				\
	$(GTK_LIBS)				\
	$(NULL)

BUILT_SOURCES =					\
	cafekbd-indicator-marshal.c		\
	cafekbd-indicator-marshal.h		\
	cafekbd-keyboard-drawing-marshal.c	\
	cafekbd-keyboard-drawing-marshal.h	\
	cafekbd-keyboard-drawing-resources.c	\
	cafekbd-keyboard-drawing-resources.h	\
	$(NULL)

CLEANFILES = $(BUILT_SOURCES)

cafekbdincdir = $(includedir)/libcafekbd
cafekbdinc_HEADERS =				\
	cafekbd-desktop-config.h		\
	cafekbd-keyboard-config.h		\
	cafekbd-indicator.h			\
	cafekbd-status.h			\
	cafekbd-indicator-config.h		\
	cafekbd-keyboard-drawing.h		\
	cafekbd-util.h				\
	$(NULL)

noinst_HEADERS =				\
	$(extra_nih)				\
	cafekbd-config-private.h		\
	$(NULL)

gsettingsschema_in_files = org.cafe.peripherals-keyboard-xkb.gschema.xml.in
gsettings_SCHEMAS = $(gsettingsschema_in_files:.xml.in=.xml)
@GSETTINGS_RULES@

EXTRA_DIST =					\
	cafekbd-indicator-marshal.list		\
	cafekbd-keyboard-drawing-marshal.list	\
	$(gsettingsschema_in_files)		\
	org.cafe.peripherals.keyboard.gresource.xml \
	show-layout.ui				\
	$(NULL)

DISTCLEANFILES = $(gsettings_SCHEMAS)

GLIB_GENMARSHAL = $(shell pkg-config --variable=glib_genmarshal glib-2.0)

cafekbd-indicator-marshal.h: cafekbd-indicator-marshal.list
	$(AM_V_GEN)$(GLIB_GENMARSHAL) --prefix=cafekbd_indicator $(srcdir)/cafekbd-indicator-marshal.list --header > $@

cafekbd-indicator-marshal.c: cafekbd-indicator-marshal.h
	$(AM_V_GEN)$(GLIB_GENMARSHAL) --prefix=cafekbd_indicator $(srcdir)/cafekbd-indicator-marshal.list --body > $@

cafekbd-keyboard-drawing-marshal.h: cafekbd-keyboard-drawing-marshal.list
	$(AM_V_GEN)( $(GLIB_GENMARSHAL) --prefix=cafekbd_keyboard_drawing $(srcdir)/cafekbd-keyboard-drawing-marshal.list \
                            --header > cafekbd-keyboard-drawing-marshal.tmp \
          && mv cafekbd-keyboard-drawing-marshal.tmp cafekbd-keyboard-drawing-marshal.h ) \
        || ( rm -f cafekbd-keyboard-drawing-marshal.tmp && exit 1 )

cafekbd-keyboard-drawing-marshal.c: cafekbd-keyboard-drawing-marshal.h
	$(AM_V_GEN)( $(GLIB_GENMARSHAL) --prefix=cafekbd_keyboard_drawing $(srcdir)/cafekbd-keyboard-drawing-marshal.list \
                            --body > cafekbd-keyboard-drawing-marshal.tmp \
          && mv cafekbd-keyboard-drawing-marshal.tmp cafekbd-keyboard-drawing-marshal.c ) \
        || ( rm -f cafekbd-keyboard-drawing-marshal.tmp && exit 1 )


cafekbd-keyboard-drawing-resources.h cafekbd-keyboard-drawing-resources.c: org.cafe.peripherals.keyboard.gresource.xml Makefile $(shell $(GLIB_COMPILE_RESOURCES) --generate-dependencies --sourcedir $(srcdir) $(srcdir)/org.cafe.peripherals.keyboard.gresource.xml)
	$(AM_V_GEN) XMLLINT=$(XMLLINT) $(GLIB_COMPILE_RESOURCES) --target $@ --sourcedir $(srcdir) --generate --c-name cafekbd $<

-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS = Matekbd-1.0.gir
INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir) --warn-all
INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir)

if HAVE_INTROSPECTION
introspection_sources = $(cafekbdinc_HEADERS) \
        $(libcafekbd_la_SOURCES) \
        $(libcafekbdui_la_SOURCES)

Matekbd-1.0.gir: libcafekbd.la libcafekbdui.la
Matekbd_1_0_gir_INCLUDES = GObject-2.0 Gtk-3.0 xlib-2.0 Xkl-1.0
Matekbd_1_0_gir_CFLAGS = $(libcafekbdui_la_CFLAGS)
Matekbd_1_0_gir_LIBS = libcafekbd.la libcafekbdui.la
Matekbd_1_0_gir_FILES = $(introspection_sources)

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES += $(gir_DATA) $(typelib_DATA)
endif
