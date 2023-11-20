#ifndef __GUI_UTIL_TEXT_STRING_H__
#define __GUI_UTIL_TEXT_STRING_H__

#include "feature_all.h"
#include "system_util_all.h"
#include "gui_core_all.h"

extern unsigned char* gui_util_text_string_get_string(unsigned char value_type, int value,unsigned char* buff,unsigned short buff_len);
extern unsigned char* gui_util_text_string_get_string_from_font(const gui_font_struct* text, unsigned char* buff,unsigned short buff_len);

#endif


