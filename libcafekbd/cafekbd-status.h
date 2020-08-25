/*
 * Copyright (C) 2009 Sergey V. Udaltsov <svu@gnome.org>
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

#ifndef __CAFEKBD_STATUS_H__
#define __CAFEKBD_STATUS_H__

#include <gtk/gtk.h>

#include <libxklavier/xklavier.h>

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct _CafekbdStatus CafekbdStatus;
	typedef struct _CafekbdStatusPrivate CafekbdStatusPrivate;
	typedef struct _CafekbdStatusClass CafekbdStatusClass;

	#define CAFEKBD_TYPE_STATUS             (cafekbd_status_get_type ())
	#define CAFEKBD_STATUS(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), CAFEKBD_TYPE_STATUS, CafekbdStatus))
	#define CAFEKBD_STATUS_CLASS(obj)       (G_TYPE_CHECK_CLASS_CAST ((obj), CAFEKBD_TYPE_STATUS,  CafekbdStatusClass))
	#define CAFEKBD_IS_STATUS(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CAFEKBD_TYPE_STATUS))
	#define CAFEKBD_IS_STATUS_CLASS(obj)    (G_TYPE_CHECK_CLASS_TYPE ((obj), CAFEKBD_TYPE_STATUS))
	#define CAFEKBD_STATUS_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), CAFEKBD_TYPE_STATUS, CafekbdStatusClass))

	struct _CafekbdStatus {
		GtkStatusIcon parent;
		CafekbdStatusPrivate *priv;
	};

	struct _CafekbdStatusClass {
		GtkNotebookClass parent_class;
	};

	extern GType cafekbd_status_get_type (void);

	extern GtkStatusIcon *cafekbd_status_new (void);

	extern void cafekbd_status_reinit_ui (CafekbdStatus * gki);

	extern void cafekbd_status_set_angle (CafekbdStatus * gki,
					   gdouble angle);

	extern XklEngine *cafekbd_status_get_xkl_engine (void);

	extern gchar **cafekbd_status_get_group_names (void);

	extern gchar *cafekbd_status_get_image_filename (guint group);

	extern void
	 cafekbd_status_set_tooltips_format (const gchar str[]);

#ifdef __cplusplus
}
#endif
#endif
