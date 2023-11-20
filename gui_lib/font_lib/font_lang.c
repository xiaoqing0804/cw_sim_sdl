#include "font_lang.h"
#include "stdio.h"
#include "string.h"
#include "feature_all.h"
#include "data_common.h"
#include "font_convert.h"
#include "font_lang_arabic.h"

unsigned int font_lang_utf8_to_unicode(const char *utf8_str, unsigned short* unicode_str)
{
	const char * p_string = utf8_str;
	int len = strlen(p_string);
	
	unsigned long unicode = 0;
	unsigned int index = 0;
	int num_bytes = 0;

	/* 1. get display string all len. */
	while(len > 0)
	{
		if(index >= FONT_UTF8_TO_UNICODE_SIZE - 1)
			break;
			
		/* 1.get unicode data. */
		num_bytes = utf8_to_unicode((const unsigned char *)p_string, &unicode);
		if(num_bytes == 0)
			break;
		
		if(num_bytes < 0)
		{
			num_bytes = ABS(num_bytes);
			unicode = 0x0001;
		}
		
		/* point to next string char. */
		p_string += num_bytes;
		if(len >= num_bytes)
			len -= num_bytes;
		else
			len = 0;
		
		unicode_str[index++] = unicode;
	}
	return index;
}

unsigned int font_lang_letter_shape(unsigned short* unicode_str, unsigned int unicode_len)
{
	if(font_lang_arabic_check(unicode_str,unicode_len))
	{
		return font_lang_arabic_letter_shape(unicode_str, unicode_len);
	}
	return unicode_len;
}


unsigned char font_lang_is_right_to_left()
{
	switch(g_language.num)
	{
	case (unsigned char)LANGUAGE_TYPE_ARABIC:
	case (unsigned char)LANGUAGE_TYPE_HEBREW:
		return 1;

	default:
		return 0;
	}
}


