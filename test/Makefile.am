noinst_PROGRAMS = cafekbd-indicator-test \
                  cafekbd-keyboard-drawing-test \
                  cafekbd-status-test

common_CFLAGS = $(WARN_CFLAGS) -I$(top_srcdir) -Wall \
	$(GTK_CFLAGS) \
	$(LIBXKLAVIER_CFLAGS) \
	-DCAFELOCALEDIR="\"$(datadir)/locale\""
	
common_LDFLAGS = $(GTK_LIBS) \
	$(LIBXKLAVIER_LIBS) \
	$(top_builddir)/libcafekbd/libcafekbd.la	\
	$(top_builddir)/libcafekbd/libcafekbdui.la

cafekbd_indicator_test_CFLAGS=$(common_CFLAGS)

cafekbd_indicator_test_LDFLAGS=$(common_LDFLAGS)

cafekbd_keyboard_drawing_test_CFLAGS=$(common_CFLAGS)

cafekbd_keyboard_drawing_test_LDFLAGS=$(common_LDFLAGS)

cafekbd_status_test_CFLAGS=$(common_CFLAGS)

cafekbd_status_test_LDFLAGS=$(common_LDFLAGS)
