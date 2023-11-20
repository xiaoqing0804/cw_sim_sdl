#include "gui_surface_control_base.h"
#include "gui_surface_box_image_number.h"
#include "gui_surface_box_label.h"

void gui_surface_control_digital_change(gui_box_struct* box, unsigned char* str)
{
    gui_widget_struct* widget = box->widget;
	const gui_control_digital_struct* digital = (const gui_control_digital_struct *)widget->children;
	if(digital->value_type == GUI_DIGITAL_VALUE_TYPE_IMAGE)
	{
		gui_surface_box_image_number_change_content(box,digital->value.image_number, str);
	}
	else if(digital->value_type == GUI_DIGITAL_VALUE_TYPE_FONT)
	{
		gui_surface_box_label_change_content(box,digital->value.font,str);
	}
}


