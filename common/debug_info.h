#ifndef _DEBUG_INFO_H
#define _DEBUG_INFO_H

// #include "asm/cpu.h"
// #include "generic/typedef.h"
#include "feature.h"
#include "pid_type.h"

#if defined(__CW_JL__)
#define DBG_DIRECT(fmt, ...)   log_print(2,0,fmt "\r\n", ## __VA_ARGS__)
#else
#define DBG_DIRECT(fmt,...)      printf(fmt, ##__VA_ARGS__)
#endif

#if DEBUG_EN
#define LOG_DEBUG(fmt,...)      printf(fmt, ##__VA_ARGS__)
#else
#define LOG_DEBUG(fmt,...)      do{}while(0)
#endif

#define ERROR_						"E: "
#define WARNING_ 					"W: "
#define OK_							"O: "


#if DEBUG_EN

#define SYS_DEBUG_EN						1
#define SYS_OS_DEBUG_EN					1
#define GUI_DEBUG_EN                		1
#define DATA_MANAGER_DEBUG_EN			0
#define DATA_TRANSFER_DEBUG_EN			0
#define DATA_MESSAGE_DEBUG_EN			0
#define DATA_SLEEP_DEBUG_EN			0
#define DATA_REC_DEBUG_EN				0
#define DATA_TRN_DEBUG_EN				0
#define DATA_COMMON_DEBUG_EN				0
#define DATA_TEST_DEBUG_EN				0
#define DATA_PASSTHROUGH_EN				0
#define DATA_GPS_DEBUG_EN				0
#define DATA_WATCHFACE_DEBUG_EN			0
#define OTA_DEBUG_EN						0
#define BT_DEBUG_EN						0
#define RTC_DEBUG_EN						0
#define TWI_DEBUG_EN						0
#define TP_DEBUG_EN						0
#define HR_DEBUG_EN						0
#define HR_TEST_DEBUG_EN					0
#define STOPWATCH_DEBUG_EN				0
#define MOTOR_DEBUG_EN					0
#define LED_DEBUG_EN						0
#define ARITH_DEBUG_EN					0
#define GPS_DEBUG_EN						0
#define GPS_TEST_DEBUG_EN				0
#define OLED_DEBUG_EN					0
#define LIS2DH_DEBUG_EN					0
#define WDT_DEBUG_EN						0
#define KEY_DEBUG_EN						0
#define CYCLING_DEBUG_EN					0
#define MIX_SPORT_DEBUG_EN				0
#define BATTERY_DEBUG_EN					0
#define WORKOUT_DEBUG_EN					0
#define TEST_DEBUG_EN					0
#define BLE_PRINTF_EN					0
#define AU_DEBUG_EN						0
#define GAME_DEBUG_EN                   0
#define RECORD_DEBUG_EN						0
#define MUSIC_DEBUG_EN                      0
#define DATALAYER_DEBUG_EN                      0
#define ALIPAY_DEBUG_EN                 0				// TCFG_PAY_ALIOS_ENABLE

#else

#define SYS_DEBUG_EN						0
#define SYS_OS_DEBUG_EN					0
#define GUI_DEBUG_EN                		0
#define DATA_MANAGER_DEBUG_EN			0
#define DATA_TRANSFER_DEBUG_EN			0
#define DATA_MESSAGE_DEBUG_EN			0
#define DATA_SLEEP_DEBUG_EN			0
#define DATA_REC_DEBUG_EN				0
#define DATA_TRN_DEBUG_EN				0
#define DATA_COMMON_DEBUG_EN				0
#define DATA_TEST_DEBUG_EN				0
#define DATA_PASSTHROUGH_EN				0
#define DATA_GPS_DEBUG_EN				0
#define DATA_WATCHFACE_DEBUG_EN			0
#define OTA_DEBUG_EN						0
#define BT_DEBUG_EN						0
#define RTC_DEBUG_EN						0
#define TWI_DEBUG_EN						0
#define TP_DEBUG_EN						0
#define HR_DEBUG_EN						0
#define STOPWATCH_DEBUG_EN				0
#define MOTOR_DEBUG_EN					0
#define LED_DEBUG_EN						0
#define ARITH_DEBUG_EN					0
#define GPS_DEBUG_EN						0
#define GPS_TEST_DEBUG_EN				0
#define OLED_DEBUG_EN					0
#define LIS2DH_DEBUG_EN					0
#define WDT_DEBUG_EN						0
#define KEY_DEBUG_EN						0
#define CYCLING_DEBUG_EN					0
#define MIX_SPORT_DEBUG_EN				0
#define BATTERY_DEBUG_EN					0
#define WORKOUT_DEBUG_EN					0
#define TEST_DEBUG_EN					0
#define BLE_PRINTF_EN					0
#define AU_DEBUG_EN						0
#define GAME_DEBUG_EN                   0
#define RECORD_DEBUG_EN                 0
#define MUSIC_DEBUG_EN                      0
#define DATALAYER_DEBUG_EN                      0
#define ALIPAY_DEBUG_EN                 0				// TCFG_PAY_ALIOS_ENABLE

