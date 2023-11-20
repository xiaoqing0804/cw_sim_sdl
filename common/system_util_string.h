#ifndef __SYSTEM_UTIL_STRING_H__
#define __SYSTEM_UTIL_STRING_H__

#include "feature_all.h"

extern unsigned short length_of_string(unsigned char* arrary, unsigned short arrary_count);
extern unsigned short get_string_from_number(unsigned char* arrary, unsigned short arrary_count, unsigned int number);
extern unsigned short get_string_from_number_with_len(unsigned char* arrary, unsigned short arrary_count, unsigned int number, unsigned int num_len);
extern unsigned short get_string_from_encoding(unsigned char* arrary, unsigned short arrary_count, unsigned char* value);


extern int chset_utf8_to_ucs2(unsigned char* dest, unsigned char* utf8);
extern int chset_ucs2_to_utf8(unsigned char* utf8, unsigned short ucs2);

#endif


