#include "gui_util_text_string.h"
#include "language.h"
#include "system_util_all.h"


unsigned char* gui_util_text_string_get_string(unsigned char value_type, int value,unsigned char* buff,unsigned short buff_len)
{
	unsigned char* str;
	if(value_type == GUI_FONT_VALUE_TYPE_STRING_ID)
	{
		str = (unsigned char*)GUI_Get_ID_String((STRING_ID_TYPE)value);
	}
	else if(value_type == GUI_FONT_VALUE_TYPE_NUMBER)
	{
	    str = buff;
		get_string_from_number(str,buff_len,value);
	}
    else {
        str = (unsigned char*)value;
    }
	return str;
}


unsigned char* gui_util_text_string_get_string_from_font(const gui_font_struct* text, unsigned char* buff,unsigned short buff_len)
{
	unsigned char* str;
	if(text->value_type == GUI_FONT_VALUE_TYPE_STRING_ID)
	{
		str = (unsigned char*)GUI_Get_ID_String((STRING_ID_TYPE)text->value.string_id);
	}
	else if(text->value_type == GUI_FONT_VALUE_TYPE_NUMBER)
	{
	    str = buff;
		get_string_from_number(str,buff_len,text->value.number);
	}
    else {
        str = (unsigned char*)text->value.string;
    }
	return str;
}


