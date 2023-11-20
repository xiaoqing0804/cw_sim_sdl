

#include "feature_all.h"
#include "bsp_includes.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_receive_package.h"
#include "data_manager_message.h"

#include "data_manager_contact.h"

#include "srv_call.h"

#include "application.h"
#include "gui_core_all.h"

#include "app_window_call_clog.h"
#include "app_window_call_clog_ui.h"
#include "app_window_call_clog_layout.h"

///////////////////////////////////////////////////////////////////////////////////////////
static gui_image_struct gui_call_clog_item_pic =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.x = 155,
	.y = 65,
};

static gui_image_struct gui_call_clog_item_head_portrait =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.x = 50,
	.y = 0,
	.data = &pic_head_portrait_info,
};


static gui_font_struct gui_call_clog_item_number =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.x = 166,
	.y = 0,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_SMALL, // SYS_FONT_NUMBER_20,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "1234567890",
};

static gui_font_struct gui_call_clog_item_time =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.x = 200,
	.y = 60,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_XSMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "1234567890",
};


static const gui_mix_struct gui_call_clog_item[] =
{
	{
		.data = &gui_call_clog_item_pic,
	},
	{
		.data = &gui_call_clog_item_number,
	},
    {
        .data = &gui_call_clog_item_time,
    },
    {
      .data = &gui_call_clog_item_head_portrait,
    },
};

static gui_widget_struct gui_call_clog_widget_temp = {
        .id = 20,
        .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
        .width = LCD_SIZE_WIDTH,
        .height = GUI_CALL_CLOG_ITEM_H,
        .visible= 1,
        .child_num = countof(gui_call_clog_item),
        .children = gui_call_clog_item
};


static const gui_font_struct gui_call_clog_txt =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .size = SYS_FONT_MEDIUM,
    .auto_wrap = 1,
    .width = LCD_SIZE_WIDTH,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_ID_CALLLOG,
};

static const gui_mix_struct gui_call_clog_txt_widget[] =
{
	{
		.data = &gui_call_clog_txt,
	},
};

static gui_widget_struct gui_call_clog_widget_txt = {
        .id = 21,
        .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
        .width = LCD_SIZE_WIDTH,
        .height = GUI_CALL_CLOG_ITEM_H,
        .visible= 1,
        .child_num = countof(gui_call_clog_txt_widget),
        .children = gui_call_clog_txt_widget
};

static void app_window_call_clog_list_init_box_data(gui_box_struct* box, unsigned int idx)
{
    Get_Index_Contact_t  index_contact;
    const picture_info_struct* pic;

    if (box->id == 0)
    {
        box->id = idx+CALL_DIAL_CLOG_BASE_ID;
        box->type = TYPE_GUI_CONTROL_LAYOUT_ITEM;
        box->widget = &gui_call_clog_widget_temp;
        box->x = 0;
        box->y = 0;
        box->width = LCD_SIZE_WIDTH;
        box->height = GUI_CALL_CLOG_ITEM_H;
        box->visible = 1;

        index_contact.index = idx;
        index_contact.data = (unsigned char*)&(call_record.Person_infor[0]);
        block_get_history_contact_Item(&index_contact);
        // icon
        switch(call_record.Person_infor[0].status[0])
        {
        case   CALL_IN:
            pic = &pic_calllog_in_info;
            break;
        case    CALL_OUT:
            pic = &pic_calllog_out_info;
            break;
        case CALL_IN_NONE:
        default:
            pic = &pic_calllog_miss_info;
            break;
        }

        gui_call_clog_item_pic.data = pic;
        if (0 == strlen(call_record.Person_infor[0].Name)) {
            gui_call_clog_item_number.value.string = call_record.Person_infor[0].Number;
        }
        else {
            gui_call_clog_item_number.value.string = call_record.Person_infor[0].Name;
        }
        gui_call_clog_item_time.value.string = call_record.Person_infor[0].time;
    }
}


/// @brief 判断有无通话记录
/// @param count
static void have_or_not_call_records(int count)
{
	gui_box_struct* call_no = gui_surface_get_box(&app_call_clog_screen, CALL_DIAL_PAD_NO);
    gui_box_struct* call_no_call_record = gui_surface_get_box(&app_call_clog_screen, CALL_DIAL_PAD_NO_CALL_RECORD);
    gui_box_struct* call_bg= gui_surface_get_box(&app_call_clog_screen, CALL_DIAL_PAD_TOP_BG);
	gui_box_struct* call_txt = gui_surface_get_box(&app_call_clog_screen, CALL_DIAL_PAD_TOP_TXT);
    if (count == 0) {
        gui_surface_box_change_visible(call_no, 1);
        gui_surface_box_change_visible(call_no_call_record, 1);
        gui_surface_box_change_visible(call_bg, 0);
        gui_surface_box_change_visible(call_txt, 0);
    }
    else {
        gui_surface_box_change_visible(call_no, 0);
        gui_surface_box_change_visible(call_no_call_record, 0);
        gui_surface_box_change_visible(call_bg, 1);
        gui_surface_box_change_visible(call_txt, 1);
    }
}

/// @brief 有通话记录时界面信息
/// @param void
static void app_window_call_clog_refresh_function()
{
     int idx, count = block_read_contact_history_num();

    have_or_not_call_records(count);

    gui_surface_struct* surface = gui_surface_get_surface(&app_call_clog_screen);
		gui_surface_layout_listview_dynamic_init(surface);
    if (surface != NULL) {
        for (idx=count-1; idx>=0; idx--) {
            gui_box_struct* box = gui_surface_layout_listview_dynamic_get_box(surface, idx+CALL_DIAL_CLOG_BASE_ID);    // gui_surface_cache_add_box();
            if (box != NULL) {
                app_window_call_clog_list_init_box_data(box, idx);
				gui_surface_layout_listview_dynamic_add_item(surface,box);
            }
        }

		gui_surface_layout_listview_dynamic_finish(surface);
    }
}

/// @brief 
void app_window_call_clog_refresh(void)
{
    app_window_call_clog_refresh_function();
}

/// @brief 通话记录点击回拨
/// @param event
void app_window_call_clog_item_click_function(char event)
{
    Get_Index_Contact_t  index_contact;
    unsigned int idx, count ;
	if((ext_btaud_status_get()->dev_status > 0)&&(get_ble_connect_flag() > 0)){
    	count = block_read_contact_history_num();
        idx = event - CALL_DIAL_CLOG_BASE_ID;
        if (idx < count) {
            index_contact.index = idx;
            index_contact.data = (unsigned char*)&(call_record.Person_infor[0]);
            block_get_history_contact_Item(&index_contact);

#if defined(__EXT_BT_AUDIO__)
            ext_btaud_send_cmd(AU_CMD_CALL_DIAL, (unsigned char *)call_record.Person_infor[0].Number, sizeof(call_record.Person_infor[0].Number));
#endif
        }
	}
}



//****************************************************call clog****************************************************//
