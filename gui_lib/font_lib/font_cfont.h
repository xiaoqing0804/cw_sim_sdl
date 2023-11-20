#ifndef __FNT_CFONT_H__
#define __FNT_CFONT_H__

typedef enum{
    SYS_FONT_XSMALL,
    SYS_FONT_SMALL,
    SYS_FONT_MEDIUM,
    SYS_FONT_LARGE,
    SYS_FONT_XLARGE,
    SYS_FONT_XXLARGE,
    SYS_FONT_NUMBER_15,
    SYS_FONT_NUMBER_17,
    SYS_FONT_NUMBER_20,
    SYS_FONT_NUMBER_23,
    SYS_FONT_NUMBER_26,
    SYS_FONT_NUMBER_29,
    SYS_FONT_NUMBER_32,
    SYS_FONT_NUMBER_35,
    SYS_FONT_NUMBER_38,
    SYS_FONT_NUMBER_45,
    SYS_FONT_NUMBER_50,
    SYS_FONT_MAX
}SYS_FONT_TYPE;

#define MAX_SYS_FONTS           3   // 每种字体大小，最多可安装3个字库 ... 
#define MAX_SYS_FONT_CACHE      128 

typedef struct
{
    unsigned short code;
    unsigned char  bitPoint:5;  // 1, 2, 4, 8 ...
    unsigned char  mcuData:1;   // 0 - 外部flash; 1 - mcu flash.
    unsigned char  alinSize:1;  // 字模数据行对齐方式； 0 - 1字节对齐； 1 - 4字节对齐.
    unsigned char  lineFlag:1;  // 如果此字符会与前一个字符叠加，则置为1， 而且指示这个字符前不能换行.
    unsigned char  xDist;       // 字符占位宽度
    unsigned char  xSize;
    unsigned char  ySize;       // 
    signed   char  xPos;
    signed   char  yPos;
    unsigned int   datAddr;     // flash addr.  (gui_font_char_bitmap_struct)
}font_char_info_struct;


typedef struct
{
    unsigned char xSize;        // char x size; 
    unsigned char ySize;        // char y size;
    signed   char xPos;         // char x pos;
    signed   char yPos;         // char y pos;
    unsigned char bitmap[1];    // 可变数组，大小计算方法为: (((xSize * bitsPerPixel) + 7)/8) * ySize
}font_char_bitmap_struct;


// 初始化cfont
extern void font_init(void);


// 安装客制字库
// param: 
//   szType - 字体大小(SYS_FONT_TYPE) ..
//     addr - 客制字库的地址
// return：
//       -1 - 错误（当前系统中字库数超过了 MAX_SYS_FONTS ）...
//    other - 安装成功.
extern int font_install(unsigned int szType, unsigned int addr);
extern int font_install_internal(unsigned int szType, void* addr);


// 从系统字库(包括客制安装字库)中获取指定字符的信息 ..
// param：
//   szType - 字体大小(SYS_FONT_TYPE) ..
//     code - 字符unicode编码
//     info - [out] 携带字符信息返回 
// return：
//       -1 - 错误 (系统字库中找不到这个字符) ..
//    other - 获取成功，返回字符在flash中的地址(同：info->datAddr)
extern int font_get_char(unsigned int szType, unsigned short code, font_char_info_struct* info);


// 从指定字库中获取一个字符信息 
// param: 
//     addr - 客制字库的地址
//     code - unicode
//     info - [out] 携带字符信息返回 
// return：
//       -1 - 错误 (系统字库中找不到这个字符) ..
//    other - 获取成功，返回字符在flash中的地址(同：info->datAddr)
extern int font_get_char_ext(unsigned int addr, unsigned short code, font_char_info_struct* info);


// 显示一个字符
// param: 
//        x - 
//        y - 
//     info - [in] 字符信息
// return：
//       -1 - 错误 (系统字库中找不到这个字符) ..
//    other - 成功
extern int font_disp_char(int x, int y, font_char_info_struct* info);


///////////////////////////////////////////////////////////////////////////////////
// 获取字体高度
// param: 
//   szType - 字体大小(SYS_FONT_TYPE) ..
// return：
//       -1 - 错误 (系统字库中找不到这个字符) ..
//    other - 字体高度
extern int font_get_height(unsigned int szType);


///////////////////////////////////////////////////////////////////////////////////
// 获取指定字库的字体高度
// param: 
//     addr - 客制字库的地址
// return：
//       -1 - 错误 (系统字库中找不到这个字符) ..
//    other - 字体高度
extern int font_get_height_ext(unsigned int addr);

///////////////////////////////////////////////////////////////////////////////////
// 检查是否安装字体
// param:
//   szType - 字体大小(SYS_FONT_TYPE) ..
// return：
//    szType 或者 字体没有安装时，返回小一号已安装字体
extern unsigned int font_chk_size(unsigned int szType);

// 
extern font_char_bitmap_struct* font_get_bitmap(font_char_info_struct* char_info);

extern font_char_bitmap_struct* font_get_bitmap_ext(font_char_info_struct* char_info, unsigned char* buff, unsigned int buff_len);

#endif


