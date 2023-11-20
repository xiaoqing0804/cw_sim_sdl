#ifndef _DATA_COMMON_H
#define _DATA_COMMON_H

#include "time.h"

#include "data_transfer.h"      // 20211220 Taylor.Le, + BLE_DATA_TRANSFER_V2
#include "language.h"
#include "picture.h"
#include "sport_type.h"


#define WIDGET_MAX_TOTAL 7

#define ALARM_CLOCK_MAX_TOTAL 5
//================== all user struct define ==========
typedef struct
{
	unsigned char id_num[4];
	unsigned char sex;		//0:man , 1:woman
	unsigned char age;		//
	unsigned char hight;	//cm
	unsigned char weight;   //kg
	unsigned char LR_hand;  //0: left , 1: right.
}user_info_struct;

typedef struct
{
	unsigned char watch_onoff;
	unsigned char menu_onoff;
}shake_style_struct;

typedef struct
{
	unsigned char silent_onoff;
	unsigned char vib_onoff;
	unsigned char vib_volume;
}vib_mode_struct;


typedef struct
{
	unsigned char num;	//语言类型序号, 0：英语, 1: 中文
}language_setting_struct;

#define CHECK_CLOCK_ALARM_TIME	(30*60)		//unit : sec
#define ALARM_ITEM_SIZE			(sizeof(alarm_info_struct))  //sizeof(alarm_info_struct)
typedef enum
{
	ALARM_TYPE_NORMAL = 0,
	ALARM_TYPE_REMIND,
}ALARM_TYPE;

typedef struct
{
	unsigned char type; //see ALARM_TYPE.
	unsigned char week_repeat; // week alarm repeat bit set
	unsigned char hour;
	unsigned char min;
	unsigned char status;	//0:close , 1:open
}alarm_info_struct;

#define MAX_ALARM		6
typedef struct
{
	unsigned char items;
	alarm_info_struct alarm_info[MAX_ALARM];
}alarm_data_block_t;

typedef struct
{
	unsigned char abs_time[4];			//abs time
	unsigned char offset_time[4];		//offset time
	union{
		unsigned char all;
		struct{
			unsigned char hour : 1; 	// 0: 12h, 1:24h.
			unsigned char mon_day : 1;	// 0: mon-day, 1: day-mon.
		}bit;
	}format;
}time_sync_struct;

typedef struct
{
	unsigned char phone_type;	// 0: android , 1: ios.
	unsigned char pair_type;	// 0: no pair , 1: open pair.
}start_piar_struct;

typedef enum
{
	PAIR_STATUS_NULL = 0, //no pair.
	PAIR_STATUS_CONFIRM, //pair confirm.
	PAIR_STATUS_CANCEL, //pair cancel.
}PAIR_STATUS_TYPE;

typedef struct
{
	unsigned char status;		//pair status , see PAIR_STATUS_TYPE.
	unsigned char phone_type;	//phone type , 0: android , 1: ios.
}pair_finish_struct;

typedef struct
{
	unsigned char battery_capacity;
}battery_info_struct;

typedef struct
{
	unsigned char items;		//the ID number.
	unsigned char customer_id;

	// b0: hr-flag;  b1: g-sensor;	b2: xxx; b3: xxx;
	// b[4~7]: hr-module (VC31S=1, VC32S=2, LC11=3, PAH8007=4, SC7R3x=5, HRS3300=6, LC10A=7, HX3605=8  ... )
	unsigned char hardware_id;
	unsigned char code_id;
	unsigned char picture_id;
	unsigned char font_id;
#ifdef BLE_DATA_TRANSFER_V2
    unsigned char customer_id_h; // customer_id 的高字节位  Taylor.Le  add for V2.
#endif
}dev_id_struct;

typedef struct
{
	dev_id_struct dev_id; //device id.
	unsigned char mac_addr[6]; //device address.
}dev_info_struct;

