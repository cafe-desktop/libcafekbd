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

#include <config.h>

#include <cafekbd-util.h>

#include <time.h>

#include <glib/gi18n-lib.h>

#include <libxklavier/xklavier.h>

#include <gio/gio.h>

#include <cdk/cdkx.h>

#include <cafekbd-config-private.h>

static void
cafekbd_log_appender (const char file[], const char function[],
		   int level, const char format[], va_list args)
{
	time_t now = time (NULL);
	g_log (NULL, G_LOG_LEVEL_DEBUG, "[%08ld,%03d,%s:%s/] \t",
	       (long) now, level, file, function);
	g_logv (NULL, G_LOG_LEVEL_DEBUG, format, args);
}

void
cafekbd_install_glib_log_appender (void)
{
	xkl_set_log_appender (cafekbd_log_appender);
}

#define CAFEKBD_PREVIEW_CONFIG_SCHEMA  CAFEKBD_CONFIG_SCHEMA ".preview"

const gchar CAFEKBD_PREVIEW_CONFIG_KEY_X[] = "x";
const gchar CAFEKBD_PREVIEW_CONFIG_KEY_Y[] = "y";
const gchar CAFEKBD_PREVIEW_CONFIG_KEY_WIDTH[] = "width";
const gchar CAFEKBD_PREVIEW_CONFIG_KEY_HEIGHT[] = "height";

/**
 * cafekbd_preview_load_position:
 *
 * Returns: (transfer full): A rectangle to use
 */
CdkRectangle *
cafekbd_preview_load_position (void)
{
	CdkRectangle *rv = NULL;
	gint x, y, w, h;
	GSettings* settings = g_settings_new (CAFEKBD_PREVIEW_CONFIG_SCHEMA);

	x = g_settings_get_int (settings, CAFEKBD_PREVIEW_CONFIG_KEY_X);
	y = g_settings_get_int (settings, CAFEKBD_PREVIEW_CONFIG_KEY_Y);
	w = g_settings_get_int (settings, CAFEKBD_PREVIEW_CONFIG_KEY_WIDTH);
	h = g_settings_get_int (settings, CAFEKBD_PREVIEW_CONFIG_KEY_HEIGHT);

	g_object_unref (settings);

	rv = g_new (CdkRectangle, 1);
	if (x == -1 || y == -1 || w == -1 || h == -1) {
		/* default values should be treated as
		 * "0.75 of the screen size" */
		CdkScreen *scr = cdk_screen_get_default ();
		w = WidthOfScreen (cdk_x11_screen_get_xscreen (scr));
		h = HeightOfScreen (cdk_x11_screen_get_xscreen (scr));
		rv->x = w >> 3;
		rv->y = h >> 3;
		rv->width = w - (w >> 2);
		rv->height = h - (h >> 2);
	} else {
		rv->x = x;
		rv->y = y;
		rv->width = w;
		rv->height = h;
	}
	return rv;
}

void
cafekbd_preview_save_position (CdkRectangle * rect)
{
	GSettings* settings = g_settings_new (CAFEKBD_PREVIEW_CONFIG_SCHEMA);

	g_settings_delay (settings);

	g_settings_set_int (settings, CAFEKBD_PREVIEW_CONFIG_KEY_X, rect->x);
	g_settings_set_int (settings, CAFEKBD_PREVIEW_CONFIG_KEY_Y, rect->y);
	g_settings_set_int (settings, CAFEKBD_PREVIEW_CONFIG_KEY_WIDTH, rect->width);
	g_settings_set_int (settings, CAFEKBD_PREVIEW_CONFIG_KEY_HEIGHT, rect->height);

	g_settings_apply (settings);

	g_object_unref (settings);
}

/**
 * cafekbd_strv_append:
 *
 * Returns: (transfer full) (array zero-terminated=1): Append string to strv array
 */
gchar **
cafekbd_strv_append (gchar ** arr, gchar * element)
{
	gint old_length = (arr == NULL) ? 0 : g_strv_length (arr);
	gchar **new_arr = g_new0 (gchar *, old_length + 2);
	if (arr != NULL) {
		memcpy (new_arr, arr, old_length * sizeof (gchar *));
		g_free (arr);
	}
	new_arr[old_length] = element;
	return new_arr;
}

