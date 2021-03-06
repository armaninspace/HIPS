/*
 * orig_view_ui.c - User interface object initialization functions.
 * This file was generated by `gxv' from `orig_view.G'.
 * DO NOT EDIT BY HAND.
 */

#include <stdio.h>
#include <sys/param.h>
#include <sys/types.h>
#include <xview/xview.h>
#include <xview/canvas.h>
#include <xview/icon_load.h>
#include <xview/panel.h>
#include <xview/scrollbar.h>
#include <xview/svrimage.h>
#include <xview/termsw.h>
#include <xview/text.h>
#include <xview/tty.h>
#include <xview/xv_xrect.h>
#include "orig_view_ui.h"

/*
 * Initialize an instance of object `win'.
 */
orig_view_win_objects *
orig_view_win_objects_initialize(ip, owner)
	orig_view_win_objects	*ip;
	Xv_opaque	owner;
{
	if (!ip && !(ip = (orig_view_win_objects *) calloc(1, sizeof (orig_view_win_objects))))
		return (orig_view_win_objects *) NULL;
	if (!ip->win)
		ip->win = orig_view_win_win_create(ip, owner);
	if (!ip->canvas)
		ip->canvas = orig_view_win_canvas_create(ip, ip->win);
	return ip;
}

/*
 * Create object `win' in the specified instance.

 */
Xv_opaque
orig_view_win_win_create(ip, owner)
	caddr_t		ip;
	Xv_opaque	owner;
{
	Xv_opaque	obj;
	
	obj = xv_create(owner, FRAME,
		XV_KEY_DATA, INSTANCE, ip,
		XV_WIDTH, 800,
		XV_HEIGHT, 800,
		XV_LABEL, "Original Image ",
		FRAME_CLOSED, FALSE,
		FRAME_SHOW_FOOTER, FALSE,
		FRAME_SHOW_RESIZE_CORNER, TRUE,
		NULL);
	return obj;
}

/*
 * Create object `canvas' in the specified instance.

 */
Xv_opaque
orig_view_win_canvas_create(ip, owner)
	caddr_t		ip;
	Xv_opaque	owner;
{
	extern void	orig_image_repaint_proc();
	Xv_opaque	obj;
	
	obj = xv_create(owner, CANVAS,
		XV_KEY_DATA, INSTANCE, ip,
		XV_X, 0,
		XV_Y, 0,
		XV_WIDTH, WIN_EXTEND_TO_EDGE,
		XV_HEIGHT, WIN_EXTEND_TO_EDGE,
		CANVAS_REPAINT_PROC, orig_image_repaint_proc,
		CANVAS_X_PAINT_WINDOW, TRUE,
		NULL);
	xv_set(canvas_paint_window(obj), XV_KEY_DATA, INSTANCE, ip, NULL);
	return obj;
}

