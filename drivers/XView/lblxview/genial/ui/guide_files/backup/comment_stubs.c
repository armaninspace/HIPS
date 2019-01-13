/*
 * comment_stubs.c - Notify and event callback function stubs.
 * This file was generated by `gxv' from `comment.G'.
 */

#include <stdio.h>
#include <sys/param.h>
#include <sys/types.h>
#include <xview/xview.h>
#include <xview/panel.h>
#include <xview/textsw.h>
#include <xview/xv_xrect.h>
#include "comment_ui.h"
#include "gen.h"
#include "genial.h"


/*
 * Global object definitions.
 */
comment_comm_win_objects	*Comment_comm_win;

#ifdef MAIN

/*
 * Instance XV_KEY_DATA key.  An instance is a set of related
 * user interface objects.  A pointer to an object's instance
 * is stored under this key in every object.  This must be a
 * global variable.
 */
Attr_attribute	INSTANCE;

main(argc, argv)
	int	argc;
	char	**argv;
{
	/*
	 * Initialize XView.
	 */
	xv_init(XV_INIT_ARGC_PTR_ARGV, &argc, argv, NULL);
	INSTANCE = xv_unique_key();
	
	/*
	 * Initialize user interface components.
	 * Do NOT edit the object initializations by hand.
	 */
	Comment_comm_win = comment_comm_win_objects_initialize(NULL, NULL);
	
	
	/*
	 * Turn control over to XView.
	 */
	xv_main_loop(Comment_comm_win->comm_win);
	exit(0);
}

#endif


/*
 * Done callback function for `comm_win'.
 */
void
cmtfile_save(frame)
	Frame		frame;
{
	fputs("comment: cmtfile_save\n", stderr);
	xv_set(frame, XV_SHOW, FALSE, NULL);
	
	/* gxv_start_connections DO NOT EDIT THIS SECTION */
	/* gxv_end_connections */

}