
#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"
#include "data_common.h"

#include "gui_window.h"
#include "gui_surface_box_label.h"

#include "app_window_factory_worker.h"
#include "app_window_stand_alone.h"

#define GUI_FACT_RPT_ITEM_H    40

static const gui_font_struct gui_fact_report_text_title =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "测试模式选择",
};


static const gui_widget_struct gui_fact_report_widgets[] =
{
	{
		.type = TYPE_GUI_CONTROL_LABEL,
		.y = 10,
		.width = LCD_SIZE_WIDTH,
		.height = 30,
		.visible= 1,
        .child_num = 1,
        .children = &gui_fact_report_text_title,
	},
};

static const gui_layout_list_struct gui_fact_report_layout =
{
	.total = 0,
	.height = 0,
	.row_height = GUI_FACT_RPT_ITEM_H,

	.top = 40,
	.bottom = 0,
	.space = 10,
	.scroll = 1,
};

static const gui_screen_struct gui_screen_fact_report =
{
    .type = TYPE_GUI_LAYOUT_LIST,
    .children = gui_fact_report_widgets,
    .child_num = countof(gui_fact_report_widgets),
    .layout_config = &gui_fact_report_layout,
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
static gui_font_struct gui_fact_rpt_item_name =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
	.y = 0,
	.width = LCD_SIZE_WIDTH,
	.height = GUI_FACT_RPT_ITEM_H,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "",
};

// static const gui_font_struct gui_fact_rpt_item_pass =
// {
// 	.type = TYPE_GUI_DRAW_TEXT,
//     .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_RIGHT, GUI_ALIGN_VCENTER),
// 	.x = 10,
// 	.y = 0,
//     .width = LCD_SIZE_WIDTH - 20,
//     .height = GUI_FACT_RPT_ITEM_H,
//     .color = COLOR_RGB(0, 255, 0),
//     .size = SYS_FONT_MEDIUM,
//     .value_type = GUI_FONT_VALUE_TYPE_STRING,
//     .value.string = "pass",
// };

// static const gui_font_struct gui_fact_rpt_item_fail =
// {
// 	.type = TYPE_GUI_DRAW_TEXT,
//     .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_RIGHT, GUI_ALIGN_VCENTER),
// 	.x = 10,
// 	.y = 0,
//     .width = LCD_SIZE_WIDTH - 20,
//     .height = GUI_FACT_RPT_ITEM_H,
//     .color = COLOR_RGB(255, 0, 0),
//     .size = SYS_FONT_MEDIUM,
//     .value_type = GUI_FONT_VALUE_TYPE_STRING,
//     .value.string = "fail",
// };


static gui_mix_struct gui_fact_rpt_item[] =
{
	{
		.data = &gui_fact_rpt_item_name,
	},
    // {
    //     .data = &gui_fact_rpt_item_pass,
    // },
};

static const gui_widget_struct gui_fact_rpt_widget_temp = {
        .id = 20,
        .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
        .width = LCD_SIZE_WIDTH,
        .height = GUI_FACT_RPT_ITEM_H,
        .visible= 1,
        .child_num = countof(gui_fact_rpt_item),
        .children = gui_fact_rpt_item
};

static void app_window_fact_rpt_refresh(void)
{
    gui_box_struct* box;
    factory_test_item_struct* fact_item;
    unsigned int idx, count = factory_test_get_count();
    unsigned short flags = factory_test_get_pass_flags();
    gui_surface_struct* surface = gui_surface_get_surface(&gui_screen_fact_report);

    SYS_DEBUG("app: factory_report, count=%d", count);

	gui_surface_layout_listview_dynamic_init(surface);
    if (surface != NULL) {
        for (idx=0; idx<count; idx++) {
            box =gui_surface_layout_listview_dynamic_get_box(surface, idx+10); //gui_surface_cache_add_box();
            fact_item = factory_test_get_item(idx);
            if (box != NULL && fact_item != NULL) {
                box->id = idx+10;
                box->type = TYPE_GUI_CONTROL_LAYOUT_ITEM;
                box->widget = &gui_fact_rpt_widget_temp;
                box->x = 0;
                box->y = 0;
                box->width = LCD_SIZE_WIDTH;
                box->height = GUI_FACT_RPT_ITEM_H;
                box->visible = 1;

                gui_fact_rpt_item_name.value.string = fact_item->name;
				gui_surface_layout_listview_dynamic_add_item(surface,box);
            }
        }

		gui_surface_layout_listview_dynamic_finish(surface);
    }

}



/*-----------------------------系统事件--------------------------------------*/
static void app_window_fact_report_init(void *buf)
{
}

static void app_window_fact_report_load(void)
{
	gui_surface_struct* surface = gui_surface_get_surface(&gui_screen_fact_report);
	gui_surface_layout_listview_dynamic_create(surface,app_window_fact_rpt_refresh);
}


static void app_window_fact_report_entry(void)
{
}


static void app_window_fact_report_exit()
{
}

static void app_window_fact_report_destroy()
{

}

static void app_window_stand_alone_touch_event_click_on_layout_item(gui_click_layout_struct *event)
{
	SYS_DEBUG("app_window_test1_touch_event_click_on_layout_item x=%d y=%d index=%d",event->x,event->y,event->id);
    unsigned char stand_alone = event->id-10;

    application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH,&app_window_factory_worker,&stand_alone);

}

/*-----------------------------配置--------------------------------------*/
static const gui_window_config_struct app_window_fact_report_config =
{
	.entry_back_to_destory = 1,
};


const gui_window_struct app_window_stand_alone =
{
	.screen = &gui_screen_fact_report,
	.config = &app_window_fact_report_config,

    .click_on_layout_item = app_window_stand_alone_touch_event_click_on_layout_item,

	.init = app_window_fact_report_init,
	.load = app_window_fact_report_load,
	.entry = app_window_fact_report_entry,
	.exit = app_window_fact_report_exit,
	.destroy = app_window_fact_report_destroy,
};




