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

#ifndef __CAFEKBD_KEYBOARD_CONFIG_H__
#define __CAFEKBD_KEYBOARD_CONFIG_H__

#include <X11/Xlib.h>
#include <glib.h>
#include <gio/gio.h>
#include <libxklavier/xklavier.h>

extern const gchar CAFEKBD_KEYBOARD_CONFIG_KEY_MODEL[];
extern const gchar CAFEKBD_KEYBOARD_CONFIG_KEY_LAYOUTS[];
extern const gchar CAFEKBD_KEYBOARD_CONFIG_KEY_OPTIONS[];

/*
 * Keyboard Configuration
 */
typedef struct _CafekbdKeyboardConfig CafekbdKeyboardConfig;
struct _CafekbdKeyboardConfig {
	gchar *model;
	gchar **layouts_variants;
	gchar **options;

	/* private, transient */
	GSettings *settings;
	int config_listener_id;
	XklEngine *engine;
};

/*
 * CafekbdKeyboardConfig functions
 */
extern void cafekbd_keyboard_config_init (CafekbdKeyboardConfig * kbd_config,
				       XklEngine * engine);
extern void cafekbd_keyboard_config_term (CafekbdKeyboardConfig * kbd_config);

extern void cafekbd_keyboard_config_load_from_gsettings (CafekbdKeyboardConfig *
						  kbd_config,
						  CafekbdKeyboardConfig *
						  kbd_config_default);

extern void cafekbd_keyboard_config_save_to_gsettings (CafekbdKeyboardConfig *
						kbd_config);

extern void cafekbd_keyboard_config_load_from_x_initial (CafekbdKeyboardConfig *
						      kbd_config,
						      XklConfigRec * buf);

extern void cafekbd_keyboard_config_load_from_x_current (CafekbdKeyboardConfig *
						      kbd_config,
						      XklConfigRec * buf);

extern void cafekbd_keyboard_config_start_listen (CafekbdKeyboardConfig *
					       kbd_config,
					       GCallback func,
					       gpointer user_data);

extern void cafekbd_keyboard_config_stop_listen (CafekbdKeyboardConfig *
					      kbd_config);

extern gboolean cafekbd_keyboard_config_equals (CafekbdKeyboardConfig *
					     kbd_config1,
					     CafekbdKeyboardConfig *
					     kbd_config2);

extern gboolean cafekbd_keyboard_config_activate (CafekbdKeyboardConfig *
					       kbd_config);

extern const gchar *cafekbd_keyboard_config_merge_items (const gchar * parent,
						      const gchar * child);

extern gboolean cafekbd_keyboard_config_split_items (const gchar * merged,
						  gchar ** parent,
						  gchar ** child);

extern gboolean cafekbd_keyboard_config_get_descriptions (XklConfigRegistry *
						       config_registry,
						       const gchar * name,
						       gchar **
						       layout_short_descr,
						       gchar **
						       layout_descr,
						       gchar **
						       variant_short_descr,
						       gchar **
						       variant_descr);

extern const gchar *cafekbd_keyboard_config_format_full_layout (const gchar
							     *
							     layout_descr,
							     const gchar *
							     variant_descr);

extern gchar *cafekbd_keyboard_config_to_string (const CafekbdKeyboardConfig *
					      config);

extern gchar
    **cafekbd_keyboard_config_add_default_switch_option_if_necessary (gchar **
								  layouts_list,
								  gchar **
								  options_list,
								  gboolean
								  *
								  was_appended);

#endif
