#include "debug_info.h"
#include "bsp_includes.h"
#include "os_mem.h"
#include "data_common.h"
#include "data_manager_qr_info.h"
#include "storage_qr_info.h"
#include "application_config_app_info.h"

#include "gui_window.h"

#include "app_window_qr_card_list.h"
#include "app_window_qr_card_list_ui.h"
#include "app_window_qr_card_list_layout.h"


#if defined(GUI_QR_INFO_SUPPORT)&&GUI_QR_INFO_SUPPORT

static gui_font_struct g_gui_qr_card_list_item_text =     // must with static!
{
    .type = TYPE_GUI_DRAW_TEXT,
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT , GUI_ALIGN_VCENTER),
#if (LCD_SHAPE == LCD_CIRCLE)
    .x = 160,
#else
    .x = 100,
#endif
    .width = LCD_SIZE_WIDTH - 120,
    .height = QR_CARD_LIST_ITEM_HEIGHT,
    .scroll = 1,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
};


static gui_image_struct g_gui_qr_card_list_item_pic =     // must with static!
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_NONE , GUI_ALIGN_VCENTER),
#if (LCD_SHAPE == LCD_CIRCLE)
	.x = 60,
#else
	.x = 30,
#endif
	.y = (QR_CARD_LIST_ITEM_HEIGHT-80)/2,
 	.data = NULL,
};

/*
static const gui_image_struct gui_qr_card_bg =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.x = 280,
	.y = 0,
    .data = &pic_app_set_bg_info,
};*/

static const gui_mix_struct gui_qr_card_list_item[] =
{
   {.data = &g_gui_qr_card_list_item_text  },
   {.data = &g_gui_qr_card_list_item_pic   },
   //{.data = &gui_qr_card_bg  },
};

static const gui_widget_struct gui_qr_card_list_info = {
	   .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
	   .width = LCD_SIZE_WIDTH,
	   .height = QR_CARD_LIST_ITEM_HEIGHT,
	   .visible= 1,
       .clip = 1,
	   .child_num = countof(gui_qr_card_list_item),
	   .children = gui_qr_card_list_item
};

void app_window_qr_card_list_list_refresh(void)
{
    qr_code_info_struct* qr_info;
    gui_surface_struct* surface;
    gui_box_struct*     box;
	picture_info_struct*   pic;

    unsigned int box_idx;
    unsigned int icon_num;

    qr_info = (qr_code_info_struct*)os_mem_alloc(RAM_TYPE_DATA_ON, sizeof(qr_code_info_struct));
    if (qr_info == NULL)    return;

    icon_num = storage_qr_get_count();
    surface = gui_surface_get_surface(&gui_screen_qr_card_list);
	gui_box_struct* qr_no = gui_surface_get_box(&gui_screen_qr_card_list, QR_CARD_LIST_NO);
    if (surface != NULL) {
        gui_surface_layout_listview_dynamic_init(surface);
		if(icon_num > 0) {
			gui_surface_box_change_visible(qr_no,0);
		}
		else {
			gui_surface_box_change_visible(qr_no,1);
		}
		for (box_idx=0; box_idx<icon_num; box_idx++) {
            box = gui_surface_layout_listview_dynamic_get_box(surface, box_idx + QR_CARD_LIST_BASE_ID);
            if ((box != NULL)) {
                storage_qr_get(box_idx, qr_info);
                box->id = box_idx + QR_CARD_LIST_BASE_ID;
                box->type = TYPE_GUI_CONTROL_LAYOUT_ITEM;
                box->widget = &gui_qr_card_list_info;
                box->x = gui_qr_card_list_info.x;
                box->y = gui_qr_card_list_info.y;
                box->width = gui_qr_card_list_info.width;
                box->height = gui_qr_card_list_info.height;
                box->visible = gui_qr_card_list_info.visible;
                box->value = qr_info->type;

				pic = app_qr_card_get_picture_by_type(qr_info->type);
				g_gui_qr_card_list_item_pic.data = pic;

				SYS_DEBUG("app_window_qr_card_list_list_refresh =%s", qr_info->name);
				g_gui_qr_card_list_item_text.value.string = qr_info->name;

                gui_surface_layout_listview_dynamic_add_item(surface,box);
            }
        }
		gui_surface_layout_listview_dynamic_finish(surface);
    }
    os_mem_free(qr_info);
}

void app_window_qr_card_storage_reflash_handler(void* buf)
{
    gui_surface_struct* surface = gui_surface_get_surface(&gui_screen_qr_card_list);
    if (surface != NULL) {
        gui_surface_layout_listview_clear_item_box(surface);
        app_window_qr_card_list_list_refresh();
        gui_surface_commit();
    }
}

#endif
