
#include "debug_info.h"

#include "font_convert.h"
#include "system_util_string.h"

//#define FONT_CODE_POOL_SIZE 256    // 128, 256, 

// 循环pool
//static font_char_info_struct g_font_char_info_pool[FONT_CODE_POOL_SIZE] = {0};
//static unsigned char         g_font_char_info_index;

static unsigned char            g_font_size_type = SYS_FONT_MEDIUM;            // SYS_FONT_MAX


// 获取字符的utf8编码长度 ...
int utf8_get_size(unsigned char ch)
{
    int utf8_size = (int)0;
    unsigned char temp = ch & 0xf0;

    if(ch < 0x80) {
        return 1;
    }

    switch(temp) {
    case 0xf0:
        utf8_size = 4;
        break;
    case 0xe0:
        utf8_size = 3;
        break;
    default:
        if((temp & 0xc0) == 0xc0) {
            utf8_size = 2;
        }
        break;
    }
    return utf8_size;
}

// 指定实际最大字符数量，拷贝utf8字符串..
int utf8_nc_copy(unsigned char* pDes, unsigned char* pSrc, unsigned int char_count)
{
    int cpy_len = 0;
    int ch_len;
    if (pDes == NULL || pSrc == NULL || char_count == 0)   return 0;

    while(char_count) {
        ch_len = utf8_get_size(*pSrc);
        if (ch_len <= 0) {
            break;
        }

        switch(ch_len) {
            case 4:
                *pDes ++ = *pSrc ++;
            case 3:
                *pDes ++ = *pSrc ++;
            case 2:
                *pDes ++ = *pSrc ++;
            case 1:
                *pDes ++ = *pSrc ++;
                cpy_len += ch_len;
                break;

            default:
                pSrc += ch_len;
                break;
        }
        char_count --;
    }
    *pDes = 0;
    return cpy_len;
}

// 指定实际最大字符串长度，拷贝utf8字符串..
int utf8_n_copy_ext(unsigned char* pDes, unsigned char* pSrc, unsigned int des_len, unsigned int* utf8_num)
{
    unsigned int ch_num = 0;
    int cpy_len = 0;
    int ch_len;
    if (pDes == NULL || pSrc == NULL || des_len == 0) {
        if (utf8_num != NULL) *utf8_num = 0;
        return 0;
    }

    while(des_len) {
        ch_len = utf8_get_size(*pSrc);
        if (ch_len <= 0 || des_len < ch_len) {
            break;
        }

        switch(ch_len) {
            case 4:
                *pDes ++ = *pSrc ++;
            case 3:
                *pDes ++ = *pSrc ++;
            case 2:
                *pDes ++ = *pSrc ++;
            case 1:
                *pDes ++ = *pSrc ++;
                cpy_len += ch_len;
                ch_num ++;
                break;

            default:
                pSrc += ch_len;
                break;
        }
        des_len -= ch_len;
    }
    if (utf8_num != NULL) *utf8_num = ch_num;
    return cpy_len;
}

int utf8_n_copy(unsigned char* pDes, unsigned char* pSrc, unsigned int des_len)
{
    return utf8_n_copy_ext(pDes, pSrc, des_len, NULL);
}

//裁剪
int utf8_n_clip(unsigned char* pSrc, unsigned int des_len)
{
    int cpy_len = 0;
    int ch_len;
    if ( pSrc == NULL || des_len == 0)   return 0;

    while(des_len) {
        ch_len = utf8_get_size(*pSrc);
        if (ch_len <= 0 || des_len < ch_len) {
            break;
        }
        
        switch(ch_len) {
            case 4:
                *pSrc ++;
            case 3:
                *pSrc ++;
            case 2:
                *pSrc ++;
            case 1:
                *pSrc ++;
                cpy_len += ch_len;
                break;

            default:
                pSrc += ch_len;
                break;
        }
        des_len -= ch_len;
    }

    *pSrc=0;
    
    return cpy_len;
}

