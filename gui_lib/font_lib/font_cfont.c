
#include "stdio.h"
#include "string.h"

#include "debug_info.h"
#include "picture.h"
#include "data_manager_flash.h"
#include "data_manager.h"

#define __CFNT_SUPPORTED__
#if defined(__CFNT_SUPPORTED__)
#include "font_cfont.h"

///////////////////////////////////////////////////////////////////////////////////
#define GUI_FONT_RES_INT
typedef struct
{
    unsigned int szType;
    unsigned int datAddr;
    unsigned int datSize;
}cfont_resource_struct;
#include "GUI_FontResource.h"

/*
字库文件格式V1.0

=====================文件开始==================================================
字库文件信息：
        {gui_font_font_info_struct}

------------------------------------------------------------------------------
全字符表：以unicode为索引， 结构见 unicode_map_struct  |   分区字符表：
        {cfont_unicode_map_struct}                     |         {cfont_rang_map_struct}
        {cfont_unicode_map_struct}                     |         {cfont_rang_map_struct}
        {cfont_unicode_map_struct}                     |            ...
        {cfont_unicode_map_struct}                     |         {cfont_char_map_struct}
          ...                                          |         {cfont_char_map_struct}
                                                       |            ...
------------------------------------------------------------------------------
字模数据区:      包含字模数据头部信息 和 字模位图数据 两个部分
        {cfont_char_bitmap_struct}
        {cfont_char_bitmap_struct}
        {cfont_char_bitmap_struct}
        {cfont_char_bitmap_struct}
        {cfont_char_bitmap_struct}
          ...

=====================文件结束==================================================
*/


/*
相关数据结构：
===============================================================================
1、字库文件信息数据结构 (4Bytes)
*/
#define FONT_MAGIC      0x746E4643	// CFnt
#define FONT_BPP_1		0
#define FONT_BPP_2		1
#define FONT_BPP_4		2
#define FONT_BPP_8		3
typedef struct
{
	unsigned int magic;                 // cfnt
    unsigned int ySize        : 8;      // 字符高度
    unsigned int bitsPerPixel : 2;      // 每像素点的位数：0 - 1位;
                                        //                 1 - 2位;
                                        //                 2 - 4位;
                                        //                 3 - 8位
    unsigned int mcu_flash    : 1;      //  是否在mcu code区flash: 0: 外部flash； 1: 内部flash..

    unsigned int mapType      : 1;      // 字符表的类型： 0: 全字符表，最大大小为65536，以unicode为索引直接查找；
                                        //                1: 分区字符表，以相邻字符组成一个区，查找的时候需要分区查找;
    unsigned int infoSize     : 18;     // 字库头部数据大小，包括本数据结构、全字符表 或者 分区字符表和字符表 最大65536 Entries
    unsigned int alinSize     : 1;      // 字模数据行对齐方式： 0 - 一字节对齐； 1 - 四字节对齐
    unsigned int reserveBit   : 1;

	unsigned short mapNumber;			// 字符表的数目 全字符表 或者 分区字符表
	unsigned short charNumber;			// 字符数目
}cfont_info_struct;

/*
===============================================================================
2、字符表数据结构
全字符表  (4Bytes)：
*/
typedef struct
{
    unsigned int xDist          : 7;    // 指示字符的占位宽度，方便计算字符串长度。
                                        // 如像有些字符，显示时需要叠加到前一个字符上去，
                                        // 此处的值应该为该字符本身宽度 减去 需要前移 或者 加上 后移的位移量, 最小值为0。
    unsigned int lineFlag       : 1;    // 如果此字符会与前一个字符叠加，则置为1， 而且指示这个字符前不能换行.
    unsigned int datOffset      : 24;   // 指示字模数据的位置,以字模数据区的起始点为基础计算

}cfont_unicode_map_struct;

/*
------------------------------------------------------------------------------
分区字符表 (4Bytes)：
*/
typedef struct
{
    unsigned short baseCode;            // 分区开始字符 unicode 码
	unsigned short endCode;				// 分区结束字符 unicode 码
    unsigned short index;               // 指示baseCode字符在 char map中的索引
	unsigned short Reserve;				//

}cfont_rang_map_struct;

