#ifndef _DATA_TRANSFER_PACKAGE_H
#define _DATA_TRANSFER_PACKAGE_H

#include "data_transfer.h"

#define TEST_PRINTF_PACKAGE_EN		0


typedef struct{
	unsigned char flag;
	unsigned char buf[20];
}send_ack_struct;

typedef struct send_datatype_struct_t send_datatype_struct;
struct send_datatype_struct_t
{
	const unsigned char data_type;
	const unsigned int len;
	unsigned char * const data;
	unsigned int (* const fun)(const send_datatype_struct *info);	//return the real data length.
};

typedef struct
{
	unsigned char send_N;
	unsigned int cmd_send_pos;
	unsigned int cmd_len;
	unsigned char cmd_data[(MAX_SEND_INDEX+1)*20];
	unsigned int ack_len;
	unsigned char ack_data[20];
}ble_send_data_struct;

typedef enum
{
	OTA_APP_CRC16,
	OTA_FLASH_CRC16,
}OTA_CRC16_TYPE;

typedef struct
{
	unsigned char data_type;
	unsigned int len;
	unsigned char const *const data;
}mix_datatype_struct;

extern ble_send_data_struct ble_data;

extern unsigned short calculate_crc16(unsigned short crc16,unsigned char *buf, unsigned int len);
extern void test_printf_package(unsigned char *package_data,unsigned short len);
extern void send_ack_timer_handler(void *argument);
extern unsigned char send_datatype_info_to_app(unsigned char data_type);
extern void mix_package_init(void);
extern void check_gsensor_data_timer_handler(void *argument);
extern void send_ack_to_app(head_package_struct *head_info, unsigned char ack_type);

#endif //_DATA_TRANSFER_PACKAGE_H