typedef struct
{
	unsigned int startSecs;
	unsigned int walkSteps;
	unsigned int distance;
	unsigned int calories;
	unsigned int duration;	//unit : s.
}sport_info_struct;

typedef struct
{
	unsigned char time[4];			//heart start time
	unsigned char heart_nums;		//heart number
}heart_item_struct;

typedef struct
{
	unsigned char time[4];		//心率的起始时间
	unsigned char bp_sbp;      //高血压
	unsigned char bp_dbp;		//低血压
}BP_item_struct;

typedef struct
{
	unsigned char time[4];		//心率的起始时间
	unsigned char O2;      		//血氧
}O2_item_struct;

typedef enum{
	HR_CONTROL_TYPE_NULL = 0,
	HR_CONTROL_TYPE_HR,
	HR_CONTROL_TYPE_BP,
	HR_CONTROL_TYPE_O2,
	HR_CONTROL_TYPE_ECG,
}HR_CONTROL_TYPE;

typedef struct
{
	struct{
		unsigned char onoff : 4; // 0: off, 1: on.
		unsigned char type : 4; // see HR_CONTROL_TYPE.
	}bit;
}HR_control_struct;

typedef struct
{
	unsigned char weather;		//type: 0. sunny, 1. cloudy, 2. partly_cloudy, 3. rain, 4. snow.
	signed char low_temperature;  //low value;
	signed char high_temperature;  //high value;
	unsigned char PM[2];		//pm value.
}weather_info_item_struct;

typedef struct
{
	unsigned char time[4];		//the first day weather time.
	weather_info_item_struct item[3]; // [0]: today, [1]: tomorrow, [2]: the day after tomorrow.
}weather_info_struct;

typedef struct
{
	unsigned char sec;	//[0~59]
	unsigned char min;  //[0~59]
	unsigned char hour; //[0~23]
	unsigned char day;	//[1~31]
	unsigned char wed;	//[0~6]:0->sunday , 1->monday ,....,6->saturday
	unsigned char mon;	//[1~12]
	unsigned int year;	//it must 4 number, as 2016.
}time_struct;

typedef struct
{
	unsigned char onoff;	//0:close music , 1:open music
}find_phone_struct;

typedef struct
{
	unsigned char step[4];	   		//unit: setp
	unsigned char distance[4];      //unit: m
	unsigned char calories[4];		//unit: calories
	unsigned char sleep[2];			//unit: min
	unsigned char sport_time[2];	//unit: min
}user_target_struct;

typedef struct
{
	unsigned char attribute;    // attribute type : name , number , message .
    unsigned char len;		  //the message data length.
    unsigned char data[1];   //message item data point.
}message_item_struct;

typedef struct
{
	unsigned char abs_time[4];  //time
	unsigned char type;			//MESSAGE_TYPE
	unsigned char info_items;	//items
	message_item_struct info[1];	//message item info point, the num is info_items.
}message_notice_struct;

typedef struct
{
	unsigned char onoff;	//0: close , 1: open
}ble_pair_enable_struct;

typedef struct
{
	unsigned char onoff;	//0: don't open , 1: has open
}ble_pair_status_struct;

/* mix sport  */
typedef struct
{
	unsigned char start_time[4];
	unsigned char end_time[4];
	unsigned char distance[4];
	unsigned char aver_heartrate;		//aver heartrate
	unsigned char max_heartrate;
	unsigned char step[4];
	unsigned char calories[4];
	unsigned char aver_speed[2];		//dispaly is current speed, result is aver speed
	unsigned char max_speed[2];
}mix_sport_info_struct;

typedef struct
{
	unsigned char mix_sport_type; //see MIX_SPORT_TYPE
	union
	{
		unsigned char data[36];
		mix_sport_info_struct info;
	}type;
}mix_sport_struct;


typedef struct
{
	unsigned char hour;
	unsigned char min;
	unsigned char offon;	//0:close , 1:open
	unsigned char repeat;	//0: once;  bit[0:6] week day;  bit7: every day.
}alarm_clock_info_struct;


