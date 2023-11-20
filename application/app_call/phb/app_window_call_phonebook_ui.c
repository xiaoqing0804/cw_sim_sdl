#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_receive_package.h"
#include "data_manager_message.h"

#ifdef __PHONE_BOOK_SYNC_SUPPORTED__
#include "data_manager_contact.h"
#endif

#include "srv_call.h"

#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_canvas.h"
#include "gui_surface_control_base.h"

#include "app_window_call_phonebook_layout.h"
#include "app_window_call_phonebook_ui.h"

//****************************************************call phonebook****************************************************//
/// @brief 联系人界面显示创建
/// @param gui_box_struct* box
/// @param unsigned int idx
static void app_window_call_phb_list_init_box_data(gui_box_struct* box, unsigned int idx)
{
    Get_Index_Contact_t  index_contact;
	if (box->id == 0) {
		box->id = idx+CALL_DIAL_PHB_BASE_ID;
		box->type = TYPE_GUI_CONTROL_LAYOUT_ITEM;
		box->widget = &gui_call_phb_widget_temp;
		box->x = 0;
		box->y = 0;
		box->width = LCD_SIZE_WIDTH;
		box->height = GUI_CALL_PHB_ITEM_H;
		box->visible = 1;

		index_contact.index = idx;
		index_contact.data = (unsigned char*)&(contact.Person_infor[0]);
		block_get_contact_Item(&index_contact);

		gui_call_phb_item_name.value.string = contact.Person_infor[0].Name;
		gui_call_phb_item_number.value.string = contact.Person_infor[0].Number;
	}
}
/// @brief 有无联系人判断
/// @param int count
static void have_or_not_call_book(int count)
{
    gui_box_struct* call_no = gui_surface_get_box(&app_call_phb_screen, CALL_DIAL_PAD_NO);
	gui_box_struct* call_no_icon = gui_surface_get_box(&app_call_phb_screen, CALL_DIAL_PAD_NO_CONTACT);
	gui_box_struct* call_bg= gui_surface_get_box(&app_call_phb_screen, CALL_DIAL_PAD_TOP_BG);
	gui_box_struct* call_txt = gui_surface_get_box(&app_call_phb_screen, CALL_DIAL_PAD_TOP_TXT);

	if(count == 0)
    {
 		gui_surface_box_change_visible(call_no_icon,1);
		gui_surface_box_change_visible(call_no,1);
		gui_surface_box_change_visible(call_bg,0);
		gui_surface_box_change_visible(call_txt,0);
    }
	else
	{
		gui_surface_box_change_visible(call_no_icon,0);
		gui_surface_box_change_visible(call_no,0);
		gui_surface_box_change_visible(call_bg,1);
		gui_surface_box_change_visible(call_txt,1);
	}
 }

/// @brief 添加联系人时界面更新
/// @param void
 static void app_window_call_phone_book_refrsh_function()
{
    unsigned int idx, count = block_read_contact_num(); 
    SYS_DEBUG("count_num = %d",count);

    have_or_not_call_book(count);

    gui_surface_struct* surface = gui_surface_get_surface(&app_call_phb_screen);
	gui_surface_layout_listview_dynamic_init(surface);
    if (surface != NULL) {
        for (idx=0; idx<count; idx++) {
            gui_box_struct* box = gui_surface_layout_listview_dynamic_get_box(surface, idx+CALL_DIAL_PHB_BASE_ID);	// gui_surface_cache_add_box();
            if (box != NULL) {
				app_window_call_phb_list_init_box_data(box, idx);
               	gui_surface_layout_listview_dynamic_add_item(surface,box);
            }
        }
        gui_surface_layout_listview_dynamic_finish(surface);
    }
}

void app_window_call_phone_book_refrsh(void)
{
    app_window_call_phone_book_refrsh_function();
}

/// @brief 联系人点击响应
/// @param char event
void app_window_call_phb_item_click_function(char event)
{
	SYS_DEBUG("call_click");
    Get_Index_Contact_t  index_contact;
    unsigned int idx, count;
	if((ext_btaud_status_get()->dev_status > 0)&&(get_ble_connect_flag() > 0)){
		count = block_read_contact_num();
	    idx = (event - CALL_DIAL_PHB_BASE_ID);
		SYS_DEBUG("idx=%d count=%d",idx,count);
	    if (idx < count) {
	        index_contact.index = idx;
	        index_contact.data = (unsigned char*)&(contact.Person_infor[0]);
	        block_get_contact_Item(&index_contact);

	        ext_btaud_send_cmd(AU_CMD_CALL_DIAL, (unsigned char *)contact.Person_infor[0].Number, strlen((char*)contact.Person_infor[0].Number));
			SYS_DEBUG("NUMBER = %s ",contact.Person_infor[0].Number);
			application_close_act_timer(APPLICATION_TIMER_ACT);
			application_open_act_timer(APPLICATION_TIMER_ACT, 200);
	    }
	}
	else{
		return;
	}
}

//****************************************************call phonebook****************************************************//




