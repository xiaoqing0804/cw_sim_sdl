#ifndef _FACTORY_TEST_H
#define _FACTORY_TEST_H

#include "sys_timer_thread.h"
#include "pin_define.h"

#define FACTORY_TEST_PIN		_FACTORY_TEST_PIN

typedef enum{
	FACTORY_TEST_TIMER_NULL = TIMER_ID_INIT(THREAD_ID_FACTORY_TEST),

	/* factory test uart read. */
	FACTORY_TEST_TIMER_WATHCDOG,

	FACTORY_TEST_TIMER_UART_RAED,
	FACTORY_TEST_TIMER_DISPLAY,
	FACTORY_TEST_TIMER_ADV_STOP,
	FACTORY_TEST_TIMER_SLEEP,
	FACTORY_TEST_TIMER_MOTOR,

    FACTORY_UART_DATA_RECEIVE,

	FACTORY_TEST_TIMER_NUM_MAX
}TIMER_ID_ENUM(THREAD_ID_FACTORY_TEST);

typedef enum
{
	FACTORY_TEST_CMD_NULL = 0,
	FACTORY_TEST_CMD_BLE_MAC,
	FACTORY_TEST_CMD_GSENSOR,
	FACTORY_TEST_CMD_ADC,
	FACTORY_TEST_CMD_BLE_ADV,
	FACTORY_TEST_CMD_BLE_RSSI,
	FACTORY_TEST_CMD_FLASH,
	FACTORY_TEST_CMD_SLEEP,
	FACTORY_TEST_CMD_VERSION,
	FACTORY_TEST_CMD_FONT,

	FACTORY_TEST_CMD_ALL,
}FACTORY_TEST_CMD_TYPE;

typedef struct
{
	unsigned short font_crc16;
	unsigned short rssi;
	unsigned char  ble_adv[4];
}factory_test_info_struct;

extern void factory_test_ble_rssi(unsigned int rssi);
extern void factory_test_ble_mac(void);
extern void factory_test_version(void);
extern void factory_test_receive_data_handler(void);
extern void factory_test_send_data(unsigned char *data, unsigned int len);

extern unsigned char factory_test_pin_status_get(void);
extern unsigned char factory_test_check(void);

#endif //_FACTORY_TEST_H


