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

#ifndef CAFEKBD_KEYBOARD_DRAWING_H
#define CAFEKBD_KEYBOARD_DRAWING_H 1

#include <ctk/ctk.h>
#include <X11/XKBlib.h>
#include <X11/extensions/XKBgeom.h>

#ifdef __cplusplus
extern "C" {
#endif
#define CAFEKBD_KEYBOARD_DRAWING(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), cafekbd_keyboard_drawing_get_type (), \
                               CafekbdKeyboardDrawing))
#define CAFEKBD_KEYBOARD_DRAWING_CLASS(clazz) (G_TYPE_CHECK_CLASS_CAST ((clazz), cafekbd_keyboard_drawing_get_type () \
                                       CafekbdKeyboardDrawingClass))
#define CAFEKBD_IS_KEYBOARD_DRAWING(obj) G_TYPE_CHECK_INSTANCE_TYPE ((obj), cafekbd_keyboard_drawing_get_type ())
typedef struct _CafekbdKeyboardDrawing CafekbdKeyboardDrawing;
typedef struct _CafekbdKeyboardDrawingClass CafekbdKeyboardDrawingClass;

typedef struct _CafekbdKeyboardDrawingItem CafekbdKeyboardDrawingItem;
typedef struct _CafekbdKeyboardDrawingKey CafekbdKeyboardDrawingKey;
typedef struct _CafekbdKeyboardDrawingDoodad CafekbdKeyboardDrawingDoodad;
typedef struct _CafekbdKeyboardDrawingGroupLevel
 CafekbdKeyboardDrawingGroupLevel;
typedef struct _CafekbdKeyboardDrawingRenderContext
 CafekbdKeyboardDrawingRenderContext;

typedef enum {
	CAFEKBD_KEYBOARD_DRAWING_ITEM_TYPE_INVALID = 0,
	CAFEKBD_KEYBOARD_DRAWING_ITEM_TYPE_KEY,
	CAFEKBD_KEYBOARD_DRAWING_ITEM_TYPE_KEY_EXTRA,
	CAFEKBD_KEYBOARD_DRAWING_ITEM_TYPE_DOODAD
} CafekbdKeyboardDrawingItemType;

typedef enum {
	CAFEKBD_KEYBOARD_DRAWING_POS_TOPLEFT,
	CAFEKBD_KEYBOARD_DRAWING_POS_TOPRIGHT,
	CAFEKBD_KEYBOARD_DRAWING_POS_BOTTOMLEFT,
	CAFEKBD_KEYBOARD_DRAWING_POS_BOTTOMRIGHT,
	CAFEKBD_KEYBOARD_DRAWING_POS_TOTAL,
	CAFEKBD_KEYBOARD_DRAWING_POS_FIRST =
	    CAFEKBD_KEYBOARD_DRAWING_POS_TOPLEFT,
	CAFEKBD_KEYBOARD_DRAWING_POS_LAST =
	    CAFEKBD_KEYBOARD_DRAWING_POS_BOTTOMRIGHT
} CafekbdKeyboardDrawingGroupLevelPosition;

/* units are in xkb form */
struct _CafekbdKeyboardDrawingItem {
	/*< private > */

	CafekbdKeyboardDrawingItemType type;
	gint origin_x;
	gint origin_y;
	gint angle;
	guint priority;
};

/* units are in xkb form */
struct _CafekbdKeyboardDrawingKey {
	/*< private > */

	CafekbdKeyboardDrawingItemType type;
	gint origin_x;
	gint origin_y;
	gint angle;
	guint priority;

	XkbKeyRec *xkbkey;
	gboolean pressed;
	guint keycode;
};

/* units are in xkb form */
struct _CafekbdKeyboardDrawingDoodad {
	/*< private > */

	CafekbdKeyboardDrawingItemType type;
	gint origin_x;
	gint origin_y;
	gint angle;
	guint priority;

	XkbDoodadRec *doodad;
	gboolean on;		/* for indicator doodads */
};

struct _CafekbdKeyboardDrawingGroupLevel {
	gint group;
	gint level;
};

struct _CafekbdKeyboardDrawingRenderContext {
	cairo_t *cr;

	gint angle;		/* current angle pango is set to draw at, in tenths of a degree */
	PangoLayout *layout;
	PangoFontDescription *font_desc;

	gint scale_numerator;
	gint scale_denominator;

	CdkRGBA dark_color;
};

struct _CafekbdKeyboardDrawing {
	/*< private > */

	CtkDrawingArea parent;

	cairo_surface_t *surface;
	XkbDescRec *xkb;
	gboolean xkbOnDisplay;
	guint l3mod;

	CafekbdKeyboardDrawingRenderContext *renderContext;

	/* Indexed by keycode */
	CafekbdKeyboardDrawingKey *keys;

	/* list of stuff to draw in priority order */
	GList *keyboard_items;

	CdkRGBA *colors;

	guint timeout;
	guint idle_redraw;

	CafekbdKeyboardDrawingGroupLevel **groupLevels;

	guint mods;

	Display *display;
	gint screen_num;

	gint xkb_event_type;

	CafekbdKeyboardDrawingDoodad **physical_indicators;
	gint physical_indicators_size;

	guint track_config:1;
	guint track_modifiers:1;
};

struct _CafekbdKeyboardDrawingClass {
	CtkDrawingAreaClass parent_class;

	/* we send this signal when the user presses a key that "doesn't exist"
	 * according to the keyboard geometry; it probably means their xkb
	 * configuration is incorrect */
	void (*bad_keycode) (CafekbdKeyboardDrawing * drawing, guint keycode);
};

GType cafekbd_keyboard_drawing_get_type (void);
CtkWidget *cafekbd_keyboard_drawing_new (void);

gboolean cafekbd_keyboard_drawing_render (CafekbdKeyboardDrawing * kbdrawing,
				       cairo_t * cr,
				       PangoLayout * layout,
				       double x, double y,
				       double width, double height,
				       gdouble dpi_x, gdouble dpi_y);
gboolean cafekbd_keyboard_drawing_set_keyboard (CafekbdKeyboardDrawing *
					     kbdrawing,
					     XkbComponentNamesRec * names);

const gchar* cafekbd_keyboard_drawing_get_keycodes(CafekbdKeyboardDrawing* kbdrawing);
const gchar* cafekbd_keyboard_drawing_get_geometry(CafekbdKeyboardDrawing* kbdrawing);
const gchar* cafekbd_keyboard_drawing_get_symbols(CafekbdKeyboardDrawing* kbdrawing);
const gchar* cafekbd_keyboard_drawing_get_types(CafekbdKeyboardDrawing* kbdrawing);
const gchar* cafekbd_keyboard_drawing_get_compat(CafekbdKeyboardDrawing* kbdrawing);

void cafekbd_keyboard_drawing_set_track_modifiers (CafekbdKeyboardDrawing *
						kbdrawing,
						gboolean enable);
void cafekbd_keyboard_drawing_set_track_config (CafekbdKeyboardDrawing *
					     kbdrawing, gboolean enable);

void cafekbd_keyboard_drawing_set_groups_levels (CafekbdKeyboardDrawing *
					      kbdrawing,
					      CafekbdKeyboardDrawingGroupLevel
					      * groupLevels[]);


void cafekbd_keyboard_drawing_print (CafekbdKeyboardDrawing * drawing,
				  CtkWindow * parent_window,
				  const gchar * description);


CtkWidget* cafekbd_keyboard_drawing_new_dialog (gint group, gchar* group_name);

#ifdef __cplusplus
}
#endif
#endif				/* #ifndef CAFEKBD_KEYBOARD_DRAWING_H */