typedef struct
{
	unsigned char flag;		        //1: turn on    0:off
	unsigned char lock_stat;		//1: locked     0:unlocked
	unsigned char ultimate_password_indx[4];	//password 8888.
	unsigned char password_indx[4];	//password 8888.
}password_struct;


typedef struct
{
	unsigned char index;		 // 推送的二维码 id,
	unsigned char type;			 // 推送二维码的类型//如微信，QQ，支付宝等
	unsigned char name[20]; 	 //推送二维码自定义命名 //最多20个char
	unsigned short len;					 //二维码内容长度；
	unsigned char content[400];  //根据长度推送的内容             超过400不给推送
}qr_code_info_struct;

typedef enum
{
	MUSIC_CMD_NULL = 0,
	MUSIC_CMD_PLAY,			//open music.
	MUSIC_CMD_PAUSE,		//pause music.
	MUSIC_CMD_STOP,			//stop music.
	MUSIC_CMD_BACKWARD,		//backward .
	MUSIC_CMD_FORWARD,		//forward.
	MUSIC_CMD_PP,			//play/pause.
	MUSIC_CMD_CONTENT,		//get music content.
	MUSIC_CMD_VOLUME_UP,	//volume up.
	MUSIC_CMD_VOLUME_DOWN,	//volume down.
	MUSIC_CMD_VOLUME_VALUE, //get music volume value.
}MUSIC_CMD_TYPE;

typedef struct
{
	unsigned char command;     //music control command , see MUSIC_CMD_TYPE.
}music_control_struct;

typedef struct
{
	unsigned char command;	   //music control command , see MUSIC_CMD_TYPE.
	unsigned char len;
	char data[64];
} music_content_struct;

typedef enum
{
	CALL_CMD_NULL = 0,
	CALL_CMD_ANSWER_CALL,	//answer call.
	CALL_CMD_HANGUP_CALL,	//hangup call.
	CALL_CMD_SOUND_OFF,		//sound off.
}CALL_CMD_TYPE;

typedef struct
{
	unsigned char cmd_type;	//commond type, see CALL_CMD_TYPE
}call_control_struct;

typedef struct
{
	unsigned char flag;				//0: close, 1: open.
	unsigned char noon_onoff;	//0: close, 1: open.
								//午休免打扰中午12:00至下午02:00不要提醒我
	unsigned char week_repeat;		//bit0->monday , bit1->tuesday , bit6->sunday.
	unsigned char start_time_hour;	//start time: hour.
	unsigned char start_time_min;	//start time: min.
	unsigned char end_time_hour;		//end time: hour.
	unsigned char end_time_min;		//end time: min.
}sitting_remind_struct;

typedef struct
{
	unsigned char start_time_hour;	//start time : hour.
	unsigned char start_time_min;	//start time : min.
	unsigned char end_time_hour;	//end time : hour.
	unsigned char end_time_min;		//end time : min.
}forget_disturb_item_struct;

typedef struct
{
	unsigned char switch_flag;	//0: close , 1: open.
	unsigned char items;	//forget disturb items.
	forget_disturb_item_struct info[5];//forget disturb info.
}forget_disturb_struct;

typedef struct
{
	unsigned char onoff;	// 0: off , 1: on.
}photograph_onoff_struct;

typedef struct
{
	unsigned char index;
}watch_face_struct;

