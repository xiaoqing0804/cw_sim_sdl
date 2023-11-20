#ifndef _OTA_H
#define _OTA_H

#include "data_manager_flash.h"
#include "data_transfer.h"

#define OTA_INFO	"OTA[I]: "
#define OTA_DBG	    "OTA[D]: "
#define OTA_ERR	    "OTA[E]: "


#define OTA_TMP_ADDR    SECTOR_2_OTA_BASE
#define OTA_TMP_SIZE    SECTOR_2_OTA_SIZE

#define MCU_FLASH_BASE	(OTA_TMP_ADDR)
#define MCU_FLASH_END	(OTA_TMP_ADDR+OTA_TMP_SIZE) //512K.


typedef enum
{
	FLASH_CMD_OTA_SAVE_DATA = 0,
	FLASH_CMD_OTA_SAVE_ITEM,
	FLASH_CMD_OTA_READ_ITEM,
	FLASH_CMD_OTA_CLEAR_ITEM,
	FLASH_CMD_OTA_CHECK_FINISH,
}FLASH_CMD_OTA;

typedef  enum
{
	OTA_NONE = 0,
	OTA_RUNING,
	OTA_FINISH_SUCCESS,
	OTA_FINISH_WRONG,
	OTA_IMG_SIZE_ERROR,
	OTA_IMG_CRC16_ERROR,
	OTA_ITEM_HEAD_LEN_ERROR,
	OTA_ITEM_HEAD_LEN_ERROR_ALL = OTA_ITEM_HEAD_LEN_ERROR + 10,
	OTA_ITEM_MEDIA_ERROR,
	OTA_ITEM_MEDIA_ERROR_ALL = OTA_ITEM_MEDIA_ERROR + 10,
	OTA_ITEM_SIZE_ERROR,
	OTA_ITEM_SIZE_ERROR_ALL = OTA_ITEM_SIZE_ERROR + 10,
	OTA_ITEM_CRC16_ERROR,
	OTA_ITEM_CRC16_ERROR_ALL = OTA_ITEM_CRC16_ERROR + 10,

}OTA_STATUS_TYPE;

typedef  struct
{
	unsigned char status;			//see OTA_STATUS_TYPE
	unsigned char file_crc16[2];	//the all img file crc16
	unsigned char file_size[4];		//the all img file size
	unsigned char file_pos[4];		//the img file current tarnsfer pos.
}OTA_status_struct;

typedef struct
{
	unsigned int ota_img_start_addr;		//the ota img file start address in spi flash.
	unsigned int _ota_img_start_addr;		//the ota_img_addr xor value.
	unsigned int ota_img_end_addr;			//the ota img file end address in spi flash.
	unsigned int _ota_img_end_addr;			//the ota_img_addr xor value.
	unsigned int label;						//the ota updata label , it must 0x1A2B3C4D.
	unsigned int _label;					//the label xor value.
}OTA_label_struct;


typedef struct
{
    unsigned int write_addr;
    unsigned char *pdata;
    unsigned int len;
}ota_data_struct;

//================================================================
// ota-data-package
typedef  struct
{
	unsigned char file_crc16[2];	//the all img file crc16
	unsigned char file_size[4];		//the all img file size
	unsigned char file_pos[4];		//the img file current tarnsfer pos.
}OTA_file_struct;

typedef struct
{
	OTA_file_struct head;	//ota info head data.
	unsigned char data[1];	//ota data point.
}OTA_send_data_struct;
//================================================================

typedef	enum
{
	FILE_TYPE_NULL = 0,
	FILE_TYPE_CUSTOMER,
	FILE_TYPE_HARDWARE,
	FILE_TYPE_CODE,
	FILE_TYPE_PIC,
	FILE_TYPE_FONT,
	FILE_TYPE_DATA,
}OTA_FILE_TYPE;

typedef enum
{
	MEDIA_MCU_FLASH = 0,	//MCU flash.
	MEDIA_SPI_FLASH,		//SPI flash.
	MEDIA_SUM
}OTA_FILE_MEDIA_TYPE;


//#ifdef BLE_DATA_TRANSFER_V2
//  *.img file format:
// ==============================================================
// img_head:    {OTA_img_head_struct}
// --------------------------------------------------------------
// item custom:  {OTA_item_head_struct}
// --------------------------------------------------------------
// item hw:      {OTA_item_head_struct}
// --------------------------------------------------------------
// item code:    {OTA_item_head_struct}  + app.bin
// --------------------------------------------------------------
// item pic:     {OTA_item_head_struct}
// --------------------------------------------------------------
// item font:    {OTA_item_head_struct}  + picture_font_merge.bin
// --------------------------------------------------------------
// item data:    {OTA_item_head_struct}
// ==============================================================
//#endif

// img-file, file-head
typedef struct
{
	unsigned char len[4];			//the all img length , include itself.
	unsigned char crc16[2];			//the all img crc16 , none iteself.
	unsigned char items;			//the img has file number.
}OTA_img_head_struct;

// img-file, item-head
typedef	struct
{
	unsigned char head_len;			//the file head length , include itself , but don't user data.
#ifdef BLE_DATA_TRANSFER_V2
    unsigned char file_type:4;        //the file type , see OTA_FILE_TYPE.
    unsigned char ver_high:4;        //the file type , see OTA_FILE_TYPE.
#else
	unsigned char file_type;		//the file type , see OTA_FILE_TYPE.
#endif
	unsigned char version_id;		//this file version id.
	unsigned char media_type;		//the data media.
	unsigned char start_addr[4];	//the data media start address.
	unsigned char end_addr[4];		//the data media end address.
	unsigned char data_len[4];		//the data length.
	unsigned char data_crc16[2];	//the data crc16.
}OTA_item_head_struct;

// 
typedef struct
{
    OTA_img_head_struct  img_head;         // img file head
    OTA_item_head_struct item_head;        // current download item
    unsigned char temp_rev[8];

    // OTA_item_head info
	unsigned char img_item_start_addr[4];	//the data media start address.
	unsigned char img_item_end_addr[4];		//the data media end address.
	unsigned char img_item_data_len[4];		//the data length.
	unsigned char img_item_data_crc16[2];	//the data crc16.
    unsigned char img_item_type;
	
    // download
    unsigned char ota_status;               // fsm 
    unsigned char img_item_write_addr[4];
    unsigned char item_flags[12];               // 
    unsigned char data_remaind[4];

}OTA_fsm_struct;


extern OTA_status_struct g_OTA_status;

extern unsigned short spi_flash_crc16(unsigned short crc16, unsigned int addr, unsigned int len);

extern unsigned char handler_ota_data(cmd_package_struct *argument);
extern unsigned char block_save_ota_data_to_flash(unsigned int write_addr, unsigned char *data, unsigned int len);
extern unsigned char block_restore_ota_item_from_flash(void);
extern unsigned char block_check_ota_finish(void);
extern unsigned int data_manager_OTA_handler(unsigned int cmd,void *argument);

extern void ota_finish_timer_handler(void *argument);
extern unsigned char ota_font_updata_check(void);
extern unsigned char ota_is_updating(void);
extern unsigned char ota_get_status(unsigned int* fileSize, unsigned int* filePos);

extern void ota_factory_reset(void);

extern void ota_test_update(void* argument);

#endif //_OTA_H

