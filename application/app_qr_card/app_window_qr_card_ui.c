#include "debug_info.h"
#include "bsp_includes.h"
#include "os_mem.h"
#include "storage_qr_info.h"

#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_qrcode.h"
#include "gui_surface_box_scale.h"

#include "app_window_qr_card.h"
#include "app_window_qr_card_layout.h"
#include "app_window_qr_card_list.h"
#include "app_window_qr_card_list_ui.h"
#include "app_window_qr_card_common.h"

#if defined(GUI_QR_INFO_SUPPORT)&&GUI_QR_INFO_SUPPORT

void app_window_qr_card_ui_load(qr_code_info_struct* qr_info, unsigned int qr_card_indx)
{
	gui_box_struct* box;

    storage_qr_get(qr_card_indx, qr_info);

	box = gui_surface_get_box(&gui_screen_qr_card, QR_CARD_ID_CODE);
	if (box != NULL) {
		gui_surface_box_qrcode_change(box, qr_info->content);
	}

	box = gui_surface_get_box(&gui_screen_qr_card, QR_CARD_TEXT_ID_CODE);
	if (box != NULL) {
		gui_surface_box_label_change_string(box,(unsigned char *)qr_info->name);
	}

	box = gui_surface_get_box(&gui_screen_qr_card, QR_CARD_ICON_ID_CODE);
	if (box != NULL) {
		picture_info_struct* pic = app_qr_card_get_picture_by_type(qr_info->type);
		if (pic != NULL) {
			gui_surface_box_image_change(box, pic);
			//box->scale = 1.0f;
			//gui_surface_box_scale(gui_surface_get_surface(&gui_screen_qr_card), box, 0.4f);
			box->visible = 1;
		}
		else {
			box->visible = 0;
		}
	}
}

#endif

