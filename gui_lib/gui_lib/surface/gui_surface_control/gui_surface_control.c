#include "gui_surface_control.h"

void gui_surface_control_parse(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;
	switch(widget->type)
	{
		case TYPE_GUI_CONTROL_DATE:
            gui_surface_control_date_create(box);
            break;
			
		case TYPE_GUI_CONTROL_TIME:
			gui_surface_control_time_create(box);
			break;
		case TYPE_GUI_CONTROL_TIME_HOUR:
			gui_surface_control_time_hour_create(box);
			break;
		case TYPE_GUI_CONTROL_TIME_MIN:
			gui_surface_control_time_min_create(box);
			break;
        case TYPE_GUI_CONTROL_BT_ICON:
            gui_surface_control_bt_icon_create(box);
            break;

        case TYPE_GUI_CONTROL_ANIMATION:
            gui_surface_control_animation_create(box);
            break;

        case TYPE_GUI_CONTROL_BATT_ICON:
            gui_surface_control_batt_icon_create(box);
            break;

        case TYPE_GUI_CONTROL_BATT_LABEL:
            gui_surface_control_batt_label_create(box);
            break;

        case TYPE_GUI_CONTROL_SWITCH:
            gui_surface_control_switch_create(box);
            break;

        case TYPE_GUI_CONTROL_RING:
            gui_surface_control_ring_create(box);
            break;

        case TYPE_GUI_CONTROL_CHART:
            gui_surface_control_chart_create(box);
            break;

        case TYPE_GUI_CONTROL_SCROLL_TEXT:
            gui_surface_control_scrolltext_create(box);
            break;

        case TYPE_GUI_CONTROL_IMAGE_9SLICE:
            //gui_surface_box_image_9slice_create(box);
            break;
	}
}

void gui_surface_control_exit(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;

	switch(widget->type)
	{
		case TYPE_GUI_CONTROL_DATE:
            gui_surface_control_date_exit(box);
            break;
			
		case TYPE_GUI_CONTROL_TIME:
			gui_surface_control_time_exit(box);
			break;
		
		case TYPE_GUI_CONTROL_TIME_HOUR:
			gui_surface_control_time_hour_exit(box);
			break;
		
		case TYPE_GUI_CONTROL_TIME_MIN:
			gui_surface_control_time_min_exit(box);
			break;		
        case TYPE_GUI_CONTROL_BT_ICON:
            gui_surface_control_bt_icon_exit(box);
            break;

        case TYPE_GUI_CONTROL_ANIMATION:
            gui_surface_control_animation_exit(box);
            break;

        case TYPE_GUI_CONTROL_BATT_ICON:
            gui_surface_control_batt_icon_exit(box);
            break;

        case TYPE_GUI_CONTROL_BATT_LABEL:
            gui_surface_control_batt_label_exit(box);
            break;

        case TYPE_GUI_CONTROL_SWITCH:
            gui_surface_control_switch_exit(box);
            break;
        
        case TYPE_GUI_CONTROL_RING:
            gui_surface_control_ring_exit(box);
            break;

        case TYPE_GUI_CONTROL_CHART:
            gui_surface_control_chart_exit(box);
            break;

        case TYPE_GUI_CONTROL_SCROLL_TEXT:
            gui_surface_control_scrolltext_exit(box);
            break;
	}
}



