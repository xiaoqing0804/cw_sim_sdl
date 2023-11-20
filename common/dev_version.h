#ifndef _DEV_VERSION_H
#define _DEV_VERSION_H

#include "debug_info.h"
#include "pin_define.h"

//===================================================
#define PID_NUM		        PID_0569_DG0525_M35L_AN88

#define DFT_DEV_NAME			"AN88"
#define DFT_DEV_HFP_NAME		"AN88"


#define DEV_CUSTOMER_ID		PID_NUM		//customer ID.

#if DEVELOP_VERSION
	#define DEV_FONT_ID		0			//font ID.
#elif DEBUG_EN
	#define DEV_FONT_ID		1			//font ID.
#else
	#define DEV_FONT_ID		0			//font ID.
#endif

//#define BOOTLOADER_ID		((*(unsigned int *)0x00077000) & 0xFF)	//bootloader ID.
//===================================================
typedef enum
{
	HW_TYPE_NULL = 0,
	HW_TYPE_V10,
	HW_TYPE_V11,
}HARDWARE_VERSION_TYPE;

#define HW_PIN		_HW_PIN

typedef struct
{
	unsigned int start_addr;		//media start addr.
	unsigned int end_addr;			//media end addr.
	unsigned int type;				//see OTA_FILE_TYPE.
    unsigned int id;                //0 ~ 255
}version_info_struct;

typedef struct
{
	const unsigned int flag;
	const unsigned int base_addr;
	const unsigned int end_addr;
	const unsigned int items;
	const version_info_struct customer;
	const version_info_struct code;
	const version_info_struct pic;
	const version_info_struct font;
}dev_version_struct;

extern const dev_version_struct g_dev_version;
extern unsigned char g_hardware_version;

extern void init_hardware_version(void);


#if defined(__CW_APP_TEST__)
#define DEV_BLE_NAME_MAX		15
#define DEV_EDR_NAME_MAX		23
extern unsigned char g_cust_ble_name[DEV_BLE_NAME_MAX+1];
extern unsigned char g_cust_edr_name[DEV_EDR_NAME_MAX+1];

#define DEV_NAME			g_cust_ble_name
#define DEV_HFP_NAME		g_cust_edr_name
#else
#define DEV_NAME			DFT_DEV_NAME
#define DEV_HFP_NAME		DFT_DEV_HFP_NAME
#endif



#endif //_DEV_VERSION_H

