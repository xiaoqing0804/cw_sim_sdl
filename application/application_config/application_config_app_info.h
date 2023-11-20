#ifndef _APPLICATION_CONFIG_APP_INFO_H
#define _APPLICATION_CONFIG_APP_INFO_H

#include "data_common.h"
#include "language.h"
#include "picture.h"

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

typedef enum
{
	APP_INFO_ID_NONE = 0,
	APP_INFO_ID_BREATHE,	//����ѵ��
	APP_INFO_ID_CALC, 		//������
	APP_INFO_ID_CALL,
	APP_INFO_ID_FIND,		//�����ֻ�
	APP_INFO_ID_HR,			//����
	APP_INFO_ID_METT, 		//÷��
	APP_INFO_ID_MUSIC,		//����
	APP_INFO_ID_O2,			//Ѫ��
	APP_INFO_ID_PHOTO,		//���
	APP_INFO_ID_PRESSURE,	//ѹ��
	APP_INFO_ID_QR,			//��ά��
	APP_INFO_ID_SETTING,	//����
	APP_INFO_ID_SLEEP,		//˯��
	APP_INFO_ID_SPORT,		//�˶�
	//APP_INFO_ID_SPORT_2,	//�˶�
	APP_INFO_ID_STEP,		//����
	APP_INFO_ID_STOPWATCH,	//��ʱ
	APP_INFO_ID_TEMPERATURE,//�¶�
	APP_INFO_ID_WEATHER,	//����
	APP_INFO_ID_KEY,
    APP_INFO_ID_HOME,       // ����������
    APP_INFO_ID_ABOUT,      // ����
    APP_INFO_ID_BRIGHTNESS, // ����
    APP_INFO_ID_COUNTER,    // ����ʱ
    APP_INFO_ID_DISTURB,    // ��������
    APP_INFO_ID_LANGUAGE,   // ����
    APP_INFO_ID_LCDTIMEOUT, // lcd Ϣ������
    APP_INFO_ID_REBOOT,     // ����
    APP_INFO_ID_RESTORE,    // �ָ���������
    APP_INFO_ID_SHAKE,      // ҡһҡ
    APP_INFO_ID_SHUTDOWN,   // �ػ�
    APP_INFO_ID_SOS,        // ���� SOS  �绰
    APP_INFO_ID_VIB,        // ������
    APP_INFO_ID_WATCHFACE,  // ����ѡ��
    APP_INFO_ID_WRIST,      // ̧����������

	APP_INFO_ID_ALARM,      // ����
	APP_INFO_ID_BLOOD,      // Ѫѹ
	APP_INFO_ID_CLACULATOR, // ������
	APP_INFO_ID_MESSAGE, 	// ��Ϣ
	APP_INFO_ID_TELEPHONE,
	APP_INFO_ID_SIRI, //��������

	APP_INFO_ID_HRV, //ѹ��

	APP_INFO_ID_QR_PUSH,
    APP_INFO_ID_GAME,
    APP_INFO_ID_WOMAN,//女性生理周期

    APP_INFO_ID_CONTACTS, //��ϵ��call_log
    APP_INFO_ID_CALL_LOG, //ͨ����¼
    APP_INFO_ID_CALENDAR, //����
    APP_INFO_ID_PASSWORD,//����

	APP_INFO_ID_BED,	//床头灯
	APP_INFO_ID_SCREEN_SET,
	APP_INFO_ID_SCREEN_MENU,
	APP_INFO_ID_CONSTANT_LIGHTE,
	APP_INFO_ID_AOD_DIAL,
	APP_INFO_ID_WIDGET,
	APP_INFO_ID_LOCK,

    APP_INFO_ID_ALIPAY,     // TCFG_PAY_ALIOS_ENABLE
	APP_INFO_ID_MAX
}APP_INFO_ID;


#define APP_PICS_NUM      8
#define APP_PICS(name)    { \
                       	&pic_app_##name##_88_info,&pic_app_##name##_88_info, &pic_app_##name##_88_info, &pic_app_##name##_88_info, \
                        &pic_app_##name##_88_info,&pic_app_##name##_88_info, &pic_app_##name##_88_info, &pic_app_##name##_88_info,}

#if GUI_SIDEBAR_SUPPORT
//#define APP_SIDEBAR_PIC(name) &pic_app_sidebar_##name##_info
#define APP_SIDEBAR_PIC(name) NULL
#else
#define APP_SIDEBAR_PIC(name) NULL
#endif

#if GUI_WIDGET_SUPPORT
#define APP_WIDGET_PIC(name) &pic_app_##name##_88_info
#else
#define APP_WIDGET_PIC(name) NULL
#endif


typedef struct _tag_app_info app_info_struct;
struct _tag_app_info
{
	APP_INFO_ID id;
	STRING_ID_TYPE name;
	const gui_window_struct *window;
	const picture_info_struct *icon_sidebar;
	const picture_info_struct *icon_widget;
	const picture_info_struct *icons[APP_PICS_NUM];
	void (*entryApp)(app_info_struct* app_info);
};

extern app_info_struct* get_app_info_by_id(APP_INFO_ID id);
extern picture_info_struct* get_app_normal_icon_by_info(app_info_struct* app_info);
extern picture_info_struct* get_app_normal_icon_by_id(APP_INFO_ID id);
extern void entry_app_by_id(APP_INFO_ID id);
extern void entry_app_by_info(app_info_struct *app_info);


#endif //_DATA_APP_INFO_H


