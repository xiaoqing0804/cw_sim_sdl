#include <stdio.h>
#include <string.h>
#include "barcode_code128c.h"

static const unsigned char* g_barcode_code128c_line_table[107] = { 
	"212222", "222122", "222221", "121223", 
	"121322", "131222", "122213", "122312", 
	"132212", "221213", "221312", "231212", 
	"112232", "122132", "122231", "113222",
	"123122", "123221", "223211", "221132", 
	"221231", "213212", "223112", "312131", 
	"311222", "321122", "321221", "312212", 
	"322112", "322211", "212123", "212321", 
	"232121", "111323", "131123", "131321", 
	"112313", "132113", "132311", "211313", 
	"231113", "231311", "112133", "112331", 
	"132131", "113123", "113321", "133121", 
	"313121", "211331", "231131", "213113",
	"213311", "213131", "311123", "311321", 
	"331121", "312113", "312311", "332111", 
	"314111", "221411", "431111", "111224", 
	"111422", "121124", "121421", "141122", 
	"141221", "112214", "112412", "122114", 
	"122411", "142112", "142211", "241211", 
	"221114", "413111", "241112", "134111", 
	"111242", "121142", "121241", "114212", 
	"124112", "124211", "411212", "421112",
	"421211", "212141", "214121", "412121", 
	"111143", "111341", "131141", "114113", 
	"114311", "411113", "411311", "113141", 
	"114131", "311141", "411131", "211412", 
	"211214", "211232", "2331112"
};

static const unsigned short g_barcode_code128c_value_table[107] =
{
    0x6cc, /*0*/	0x66c, /*1*/	0x666, /*2*/	0x498, /*3*/
    0x48c, /*4*/	0x44c, /*5*/	0x4c8, /*6*/	0x264, /*7*/  
	0x464, /*8*/	0x648, /*9*/	0x644, /*10*/	0x624, /*11*/
	0x59c, /*12*/	0x4dc, /*13*/	0x4ce, /*14*/	0x5cc, /*15*/
	0x4ec, /*16*/	0x4e6, /*17*/	0x672, /*18*/	0x65c, /*19*/
	0x64e, /*20*/	0x6e4, /*21*/	0x674, /*22*/	0x76e, /*23*/
	0x74c, /*24*/	0x72c, /*25*/	0x726, /*26*/	0x764, /*27*/
	0x734, /*28*/	0x732, /*29*/	0x6d8, /*30*/	0x6c6, /*31*/
	0x636, /*32*/	0x518, /*33*/	0x458, /*34*/	0x446, /*35*/
	0x588, /*36*/	0x468, /*37*/	0x462, /*38*/	0x688, /*39*/
	0x628, /*40*/	0x622, /*41*/	0x5b8, /*42*/	0x58e, /*43*/
	0x46e, /*44*/	0x5d8, /*45*/	0x5c6, /*46*/	0x476, /*47*/
	0x776, /*48*/	0x68e, /*49*/	0x62e, /*50*/	0x6e8, /*51*/
	0x6e2, /*52*/	0x6ee, /*53*/	0x758, /*54*/	0x746, /*55*/
	0x716, /*56*/	0x768, /*57*/	0x762, /*58*/	0x71a, /*59*/
	0x77a, /*60*/	0x642, /*61*/	0x78a, /*62*/	0x530, /*63*/
	0x50c, /*64*/	0x4b0, /*65*/	0x486, /*66*/	0x42c, /*67*/
	0x426, /*68*/	0x590, /*69*/	0x584, /*70*/	0x4d0, /*71*/
	0x4c2, /*72*/	0x434, /*73*/	0x432, /*74*/	0x612, /*75*/
	0x650, /*76*/	0x7ba, /*77*/	0x614, /*78*/	0x47a, /*79*/
	0x53c, /*80*/	0x4ac, /*81*/	0x45e, /*82*/	0x5e4, /*83*/
	0x4f4, /*84*/	0x4f2, /*85*/	0x7a4, /*86*/	0x794, /*87*/
	0x792, /*88*/	0x6de, /*89*/	0x6f6, /*90*/	0x7b6, /*91*/
	0x578, /*92*/	0x51e, /*93*/	0x45e, /*94*/	0x5e8, /*95*/
	0x5e2, /*96*/	0x7a8, /*97*/	0x7a2, /*98*/	0x5de, /*99*/
	0x5ee, /*100*/	0x75e, /*101*/	0x7ae, /*102*/	0x684, /*103*/
	0x690, /*104*/	0x69c, /*105*/	0x18eb, /*106*/
};

int barcode_code128c_create(unsigned char* data, unsigned char data_len, unsigned char* code_data, unsigned char code_data_len)
{
	unsigned char i = 0;
	unsigned int verify_bit = 0;

    if(data == NULL || code_data == NULL)
        return -1;

	if(data_len >= BARCODE_MAX_INPUT_DATA_LEN || code_data_len < (BARCODE_CODE128C_OTHER_LEN + data_len))
        return -1;

    memset(code_data, 0, code_data_len);

	code_data[0] = BARCODE_CODE128C_START_CHAR;
	verify_bit = BARCODE_CODE128C_START_CHAR;

	for(i = 0; i < data_len; i++)
	{
        code_data[i + 1] = data[i];
		verify_bit = verify_bit + (i + 1)*data[i];
	}
    
	verify_bit = verify_bit % 103; 
	code_data[i + 1] = verify_bit;
	code_data[i + 2] = BARCODE_CODE128C_STOP_CHAR;

	return 0;
}

short barcode_code128c_get_width_by_all_len(unsigned char code_data_len)
{
	return (code_data_len - 1) * 11 + 13;
}

short barcode_code128c_get_width_by_orgin_len(unsigned char data_len)
{
	return (data_len + 2) * 11 + 13;
}

const unsigned char* barcode_code128c_get_line(unsigned char index)
{
	if(index >= countof(g_barcode_code128c_line_table))
		index = 0;
	return g_barcode_code128c_line_table[index];
}

unsigned short barcode_code128c_get_value(unsigned char index)
{
	if(index >= countof(g_barcode_code128c_value_table))
		index = 0;
	return g_barcode_code128c_value_table[index];
}