typedef struct
{
	unsigned char onoff;	//0: close, 1: open. 总开关
	union{
		unsigned char all[4];
		struct
		{
			unsigned char NOTIFICATION_DISPLAY_QQ : 1;
			unsigned char NOTIFICATION_DISPLAY_WECHAT : 1;
			unsigned char NOTIFICATION_DISPLAY_EMAIL: 1;
			unsigned char NOTIFICATION_DISPLAY_FACEBOOK : 1;
			unsigned char NOTIFICATION_DISPLAY_TWITTER : 1;
			unsigned char NOTIFICATION_DISPLAY_WHATSAPP : 1;
			unsigned char NOTIFICATION_DISPLAY_INSTAGRAM : 1;
			unsigned char NOTIFICATION_DISPLAY_SKYPE : 1;

			unsigned char NOTIFICATION_DISPLAY_LINKED_IN :1;
			unsigned char NOTIFICATION_DISPLAY_LINE : 1;
			unsigned char NOTIFICATION_DISPLAY_OTHER: 1;
			unsigned char NOTIFICATION_DISPLAY_KAKAO_TALK : 1;
			unsigned char NOTIFICATION_DISPLAY_TELEGRAM: 1;
			// ANCS NEW

			unsigned char notification_reserved_1 : 3;
		}bit;
	}select;
}message_display_struct;

typedef struct
{
	signed short x;
	signed short y;
	signed short z;
}gsensor_test_struct;

typedef struct
{
	union{
		unsigned char all[8];
		struct{
			unsigned char weight : 4;    //0: kg , 1 :lb ,2 :st
			unsigned char distance : 4;  //0: m , 1 : mile
			unsigned char weather : 4;   //0: C ,  1: F
			unsigned char reserved : 4;
		}bit;
	}select;
}unit_setting_struct;

typedef enum
{
	SYS_MODE_NULL = 0,
	SYS_MODE_NORMAL_TYPE,
	SYS_MODE_LOW_POWER_TYPE,
	SYS_MODE_SHUTDOWN_TYPE,
	SYS_MODE_FACTORY_TEST_TYPE,
}system_mode_type;

typedef struct
{
	unsigned char num; //the select active watch number.
	unsigned char watch[20]; //the active watch index.
}watch_setting_struct;

typedef struct
{
	unsigned char onoff;			// 0: close, 1: open.
	unsigned char start_hour;	//start time : hour.
	unsigned char start_min;		//start time : min.
	unsigned char end_hour;		//end time : hour.
	unsigned char end_min;		//end time : min.
	unsigned char interval;		// 0: 30min, 1: 1Hour, 2: 2H, 3: 3H.
}drink_alarm_struct;

typedef struct
{
	unsigned char onoff;			// 0: close, 1: open.
	unsigned char start_hour;		//start time : hour.
	unsigned char start_min;		//start time : min.
	unsigned char end_hour;		//end time : hour.
	unsigned char end_min;			//end time : min.
}hand_rise_switch_struct;

typedef struct
{
	unsigned char min10_onoff;	// 0: close, 1: open.
	unsigned char hour24_onoff;  // 0: close, 1: open.
	unsigned char reserved[6];		//保留
}heart_auto_switch_struct;

typedef struct
{
	unsigned char onoff;			// 0: close, 1: open.
}call_alarm_struct;

typedef struct
{
	unsigned char onoff;			// 0: close, 1: open.
}message_alarm_struct;

typedef struct
{
	unsigned char onoff;			// 0: close, 1: open.
}target_alarm_struct;

typedef enum
{
	APP_SPORT_STATUS_STOP = 0, //stop
	APP_SPORT_STATUS_START,	//start
	APP_SPORT_STATUS_PAUSE,	//pause
	APP_SPORT_STATUS_CONTINUE, //continue
	APP_SPORT_STATUS_STOP_FORCE, //force stop
	APP_SPORT_STATUS_SYNC, //app sport data sync request.
}APP_SPORT_STATUS_TYPE;

typedef  struct
{
	unsigned char  type;  //run, cycling, swimming, walk......
	unsigned char  status;  //see APP_SPORT_STATUS_TYPE.
	unsigned char  time[4];  //sport time, unit: s.
	unsigned char  distance[4];  //sport distance, unit: m.
}app_sport_struct;

typedef struct
{
	unsigned char buf[20];
}test_debug_struct;

typedef struct
{
	unsigned char onoff; //0: off, 1: on.
}app_test_struct;

