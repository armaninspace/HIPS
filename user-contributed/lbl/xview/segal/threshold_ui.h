#ifndef	threshold_HEADER
#define	threshold_HEADER

/*
 * threshold_ui.h - User interface object and function declarations.
 * This file was generated by `gxv' from `threshold.G'.
 * DO NOT EDIT BY HAND.
 */

extern Attr_attribute	INSTANCE;


typedef struct {
	Xv_opaque	win;
	Xv_opaque	controls2;
	Xv_opaque	canv_histo;
	Xv_opaque	controls1;
	Xv_opaque	controls;
	Xv_opaque	msg_histogram;
	Xv_opaque	histo_set;
	Xv_opaque	msg_upper;
	Xv_opaque	msg_lower;
	Xv_opaque	but_threshold;
	Xv_opaque	but_close;
	Xv_opaque	controls_stats;
	Xv_opaque	msg_0;
	Xv_opaque	msg_256;
	Xv_opaque	threshold_value_upper;
	Xv_opaque	threshold_value_lower;
} threshold_win_objects;

extern threshold_win_objects	*threshold_win_objects_initialize();

extern Xv_opaque	threshold_win_win_create();
extern Xv_opaque	threshold_win_controls2_create();
extern Xv_opaque	threshold_win_canv_histo_create();
extern Xv_opaque	threshold_win_controls1_create();
extern Xv_opaque	threshold_win_controls_create();
extern Xv_opaque	threshold_win_msg_histogram_create();
extern Xv_opaque	threshold_win_histo_set_create();
extern Xv_opaque	threshold_win_msg_upper_create();
extern Xv_opaque	threshold_win_msg_lower_create();
extern Xv_opaque	threshold_win_but_threshold_create();
extern Xv_opaque	threshold_win_but_close_create();
extern Xv_opaque	threshold_win_controls_stats_create();
extern Xv_opaque	threshold_win_msg_0_create();
extern Xv_opaque	threshold_win_msg_256_create();
extern Xv_opaque	threshold_win_threshold_value_upper_create();
extern Xv_opaque	threshold_win_threshold_value_lower_create();
#endif