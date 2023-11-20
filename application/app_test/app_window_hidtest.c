
#include "sys_init.h"
#include "data_common.h"
#include "bsp_includes.h"

#include "bt_ble.h"
#include "ble_hid.h"

#include "gui_surface_box_label.h"
#include "data_receive_package.h"
#include "gui_surface_box_image.h"

#include "app_window_hidtest.h"

static const gui_font_struct gui_hidtest_up =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_MEDIUM,
	.value_type = GUI_FONT_VALUE_TYPE_STRING,
	.value.string = "up",
};

static const gui_font_struct gui_hidtest_dn =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_MEDIUM,
	.value_type = GUI_FONT_VALUE_TYPE_STRING,
	.value.string = "down",
};

static const gui_font_struct gui_hidtest_left =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_MEDIUM,
	.value_type = GUI_FONT_VALUE_TYPE_STRING,
	.value.string = "left",
};

static const gui_font_struct gui_hidtest_right =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_MEDIUM,
	.value_type = GUI_FONT_VALUE_TYPE_STRING,
	.value.string = "right",
};

static const gui_font_struct gui_hidtest_center =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_MEDIUM,
	.value_type = GUI_FONT_VALUE_TYPE_STRING,
	.value.string = "center",
};

static const gui_widget_struct gui_widget_hidtest[] =
{
	{
		.id = 1,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 0,
		.y = 0,
		.width = LCD_SIZE_WIDTH,
		.height = LCD_SIZE_HEIGHT/3,
		.visible= 1,
		.child_num = 1,
		.children = &gui_hidtest_up,
	},
    {
        .id = 2,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 0,
        .y = LCD_SIZE_HEIGHT*2/3,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT/3,
        .visible= 1,
        .child_num = 1,
        .children = &gui_hidtest_dn,
    },
    {
        .id = 3,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 0,
        .y = LCD_SIZE_HEIGHT/3,
        .width = LCD_SIZE_WIDTH/3,
        .height = LCD_SIZE_HEIGHT/3,
        .visible= 1,
        .child_num = 1,
        .children = &gui_hidtest_left,
    },
    {
        .id = 4,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = LCD_SIZE_WIDTH*2/3,
        .y = LCD_SIZE_HEIGHT/3,
        .width = LCD_SIZE_WIDTH/3,
        .height = LCD_SIZE_HEIGHT/3,
        .visible= 1,
        .child_num = 1,
        .children = &gui_hidtest_right,
    },
    {
        .id = 5,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = LCD_SIZE_WIDTH/3,
        .y = LCD_SIZE_HEIGHT/3,
        .width = LCD_SIZE_WIDTH/3,
        .height = LCD_SIZE_HEIGHT/3,
        .visible= 1,
        .child_num = 1,
        .children = &gui_hidtest_center,
    },
};


const gui_screen_struct gui_screen_hidtest =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.space_x = 0,
	.space_y = 0,
	.order = 0,
	.children = gui_widget_hidtest,
	.child_num = countof(gui_widget_hidtest),
};

static void app_window_hidtest_init(void *buf)
{

}

static void app_window_hidtest_load(void *buf)
{
}


static void app_window_hidtest_entry(void *buf)
{

}


static void app_window_hidtest_exit()
{

}

static void app_window_hidtest_destroy()
{

}



/*-----------------------------��Ӧ�¼�--------------------------------------*/
static void app_window_hidtest_click_handler(gui_click_struct *event)
{
    switch(event->id) {
        case 1:
            bt_ble_hid_mouse_drag_up();
            break;
        case 2:
            bt_ble_hid_mouse_drag_down();
            break;
        case 3:
            bt_ble_hid_mouse_drag_left();
            break;
        case 4:
            bt_ble_hid_mouse_drag_right();
            break;
        case 5:
            bt_ble_hid_mouse_double_click();
            break;
    }
}

static const gui_touch_event_struct gui_hidtest_touch_events[] =
{
    {.id = 1, .click = app_window_hidtest_click_handler},
    {.id = 2, .click = app_window_hidtest_click_handler},
    {.id = 3, .click = app_window_hidtest_click_handler},
    {.id = 4, .click = app_window_hidtest_click_handler},
    {.id = 5, .click = app_window_hidtest_click_handler},
};


/*-----------------------------����--------------------------------------*/

const gui_window_struct app_window_hidtest =
{
	.screen = &gui_screen_hidtest,
	.init = app_window_hidtest_init,
	.load = app_window_hidtest_load,
	.entry = app_window_hidtest_entry,
	.exit = app_window_hidtest_exit,
	.destroy = app_window_hidtest_destroy,

    .touch_event_num = countof(gui_hidtest_touch_events),
    .touch_events = gui_hidtest_touch_events,
};



