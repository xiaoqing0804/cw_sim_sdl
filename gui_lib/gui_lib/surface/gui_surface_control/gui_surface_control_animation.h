#ifndef __GUI_SURFACE_CONTROL_ANIMATION_H__
#define __GUI_SURFACE_CONTROL_ANIMATION_H__


#include "feature_all.h"
#include "picture.h"
#include "gui_core.h"
#include "gui_surface_control_base.h"
#include "gui_event_core_list.h"


//屏幕数组转化---------------------------------------------------------------------
extern void gui_surface_control_animation_create(gui_box_struct* box);
extern void gui_surface_control_animation_exit(gui_box_struct* box);

extern void gui_surface_control_animation_start(const gui_screen_struct* screen, unsigned int box_id);
extern void gui_surface_control_animation_stop(const gui_screen_struct* screen, unsigned int box_id);

extern void gui_surface_control_animation_set_frame(const gui_screen_struct* screen, unsigned int box_id, unsigned int ani_id, unsigned int frame_idx);

#endif

