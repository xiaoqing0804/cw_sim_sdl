
#include "debug_info.h"
#include "language.h"


unsigned char g_language_type = 0; //0: 西欧国家；1：中文/日文/韩文等

const char* GUI_Get_ID_String(STRING_ID_TYPE id)
{
	unsigned int  i;
	unsigned char language = 0;

	/* find language. */
	for(i = 0; i < LANGUAGE_LANG_NUM; i++)
	{
		if(g_language.num == sys_language_type[i])
		{
			language = i;
			break;
		}
	}
	if(language >= LANGUAGE_LANG_NUM)
	{
		language = 0;
	}

	for(i = 0; i < LANGUAGE_STRING_NUM; i++)
	{
		if(id == language_strings[i].id)
		{
			if (language_strings[i].string[language] != NULL && strlen(language_strings[i].string[language]) > 0) {
				return language_strings[i].string[language];
			}
			else {
				return language_strings[i].string[0];
			}
		}
	}

	return NULL;
}

const language_strings_struct* GUI_Get_ID(STRING_ID_TYPE id, unsigned short* number)
{
	if (number != NULL) *number = LANGUAGE_STRING_NUM;

	for(unsigned int i = 0;i < LANGUAGE_STRING_NUM;i++)
	{
		if(id == language_strings[i].id)
		{
			return &language_strings[i];
		}
	}

	return NULL;
}

//0: english, 1: chinese/japan.
void GUI_Language_check(void)
{
	if((LANGUAGE_TYPE_CHINESE == g_language.num)||(LANGUAGE_TYPE_JAPAN == g_language.num))
		g_language_type = 1;
	else
		g_language_type = 0;
}

unsigned int GUI_Language_Supported(unsigned char langType)
{
    /* find language. */
    for(unsigned char i = 0;i < LANGUAGE_LANG_NUM;i++)
    {
        if(langType == sys_language_type[i])
        {
            return 1;
        }
    }
    return 0;
}

void test_language(void)
{
#if 0
	g_setting.select.bit.language = 0;
	GUI_DispStringAt(&FONT_HZ16x16, STRING_SUN, 0, 0);
	g_setting.select.bit.language = 1;
	GUI_DispStringAt(&FONT_HZ16x16, STRING_MON, -8, 21);
	g_setting.select.bit.language = 0;
	GUI_DispStringAt(&FONT_HZ16x16, STRING_ENTER, -7, 55);
	GUI_DispStringAt(&FONT_HZ16x16, STRING_ENTER, 70, -7);
	GUI_DispStringAt(&FONT_HZ16x16, STRING_ENTER, 70, 55);
#endif
}


