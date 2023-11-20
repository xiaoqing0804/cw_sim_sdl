#ifndef _DATA_MANAGER_USER_INFO_H
#define _DATA_MANAGER_USER_INFO_H

#define LABEL_STR	__TIME__
#include "data_common.h"

typedef enum
{
	FLASH_CMD_SAVE_ALL_USER_INFO = 0,
	FLASH_CMD_SAVE_USER_INFO,
	FLASH_CMD_INIT_USER_INFO,
}FLASH_CMD_USER_INFO;

typedef struct
{
	unsigned char label[sizeof(LABEL_STR)];
}flash_erase_label_t;

typedef struct{
	unsigned char *const type_addr;
	const unsigned short len;	//the user struct size.
}user_info_struct_t;

typedef struct
{
    unsigned int addr;
}user_data_item_struct;


extern const unsigned int USER_INFO_NUM;
extern const user_info_struct_t *const p_user_info_t;

extern void clear_all_user_info(void);
extern void alarm_compare(void);
extern void drink_alarm_compare(void);
extern unsigned char disturb_check(void);
extern void block_init_user_info(void);
extern void block_save_all_reset_user_info(void);
extern unsigned char block_save_user_info(void *type_addr);
extern unsigned int data_manager_user_info_handler(unsigned int cmd,void *argument);
extern void check_new_day_time(void);
extern void new_day_timer_handler(void *argument);
extern void init_24h_data(void);

extern void block_reset_user_info(void);
extern void clock_alarm_compare(time_struct time);

#endif //_DATA_MANAGER_USER_INFO_H

