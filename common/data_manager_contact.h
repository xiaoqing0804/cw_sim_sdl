#ifndef _DATA_MANAGER_CONTACT_H
#define _DATA_MANAGER_CONTACT_H
#include "data_common.h"


#define SAVE_CONTACT_NUM_COUNT                 sizeof(Contact_t)*CONTACT_MAX_NUM+1
#define SAVE_CONTACT_NUM_Address               SECTOR_0_CONTACT_BASE         
#define SAVE_CONTACT_PERSON_Address            SECTOR_0_CONTACT_BASE + 1
#define SAVE_CONTACT_LENGTH                    sizeof(Contact_t)

#define  SAVE_RECORD_CONTACT_NUM_COUNT         1
#define  SAVE_RECORD_CONTACT_NUM_Address       SECTOR_0_CONTACT_RECORD_BASE +(1*4*1024)        
#define  SAVE_RECORD_CONTACT_PERSON_Address    SECTOR_0_CONTACT_RECORD_BASE
#define  SAVE_RECORD_CONTACT_LENGTH            sizeof(CALL_RECORD_t)




enum
{
	FLASH_CMD_CONTACT_INIT = 0,
	FLASH_CMD_CONTACT_SAVE,
	FLASH_CMD_CONTACT_READ_CONTACT_NUM,
	FLASH_CMD_CONTACT_ERASE,
	FLASH_CMD_CONTACT_GET_ITEMS,
	FLASH_CMD_CONTACT_CLEAR_ALL,
	FLASH_CMD_CONTACT_FIND,

	FLASH_CMD_CONTACT_HISTORY_INIT,
	FLASH_CMD_CONTACT_HISTORY_SAVE,
	FLASH_CMD_CONTACT_HISTORY_READ_CONTACT_NUM,
	FLASH_CMD_CONTACT_HISTORY_GET_ITEMS,
	FLASH_CMD_CONTACT_HISTORY_CLEAR_ALL,
};


extern CONTACT_t contact;
extern Call_Record_t   call_record;
//extern CALL_RECORD_t   call_record_temp;

extern void block_init_contact_info(void);
extern void block_init_contact_history_info(void);

//清除所有通话记录联系人信息
extern void Clear_All_Current_history_Contact(void);
extern unsigned int block_Clear_All_contact(void);
extern unsigned int block_read_contact_num(void);
extern unsigned int block_read_contact_history_num(void);


extern unsigned int block_delete_contact_item(unsigned char type, unsigned char *data, unsigned int len);
extern unsigned int block_get_contact_Item( Get_Index_Contact_t *data);
extern unsigned int block_get_history_contact_Item( Get_Index_Contact_t *data);

extern unsigned int block_save_contact_history_item(unsigned char type, unsigned char *data, unsigned int len);

extern void  Get_Current_Contact_index(uint8_t index,uint8_t *data);


extern unsigned int block_find_contact_by_number(unsigned char* inNumber, unsigned char* outName, unsigned int outLen);


extern unsigned int block_save_contact_item(unsigned char type, unsigned char *data, unsigned int len);

extern unsigned int data_manager_coneact_handler(unsigned int cmd,void *argument);

extern void block_clear_contact_history_info(void);		// 增加通话记录清除接口
#endif //_DATA_MANAGER_MESSAGE_H