// 转换utf8编码到unicode， 返回当前字符的utf8编码长度
int utf8_to_unicode(const unsigned char* p_char, unsigned long *unicode)
{
    int utfbytes;
    unsigned char *p_output;
    unsigned char  b1, b2, b3, b4;

    *unicode = 0x0;
    p_output = (unsigned char*)unicode;
    utfbytes = utf8_get_size(*p_char);
    switch (utfbytes)
    {
    case 1:
        *p_output = *p_char;
        break;
    case 2:
        b1 = *p_char;
        b2 = *(p_char + 1);
        if ((b2 & 0x80) != 0x80) {
            return -2;
        }
        *p_output = (b1 << 6) + (b2 & 0x3F);
        *(p_output + 1) = (b1 >> 2) & 0x07;
        break;
    case 3:
        b1 = *p_char;
        b2 = *(p_char + 1);
        b3 = *(p_char + 2);
        if (((b2 & 0x80) != 0x80) || ((b3 & 0x80) != 0x80)) {
            return -3;
        }
        *p_output = (b2 << 6) + (b3 & 0x3F);
        *(p_output + 1) = (b1 << 4) + ((b2 >> 2) & 0x0F);
        break;
    case 4: // F0 9F 98 80
        #if 0   // 我们字库不支持2字节以上的unicode。全部以 □ 字符代替.
        b1 = *p_char;
        b2 = *(p_char + 1);
        b3 = *(p_char + 2);
        b4 = *(p_char + 3);
        if (((b2 & 0x80) != 0x80) || ((b3 & 0x80) != 0x80) || ((b4 & 0x80) != 0x80)) {
            return -4;
        }
        *p_output = (b3 << 6) + (b4 & 0x3F);
        *(p_output + 1) = (b2 << 4) + ((b3 >> 2) & 0x0F);
        *(p_output + 2) = ((b1 << 2) & 0x1C)  + ((b2 >> 4) & 0x03);
        #else   // □  TCFG_PAY_ALIOS_ENABLE
        *p_output = UCS16_INVALID_CODE&0xFF;
        *(p_output + 1) = (UCS16_INVALID_CODE>>8)&0xFF;
        #endif
        break;
    default:
        utfbytes = 0;
        break;
    }
    return utfbytes;
}

// 测试utf8字符串的显示宽度和高度， 返回有多少个字符 ...
// lineFlag - [out] 如果字符串中有换行符,则此标志会置1 ...
unsigned int get_font_string_meastrue(unsigned char* utf8Str, unsigned int* width, unsigned int* height, unsigned int* lineFlag)
{
    font_char_info_struct   char_info;
    int char_addr;

    int len = 0,num_bytes = 0;
    unsigned int point_len = 0, count = 0, max_point_len = 0, max_width = LCD_SIZE_WIDTH;
    unsigned long unicode = 0;

    if (*width != 0) max_width = *width;
    *lineFlag = 0;
    *height = font_get_height(g_font_size_type);
    len = strlen((char*)utf8Str);
    while(len > 0) {
        if (*utf8Str == '\n' || point_len >= max_width) {
            *lineFlag = 1;
            if (max_point_len < point_len) {
                max_point_len = point_len;
            }
            point_len = 0;
        }

        num_bytes = utf8_to_unicode((const unsigned char *)utf8Str, &unicode);
        if(num_bytes == 0) {
            break ;
        }
        else if(num_bytes < 0) {
            num_bytes = 0 - num_bytes;
            unicode = UCS16_INVALID_CODE;   // ' ';
        }

        char_addr = font_get_char(g_font_size_type, unicode, &char_info);
        if (char_addr < 0) {
            char_addr = font_get_char(g_font_size_type, UCS16_INVALID_CODE/*' '*/, &char_info);
        }
        point_len += char_info.xDist;
        count ++;

        utf8Str += num_bytes;
        if(len >= num_bytes)
            len -= num_bytes;
        else
            len = 0;
    }
    *width = ((max_point_len == 0) ? point_len : max_point_len);

    return count;
}




// 指定显示宽度,获取一行utf8字符串, 返回有多少个字符 这一行的utf8字符串长度(Bytes) ...
// retWidth - [out] 返回当前行的实际显示宽度 ..
unsigned int get_font_chars_line_from_string(unsigned char* utf8Str, unsigned int dispWidth, unsigned int* retWidth)
{
    font_char_info_struct char_info;
    int char_addr;

    int len = 0, num_bytes = 0;
    unsigned int point_len = 0, count = 0;
    unsigned long unicode = 0;

    *retWidth = 0;
    len = strlen((char*)utf8Str);
    while(len > 0) {
        if (*utf8Str == '\n') {
            count ++;
            if (point_len != 0) {
                // 换行符不是第一个字符，则作为一行返回...
                break;
            }
            utf8Str ++;
            len --;
        }
        num_bytes = utf8_to_unicode((const unsigned char *)utf8Str, &unicode);
        if(num_bytes == 0) {
            break;
        }
        else if(num_bytes < 0) {
            num_bytes = 0 - num_bytes;
            unicode = UCS16_INVALID_CODE;   // ' ';
        }

        char_addr = font_get_char(g_font_size_type, unicode, &char_info);
        if (char_addr < 0) {
            char_addr = font_get_char(g_font_size_type, UCS16_INVALID_CODE/*' '*/, &char_info);
        }

        //SYS_DEBUG("text: tw=%d, code=%x, cw=%d, lf=%d", point_len, char_info.code, char_info.xDist, char_info.lineFlag);        
        if (((point_len+char_info.xDist) > dispWidth) && (char_info.lineFlag == 0)) {
            //SYS_DEBUG("text: new line!!!");
            break;
        }
        point_len += char_info.xDist;
        count += num_bytes;
        utf8Str += num_bytes;

        if(len >= num_bytes)
            len -= num_bytes;
        else
            len = 0;
    }
	*retWidth = point_len;
	
    return count;
}



