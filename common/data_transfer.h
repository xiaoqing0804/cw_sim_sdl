#ifndef _DATA_TRANSFER_H_
#define _DATA_TRANSFER_H_

#include "pid_type.h"
#include "dev_version.h"


// 20211220 Taylor.Le, +
//#if (PID_NUM > 255)
#define BLE_DATA_TRANSFER_V2        // 20211220 Taylor.Le, +
//#endif
// 

#define MAX_SEND_INDEX		(16)	//send cmd data frame.
#define MAX_RECV_INDEX		(16)	//receive cmd data frame.
#define HEAD_DATA_LEN		(10)		//receive head frame data length.

#if ((MAX_SEND_INDEX > 255)||(MAX_RECV_INDEX > 255))
	#error "error: the MAX_INDEX is more than 255 !!!"
#endif

typedef struct
{
	unsigned char index;
	unsigned char pid;
	unsigned char all_index;
	unsigned char N;
#ifdef BLE_DATA_TRANSFER_V2
    unsigned char cmd_type:4;
    unsigned char pid_high:4;
#else
	unsigned char cmd_type;
#endif
	unsigned char data_type;
	unsigned char crc16[2];
	unsigned char len[2];
	unsigned char data[HEAD_DATA_LEN];
}head_package_struct;

typedef struct
{
	unsigned char index;
	unsigned char data[19];
}data_package_struct;

typedef struct
{
	unsigned char head_data[HEAD_DATA_LEN];
	unsigned char data[MAX_RECV_INDEX][19];
}cmd_data_struct;

typedef struct
{
	unsigned char cmd_type;
	unsigned char data_type;
	unsigned int len;
	unsigned char *data;
}cmd_package_struct;

typedef enum
{
	CMD_TYPE_NULL = 0,
	CMD_TYPE_SEND,
	CMD_TYPE_SEND_NO_ACK,
	CMD_TYPE_REQUEST,
	CMD_TYPE_ACK,
}CMD_TYPE;

typedef enum
{
	ACK_TYPE_NULL = 0,
	ACK_TYPE_SUCCESS,
	ACK_TYPE_WRONG,
	ACK_TYPE_CRC16_WRONG,
	ACK_TYPE_OVER,
	ACK_TYPE_OTA_IMG_CRC16_ERROR,
	ACK_TYPE_OTA_IMG_SIZE_ERROR,
	ACK_TYPE_OTA_IMG_POS_ERROR,
	ACK_TYPE_OTA_IMG_DATA_ERROR,
}ACK_TYPE;

#define TEMP_LEN	16
typedef struct
{
	unsigned char send_type;
	unsigned char write_pos;
	unsigned char timeoutNums;
	unsigned char temp[TEMP_LEN];
}send_cmd_struct_t;

extern send_cmd_struct_t send_cmd_queue_struct;


typedef enum
{
	BLE_DISCONNECT = 0,
	BLE_CONNECT,
}BLE_STATUS;

typedef enum
{
	STATUS_OK = 0,
	STATUS_ERROR,
	STATUS_CMD_ERROR,
	STATUS_TYPE_ERROR,
	STATUS_DATA_NULL,
	STATUS_SIZE_ERROR,
	STATUS_ARGU_ERROR,
}RETURN_STATUS;

typedef struct
{
	DATA_TYPE type;
	unsigned char (*function)(cmd_package_struct *argument);
}recv_cmd_struct;

typedef enum
{
	PUSH_TYPE_CLEAR = 0,
	PUSH_TYPE_RESEND,
}PUSH_OUT_TYPE;

typedef enum
{
	PUSH_QUEUE_IN = 0,
	PUSH_QUEUE_OUT,
}PUSH_QUEUE_TYPE;

extern void check_app_active_timer_handler(void *argument);
extern void ble_connect_init_timer_handler(void *argument);
extern void ble_receive_data_handler(unsigned char *data);
extern void ble_connect_init(BLE_STATUS ble_status);
extern void send_cmd_timer_handler(void *argument);
extern void wait_ack_timeout_timer_handler(void *argument);
extern unsigned char check_queue_status(void);
extern unsigned char check_data_type_queue_status(DATA_TYPE data_type);
extern unsigned char push_data_type_to_queue(DATA_TYPE data_type);
extern unsigned char get_ble_connect_flag(void);
extern void data_transfer_init(void);

#endif

