#ifndef __BARCODE_CODE128C_H__
#define __BARCODE_CODE128C_H__

#include "feature_all.h"

#define BARCODE_MAX_INPUT_DATA_LEN (60)

#define BARCODE_CODE128C_OTHER_LEN (3)
#define BARCODE_CODE128C_START_CHAR (105)
#define BARCODE_CODE128C_STOP_CHAR (106)
#define BARCODE_CODE128C_MAX_CHAR (7)

extern int   barcode_code128c_create(unsigned char* pData, unsigned char nInputLen, unsigned char* pRes, unsigned char nResLen);
extern short barcode_code128c_get_width_by_all_len(unsigned char code_data_len);
extern short barcode_code128c_get_width_by_orgin_len(unsigned char data_len);
extern const unsigned char* barcode_code128c_get_line(unsigned char index);
extern unsigned short barcode_code128c_get_value(unsigned char index);

#endif