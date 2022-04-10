noinst_PROGRAMS = cafekbd-indicator-test \
                  cafekbd-keyboard-drawing-test \
                  cafekbd-status-test

CFLAGS_common = $(WARN_CFLAGS) -I$(top_srcdir) -Wall \
	$(GTK_CFLAGS) \
	$(LIBXKLAVIER_CFLAGS) \
	-DCAFELOCALEDIR="\"$(datadir)/locale\""
	
LDFLAGS_common = $(GTK_LIBS) \
	$(LIBXKLAVIER_LIBS) \
	$(top_builddir)/libcafekbd/libcafekbd.la	\
	$(top_builddir)/libcafekbd/libcafekbdui.la

cafekbd_indicator_test_CFLAGS=$(CFLAGS_common)

cafekbd_indicator_test_LDFLAGS=$(LDFLAGS_common)

cafekbd_keyboard_drawing_test_CFLAGS=$(CFLAGS_common)

cafekbd_keyboard_drawing_test_LDFLAGS=$(LDFLAGS_common)

cafekbd_status_test_CFLAGS=$(CFLAGS_common)

cafekbd_status_test_LDFLAGS=$(LDFLAGS_common)