#endif //DEBUG_EN


#if AU_DEBUG_EN
	#define AU_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define AU_DEBUG(fmt,...)		do{ }while(0)
#endif

#if TEST_DEBUG_EN
	#define TEST_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define TEST_DEBUG(fmt,...)		do{ }while(0)
#endif

#if HR_TEST_DEBUG_EN
	#define HR_TEST_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define HR_TEST_DEBUG(fmt,...)		do{ }while(0)
#endif

#if SYS_DEBUG_EN
	#define SYS_DEBUG(fmt,...)       do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define SYS_DEBUG(fmt,...)		do{ }while(0)
#endif

#if TP_DEBUG_EN
	#define TP_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define TP_DEBUG(fmt,...)		do{ }while(0)
#endif

#if TWI_DEBUG_EN
	#define TWI_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define TWI_DEBUG(fmt,...)		do{ }while(0)
#endif

#if SYS_OS_DEBUG_EN
	#define SYS_OS_DEBUG(fmt,...)       do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define SYS_OS_DEBUG(fmt,...)		do{ }while(0)
#endif

#if GUI_DEBUG_EN
	#define GUI_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define GUI_DEBUG(fmt,...)		do{ }while(0)
#endif

#if DATA_TRANSFER_DEBUG_EN
	#define DATA_TRANSFER_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define DATA_TRANSFER_DEBUG(fmt,...)		do{ }while(0)
#endif

#if DATA_MESSAGE_DEBUG_EN
	#define DATA_MESSAGE_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define DATA_MESSAGE_DEBUG(fmt,...)		do{ }while(0)
#endif

#if DATA_SLEEP_DEBUG_EN
	#define DATA_SLEEP_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define DATA_SLEEP_DEBUG(fmt,...)		do{ }while(0)
#endif

#if DATA_REC_DEBUG_EN
	#define DATA_REC_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define DATA_REC_DEBUG(fmt,...)		do{ }while(0)
#endif

#if DATA_TRN_DEBUG_EN
	#define DATA_TRN_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define DATA_TRN_DEBUG(fmt,...)		do{ }while(0)
#endif

#if DATA_COMMON_DEBUG_EN
	#define DATA_COMMON_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define DATA_COMMON_DEBUG(fmt,...)		do{ }while(0)
#endif

#if DATA_TEST_DEBUG_EN
	#define DATA_TEST_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define DATA_TEST_DEBUG(fmt,...)		do{ }while(0)
#endif

#if DATA_PASSTHROUGH_EN
	#define DATA_PASSTHROUGH(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define DATA_PASSTHROUGH(fmt,...)		do{ }while(0)
#endif

#if DATA_MANAGER_DEBUG_EN
	#define DATA_MANAGER_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define DATA_MANAGER_DEBUG(fmt,...)		do{ }while(0)
#endif

#if DATA_GPS_DEBUG_EN
	#define DATA_GPS_DEBUG(fmt,...)       do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define DATA_GPS_DEBUG(fmt,...)       do{ }while(0)
#endif

#if DATA_WATCHFACE_DEBUG_EN
	#define DATA_WATCHFACE_DEBUG(fmt,...)       do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define DATA_WATCHFACE_DEBUG(fmt,...)       do{ }while(0)
#endif

