#ifndef _DATA_PASSTHROUGH_H
#define _DATA_PASSTHROUGH_H

#include "data_transfer.h"

typedef enum{
	MCU_SEND_OK = 0,
	MCU_SEND_NOT_FINISH,
	MCU_SEND_DISCONNECT,
	MCU_SEND_BUSY,
	MCU_SEND_NO_ACK,
	MCU_SEND_DATA_NULL,
	MCU_SEND_LEN_OVER,
}MCU_SEND_STATUS;

typedef struct{
	unsigned int length;
	unsigned int read_pos;
	unsigned int write_pos;
	unsigned char data[(MAX_RECV_INDEX+2)*20]; //it must times of 20 bytes !
}ble_receive_data_struct;

extern void data_passthrough_init(void);
extern void Printf_Data(unsigned char *data,unsigned short len);
extern void clear_ble_receive_data_flag(void);
extern void test_data_passthrough(void *argument);
extern void ble_read_timer_handler(void *argument);
extern void ble_read_data(unsigned char *data,unsigned int length);
extern void ble_send_timer_handler(void *argument);
extern void ble_heart_data_save(unsigned char *data, unsigned int len);


#endif //_DATA_PASSTHROUGH_H