typedef struct
{
    unsigned int xDist          : 7;    // 指示字符的占位宽度，方便计算字符串长度。
                                        // 如像有些字符，显示时需要叠加到前一个字符上去，
                                        // 此处的值应该为该字符本身宽度 减去 需要前移 或者 加上 后移的位移量。
    unsigned int lineFlag       : 1;    // 如果此字符会与前一个字符叠加，则置为1， 而且指示这个字符前不能换行.
    unsigned int datOffset      : 24;   // 指示字模数据的位置,以字模数据区的起始点为基础计算

}cfont_char_map_struct;

/*
===============================================================================
3、字模数据头部信息数据结构
*/
typedef struct
{
    unsigned char xSize;        // char x size;
    unsigned char ySize;        // char y size;
    signed   char xPos;         // char x pos;
    signed   char yPos;         // char y pos;
    unsigned char bitmap[1];    // 可变数组，大小计算方法为: (((xSize * bitsPerPixel) + 7)/8) * ySize

}cfont_char_bitmap_struct;
///////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////
#if MAX_SYS_FONT_CACHE
typedef struct
{
    unsigned char          szType[MAX_SYS_FONT_CACHE];
    unsigned short         tStamp[MAX_SYS_FONT_CACHE];
    font_char_info_struct  char_info[MAX_SYS_FONT_CACHE];
}sys_font_cache_struct;
static sys_font_cache_struct    g_sys_font_cache;
static unsigned short           g_sys_font_cache_tstamp;
#endif


typedef struct
{
    cfont_info_struct   cfnt;
    unsigned int        addr;
    unsigned char       (*cfnt_data_read)(unsigned int addr,unsigned char * data,unsigned int len);
}sys_font_info_struct;
static sys_font_info_struct g_sys_fonts[SYS_FONT_MAX][MAX_SYS_FONTS];
static unsigned char        g_sys_font_number[SYS_FONT_MAX];
static unsigned char        g_sys_font_bpp[4];


#define MAX_CFONT_CHAR_DATA   1024
static unsigned int g_sys_font_data[MAX_CFONT_CHAR_DATA/4];
static const cfont_char_bitmap_struct* g_cfont_bitmap = (cfont_char_bitmap_struct*)g_sys_font_data;

#define SYS_FONT_SIZE(fnt)      (((fnt) - g_sys_fonts)/(MAX_SYS_FONTS*(sizeof(sys_font_info_struct))))


