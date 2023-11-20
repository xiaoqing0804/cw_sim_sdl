#ifndef __GUI_SURFACE_H__
#define __GUI_SURFACE_H__

#include "feature_all.h"
#include "gui_core_screen.h"
#include "gui_core_screen_control.h"
#include "gui_surface_box.h"

extern void gui_surface_change_order(void);
extern gui_surface_struct* gui_surface_get_surface_by_index(unsigned char index);
extern gui_surface_struct* gui_surface_get_top_surface(void);
extern gui_surface_struct* gui_surface_get_main_surface(void);
extern gui_surface_struct* gui_surface_get_vice_surface(void);
extern unsigned char gui_surface_is_at_orgin(void);
extern short gui_surface_main_get_offset_x(void);
extern short gui_surface_main_get_offset_y(void);
extern short gui_surface_vice_get_offset_x(void);
extern short gui_surface_vice_get_offset_y(void);
extern unsigned char gui_surface_is_update(void);
extern void gui_surface_clear_update_flag(void);
extern void gui_surface_force_update(void);


//屏幕数组转化---------------------------------------------------------------------
extern void gui_surface_create_main_surface(const gui_window_struct* window);
extern void gui_surface_create_vice_surface(const gui_window_struct* window);
extern void gui_surface_exit_surface(gui_surface_struct* surface);
extern void gui_surface_swap_surface(void);
extern void gui_surface_clear_main_surface(void);
extern void gui_surface_clear_vice_surface(void);
extern void gui_surface_clear_all_surface(void);
extern void gui_surface_load_surface(void);


//界面改变--------------------------------------------------------------------------
extern void gui_surface_main_surface_move(short x,short y);
extern void gui_surface_main_surface_move_to(short x,short y);
extern void gui_surface_main_surface_move_x(short x);
extern void gui_surface_main_surface_move_to_x(short x);
extern void gui_surface_main_surface_move_y(short y);
extern void gui_surface_main_surface_move_to_y(short y);
extern void gui_surface_main_surface_order(char order);
extern void gui_surface_main_surface_scale_all(float scale);
extern void gui_surface_main_surface_scale_by(float scale);
extern void gui_surface_vice_surface_move(short x,short y);
extern void gui_surface_vice_surface_move_to(short x,short y);
extern void gui_surface_vice_surface_move_x(short x);
extern void gui_surface_vice_surface_move_to_x(short x);
extern void gui_surface_vice_surface_move_y(short y);
extern void gui_surface_vice_surface_move_to_y(short y);
extern void gui_surface_vice_surface_order(char order);
extern void gui_surface_vice_surface_scale_all(float scale);
extern void gui_surface_vice_surface_scale_by(float scale);
extern void gui_surface_commit(void);

extern gui_box_struct* gui_surface_get_box(const gui_screen_struct* screen,unsigned short id);
extern gui_box_struct* gui_surface_get_box_by_id(gui_surface_struct* surface,unsigned short id);
extern gui_box_struct* gui_surface_get_box_from_main_surface(unsigned short id);
extern gui_box_struct* gui_surface_get_box_by_index(const gui_screen_struct* screen,short index);
extern gui_box_struct* gui_surface_get_box_by_type(gui_surface_struct* surface, unsigned char box_type);
extern gui_box_struct* gui_surface_get_by_position(gui_surface_struct* surface, short x, short y);
extern gui_surface_struct* gui_surface_get_surface(const gui_screen_struct* screen);
extern gui_surface_struct* gui_surface_get_surface_by_window(gui_window_struct* window);

extern void gui_surface_add_box(gui_surface_struct* surface, gui_box_struct* box);
extern void gui_surface_remove_box(gui_surface_struct* surface, gui_box_struct* box);
extern void gui_surface_take_box_to_finally(gui_surface_struct* surface, gui_box_struct* box);

#endif

