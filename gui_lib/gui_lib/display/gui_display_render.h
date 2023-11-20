#ifndef __GUI_DISPLAY_RENDER_H__
#define __GUI_DISPLAY_RENDER_H__

#include "feature_all.h"
#include "gui_surface.h"
#include "gui_surface_box.h"

typedef struct _gui_render_struct gui_render_struct;
struct _gui_render_struct
{
	unsigned char type;
	unsigned char rotate;
	unsigned char alpha; // 0~255

	unsigned char cache : 1;

	char anchor_x;	 //使用宏 ANCHOR_VALUE
	char anchor_y;	 //使用宏 ANCHOR_VALUE
	short surface_x;

	short x;
	short y;
	short width;
	short height;

	short clip_left;
	short clip_top;
	short clip_right;
	short clip_bottom;

	float scale;
	unsigned int value;

	void *data;
	void *window_owner;

	gui_render_struct *next;
};

typedef struct
{
	unsigned short index;
	gui_render_struct* buff;
}gui_render_list_struct;

typedef struct
{
	unsigned char update;
	unsigned char swap;
	unsigned short count;
	gui_render_list_struct* list;
	gui_render_struct* frist;
	gui_render_struct* end;
}gui_frame_struct;


extern void gui_display_render_init(void);
extern void gui_display_render_deinit(void);
extern gui_render_struct* gui_display_render_frist(void);

extern void gui_display_render_add(gui_scale_struct *gui_scale);
extern void gui_display_render_add_compose(gui_scale_struct *gui_scale);
extern void gui_display_render_clear(void);

#if GUI_RENDER_BUFFER_TOTAL_SUPPORT >= 3
extern void gui_display_render_init_data(void);
extern void gui_display_render_switch_to_node(void);
extern void gui_display_render_switch_to_render(void);
#endif

extern void gui_display_render_clear_cache_images(gui_surface_struct* surface);

#endif

