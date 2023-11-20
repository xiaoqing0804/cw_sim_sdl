#ifndef __FEATURE_VERNO_H__
#define __FEATURE_VERNO_H__

#include "feature_define.h"

#if 0
#define PID_NUM				PID_0100_SN92

#define DEV_NAME			"PBL LEAP"
#define BLE_NAME			DEV_NAME
#define AUDIO_NAME			DEV_NAME

#define DEV_CODE_ID			1			//code ID.
#define DEV_PIC_ID			0			//picture ID.

#if DEBUG_EN
#define DEV_FONT_ID			1			//font ID.
#else
#define DEV_FONT_ID			0			//font ID.
#endif

#endif


/****************主控硬件信息***********************/
#define PLATFORM_SDK  			"RTL8762CK"
#define PLATFORM_PCBA_MODEL  	"DE007-02"
#define PLATFORM_RAM_SIZE 		160*1024      //160KB
#define PLATFORM_FLASH_SIZE 	8*1024*1024   //8M

#endif