typedef enum
{
	POWER_TYPE_OLED = 0,
	POWER_TYPE_MOTOR,
	POWER_TYPE_HR,
	POWER_TYPE_GSENSOR,
	POWER_TYPE_BATTERY,
	POWER_TYPE_BTAUD,

	POWER_TYPE_SUM
}POWER_ANALYSIS_TYPE;

typedef struct
{
	unsigned short voltage; //battery voltage
	unsigned char percent; //battery percent
	unsigned char charge_num;
	unsigned int start[POWER_TYPE_SUM];
	unsigned int all[POWER_TYPE_SUM];  //unit: ms.
}power_analysis_struct;

typedef struct
{
	union{
		unsigned char all [4];
		struct
		{
			unsigned char BP :1; //BP function
			unsigned char O2 : 1; //O2 function
			unsigned char ECG : 1; //ECG function
			unsigned char weather_num : 2;
			unsigned char hr_24H : 1;	//hr 24h switch.

			unsigned char woman_stage : 1;
            //unsigned char photograph : 1;
			unsigned char call_function:1;  // call, phonebook, call-log
            unsigned char real_time_weather : 1; //实时天气
            unsigned char btedr_call : 1; //通话蓝牙
            unsigned char auto_connect_bluetooth : 1;	// 通话蓝牙一次连接
		    unsigned char qr_code_manager : 1;				// APP 二维码管理
		    unsigned char hr_measure_button : 1;	//APP心率点击测量按钮 0-close 1-open
			unsigned char photo_watchface : 1;	//相册表盘 0-close 1-open
			unsigned char download_logo : 1;
            unsigned char alipay_support : 1;	// 是否支持支付宝功能，只在激活设备时有效
		}bit;
	}select;
}function_control_struct;

typedef struct
{
	unsigned char lcd_width[2];
	unsigned char lcd_height[2];
	unsigned char reserved[12];
}hardware_info_struct;


typedef struct
{
    unsigned char edr_addr[6];
    unsigned char edr_name[24];
}btedr_device_struct;


#ifdef __PHONE_BOOK_SYNC_SUPPORTED__

#define CONTACT_MAX_NUM        50
#define CONTACT_PAGE_NUM       3

#define CONTACT_HISTORY_MAX_NUM        50   // Taylor.Le, 100
#define CONTACT_HISTORY_PAGE_NUM       3

#define Max_Number_Length     20
#define Max_Name_Length       20

typedef struct
{
    //char id;
    unsigned char  Name[Max_Name_Length];
    unsigned char  Number[Max_Number_Length];
    //char  time[5];

}Contact_t;

typedef struct
{
    unsigned char CONTACT_NUM;
    Contact_t Person_infor[1];
}CONTACT_t;


typedef	struct
{
    unsigned char index;
    unsigned char *data;

}Get_Index_Contact_t;


typedef enum
{
    CALL_NONE=0,
    CALL_IN=  1,
    CALL_OUT= 2,
    CALL_IN_NONE=3,
}Call_Status_t;

typedef struct
{
	unsigned char status[1];
	unsigned char Number[Max_Number_Length];
    unsigned char   Name[Max_Name_Length];			// 通话记录保存名称
    unsigned char    time[20];
} CALL_RECORD_t;

typedef	struct
{
    unsigned char Record_Num;
    CALL_RECORD_t   Person_infor[1];

}Call_Record_t;

typedef struct
{
    unsigned char xoffset;
    unsigned char yoffset;

}Contact_Position_t;


typedef struct
{
    Contact_Position_t   picture;
    Contact_Position_t   Name;
    Contact_Position_t   Number;
}Call_Contact_Position_t;

#endif

typedef struct
{

 	STRING_ID_TYPE string;
 	const picture_info_struct *const pic;
	MIX_SPORT_TYPE id;
}self_window_info_struct;


