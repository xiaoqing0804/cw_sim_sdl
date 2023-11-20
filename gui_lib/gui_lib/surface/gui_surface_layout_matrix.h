#ifndef __GUI_SURFACE_LAYOUT_MATRIX_H__
#define __GUI_SURFACE_LAYOUT_MATRIX_H__

#include "feature_all.h"
#include "gui_core.h"

/*******************************数据接口************************************/
extern unsigned char gui_surface_layout_matrix_click_layout(gui_surface_struct *surface);
extern short gui_surface_layout_matrix_get_count(gui_surface_struct *surface);
extern gui_box_struct *gui_surface_layout_matrix_get_item(gui_surface_struct *surface, short index);
extern short gui_surface_layout_matrix_get_item_position(gui_surface_struct *surface, gui_box_struct *find_box);
// 点击在列表的哪个条目上,返回条目编号
extern short gui_surface_layout_matrix_get_item_index(gui_surface_struct *surface, gui_touch_point_struct *touch_point);
extern gui_box_struct *gui_surface_layout_matrix_get_center_item(gui_surface_struct *surface);
extern void gui_surface_layout_matrix_move_to_center_box(gui_surface_struct *surface, gui_box_struct *center_box);
extern void gui_surface_layout_matrix_move_to_screen_center(gui_surface_struct *surface);
extern unsigned char gui_surface_layout_matrix_move_offset_step(gui_surface_struct *surface, short offset_x, short offset_y);
extern unsigned char gui_surface_layout_matrix_move_to_step(gui_surface_struct *surface, short move_to_x, short move_to_y);
extern unsigned char gui_surface_layout_matrix_move_to_screen_center_step(gui_surface_struct *surface);
extern unsigned char gui_surface_layout_matrix_move_to_center_box_step(gui_surface_struct *surface);
extern void gui_surface_layout_matrix_exit(void);
extern void gui_surface_layout_matrix_stop_timer(void);
extern unsigned char gui_surface_layout_matrix_timer_running(void);

/*******************************操作接口************************************/
// 根据排版类型，进行排版
extern void gui_surface_layout_matrix_arrange(gui_surface_struct *surface);
// 对排版中的子元素，使用指定的偏移
extern void gui_surface_layout_matrix_offset(gui_surface_struct *surface, short layout_offset_x, short layout_offset_y);
// 对排版中的子元素，进行指定的偏移
extern void gui_surface_layout_matrix_move(gui_surface_struct *surface, short move_offset_x, short move_offset_y);
// 初始化网格
extern void gui_surface_layout_matrix_init_orgin_nets(gui_surface_struct *surface);
// 网格排版参数
extern void gui_surface_layout_matrix_init_orgin_net_size(gui_surface_struct *surface);
// 初始化网格原始位置(在放大和缩小的边缘,这里的缩放比例是1)
extern void gui_surface_layout_matrix_init_orgin_net_position(gui_surface_struct *surface);
// 提交位置偏移，提交一次图标的具体位置（当使用正中间box做位置前,需要调用一次，保证同步）
extern void gui_surface_layout_matrix_commit_position(gui_surface_struct *surface);
// 计算小模式状态下的位置（该模式都是平放，间隔和大小都一样）
extern void gui_surface_layout_matrix_calculate_small_zoom_position(gui_surface_struct *surface);
// 计算大模式状态时的位置（注意如果朝应用模式放大时，是整体放大，起点是这里，所以先要保证cache同步）
extern void gui_surface_layout_matrix_calculate_big_zoom_position(gui_surface_struct *surface);
// 计算应用模式状态时的位置（整体放大）
extern void gui_surface_layout_matrix_calculate_app_zoom_position(gui_surface_struct *surface);

/*************************进入应用模式时的定时器*************************/
extern void gui_surface_layout_matrix_entry_list(gui_surface_struct *surface);
extern void gui_surface_layout_matrix_entry_app(gui_surface_struct *surface);
extern void gui_surface_layout_matrix_entry_home_app(gui_surface_struct *surface);

/*************************大模式时的定时器*************************/

/*************************小模式时的定时器*************************/

/*************************按拨码器时单步放大缩小*************************/
extern void gui_surface_layout_matrix_app_zoom(gui_surface_struct *surface, DIRECTION_TYPE direction);
extern void gui_surface_layout_matrix_big_zoom(gui_surface_struct *surface, DIRECTION_TYPE direction);
extern void gui_surface_layout_matrix_small_zoom(gui_surface_struct *surface, DIRECTION_TYPE direction);
extern void gui_surface_layout_matrix_switch_to_item(gui_surface_struct *surface, DIRECTION_TYPE direction);

/*******************************************触摸，手指滑动时的缩放*******************************************************/
// 手指滑动结束，会找寻中间位置
extern void gui_surface_layout_matrix_touch_end(gui_surface_struct *surface);

/*******************************************触摸，手指点击*******************************************************/
extern void gui_surface_layout_matrix_touch_on_small_timer(unsigned int timer, void *param);

// 在最小状态下，点击会放大到最大模式下
extern void gui_surface_layout_matrix_touch_on_small_mode(gui_surface_struct *surface);

#endif
