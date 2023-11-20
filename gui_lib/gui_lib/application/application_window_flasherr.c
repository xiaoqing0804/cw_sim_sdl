#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "data_common.h"
#include "data_manager_flash.h"
#include "OTA.h"
#include "app_task_main.h"

#include "gui_window.h"

#include "application_window_flasherr.h"

static unsigned char g_nor_res_check_err;
static unsigned char g_inter_res_check_err;

static const gui_image_struct gui_flasherr_image = 
{
	.type  = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .data  = &pic_ota_info,
};

static const gui_image_struct gui_flasherr_image1 = 
{
	.type  = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_RIGHT , GUI_ALIGN_TOP),
    .data  = &pic_ota_num_1_info,
};
static const gui_image_struct gui_flasherr_image2 = 
{
	.type  = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT , GUI_ALIGN_TOP),
    .data  = &pic_ota_num_2_info,
};

static const gui_widget_struct gui_flasherr_widget[] =
{
	{
		.type = TYPE_GUI_CONTROL_IMAGE,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
		.visible= 1,
        .child_num = 1,
        .children = &gui_flasherr_image,
	},
	{
        .id = 1,
		.type = TYPE_GUI_CONTROL_IMAGE,
        .x = 0,
        .y = LCD_SIZE_HEIGHT/4,
        .width = LCD_SIZE_HALF_WIDTH,
        .height = LCD_SIZE_HEIGHT/4,
		.visible= 0,
        .child_num = 1,
        .children = &gui_flasherr_image1,
	},
	{
        .id = 2,
		.type = TYPE_GUI_CONTROL_IMAGE,
        .x = LCD_SIZE_HALF_WIDTH,
        .y = LCD_SIZE_HEIGHT/4,
        .width = LCD_SIZE_HALF_WIDTH,
        .height = LCD_SIZE_HEIGHT/4,
		.visible= 0,
        .child_num = 1,
        .children = &gui_flasherr_image2,
	},
};

static const gui_screen_struct gui_screen_flasherr =
{
	.children = gui_flasherr_widget,
	.child_num = countof(gui_flasherr_widget),
};


/*-----------------------------系统事件--------------------------------------*/
static void application_window_flasherr_init(void *buf)
{
}

static void application_window_flasherr_load(void *buf)
{
    if (g_nor_res_check_err) {
        gui_box_struct* box = gui_surface_get_box(&gui_screen_flasherr, 1);
        if (box != NULL) {
            box->visible = 1;
        }
    }
    if (g_inter_res_check_err) {
        gui_box_struct* box = gui_surface_get_box(&gui_screen_flasherr, 2);
        if (box != NULL) {
            box->visible = 1;
        }
    }
}

static void application_window_flasherr_entry(void *buf)
{
}


static void application_window_flasherr_exit()
{
}

static void application_window_flasherr_destroy()
{
}


/*-----------------------------配置--------------------------------------*/
static const app_window_event_struct application_window_flasherr_static_events[] =
{
	{.id = EVENT_ALL,	.handler = NULL	},
    {.id = EVENT_BL_TIMEOUT},       // 不允许灭屏 ...
};

static const gui_window_config_struct application_window_flasherr_config =
{
    .disable_scale = 1,
    .disable_go_home = 1,
    .forbid_key_back = 1,
    .forbid_gesture_back = 1,
};


const gui_window_struct application_window_flasherr =
{
	.screen = &gui_screen_flasherr,
	.config = &application_window_flasherr_config,

	.init = application_window_flasherr_init,
	.load = application_window_flasherr_load,
	.entry = application_window_flasherr_entry,
	.exit = application_window_flasherr_exit,
	.destroy = application_window_flasherr_destroy,

	.event_num = countof(application_window_flasherr_static_events),
	.events = application_window_flasherr_static_events,
};


/// @brief : 检查UI资源包是否正确 
/// @param  
/// @return : 0 - ok; other - err!!
unsigned int application_flashcrc_check_err(void)
{
    unsigned short nor_res_crc = 0, inter_res_crc = 0;

    data_manager_flash_get_crc(&nor_res_crc, &inter_res_crc);
    g_nor_res_check_err = 0;
    g_inter_res_check_err = 0;

#if (TCFG_NOR_RES && TCFG_NOR_RES_INTER)
    if (nor_res_crc != PIC_CRC16) {
        g_nor_res_check_err = 1;
    }
    if (inter_res_crc != INTER_PIC_CRC16) {
        g_inter_res_check_err = 1;
    }
#else
    if (nor_res_crc != PIC_CRC16) {
        g_nor_res_check_err = 1;
    }
#endif
    return (g_nor_res_check_err + g_nor_res_check_err);
}