enum
{
    MOREINFO_WINDOW_STYLE_LIST = 1,
    MOREINFO_WINDOW_STYLE_KALEIDOSCOPE,
    MOREINFO_WINDOW_STYLE_ICON_LIST,
    MOREINFO_WINDOW_STYLE_CELL,
    MOREINFO_WINDOW_STYLE_RING,
   	MOREINFO_WINDOW_STYLE_FLOW,
   	MOREINFO_WINDOW_STYLE_LOOP,
    MOREINFO_WINDOW_STYLE_RING_TWO,

    MOREINFO_WINDOW_STYLE_MAX,
};

typedef struct
{
	unsigned char type; //0: null, 1: normal, 2: huai yun.
	unsigned char start_time[4];
	unsigned char day_num;
	unsigned char peroid;
	unsigned char remind_onoff;  //提醒总开关，0:关，1:开
	unsigned char remind_time[2]; //提醒时间, [0]:分，[1]:时
	unsigned char remind_mode_menstrual;  //月经前一天提醒，0：关，1：开
	unsigned char remind_mode_ovulation;	//排卵开始前一天提醒,0：关，1：开
	unsigned char remind_mode_ovulation_peak;//排卵日前一天提醒，0：关，1：开
	unsigned char remind_mode_end_ovulation;	//排卵结束前一天提醒，0：关，1：开
	unsigned char reserved[8];    //保留字节
}woman_stage_info_struct;

typedef enum
{
	WOMAN_STATUS_NULL = 0,
	WOMAN_STATUS_YUEJIN,
	WOMAN_STATUS_PAILUAN,
	WOMAN_STATUS_PAILUAN_DAY,
	WOMAN_STATUS_ANQUAN,
}WOMAN_STATUS_TYPE;

typedef enum
{
	WOMAN_ALARM_NULL = 0,
	WOMAN_ALARM_YUEJIN_START,
	WOMAN_ALARM_PAILUAN_START,
	WOMAN_ALARM_PAILUAN_DAY,
	WOMAN_ALARM_PAILUAN_END,
}WOMAN_ALARM_TYPE;

typedef struct
{
	unsigned int yuejin_start;
	unsigned int yuejin_end;
	unsigned int pailuan_start;
	unsigned int pailuan_day;
	unsigned int pailuan_end;
	unsigned int anquan_start;
	unsigned int anquan_end;
	unsigned int sys_sec;
	unsigned char status; //0: yuejin, 1: pailuan, 2: anquan. see WOMAN_STATUS_TYPE.
}woman_stage_time_struct;

typedef struct
{
    unsigned int width;			// 手机宽度
	unsigned int height;		// 手机高度
}resolution_info_struct;

typedef struct
{
	unsigned char state;	//0:fail , 1:pass
	unsigned int step;	//  bit[0:9] 10个步骤
}factory_worker_info_struct;

typedef struct
{
    unsigned char power_on_logo;  //   开机logo   0：off 1：on
    unsigned char power_off_logo;  // 关机logo   0：off 1：on

}power_logo_flag_info;

