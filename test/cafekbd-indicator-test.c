/*
 * Copyright (C) 2006 Sergey V. Udaltsov <svu@gnome.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "config.h"

#include "libxklavier/xklavier.h"
#include "libcafekbd/cafekbd-indicator.h"

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include <cdk/cdk.h>
#include <cdk/cdkx.h>
#include <glib/gi18n.h>
#include <ctk/ctk.h>

#include "X11/XKBlib.h"

int main(int argc, char** argv)
{
	CtkWidget* gki;
	CtkWidget* mainwin;
	CtkWidget* vbox;

	bindtextdomain(GETTEXT_PACKAGE, CAFELOCALEDIR);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain(GETTEXT_PACKAGE);

	/* Different data dir defs in g-a and g-c-c */
	ctk_init (&argc, &argv);

	mainwin = ctk_window_new(CTK_WINDOW_TOPLEVEL);

	gki = cafekbd_indicator_new();
	cafekbd_indicator_set_tooltips_format(_("Keyboard Indicator Test (%s)"));
	cafekbd_indicator_set_parent_tooltips(CAFEKBD_INDICATOR (gki), TRUE);

	ctk_window_resize(CTK_WINDOW(mainwin), 250, 250);
	vbox = ctk_box_new(CTK_ORIENTATION_VERTICAL, 6);

	ctk_container_add(CTK_CONTAINER(mainwin), vbox);
	ctk_container_set_border_width(CTK_CONTAINER(vbox), 12);
	ctk_container_add(CTK_CONTAINER(vbox), ctk_label_new(_("Indicator:")));
	ctk_container_add(CTK_CONTAINER(vbox), gki);

	ctk_widget_show_all(mainwin);

	g_signal_connect(G_OBJECT(mainwin), "destroy", G_CALLBACK(ctk_main_quit), NULL);

	ctk_main();

	return 0;
}
