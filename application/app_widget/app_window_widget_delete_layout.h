#ifndef __APP_WINDOW_WIDGET_DELETE_LAYOUT_H__
#define __APP_WINDOW_WIDGET_DELETE_LAYOUT_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

#define WND_WIDGET_DELETE_LIST_ITEM_H (100)

typedef enum
{
    WIDGET_DELETE_LAYOUT_ID_NONE,
    WIDGET_ITEM_DEL_ICON,
    WIDGET_ITEM_ADD_ICON,
    WIDGET_ITEM_APP_ICON,
    WIDGET_ITEM_APP_NAME,
    WIDGET_ITEM_MUP_ICON,
};

extern short g_widget_delete_layout_x_left;
extern short g_widget_delete_layout_x_right;

extern gui_font_struct gui_widget_delete_app_name;
extern gui_image_struct gui_widget_delete_app_icon;
extern const gui_widget_struct gui_widget_delete_info;
extern const gui_screen_struct gui_screen_widget_delete;

#endif
