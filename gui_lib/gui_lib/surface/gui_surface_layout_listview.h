#ifndef __GUI_SURFACE_LAYOUT_LISTVIEW_H__
#define __GUI_SURFACE_LAYOUT_LISTVIEW_H__

#include "feature_all.h"
#include "gui_core.h"

extern unsigned char gui_surface_layout_listview_is_delay_create_widget(const gui_screen_struct* screen,gui_widget_struct* widget);
extern short gui_surface_layout_listview_get_item_id(gui_surface_struct* surface,short index);
extern gui_box_struct* gui_surface_layout_listview_get_item(gui_surface_struct* surface,short index);
extern short gui_surface_layout_listview_get_item_index(gui_surface_struct* surface,gui_touch_point_struct* touch_point);

/*******************************操作接口************************************/

//根据排版类型，进行排版
extern void gui_surface_layout_listview_arrange(gui_surface_struct* surface);

//对排版中的子元素，使用指定的偏移
extern void gui_surface_layout_listview_offset(gui_surface_struct* surface,short layout_offset_x,short layout_offset_y);

//对排版中的子元素，进行指定的偏移
extern void gui_surface_layout_listview_move(gui_surface_struct* surface,short offset_x,short offset_y);

extern gui_box_struct* gui_surface_layout_listview_dynamic_get_box(gui_surface_struct* surface, short id);
extern void gui_surface_layout_listview_dynamic_init(gui_surface_struct* surface);
extern void gui_surface_layout_listview_dynamic_clear_delay(gui_surface_struct *surface);
extern unsigned char gui_surface_layout_listview_dynamic_exist(gui_surface_struct* surface, gui_box_struct* box);
extern void gui_surface_layout_listview_dynamic_add_item(gui_surface_struct* surface,gui_box_struct* box);
extern void gui_surface_layout_transverse_listview_dynamic_add_item(gui_surface_struct* surface,gui_box_struct* box);//横向创建
extern void gui_surface_layout_listview_dynamic_finish(gui_surface_struct* surface);
extern void gui_surface_layout_listview_dynamic_create(gui_surface_struct* surface,void (*refresh)(void));
extern void gui_surface_layout_listview_clear_item_box(gui_surface_struct* surface);
extern void gui_surface_layout_listview_switch_to_item(gui_surface_struct* surface, DIRECTION_TYPE direction);

extern void gui_surface_layout_listview_updata_arrange(gui_surface_struct* surface);

#endif
