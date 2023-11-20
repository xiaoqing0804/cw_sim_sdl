#ifndef _DATA_MANAGER_FLASH_8M_H
#define _DATA_MANAGER_FLASH_8M_H

#include "board_config.h"

#define CW_OTA_V2           1

// 0x0001 0000              dummy 64K
#define BKP_DATA1_ADDR      (TCFG_EXT_FLASH_DUMMY_SIZE*1024)
// 0x007F 0000
#define BKP_DATA1_SIZE      (CONFIG_EXTERN_FLASH_SIZE-CONFIG_EXTERN_USER_VM_FLASH_SIZE-BKP_DATA1_ADDR)

//
//=======================================================================================================================
// 用户flash空间 ...
#define	SECTOR_BASE							BKP_DATA1_ADDR                      // 0x0001 0000
#define	SECTOR_END							(BKP_DATA1_ADDR + BKP_DATA1_SIZE)   // 0x0080 0000


//-----------------------------------------------------------------------------------------------------------------------
// 字库 和 UI 空间 ...
#define SECTOR_1_FONT_BASE					(SECTOR_BASE + 0x00000000)          // 0x0001 0000
#define SECTOR_1_FONT_SIZE                  (0x00600000)                        // 6M
#define SECTOR_1_FONT_END					(SECTOR_BASE + SECTOR_1_FONT_SIZE)  // 0x0061 0000

#define	SECTOR_1_FONT16_BASE				SECTOR_1_FONT_BASE
#define	SECTOR_1_FONT16_SIZE				(SECTOR_1_FONT16_END-SECTOR_1_FONT16_BASE)
#define	SECTOR_1_FONT16_NUM				  	(SECTOR_1_FONT16_SIZE/4096)
#define	SECTOR_1_FONT16_END					SECTOR_1_FONT_END


//-----------------------------------------------------------------------------------------------------------------------
// OTA
#define SECTOR_2_BASE						SECTOR_1_FONT_END                   // 0x0061 0000
#define SECTOR_2_SIZE                       (0x00100000)                // 1024K
#define SECTOR_2_END						(SECTOR_2_BASE + SECTOR_2_SIZE)     // 0x0071 0000

#define SECTOR_2_OTA_BASE					SECTOR_2_BASE
#define	SECTOR_2_OTA_SIZE				  	(SECTOR_2_SIZE)             // 1024K
#define	SECTOR_2_OTA_NUM					(SECTOR_2_OTA_SIZE/4096)
#define	SECTOR_2_OTA_END					(SECTOR_2_OTA_BASE+SECTOR_2_OTA_SIZE)


//-----------------------------------------------------------------------------------------------------------------------
//
#define	SECTOR_0_BASE						SECTOR_2_END                        // 0x0071 0000
#define SECTOR_0_SIZE                       (0x00040000)                        // 256K
#define	SECTOR_0_END						(SECTOR_0_BASE + SECTOR_0_SIZE)     // 0x0075 0000

#define	SECTOR_0_USER_DATA_BASE				SECTOR_0_BASE
#define	SECTOR_0_USER_DATA_SIZE				(2*4*1024)      // 8K
#define	SECTOR_0_USER_DATA_NUM				(SECTOR_0_USER_DATA_SIZE/4096)
#define	SECTOR_0_USER_DATA_END				(SECTOR_0_USER_DATA_BASE+SECTOR_0_USER_DATA_SIZE)

#define	SECTOR_0_SENSOR_TAG_BASE			SECTOR_0_USER_DATA_END
#define	SECTOR_0_SENSOR_TAG_SIZE			(4*4*1024)      // 16K
#define	SECTOR_0_SENSOR_TAG_NUM				(SECTOR_0_SENSOR_TAG_SIZE/4096)
#define	SECTOR_0_SENSOR_TAG_END				(SECTOR_0_SENSOR_TAG_BASE+SECTOR_0_SENSOR_TAG_SIZE)

#define	SECTOR_0_HISTORY_SPORT_BASE			SECTOR_0_SENSOR_TAG_END
#define	SECTOR_0_HISTORY_SPORT_SIZE			(4*4*1024)      // 16K
#define	SECTOR_0_HISTORY_SPORT_NUM			(SECTOR_0_HISTORY_SPORT_SIZE/4096)
#define	SECTOR_0_HISTORY_SPORT_END			(SECTOR_0_HISTORY_SPORT_BASE+SECTOR_0_HISTORY_SPORT_SIZE)

#define	SECTOR_0_SLEEP_BASE					SECTOR_0_HISTORY_SPORT_END
#define	SECTOR_0_SLEEP_SIZE			  		(4*4*1024)      // 16K
#define	SECTOR_0_SLEEP_NUM				  	(SECTOR_0_SLEEP_SIZE/4096)
#define	SECTOR_0_SLEEP_END					(SECTOR_0_SLEEP_BASE+SECTOR_0_SLEEP_SIZE)

