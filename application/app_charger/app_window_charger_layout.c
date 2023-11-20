#include "app_charger/app_window_charger.h"
#include "app_charger/app_window_charger_ui.h"
#include "app_charger/app_window_charger_layout.h"


#include "app_config.h"

#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "data_common.h"

#include "gui_window.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"

#include "gui_surface_control_base.h"
#include "app_ota/app_window_ota.h"

#include "app_main/app_window_main_watchface_update.h"

#if defined(TCFG_APP_PC_EN)&&TCFG_APP_PC_EN
extern void app_usb_start_req(void);            // start usb mode
extern void app_usb_stop_req(void);             // stop usb mode
extern bool app_usb_running(void);
extern int  pc_app_check(void);

static void app_window_charger_usb_update(unsigned char onoff);


static const gui_image_struct gui_usb_image =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT, GUI_ALIGN_VCENTER),
    .data = &pic_progress_bar_shut_info,
};

static const gui_font_struct gui_usb_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_RIGHT, GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "USB:",
};
#endif

const gui_picture_struct gui_charger_up_bat_image_list[] =
    {
        &pic_charger_bg_01_info,
        &pic_charger_bg_02_info,
        &pic_charger_bg_03_info,
        &pic_charger_bg_04_info,
        &pic_charger_bg_05_info,
};

const gui_batt_icon_struct gui_charger_up_bat_image =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .id = 0,
        .x = 0,
        .y = 0,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .pics_num = countof(gui_charger_up_bat_image_list),
        .gui_pics = gui_charger_up_bat_image_list,
};


static const gui_font_struct gui_charger_batt_label_text =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .color = COLOR_RGB(21, 232, 150),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING,
        .value.string = "100%",
};

static const gui_control_digital_struct gui_charger_batt_label =
    {
        .value_type = GUI_DIGITAL_VALUE_TYPE_FONT,
        .value.font = &gui_charger_batt_label_text,
};

static const gui_font_struct gui_text_charger_txt =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .id = 0,
        .x = 0,
        .y = 0,
        .anchor_x = 0,
        .anchor_y = 0,
        .max_width = 0,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .auto_wrap = 0,
        .color = COLOR_RGB(21, 232, 150),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value.string_id = STRING_CHARGING,
};

static const gui_image_struct gui_charger_icon_image =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .data = &pic_charger_logo_info,
};

static const gui_widget_struct gui_charger_widget[] =
{
        {
            .id = CHARGER_LAYOUT_UP_BATT,
            .type = TYPE_GUI_CONTROL_BATT_ICON,
            .width = LCD_SIZE_WIDTH,
            .height = LCD_SIZE_HEIGHT,
            .visible = 1,
            .clip = 0,
            .child_num = 1,
            .children = &gui_charger_up_bat_image,
        },

        {
            // data-batt
            .id = CHRAGER_LAYOUT_BATT_LABEL,
            .type = TYPE_GUI_CONTROL_BATT_LABEL,
            .x = 0,
            .y = 215,
            .width = LCD_SIZE_WIDTH,
            .height = 40,
            .visible = 1,
            .child_num = 1,
            .children = &gui_charger_batt_label,
        },

        // icon
        {
            .id = CHRAGER_LAYOUT_ICON,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = 0,
            .y = 159,
            .width = LCD_SIZE_WIDTH,
            .height = 33,
            .child_num = 1,
            .visible = 1,
            .children = &gui_charger_icon_image,
        },

        {
            .id = CHRAGER_LAYOUT_TXT,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 0,
            .y = 372,
            .width = LCD_SIZE_WIDTH,
            .height = 37,
            .visible = 1,
            .child_num = 1,
            .children = &gui_text_charger_txt,
        },

#if defined(TCFG_APP_PC_EN)&&TCFG_APP_PC_EN
    {
        .id = CHRAGER_USB_TXT_ID,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 0,
        .y = LCD_SIZE_HEIGHT-40,
        .width = LCD_SIZE_WIDTH/2,
        .height = 30,
        .child_num = 1,
        .children = &gui_usb_text,
    },
    {
        .id = CHRAGER_USB_ID,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = LCD_SIZE_WIDTH/2,
        .y = LCD_SIZE_HEIGHT-40,
        .width = LCD_SIZE_WIDTH/2,
        .height = 30,
        .child_num = 1,
        .children = &gui_usb_image,
    },
#endif
};

const gui_screen_struct gui_charger_screen =
{
	.children = gui_charger_widget,
	.child_num = countof(gui_charger_widget),
};




