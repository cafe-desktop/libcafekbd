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

#ifndef __CAFEKBD_UTIL_H__
#define __CAFEKBD_UTIL_H__

#include <glib.h>
#include <cdk/cdk.h>

extern void cafekbd_install_glib_log_appender (void);

extern CdkRectangle *cafekbd_preview_load_position (void);

extern void cafekbd_preview_save_position (CdkRectangle * rect);

/* Missing in glib */
extern gchar **cafekbd_strv_append (gchar ** arr, gchar * element);


#endif
