#ifndef __APP_WINDOW_CALL_PHB_LAYOUT_H__
#define __APP_WINDOW_CALL_PHB_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"
#include "gui_surface_control_base.h"

#define GUI_CALL_PHB_ITEM_H     100


enum{

    CALL_DIAL_PAD_NO=10,
	CALL_DIAL_PAD_NO_CONTACT,
	CALL_DIAL_PAD_TOP_BG,
	CALL_DIAL_PAD_TOP_TXT,
};


extern const gui_screen_struct app_call_phb_screen;


extern const gui_widget_struct gui_call_phb_widget_temp;
extern gui_font_struct gui_call_phb_item_name;
extern gui_font_struct gui_call_phb_item_number;

#endif