extern unsigned char g_phone_type;	//phone type , 0: android , 1: ios.
extern user_info_struct g_user;
extern language_setting_struct g_language;
extern battery_info_struct g_battery;
extern dev_info_struct g_devInfo;
extern alarm_data_block_t g_RamAlarmBlock;
extern time_sync_struct g_timeSync;
extern weather_info_struct g_weather_info;
extern find_phone_struct g_find_phone;
extern find_phone_struct g_find_device;
extern user_target_struct g_user_target;
extern ble_pair_status_struct g_ble_pair_status;
extern call_control_struct call_control;
extern music_control_struct music_control;
extern sitting_remind_struct g_sitting_remind;
extern forget_disturb_struct g_forget_disturb;
extern watch_face_struct g_watch_face;
extern message_display_struct g_message_display;
extern gsensor_test_struct g_gsensor_test_info;
extern unit_setting_struct g_unit_setting;
extern alarm_info_struct g_alarm_info;
extern watch_setting_struct g_watch_setting;
extern pair_finish_struct g_app_pair;
extern photograph_onoff_struct g_photograph_info;
extern drink_alarm_struct g_drink_alarm_info;
extern hand_rise_switch_struct g_hand_rise;
extern heart_auto_switch_struct g_heart_auto_switch;
extern call_alarm_struct g_call_alarm;
extern message_alarm_struct g_message_alarm;
extern target_alarm_struct g_target_alarm;
extern app_sport_struct g_app_sport;
extern app_sport_struct g_app_sport_sync;
extern HR_control_struct g_hr_control;
extern app_test_struct g_app_test;
extern power_analysis_struct g_power_analysis;
extern unsigned char g_system_start_flag; //0: system clear start flag, 1: system start flag set.
//extern unsigned int g_ble_mac; //ble mac addr offset.
extern unsigned char g_10min_alarm_num; //the after 10min alarm number.
extern unsigned char g_brightness;
extern unsigned char g_low_power_flag; //0: normal, 1: low power.
extern unsigned char g_app_heart_cmd_flag; //0: close, 1: open.
extern function_control_struct g_fun_control;
extern hardware_info_struct g_hardware_info;
extern shake_style_struct g_shake_style;
extern vib_mode_struct g_vib_mode;
extern unsigned short g_widget_app_list[WIDGET_MAX_TOTAL];
extern unsigned char g_moreinfo_window_style;
extern alarm_clock_info_struct g_alarm_clock[5];
extern password_struct g_password;
extern unsigned short g_key_double;
extern unsigned short g_key_long;
extern woman_stage_info_struct g_woman_stage_info;
extern woman_stage_time_struct g_woman_data;
extern WOMAN_ALARM_TYPE g_woman_stage;
extern resolution_info_struct g_phone_resolution;
extern unsigned char g_language_list_flag;
extern unsigned char g_manual_hfp_flag;

extern btedr_device_struct  g_btedr_device;

extern unsigned char g_sms_reply_index;

extern unsigned char cmp_user_info(user_info_struct* pInfo1, user_info_struct* pInfo2);
extern unsigned int sys_offset_sec_get(void);
extern void sys_sec_set(unsigned int sec);
extern unsigned int sys_sec_get(void);
extern void sys_time_set(const time_struct *time);
extern unsigned int sys_time_get(time_struct *time);
extern unsigned char sys_time_get_12h(time_struct *ptime, unsigned int *psec);
extern void set_battery_info(unsigned char current_capacity);
extern unsigned char get_battery_capacity(void);
extern void time_to_sec(const time_struct *time,unsigned int *sec);
extern void sec_to_time(unsigned int sec,time_struct *time);
extern void find_phone(unsigned char onoff);
extern void call_control_handler(CALL_CMD_TYPE cmd);
extern void ancs_phone_control(CALL_CMD_TYPE call_cmd);
extern unsigned char get_ancs_call_flag(void);
extern void ext_btaud_music_control_handler(MUSIC_CMD_TYPE cmd);
extern void Phone_music_control_handler(MUSIC_CMD_TYPE cmd);
extern void hr_control_handler(HR_CONTROL_TYPE type, unsigned char onoff);
extern unsigned char char_to_int(unsigned char *data, unsigned int *value, unsigned char num);
extern unsigned char int_to_char(unsigned int src, unsigned char *data, unsigned char len);
extern unsigned short calculate_crc16(unsigned short crc16,unsigned char *buf, unsigned int len);
extern void set_call_flag(unsigned char flag);
extern unsigned char get_call_flag(void);
extern void set_system_mode(system_mode_type type);
extern system_mode_type get_system_mode(void);
extern void target_check(void);
extern void heart_check(unsigned char hr);
extern int  take_photo(unsigned char onoff);
extern void power_analysis_handler(POWER_ANALYSIS_TYPE type, unsigned char onoff);
extern float Q_rsqrt( float number );
extern unsigned char first_connection_flag;

//工厂测试标志位
extern void factory_timer_stop_handler(void);


extern const weather_info_item_struct* get_today_weather(unsigned int* dayIndex);

#endif //_DATA_COMMON_H