#define	SECTOR_0_DAILY_HEART_BASE			SECTOR_0_SLEEP_END
#define	SECTOR_0_DAILY_HEART_SIZE			(4*4*1024)      // 16K
#define	SECTOR_0_DAILY_HEART_NUM			(SECTOR_0_DAILY_HEART_SIZE/4096)
#define	SECTOR_0_DAILY_HEART_END			(SECTOR_0_DAILY_HEART_BASE+SECTOR_0_DAILY_HEART_SIZE)

#define	SECTOR_0_SPORT_HEART_BASE			SECTOR_0_DAILY_HEART_END
#define	SECTOR_0_SPORT_HEART_SIZE			(10*4*1024)     // 40K
#define	SECTOR_0_SPORT_HEART_NUM			(SECTOR_0_SPORT_HEART_SIZE/4096)
#define	SECTOR_0_SPORT_HEART_END			(SECTOR_0_SPORT_HEART_BASE+SECTOR_0_SPORT_HEART_SIZE)

#define	SECTOR_0_MIX_SPORT_BASE				SECTOR_0_SPORT_HEART_END
#define	SECTOR_0_MIX_SPORT_SIZE			  	(2*4*1024)      // 8K
#define	SECTOR_0_MIX_SPORT_NUM				(SECTOR_0_MIX_SPORT_SIZE/4096)
#define	SECTOR_0_MIX_SPORT_END				(SECTOR_0_MIX_SPORT_BASE+SECTOR_0_MIX_SPORT_SIZE)

#define SECTOR_0_DEBUG_TEMP_BASE			SECTOR_0_MIX_SPORT_END
#define SECTOR_0_DEBUG_TEMP_SIZE			(1*4*1024)      // 4K
#define SECTOR_0_DEBUG_TEMP_NUM				(SECTOR_0_DEBUG_TEMP_SIZE/4096)
#define SECTOR_0_DEBUG_TEMP_END				(SECTOR_0_DEBUG_TEMP_BASE+SECTOR_0_DEBUG_TEMP_SIZE)

#define	SECTOR_0_MESSAGE_ALL_BASE			SECTOR_0_DEBUG_TEMP_END
#define	SECTOR_0_MESSAGE_ALL_SIZE			(4*4*1024)      // 16K
#define	SECTOR_0_MESSAGE_ALL_NUM			(SECTOR_0_MESSAGE_ALL_SIZE/4096)
#define	SECTOR_0_MESSAGE_ALL_END			(SECTOR_0_MESSAGE_ALL_BASE+SECTOR_0_MESSAGE_ALL_SIZE)

#define	SECTOR_0_CALL_BASE					SECTOR_0_MESSAGE_ALL_END
#define	SECTOR_0_CALL_SIZE					(1*4*1024)      // 4K
#define	SECTOR_0_CALL_NUM					(SECTOR_0_CALL_SIZE/4096)
#define	SECTOR_0_CALL_END					(SECTOR_0_CALL_BASE+SECTOR_0_CALL_SIZE)

#define	SECTOR_0_TEST_DEBUG_BASE			SECTOR_0_CALL_END
#define	SECTOR_0_TEST_DEBUG_SIZE			(2*4*1024)      // 8K
#define	SECTOR_0_TEST_DEBUG_NUM				(SECTOR_0_TEST_DEBUG_SIZE/4096)
#define	SECTOR_0_TEST_DEBUG_END				(SECTOR_0_TEST_DEBUG_BASE+SECTOR_0_TEST_DEBUG_SIZE)

//#ifdef __PHONE_BOOK_SYNC_SUPPORTED__
#define	SECTOR_0_CONTACT_BASE			    SECTOR_0_TEST_DEBUG_END
#define	SECTOR_0_CONTACT_SIZE			    (2*4*1024)      // 8K
#define	SECTOR_0_CONTACT_NUM			    (SECTOR_0_CONTACT_SIZE/4096)
#define	SECTOR_0_CONTACT_END			    (SECTOR_0_CONTACT_BASE+SECTOR_0_CONTACT_SIZE)

#define	SECTOR_0_CONTACT_RECORD_BASE		SECTOR_0_CONTACT_END
#define	SECTOR_0_CONTACT_RECORD_SIZE		(2*4*1024)      // 8K
#define	SECTOR_0_CONTACT_RECORD_NUM			(SECTOR_0_CONTACT_RECORD_SIZE/4096)
#define	SECTOR_0_CONTACT_RECORD_END			(SECTOR_0_CONTACT_RECORD_BASE+SECTOR_0_CONTACT_RECORD_SIZE)
//#endif


#define SECTOR_0_QA_BASE                    SECTOR_0_CONTACT_RECORD_END
#define SECTOR_0_QA_SIZE                    (4*1024)     // 4K
#define SECTOR_0_QA_END                     (SECTOR_0_QA_BASE+SECTOR_0_QA_SIZE)

#if (SECTOR_0_END < SECTOR_0_QA_END)
	#error "the SECTOR 0 has over , please adjust it !!!"
