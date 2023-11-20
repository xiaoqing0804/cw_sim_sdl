#ifndef __FONT_LANG_H__
#define __FONT_LANG_H__

extern unsigned int font_lang_utf8_to_unicode(const char *utf8_str, unsigned short* unicode_str);
extern unsigned int font_lang_letter_shape(unsigned short* unicode_str, unsigned int unicode_len);
extern unsigned char font_lang_is_right_to_left(void);

#endif


