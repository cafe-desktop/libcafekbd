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

#ifndef __CAFEKBD_INDICATOR_H__
#define __CAFEKBD_INDICATOR_H__

#include <ctk/ctk.h>

#include <libxklavier/xklavier.h>

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct _CafekbdIndicator CafekbdIndicator;
	typedef struct _CafekbdIndicatorPrivate CafekbdIndicatorPrivate;
	typedef struct _CafekbdIndicatorClass CafekbdIndicatorClass;

#define CAFEKBD_TYPE_INDICATOR             (cafekbd_indicator_get_type ())
#define CAFEKBD_INDICATOR(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), CAFEKBD_TYPE_INDICATOR, CafekbdIndicator))
#define CAFEKBD_INDICATOR_CLASS(obj)       (G_TYPE_CHECK_CLASS_CAST ((obj), CAFEKBD_TYPE_INDICATOR,  CafekbdIndicatorClass))
#define CAFEKBD_IS_INDICATOR(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CAFEKBD_TYPE_INDICATOR))
#define CAFEKBD_IS_INDICATOR_CLASS(obj)    (G_TYPE_CHECK_CLASS_TYPE ((obj), CAFEKBD_TYPE_INDICATOR))
#define CAFEKBD_INDICATOR_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), CAFEKBD_TYPE_INDICATOR, CafekbdIndicatorClass))

	struct _CafekbdIndicator {
		CtkNotebook parent;
		CafekbdIndicatorPrivate *priv;
	};

	struct _CafekbdIndicatorClass {
		CtkNotebookClass parent_class;

		void (*reinit_ui) (CafekbdIndicator * gki);
	};

	extern GType cafekbd_indicator_get_type (void);

	extern CtkWidget *cafekbd_indicator_new (void);

	extern void cafekbd_indicator_reinit_ui (CafekbdIndicator * gki);

	extern void cafekbd_indicator_set_angle (CafekbdIndicator * gki,
					      gdouble angle);

	extern XklEngine *cafekbd_indicator_get_xkl_engine (void);

	extern gchar **cafekbd_indicator_get_group_names (void);

	extern gchar *cafekbd_indicator_get_image_filename (guint group);

	extern gdouble cafekbd_indicator_get_max_width_height_ratio (void);

	extern void
	 cafekbd_indicator_set_parent_tooltips (CafekbdIndicator *
					     gki, gboolean ifset);

	extern void
	 cafekbd_indicator_set_tooltips_format (const gchar str[]);

#ifdef __cplusplus
}
#endif
#endif
