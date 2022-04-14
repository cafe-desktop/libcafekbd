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

#ifndef __CAFEKBD_INDICATOR_CONFIG_H__
#define __CAFEKBD_INDICATOR_CONFIG_H__

#include <ctk/ctk.h>

#include "libcafekbd/cafekbd-keyboard-config.h"

/*
 * Indicator configuration
 */
typedef struct _CafekbdIndicatorConfig CafekbdIndicatorConfig;
struct _CafekbdIndicatorConfig {
	int secondary_groups_mask;
	gboolean show_flags;

	gchar *font_family;
	gchar *foreground_color;
	gchar *background_color;

	/* private, transient */
	GSettings *settings;
	GSList *image_filenames;
	GtkIconTheme *icon_theme;
	int config_listener_id;
	XklEngine *engine;
};

/*
 * CafekbdIndicatorConfig functions -
 * some of them require CafekbdKeyboardConfig as well -
 * for loading approptiate images
 */
extern void cafekbd_indicator_config_init (CafekbdIndicatorConfig *
					applet_config,
					XklEngine * engine);
extern void cafekbd_indicator_config_term (CafekbdIndicatorConfig *
					applet_config);

extern void cafekbd_indicator_config_load_from_gsettings (CafekbdIndicatorConfig
						   * applet_config);
extern void cafekbd_indicator_config_save_to_gsettings (CafekbdIndicatorConfig *
						 applet_config);

extern void cafekbd_indicator_config_refresh_style (CafekbdIndicatorConfig *
						 applet_config);

extern gchar
    * cafekbd_indicator_config_get_images_file (CafekbdIndicatorConfig *
					     applet_config,
					     CafekbdKeyboardConfig *
					     kbd_config, int group);

extern void cafekbd_indicator_config_load_image_filenames (CafekbdIndicatorConfig
							* applet_config,
							CafekbdKeyboardConfig
							* kbd_config);
extern void cafekbd_indicator_config_free_image_filenames (CafekbdIndicatorConfig
							* applet_config);

/* Should be updated on Indicator/GSettings configuration change */
extern void cafekbd_indicator_config_activate (CafekbdIndicatorConfig *
					    applet_config);

extern void cafekbd_indicator_config_start_listen (CafekbdIndicatorConfig *
						applet_config,
						GCallback
						func, gpointer user_data);

extern void cafekbd_indicator_config_stop_listen (CafekbdIndicatorConfig *
					       applet_config);

#endif