#endif

//-----------------------------------------------------------------------------------------------------------------------
#define	SECTOR_01_BASE						SECTOR_0_END                        // 0x0075 0000
#define SECTOR_01_SIZE                      (0x00000000)                        // 0K
#define	SECTOR_01_END						(SECTOR_01_BASE + SECTOR_01_SIZE)   // 

//#define	SECTOR_01_SYS_INFO_BASE				SECTOR_01_BASE
//#define	SECTOR_01_SYS_INFO_SIZE				(1*4*1024)
//#define	SECTOR_01_SYS_INFO_NUM				(SECTOR_01_SYS_INFO_SIZE/4096)
//#define	SECTOR_01_SYS_INFO_END				(SECTOR_01_SYS_INFO_BASE+SECTOR_01_SYS_INFO_SIZE)


//-----------------------------------------------------------------------------------------------------------------------
// 表盘空间
#define	SECTOR_02_BASE						SECTOR_01_END                       // 0x0075 0000
#define SECTOR_02_SIZE                      (0x00090000)                        // 
#define	SECTOR_02_END						(SECTOR_02_BASE + SECTOR_02_SIZE)   // 0x007E 0000

#define	SECTOR_02_WATCHFACE_SET_BASE		SECTOR_02_BASE
#define	SECTOR_02_WATCHFACE_SET_SIZE		(0x00022000)    //136K.
#define	SECTOR_02_WATCHFACE_SET_NUM			(SECTOR_02_WATCHFACE_SET_SIZE/4096)
#define	SECTOR_02_WATCHFACE_SET_END			(SECTOR_02_WATCHFACE_SET_BASE+SECTOR_02_WATCHFACE_SET_SIZE)

#define	SECTOR_02_WATCHFACE_DEFINE_BASE		SECTOR_02_WATCHFACE_SET_END
#define	SECTOR_02_WATCHFACE_DEFINE_SIZE		(0x00065000)    //404K.
#define	SECTOR_02_WATCHFACE_DEFINE_NUM		(SECTOR_02_WATCHFACE_DEFINE_SIZE/4096)
#define	SECTOR_02_WATCHFACE_DEFINE_END		(SECTOR_02_WATCHFACE_DEFINE_BASE+SECTOR_02_WATCHFACE_DEFINE_SIZE)

#define	SECTOR_02_WATCHFACE_SET_ZOOM_BASE	SECTOR_02_WATCHFACE_DEFINE_END
#define	SECTOR_02_WATCHFACE_SET_ZOOM_SIZE	(0x00009000)    //36K.
#define	SECTOR_02_WATCHFACE_SET_ZOOM_NUM	(SECTOR_02_WATCHFACE_SET_ZOOM_SIZE/4096)
#define	SECTOR_02_WATCHFACE_SET_ZOOM_END	(SECTOR_02_WATCHFACE_SET_ZOOM_BASE+SECTOR_02_WATCHFACE_SET_ZOOM_SIZE)

#if (SECTOR_02_END < SECTOR_02_WATCHFACE_SET_ZOOM_END)
	#error "the SECTOR 02 has over , please adjust it !!!"
#endif

//-----------------------------------------------------------------------------------------------------------------------
#define	SECTOR_03_BASE						SECTOR_02_END                       // 0x007E 0000
#define SECTOR_03_SIZE                      (SECTOR_END - SECTOR_03_BASE)       // 0x0002 0000
#define	SECTOR_03_END						(SECTOR_03_BASE + SECTOR_03_SIZE)   // 

#define SECTOR_03_NVDM_BASE                 SECTOR_03_BASE
#define SECTOR_03_NVDM_SIZE                 (0x00010000)    // 64K
#define SECTOR_03_NVDM_END                  (SECTOR_03_NVDM_BASE+SECTOR_03_NVDM_SIZE)

#define SECTOR_03_TEMP_BASE                 SECTOR_03_NVDM_END
#define SECTOR_03_TEMP_SIZE                 (0x00010000)    // 64K.
#define SECTOR_03_TEMP_END                  (SECTOR_03_TEMP_BASE+SECTOR_03_TEMP_SIZE)

//
//=======================================================================================================================
//


#if (SECTOR_END < SECTOR_03_BASE)
	#error "the SECTOR 03 has over , please adjust it !!!"
#endif

extern int data_manager_flash_init(void);
extern int data_manager_flash_deinit(void);
extern int data_manager_flash_get_checksum(void);
extern int data_manager_flash_test(void);

extern void data_manager_flash_power_up(void);
extern void data_manager_flash_power_down(void);
extern unsigned char data_manager_flash_write(unsigned int addr, const unsigned char *data,unsigned int len);
extern unsigned char data_manager_flash_read(unsigned int addr, unsigned char *data,unsigned int len);
extern unsigned char data_manager_flash_erase_4k(unsigned int addr,unsigned int num);

#endif //_DATA_MANAGER_FLASH_H

