#ifndef _LANGUAGE_H
#define _LANGUAGE_H

#include "language_table.h"
#include "pid_type.h"
#include "data_common.h"

typedef struct
{
	const unsigned int id;
	const char*        string[LANGUAGE_TYPE_ALL];
}language_strings_struct;


#define LANGUAGE_LANG_NUM       sys_language_get_number()
#define LANGUAGE_STRING_NUM		sys_language_get_strings_number()


extern unsigned char g_language_type; //0: ��ŷ���ң�1������/����/���ĵ�

//extern void GUI_DispStringAt(const font_hz_struct *font_info, STRING_ID_TYPE id, int x, int y);
extern void test_language(void);
extern const char* GUI_Get_ID_String(STRING_ID_TYPE id);
extern void GUI_Language_check(void);

extern const language_strings_struct language_strings[];
extern const unsigned char sys_language_type[];
extern const language_strings_struct* GUI_Get_ID(STRING_ID_TYPE id, unsigned short* number);


#endif /* LANGUAGE_H */