// 从字符串中获取第一个字符, 返回字符后的字符串
// retFlag - [out] 成功时,此标志置1 ..
unsigned char* get_font_char_info_from_string(unsigned char* utf8Str, font_char_info_struct* char_info, unsigned int* retFlag)
{
    unsigned long  unicode = 0;
    
    int char_addr;
    int len = 0,num_bytes = 0;

    *retFlag = 0;
    len = strlen((char*)utf8Str);
    if (len > 0) {
        if (*utf8Str == '\n') {
            utf8Str ++;
            char_info->code = '\n';
            return utf8Str;
        }
        
        num_bytes = utf8_to_unicode((const unsigned char *)utf8Str, &unicode);
        if(num_bytes == 0) {
            return NULL;
        }
        else if(num_bytes < 0) {
            num_bytes = 0 - num_bytes;
            unicode = UCS16_INVALID_CODE;
        }

        char_addr = font_get_char(g_font_size_type, unicode, char_info);
        if (char_addr < 0) {
            char_addr = font_get_char(g_font_size_type, UCS16_INVALID_CODE, char_info);
        }
        
        *retFlag = 1;
        utf8Str += num_bytes;
    }
    else {
        utf8Str = NULL;
    }
    
    return utf8Str;
}


// 获取给定字符的信息
int get_font_char_info_from_code(unsigned long unicode, font_char_info_struct* char_info)
{
    int char_addr;

    char_addr = font_get_char(g_font_size_type, unicode, char_info);
    if (char_addr < 0) {
        char_addr = font_get_char(g_font_size_type, UCS16_INVALID_CODE, char_info);
    }
    
    return char_addr;
}


// 获取字库中字符的高度 
unsigned int get_font_height(void)
{
    return font_get_height(g_font_size_type);
}

// 获取字库中字符的高度 
unsigned int get_font_height_by_size(unsigned char fontSize)
{
    return font_get_height(fontSize);
}


unsigned char get_font_size(void)
{
    return g_font_size_type;
}

// 设置系统字体大小 ..
unsigned char set_font_size(unsigned int szType)
{
    unsigned char old_size = g_font_size_type;
    if (szType < SYS_FONT_MAX) {
        szType = font_chk_size(szType);
        g_font_size_type = szType;
    }
    return old_size;
}

int get_font_char_info_from_size_code(unsigned char size_type, unsigned long unicode, font_char_info_struct* char_info)
{
    int char_addr;

    size_type = font_chk_size(size_type);
    char_addr = font_get_char(size_type, unicode, char_info);
    if (char_addr < 0) {
        char_addr = 0;
    }

    return char_addr;
}



// 
/*
font_char_info_struct* get_font_chars_info_from_string(unsigned char* str, unsigned int* number)
{
    int char_addr;
    int len = 0,num_bytes = 0;

    unsigned long unicode = 0;
    unsigned char beging_index = g_font_char_info_index;

    *number = 0;
    len = strlen(str);
    while(len > 0)
    {
        num_bytes = utf8_to_unicode((const unsigned char *)str, &unicode);
        if(num_bytes == 0)
        {
            break ;
        }
        else if(num_bytes < 0)
        {
            num_bytes = 0 - num_bytes;
            unicode = ' ';
        }

        char_addr = font_get_char(SYS_FONT_MEDIUM, unicode, &g_font_char_info_pool[g_font_char_info_index]);
        if (char_addr > 0) {
            g_font_char_info_index ++;
            g_font_char_info_index &= (FONT_CODE_POOL_SIZE-1);
            *number ++;
        }

        str += num_bytes;
        if(len >= num_bytes)
            len -= num_bytes;
        else
            len = 0;
    }

	return &g_font_char_info_pool[beging_index];
}
*/


