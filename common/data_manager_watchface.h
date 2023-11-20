#ifndef _DATA_MANAGER_WATCHFACE_H
#define _DATA_MANAGER_WATCHFACE_H

#include "watchface.h"


typedef enum
{
	WATCHFACE_SUCCESS = 0,
	WATCHFACE_ERR_LEN,
	WATCHFACE_ERR_CMD_NULL,
	WATCHFACE_ERR_OVER,
	WATCHFACE_ERR_NOT_SAME,
}WATCHFACE_ERR_TYPE;

typedef struct
{
	unsigned char cmd;
	unsigned char all_len[4];
	unsigned char current_pos[4];
	unsigned char data[1];
}watchface_data_struct;

typedef struct
{
	unsigned char index; //当前表盘的序号, 0 ~ 3
	unsigned char cmd2_info[sizeof(watchface_setting_struct)-4];
	unsigned char cmd3_id[2];
	unsigned char cmd; //正在传输的表盘序号
	unsigned char all_len[4]; //整个数据包的长度
	unsigned char current_pos[4]; //当前已传输的偏移地址
}watch_face_info_struct;

extern watch_face_info_struct watchface_info;
extern unsigned char ble_watchface_flag;

extern unsigned char watchface_data_handler(unsigned char *data, unsigned int len);
extern void set_watchface_info(void);
extern void watchface_data_buf_set(unsigned int len);
extern void ble_watchface_set(unsigned char onoff);
extern unsigned char ble_watchface_flag_get(void);
extern unsigned char ble_watchface_data_save(const unsigned char *data, unsigned int len);
extern void ble_long_package_timer_handler(void *argument);
extern unsigned int watchface_transfer_flag_get(void);

extern void data_manager_watchface_reset_factory(void);


#endif //_DATA_MANAGER_WATCHFACE_H