#if OTA_DEBUG_EN
	#define OTA_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define OTA_DEBUG(fmt,...)		do{ }while(0)
#endif

#if BT_DEBUG_EN
	#define BT_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define BT_DEBUG(fmt,...)		do{ }while(0)
#endif

#if HR_DEBUG_EN
	#define HR_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define HR_DEBUG(fmt,...)		do{ }while(0)
#endif

#if STOPWATCH_DEBUG_EN
	#define STOPWATCH_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define STOPWATCH_DEBUG(fmt,...)		do{ }while(0)
#endif

#if MOTOR_DEBUG_EN
	#define MOTOR_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define MOTOR_DEBUG(fmt,...)		do{ }while(0)
#endif

#if LED_DEBUG_EN
	#define LED_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define LED_DEBUG(fmt,...)		do{ }while(0)
#endif

#if RTC_DEBUG_EN
	#define RTC_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define RTC_DEBUG(fmt,...)		do{ }while(0)
#endif

#if ARITH_DEBUG_EN
	#define ARITH_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define ARITH_DEBUG(fmt,...)		do{ }while(0)
#endif

#if GPS_DEBUG_EN
	#define GPS_DEBUG(fmt,...)       do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define GPS_DEBUG(fmt,...)		do{ }while(0)
#endif

#if GPS_TEST_DEBUG_EN
	#define GPS_TEST_DEBUG(fmt,...)       do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define GPS_TEST_DEBUG(fmt,...)		do{ }while(0)
#endif

#if OLED_DEBUG_EN
	#define OLED_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define OLED_DEBUG(fmt,...)		do{ }while(0)
#endif

#if LIS2DH_DEBUG_EN
	#define LIS2DH_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define LIS2DH_DEBUG(fmt,...)		do{ }while(0)
#endif

#if BATTERY_DEBUG_EN
#define BATTERY_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
#define BATTERY_DEBUG(fmt,...)		do{ }while(0)
#endif

#if WDT_DEBUG_EN
	#define WDT_DEBUG(fmt,...)       do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define WDT_DEBUG(fmt,...)		do{ }while(0)
#endif

#if WORKOUT_DEBUG_EN
	#define WORKOUT_DEBUG(fmt,...)		do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define WORKOUT_DEBUG(fmt,...)		do{ }while(0)
#endif

#if KEY_DEBUG_EN
	#define KEY_DEBUG(fmt,...)       do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define KEY_DEBUG(fmt,...)		do{ }while(0)
#endif

#if CYCLING_DEBUG_EN
	#define CYCLING_DEBUG(fmt,...)       do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define CYCLING_DEBUG(fmt,...)		do{ }while(0)
#endif

#if MIX_SPORT_DEBUG_EN
	#define MIX_SPORT_DEBUG(fmt,...)       do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define MIX_SPORT_DEBUG(fmt,...)		do{ }while(0)
#endif

#if BLE_PRINTF_EN
	#define BLE_PRINTF(fmt, ...)			do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define	BLE_PRINTF(fmt, ...)			do{ }while(0)
#endif

#if GAME_DEBUG_EN
	#define GAME_DEBUG(fmt, ...)			do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
	#define	GAME_DEBUG(fmt, ...)			do{ }while(0)
#endif

#if RECORD_DEBUG_EN
    #define RECORD_DEBUG(fmt, ...)            do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
    #define RECORD_DEBUG(fmt, ...)            do{ }while(0)
#endif

#if MUSIC_DEBUG_EN
#define MUSIC_DEBUG(fmt, ...)            do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
#define MUSIC_DEBUG(fmt, ...)            do{ }while(0)
#endif

#if DATALAYER_DEBUG_EN
#define DATA_DEBUG(fmt, ...)            do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
#define DATA_DEBUG(fmt, ...)            do{ }while(0)
#endif

#if ALIPAY_DEBUG_EN				// TCFG_PAY_ALIOS_ENABLE
#define ALIPAY_DEBUG(fmt, ...)            do{ LOG_DEBUG(fmt, ##__VA_ARGS__); }while(0)
#else
#define ALIPAY_DEBUG(fmt, ...)            do{ }while(0)
#endif

#endif //_DEBUG_INFO_H

