
#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"
#include "data_common.h"

#include "gui_window.h"
#include "gui_surface_box_label.h"

#include "app_window_pwrloss.h"

extern char* p11_sys_get_assert(void);

enum
{
    PWRLOSS_BASE_ID = 10,

    PWRLOSS_OLED_ID,
    PWRLOSS_MOTOR_ID,
    PWRLOSS_HR_ID,
    PWRLOSS_GSENSOR_ID,
    PWRLOSS_BTAUD_ID,
    PWRLOSS_RESET_ID,
    PWRLOSS_LPOWER_ID,
    PWRLOSS_ASSERT_ID,
};

static const gui_font_struct gui_pwrloss_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "0",
};

#if (LCD_SHAPE == LCD_CIRCLE)
#define PWRLOSS_ITEMS_NUM   (9)
#define PWRLOSS_ITEMS_BEG   (1)
#else
#define PWRLOSS_ITEMS_NUM   (8)
#define PWRLOSS_ITEMS_BEG   (0)
#endif

#define ADD_LINE_ITEM(bid, idx) \
{   \
    .id = bid, \
    .type = TYPE_GUI_CONTROL_LABEL, \
    .y = ((PWRLOSS_ITEMS_BEG+idx)*LCD_SIZE_HEIGHT)/PWRLOSS_ITEMS_NUM,   \
    .width = LCD_SIZE_WIDTH,    \
    .height = LCD_SIZE_HEIGHT/PWRLOSS_ITEMS_NUM,    \
    .visible= 1,    \
    .child_num = 1, \
    .children = &gui_pwrloss_text,  \
}

static const gui_widget_struct gui_pwrloss_widgets[] =
{
    ADD_LINE_ITEM(PWRLOSS_OLED_ID, 0),
    ADD_LINE_ITEM(PWRLOSS_MOTOR_ID, 1),
    ADD_LINE_ITEM(PWRLOSS_HR_ID, 2),
    ADD_LINE_ITEM(PWRLOSS_GSENSOR_ID, 3),
    ADD_LINE_ITEM(PWRLOSS_BTAUD_ID, 4),
    ADD_LINE_ITEM(PWRLOSS_RESET_ID, 5),
    ADD_LINE_ITEM(PWRLOSS_LPOWER_ID, 6),
    ADD_LINE_ITEM(PWRLOSS_ASSERT_ID, 7),
};

const gui_screen_struct gui_screen_pwrloss =
{
	.children = gui_pwrloss_widgets,
	.child_num = countof(gui_pwrloss_widgets),
};


/*-----------------------------系统事件--------------------------------------*/
static void app_window_pwrloss_init(void *buf)
{

}

static void app_window_pwrloss_load(void *buf)
{
    gui_box_struct*  box;
    unsigned char reason[5] = {0};
    unsigned char lvd[5] = {0};
    char temp[64];

    box = gui_surface_get_box(&gui_screen_pwrloss, PWRLOSS_OLED_ID);
    if (box != NULL) {
        sprintf(temp, "lcd: %d", g_power_analysis.all[POWER_TYPE_OLED]);
        gui_surface_box_label_change_string(box, (unsigned char*)temp);
    }
    box = gui_surface_get_box(&gui_screen_pwrloss, PWRLOSS_MOTOR_ID);
    if (box != NULL) {
        sprintf(temp, "motor: %d", g_power_analysis.all[POWER_TYPE_MOTOR]);
        gui_surface_box_label_change_string(box, (unsigned char*)temp);
    }
    box = gui_surface_get_box(&gui_screen_pwrloss, PWRLOSS_HR_ID);
    if (box != NULL) {
        sprintf(temp, "hr: %d", g_power_analysis.all[POWER_TYPE_HR]);
        gui_surface_box_label_change_string(box, (unsigned char*)temp);
    }
    box = gui_surface_get_box(&gui_screen_pwrloss, PWRLOSS_GSENSOR_ID);
    if (box != NULL) {
        sprintf(temp, "gsensor: %d", g_power_analysis.all[POWER_TYPE_GSENSOR]);
        gui_surface_box_label_change_string(box, (unsigned char*)temp);
    }
    box = gui_surface_get_box(&gui_screen_pwrloss, PWRLOSS_BTAUD_ID);
    if (box != NULL) {
        sprintf(temp, "btaud: %d", g_power_analysis.all[POWER_TYPE_BTAUD]);
        gui_surface_box_label_change_string(box, (unsigned char*)temp);
    }

    box = gui_surface_get_box(&gui_screen_pwrloss, PWRLOSS_RESET_ID);
    if (box != NULL) {
        syscfg_read(CFG_BSP_DEBUG_REASON, reason, 5);
        sprintf(temp, "%x:%x %x %x %x", reason[4], reason[0], reason[1], reason[2], reason[3]);
        gui_surface_box_label_change_string(box, (unsigned char*)temp);
    }
    box = gui_surface_get_box(&gui_screen_pwrloss, PWRLOSS_LPOWER_ID);
    if (box != NULL) {
        syscfg_read(CFG_BSP_DEBUG_LVD_REASON, lvd, 5);
        sprintf(temp, "%x:%x %x %x %x", lvd[4], lvd[0], lvd[1], lvd[2], lvd[3]);
        gui_surface_box_label_change_string(box, (unsigned char*)temp);
    }
    box = gui_surface_get_box(&gui_screen_pwrloss, PWRLOSS_ASSERT_ID);
    if (box != NULL) {
        gui_surface_box_label_change_string(box, (unsigned char*)p11_sys_get_assert());
    }

    gui_surface_commit();
}


static void app_window_pwrloss_entry(void *buf)
{
    apptst_factory_reset();
}


static void app_window_pwrloss_exit()
{
}

static void app_window_pwrloss_destroy()
{

}

/*-----------------------------配置--------------------------------------*/
const gui_window_struct app_window_pwrloss =
{
	.screen = &gui_screen_pwrloss,

	.init = app_window_pwrloss_init,
	.load = app_window_pwrloss_load,
	.entry = app_window_pwrloss_entry,
	.exit = app_window_pwrloss_exit,
	.destroy = app_window_pwrloss_destroy,
};