static unsigned char cfnt_data_read_int(unsigned int addr,unsigned char * data,unsigned int len)
{
    memcpy(data, (unsigned char*)addr, len);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////
///
// param:
//       res_idx   - 字库资源索引
//       code      - unicode
//       char_info - [o] 携带字符信息
// return：
//      如果找到，返回 字符的 cfont_char_bitmap_struct 绝对地址.
//      否则，    返回 -1
static int cfont_find_char(sys_font_info_struct* sys_fnt, unsigned short code, font_char_info_struct* char_info)
{
    cfont_char_bitmap_struct char_bitmap;
    unsigned int index;
    unsigned int map_addr;

    //SYS_DEBUG("cfont_find_char: map_type=%d, map_n=%d, char_n=%d", sys_fnt->cfnt.mapType, sys_fnt->cfnt.mapNumber, sys_fnt->cfnt.charNumber);
    if (sys_fnt->addr == 0 || sys_fnt->cfnt.magic != FONT_MAGIC)  return -1;

    if (sys_fnt->cfnt.mapType == 0) {
        // 全字符表 ..
        if (code < sys_fnt->cfnt.mapNumber) {
            cfont_unicode_map_struct unicode_map;

            map_addr = sys_fnt->addr + sizeof(cfont_info_struct);    // unicode 字符表的起始地址.
            map_addr += (code * sizeof(cfont_unicode_map_struct));

            sys_fnt->cfnt_data_read(map_addr, (unsigned char*)&unicode_map, sizeof(cfont_unicode_map_struct));
            if (unicode_map.datOffset == 0xFFFFFF) {
                // 字库中没有这个字符的数据..
                //memset(char_info, 0, sizeof(font_char_info_struct));
                //char_info->xDist = sys_fnt->cfnt.ySize/2;       // space
                DBG_DIRECT("cfont_find_char(addr: %x, code: %x): error 0", sys_fnt->addr, code);
                return -1;
            }

            // 字符数据地址..
            char_info->datAddr = sys_fnt->addr + sys_fnt->cfnt.infoSize + unicode_map.datOffset;

            sys_fnt->cfnt_data_read(char_info->datAddr, (unsigned char*)&char_bitmap, sizeof(cfont_char_bitmap_struct)-1);
            char_info->code = code;
            char_info->bitPoint = g_sys_font_bpp[sys_fnt->cfnt.bitsPerPixel];
            char_info->mcuData  = sys_fnt->cfnt.mcu_flash;
            char_info->alinSize = sys_fnt->cfnt.alinSize;
            char_info->lineFlag = unicode_map.lineFlag;
            char_info->xDist = unicode_map.xDist;
            char_info->xSize = char_bitmap.xSize;
            char_info->ySize = char_bitmap.ySize;
            char_info->xPos = char_bitmap.xPos;
            char_info->yPos = char_bitmap.yPos;

            return char_info->datAddr;
        }
        else {
            // 字符超出了字库的字符表范围 ..
            //memset(char_info, 0, sizeof(font_char_info_struct));
            //char_info->xDist = sys_fnt->cfnt.ySize/2;       // space
            DBG_DIRECT("cfont_find_char(addr: %x, code: %x): error 1", sys_fnt->addr, code);
            return -1;
        }
    }
    else {
        // 分区字符表
        cfont_rang_map_struct  rang_map;
        cfont_char_map_struct  char_map;
        unsigned int  start_index;
        unsigned int  end_index;
        unsigned int  mid_addr, found = 0;

        // 分区表的起始地址.
        map_addr = sys_fnt->addr + sizeof(cfont_info_struct);

        // 二分法查找 ...
        start_index = 0;
        end_index = sys_fnt->cfnt.mapNumber-1;
        while(start_index <= end_index)
        {
            // 中间分区的索引..
            index = (start_index+end_index)/2;
            mid_addr = map_addr + index * sizeof(cfont_rang_map_struct);
            sys_fnt->cfnt_data_read(mid_addr, (unsigned char*)&rang_map, sizeof(cfont_rang_map_struct));
            //printf("rang[%d] {%d, %x, %x}\r\n", index, rang_map.index, rang_map.baseCode, rang_map.endCode);
            if ((rang_map.baseCode <= code) && (code <= rang_map.endCode)) {
                // 定位在当前分区内 ..
                found = 1;
                break;
            }
            else if (code > rang_map.endCode) {
                // 定位在后面分区 .
                start_index = index + 1;
            }
            else if (code < rang_map.baseCode) {
                // 定位在前面分区 .
                if (index > 0)
                    end_index = index - 1;
                else
                    break;
            }
        }
        if (found == 0) {
            //memset(char_info, 0, sizeof(font_char_info_struct));
            //char_info->xDist = sys_fnt->cfnt.ySize/2;       // space
            DBG_DIRECT("cfont_find_char(addr: %x, code: %x): error 2", sys_fnt->addr, code);
            return -1;
        }

        // 字符在字符表中的索引.
        index = rang_map.index + code - rang_map.baseCode;
        // 字符表的起始地址.
        map_addr = sys_fnt->addr + sizeof(cfont_info_struct) + sys_fnt->cfnt.mapNumber * sizeof(cfont_rang_map_struct);
        map_addr += (index*sizeof(cfont_char_map_struct));
        sys_fnt->cfnt_data_read(map_addr, (unsigned char*)&char_map, sizeof(cfont_char_map_struct));
        //SYS_DEBUG("char[%x] index:%d, offset:%d, xdist:%d, linef:%d\r\n", code, index, char_map.datOffset, char_map.xDist, char_map.lineFlag);

        // 字符数据地址..
        char_info->datAddr = sys_fnt->addr + sys_fnt->cfnt.infoSize + char_map.datOffset;
        //printf("char[%x] %d, %d\r\n", code, index, char_info->datAddr);

        sys_fnt->cfnt_data_read(char_info->datAddr, (unsigned char*)&char_bitmap, sizeof(cfont_char_bitmap_struct)-1);
        char_info->code = code;
        char_info->bitPoint = g_sys_font_bpp[sys_fnt->cfnt.bitsPerPixel];
        char_info->mcuData  = sys_fnt->cfnt.mcu_flash;
        char_info->alinSize = sys_fnt->cfnt.alinSize;
        char_info->lineFlag = char_map.lineFlag;
        char_info->xDist = char_map.xDist;
        char_info->xSize = char_bitmap.xSize;
        char_info->ySize = char_bitmap.ySize;
        char_info->xPos = char_bitmap.xPos;
        char_info->yPos = char_bitmap.yPos;

        return char_info->datAddr;
    }
}

#if MAX_SYS_FONT_CACHE
static unsigned short cfont_cache_get_tstamp(void)
{
    g_sys_font_cache_tstamp ++;
    if (g_sys_font_cache_tstamp == 0) {
        memset(g_sys_font_cache.tStamp, 0, sizeof(g_sys_font_cache.tStamp));
        g_sys_font_cache_tstamp = 1;
    }
    return g_sys_font_cache_tstamp;
}
static int cfont_find_in_cache(unsigned int szType, unsigned short code, font_char_info_struct* info)
{
    int idx;
    for (idx=0; idx<MAX_SYS_FONT_CACHE; idx++) {
        if ((g_sys_font_cache.szType[idx] == szType) && (g_sys_font_cache.char_info[idx].code == code)) {
            g_sys_font_cache.tStamp[idx] = cfont_cache_get_tstamp();
            info->code = code;
            info->bitPoint = g_sys_font_cache.char_info[idx].bitPoint;
            info->mcuData  = g_sys_font_cache.char_info[idx].mcuData;
            info->alinSize = g_sys_font_cache.char_info[idx].alinSize;
            info->lineFlag = g_sys_font_cache.char_info[idx].lineFlag;
            info->xDist    = g_sys_font_cache.char_info[idx].xDist;
            info->xSize   = g_sys_font_cache.char_info[idx].xSize;
            info->ySize   = g_sys_font_cache.char_info[idx].ySize;
            info->xPos    = g_sys_font_cache.char_info[idx].xPos;
            info->yPos    = g_sys_font_cache.char_info[idx].yPos;
            info->datAddr = g_sys_font_cache.char_info[idx].datAddr;
            return info->datAddr;
        }
    }
    return -1;
}
static int cfont_push_into_cache(unsigned int szType, font_char_info_struct* info)
{
    unsigned int idx, found = 0, refidx = 0, tstamp = 0x10000;
    for (idx=0; idx<MAX_SYS_FONT_CACHE; idx++) {
        if ((g_sys_font_cache.char_info[idx].code == 0) || (g_sys_font_cache.tStamp[idx] == 0)) {
            found = 1;
            break;
        }
        // take the smallest.
        if (tstamp > g_sys_font_cache.tStamp[idx]) {
            tstamp = g_sys_font_cache.tStamp[idx];
            refidx = idx;
        }
    }
    if (!found) {
        idx = refidx;
    }
    g_sys_font_cache.tStamp[idx] = cfont_cache_get_tstamp();
    g_sys_font_cache.szType[idx] = szType;
    g_sys_font_cache.char_info[idx].code  = info->code;
    g_sys_font_cache.char_info[idx].bitPoint = info->bitPoint;
    g_sys_font_cache.char_info[idx].mcuData  = info->mcuData;
    g_sys_font_cache.char_info[idx].alinSize = info->alinSize;
    g_sys_font_cache.char_info[idx].lineFlag = info->lineFlag;
    g_sys_font_cache.char_info[idx].xDist = info->xDist;
    g_sys_font_cache.char_info[idx].xSize = info->xSize;
    g_sys_font_cache.char_info[idx].ySize = info->ySize;
    g_sys_font_cache.char_info[idx].xPos  = info->xPos;
    g_sys_font_cache.char_info[idx].yPos  = info->yPos;
    g_sys_font_cache.char_info[idx].datAddr=info->datAddr;
    return 0;
}
#endif


///////////////////////////////////////////////////////////////////////////////////
// 获取字体高度
// param:
//   szType - 字体大小(SYS_FONT_TYPE) ..
// return：
//       -1 - 错误 (系统字库中找不到这个字符) ..
//    other - 字体高度
int font_get_height(unsigned int szType)
{
    if (szType >= SYS_FONT_MAX) {
        return -1;
    }
    return g_sys_fonts[szType][0].cfnt.ySize;
}


///////////////////////////////////////////////////////////////////////////////////
// 检查是否安装字体
// param:
//   szType - 字体大小(SYS_FONT_TYPE) ..
// return：
//    szType 或者 字体没有安装时，返回小一号已安装字体
unsigned int font_chk_size(unsigned int szType)
{
	if (szType >= SYS_FONT_MAX)	szType = SYS_FONT_MAX-1;
    while (szType) {
        if (g_sys_font_number[szType] != 0) {
            break;
        }
        szType --;
    }
    return szType;
}


///////////////////////////////////////////////////////////////////////////////////
// 从系统字库(包括客制安装字库)中获取指定字符的信息 ..
// param：
//   szType - 字体大小(SYS_FONT_TYPE) ..
//     code - 字符unicode编码
//     info - [out] 携带字符信息返回
// return：
//       -1 - 错误 (系统字库中找不到这个字符) ..
//    other - 获取成功，返回字符在flash中的地址(同：info->datAddr)
int font_get_char(unsigned int szType, unsigned short code, font_char_info_struct* info)
{
    int ret, idx;

    if (szType >= SYS_FONT_MAX) {
        return -1;
    }

#if MAX_SYS_FONT_CACHE
    // find cache.
    ret = cfont_find_in_cache(szType, code, info);
    if (ret > 0) return ret;
#endif

    //SYS_DEBUG("font_get_char: type=%d, num=%d", szType, g_sys_font_number[szType]);
    for (idx=0; idx<g_sys_font_number[szType]; idx++) {
        ret = cfont_find_char(&g_sys_fonts[szType][idx], code, info);
        if (ret > 0) {
            break;
        }
    }

#if MAX_SYS_FONT_CACHE
    if (ret > 0) {
        // set cache
        cfont_push_into_cache(szType, info);
    }
#endif

    //SYS_DEBUG("font_get_char: type=%d, code=%x, %d, %d, %d", szType, code, info->bitPoint, info->xDist, ret);

    return ret;
}


///////////////////////////////////////////////////////////////////////////////////
// 初始化cfont
void font_init(void)
{
    unsigned int idx;

    SYS_DEBUG("font_init");

    memset(g_sys_fonts, 0, SYS_FONT_MAX*MAX_SYS_FONTS*sizeof(sys_font_info_struct));
    for (idx=0; idx<SYS_FONT_MAX; idx++) {
        g_sys_font_number[idx] = 0;
    }
    g_sys_font_bpp[0] = 1;
    g_sys_font_bpp[1] = 2;
    g_sys_font_bpp[2] = 4;
    g_sys_font_bpp[3] = 8;

    // 安装初始字库 ....
    for (idx=0; idx<FONT_RESOURCE_NUM; idx++) {
        font_install(cfont_resource[idx].szType, cfont_resource[idx].datAddr);
    }

#ifdef FONT_RESOURCE_INT_NUM
    // 安装初始字库 ....
    for (idx=0; idx<FONT_RESOURCE_INT_NUM; idx++) {
        font_install_internal(cfont_resource_int[idx].szType, cfont_resource_int[idx].datAddr);
    }
#endif

#if MAX_SYS_FONT_CACHE
    // 初始化 cache ..
    g_sys_font_cache_tstamp = 0;
    memset(&g_sys_font_cache, 0, sizeof(g_sys_font_cache));
#endif
}


///////////////////////////////////////////////////////////////////////////////////
// 安装客制字库
// param:
//   szType - 字体大小(SYS_FONT_TYPE) ..
//     addr - 客制字库的地址
// return：
//       -1 - 错误（当前系统中字库数超过了 MAX_SYS_FONTS ）...
//    other - 安装成功.
int font_install(unsigned int szType, unsigned int addr)
{
    unsigned char count;

    SYS_DEBUG("font_install(%d, 0x%x)", szType, addr);

    if (szType >= SYS_FONT_MAX || addr == 0) {
        return -1;
    }

    count = g_sys_font_number[szType];
    if (count < MAX_SYS_FONTS) {

		block_spi_flash_read(addr, (unsigned char*)&g_sys_fonts[szType][count].cfnt, sizeof(cfont_info_struct));
        if (g_sys_fonts[szType][count].cfnt.magic != FONT_MAGIC) {
            // error data
            DBG_DIRECT("font_install(error 0) %x", g_sys_fonts[szType][count].cfnt.magic);
            return -1;
        }

        g_sys_fonts[szType][count].cfnt.mcu_flash = 0;
        g_sys_fonts[szType][count].addr = addr;
        g_sys_fonts[szType][count].cfnt_data_read = block_spi_flash_read;

        g_sys_font_number[szType] ++;
        return 0;
    }
    DBG_DIRECT("font_install(error 1)");
    return -1;
}

///////////////////////////////////////////////////////////////////////////////////
// 安装客制字库
// param:
//   szType - 字体大小(SYS_FONT_TYPE) ..
//     addr - 客制字库的地址
// return：
//       -1 - 错误（当前系统中字库数超过了 MAX_SYS_FONTS ）...
//    other - 安装成功.
int font_install_internal(unsigned int szType, void* addr)
{
    unsigned char count;

    SYS_DEBUG("font_install_internal(%d, 0x%x)", szType, addr);

    if (szType >= SYS_FONT_MAX) {
        return -1;
    }

    count = g_sys_font_number[szType];
    if (count < MAX_SYS_FONTS) {
        memcpy((unsigned char*)&g_sys_fonts[szType][count].cfnt, addr, sizeof(cfont_info_struct));
        if (g_sys_fonts[szType][count].cfnt.magic != FONT_MAGIC) {
            // error data
            DBG_DIRECT("font_install_internal(error %d, %x)", szType, addr);
            return -1;
        }
        g_sys_fonts[szType][count].cfnt.mcu_flash = 1;
        g_sys_fonts[szType][count].addr = (unsigned int)addr;
        g_sys_fonts[szType][count].cfnt_data_read = cfnt_data_read_int;

        g_sys_font_number[szType] ++;
        return 0;
    }
    DBG_DIRECT("font_install_internal(error 1)");
    return -1;
}


///////////////////////////////////////////////////////////////////////////////////
// 从指定字库中获取一个字符信息
// param:
//     addr - 客制字库的地址
//     code - unicode
//     info - [out] 携带字符信息返回
// return：
//       -1 - 错误 (系统字库中找不到这个字符) ..
//    other - 获取成功，返回字符在flash中的地址(同：info->datAddr)
int font_get_char_ext(unsigned int addr, unsigned short code, font_char_info_struct* info)
{
    sys_font_info_struct font_info;

    block_spi_flash_read(addr, (unsigned char*)&font_info.cfnt, sizeof(cfont_info_struct));
    if (font_info.cfnt.magic != FONT_MAGIC) {
        // error data
        DBG_DIRECT("font_get_char_ext(error %x)", addr);
        return -1;
    }

    font_info.addr = addr;
    return cfont_find_char(&font_info, code, info);
}


///////////////////////////////////////////////////////////////////////////////////
// 获取指定字库的字体高度
// param:
//     addr - 客制字库的地址
// return：
//       -1 - 错误 (系统字库中找不到这个字符) ..
//    other - 字体高度
int font_get_height_ext(unsigned int addr)
{
    sys_font_info_struct font_info;

    block_spi_flash_read(addr, (unsigned char*)&font_info.cfnt, sizeof(cfont_info_struct));
    if (font_info.cfnt.magic != FONT_MAGIC) {
        // error data
        DBG_DIRECT("font_get_height_ext(error %x)", addr);
        return -1;
    }
    return font_info.cfnt.ySize;
}


///////////////////////////////////////////////////////////////////////////////////
// 显示一个字符
// param:
//        x -
//        y -
//     info - [in] 字符信息
// return：
//       -1 - 错误 (系统字库中找不到这个字符) ..
//    other - 成功
int font_disp_char(int x, int y, font_char_info_struct* info)
{
#if 0
    if (info->datAddr != 0) {
        block_spi_flash_read(info->datAddr, (unsigned char*)g_cfont_bitmap, MAX_CFONT_CHAR_DATA);
        if (info->bitPoint == 1) {
        }
        else {
        }
    }
#endif
    return 0;
}


font_char_bitmap_struct* font_get_bitmap(font_char_info_struct* char_info)
{
#if 1
    static unsigned int addr_rd = 0;

    font_char_bitmap_struct* bmp = (font_char_bitmap_struct*)g_cfont_bitmap;
    if (addr_rd != char_info->datAddr) {
        unsigned int size = sizeof(font_char_bitmap_struct) + ((char_info->xSize * char_info->bitPoint + (8-char_info->bitPoint))/8) * char_info->ySize;
        if (size > MAX_CFONT_CHAR_DATA) {
            size = MAX_CFONT_CHAR_DATA;
        }
        if (char_info->mcuData) {
            cfnt_data_read_int(char_info->datAddr, (unsigned char*)bmp, size);
        }
        else {
            block_spi_flash_read(char_info->datAddr, (unsigned char*)bmp, size);
        }
        addr_rd = char_info->datAddr;
    }
#else
    font_char_bitmap_struct* bmp = (font_char_bitmap_struct*)gui_drivers_flash_get_share_buff();
    unsigned int size = sizeof(font_char_bitmap_struct) + ((char_info->xSize * char_info->bitPoint + (8-char_info->bitPoint))/8)*8*char_info->ySize;
    block_spi_flash_read(char_info->datAddr, (unsigned char*)bmp, size);
#endif
    return bmp;
}


font_char_bitmap_struct* font_get_bitmap_ext(font_char_info_struct* char_info, unsigned char* buff, unsigned int buff_len)
{
    font_char_bitmap_struct* bmp = (font_char_bitmap_struct*)buff;
    if (bmp != NULL) {
        unsigned int size = sizeof(font_char_bitmap_struct) + ((char_info->xSize * char_info->bitPoint + (8-char_info->bitPoint))/8) * char_info->ySize;
        if (size > buff_len) {
            size = buff_len;
        }
        //SYS_DEBUG("flash_read, size=%d", size);
        if (char_info->mcuData) {
            cfnt_data_read_int(char_info->datAddr, (unsigned char*)bmp, size);
        }
        else {
            block_spi_flash_read(char_info->datAddr, (unsigned char*)bmp, size);
        }
    }
    return bmp;
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// test
#if 0
void cfont_disp_string_test(void)
{
    //                               中国人(CN)説...
    unsigned short test_unicode[] = {0x4E2D, 0x56FD, 0x4EBA, '(', 'C', 'N', ')', 0x8AAC, 0};

    font_char_info_struct          char_info;

    unsigned int sw = 0, idx, tx, ty;
    int ret;


    for(idx=0; idx<8; idx++) {
        ret = font_get_char(SYS_FONT_SMALL, test_unicode[idx], &char_info);
        //printf("string_test: xd =%d, th =%d, dat=%d\r\n", char_info.xDist, char_info.ySize, char_info.datAddr);
        if (ret > 0) {
            sw += char_info.xDist;
        }
        else {
            //printf("not found: %x\r\n", test_unicode[idx]);
        }
    }

    tx = (390 - sw)/2;
    ty = 100;

    //printf("string_test: sw =%d, sh =%d\r\n", sw, char_info.ySize);

    for(idx=0; idx<8; idx++) {
        ret = font_get_char(SYS_FONT_SMALL, test_unicode[idx], &char_info);
        if (ret > 0) {
            block_spi_flash_read(char_info.datAddr, (unsigned char*)g_cfont_bitmap, MAX_CFONT_CHAR_DATA);
            if (char_info.bitPoint == 1) {
                ui_draw_buffer(g_cfont_bitmap->bitmap, 1, tx+g_cfont_bitmap->xPos, ty+g_cfont_bitmap->yPos,
                                g_cfont_bitmap->xSize, g_cfont_bitmap->ySize, 1);
            }
            else {
                ui_draw_buffer_bit(g_cfont_bitmap->bitmap, 1, tx+g_cfont_bitmap->xPos, ty+g_cfont_bitmap->yPos,
                                g_cfont_bitmap->xSize, g_cfont_bitmap->ySize, char_info.bitPoint);
            }
            tx += char_info.xDist;
        }
        else {
            //printf("not found: %x\r\n", test_unicode[idx]);
        }
    }
}


void cfont_disp_hello_test(void)
{
    //                               Hindi
    unsigned short test_unicode[] = {0x092C, 0x0921, 0x093C, 0x093E, 0x002C, 0x0020, 0x092E,
                             0x0927, 0x094d, 0x092f, 0x092e, 0x0020, 0x0914, 0x0930, 0x0020,
                             0x091b, 0x094b, 0x091f, 0x093e, 0x0020, 0};

    font_char_info_struct          char_info;

    unsigned int sw = 0, sh = 0, idx, tx, ty;
    int ret;

    sh = font_get_height(SYS_FONT_MEDIUM);
    for(idx=0; idx<20; idx++) {
        ret = font_get_char(SYS_FONT_MEDIUM, test_unicode[idx], &char_info);
        //printf("string_test: xd =%d, th =%d, dat=%d\r\n", char_info.xDist, char_info.ySize, char_info.datAddr);
        if (ret > 0) {
            sw += char_info.xDist;
        }
        else {
            //printf("not found: %x\r\n", test_unicode[idx]);
        }
    }

    tx = (390 - sw)/2;
    ty = (390 - sh)/2;

    //printf("string_test: sw =%d, sh =%d\r\n", sw, char_info.ySize);

    for(idx=0; idx<20; idx++) {
        ret = font_get_char(SYS_FONT_MEDIUM, test_unicode[idx], &char_info);
        if (ret > 0) {
            block_spi_flash_read(char_info.datAddr, (unsigned char*)g_cfont_bitmap, MAX_CFONT_CHAR_DATA);
            if (char_info.bitPoint == 1) {
                ui_draw_buffer(g_cfont_bitmap->bitmap, 1, tx+g_cfont_bitmap->xPos, ty+g_cfont_bitmap->yPos,
                                g_cfont_bitmap->xSize, g_cfont_bitmap->ySize, 1);
            }
            else {
                ui_draw_buffer_bit(g_cfont_bitmap->bitmap, 1, tx+g_cfont_bitmap->xPos, ty+g_cfont_bitmap->yPos,
                                g_cfont_bitmap->xSize, g_cfont_bitmap->ySize, char_info.bitPoint);
            }
            tx += char_info.xDist;
        }
        else {
            //printf("not found: %x\r\n", test_unicode[idx]);
        }
    }
}
#endif
#endif


