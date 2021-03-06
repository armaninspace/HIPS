#ifndef	image_reg_HEADER
#define	image_reg_HEADER

/*
 * image_reg_ui.h - User interface object and function declarations.
 * This file was generated by `gxv' from `image_reg.G'.
 * DO NOT EDIT BY HAND.
 */

extern Attr_attribute	INSTANCE;


typedef struct {
	Xv_opaque	win;
	Xv_opaque	controls;
	Xv_opaque	text_ref_frame;
	Xv_opaque	but_save_image_frame;
	Xv_opaque	msg_line_matching;
	Xv_opaque	msg_manual;
	Xv_opaque	msg_line1;
	Xv_opaque	msg_line2;
	Xv_opaque	but_line_scale;
	Xv_opaque	but_scale;
	Xv_opaque	text_scale_factor;
	Xv_opaque	msg_line4;
	Xv_opaque	msg_line5;
	Xv_opaque	but_up;
	Xv_opaque	but_point_translate;
	Xv_opaque	but_left;
	Xv_opaque	but_right;
	Xv_opaque	set_trans_pixel_amount;
	Xv_opaque	msg_translate;
	Xv_opaque	but_down;
	Xv_opaque	msg_line3;
	Xv_opaque	msg_line6;
	Xv_opaque	but_line_rotate;
	Xv_opaque	but_rotate;
	Xv_opaque	text_rotation_degrees;
	Xv_opaque	but_close;
} image_reg_win_objects;

extern image_reg_win_objects	*image_reg_win_objects_initialize();

extern Xv_opaque	image_reg_win_win_create();
extern Xv_opaque	image_reg_win_controls_create();
extern Xv_opaque	image_reg_win_text_ref_frame_create();
extern Xv_opaque	image_reg_win_but_save_image_frame_create();
extern Xv_opaque	image_reg_win_msg_line_matching_create();
extern Xv_opaque	image_reg_win_msg_manual_create();
extern Xv_opaque	image_reg_win_msg_line1_create();
extern Xv_opaque	image_reg_win_msg_line2_create();
extern Xv_opaque	image_reg_win_but_line_scale_create();
extern Xv_opaque	image_reg_win_but_scale_create();
extern Xv_opaque	image_reg_win_text_scale_factor_create();
extern Xv_opaque	image_reg_win_msg_line4_create();
extern Xv_opaque	image_reg_win_msg_line5_create();
extern Xv_opaque	image_reg_win_but_up_create();
extern Xv_opaque	image_reg_win_but_point_translate_create();
extern Xv_opaque	image_reg_win_but_left_create();
extern Xv_opaque	image_reg_win_but_right_create();
extern Xv_opaque	image_reg_win_set_trans_pixel_amount_create();
extern Xv_opaque	image_reg_win_msg_translate_create();
extern Xv_opaque	image_reg_win_but_down_create();
extern Xv_opaque	image_reg_win_msg_line3_create();
extern Xv_opaque	image_reg_win_msg_line6_create();
extern Xv_opaque	image_reg_win_but_line_rotate_create();
extern Xv_opaque	image_reg_win_but_rotate_create();
extern Xv_opaque	image_reg_win_text_rotation_degrees_create();
extern Xv_opaque	image_reg_win_but_close_create();

typedef struct {
	Xv_opaque	pop_ref_frame;
	Xv_opaque	canv_ref_frame;
} image_reg_pop_ref_frame_objects;

extern image_reg_pop_ref_frame_objects	*image_reg_pop_ref_frame_objects_initialize();

extern Xv_opaque	image_reg_pop_ref_frame_pop_ref_frame_create();
extern Xv_opaque	image_reg_pop_ref_frame_canv_ref_frame_create();
#endif
