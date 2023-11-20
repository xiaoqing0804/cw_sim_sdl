#ifndef _OTA_UPDATA_H
#define _OTA_UPDATA_H

extern unsigned char ota_check(void);
extern void ota_updata(void);
extern unsigned char test_ota_label_set(void);
extern void block_check_patch_img_OTA(void);

#endif //_OTA_UPDATA_H


