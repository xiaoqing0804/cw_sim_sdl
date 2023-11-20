#ifndef __APP_WINDOW_MORE_INFO_KALEIDOSCOPE_H__
#define __APP_WINDOW_MORE_INFO_KALEIDOSCOPE_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"
#include "app_window_moreinfo_kaleidoscope_layout.h"

//һ���ݣ�������ð��������Ļ�����
typedef struct
{
    gui_kaleidoscope_app_struct *app;
    gui_box_struct *box;
    float scale;  //��Ļ���ĵ���Ļ��ı�������������λ�ú��ݵİ뾶
    short status; //0��Բ��λ��  1��2 ���м���ʾ 3����Ļ 0�ص�Բ��
} gui_kaleidoscope_item_struct;


//ÿһ�����߰���2���ݣ�2����֮����1��״̬
typedef struct
{
    gui_kaleidoscope_item_struct items[2];
} gui_kaleidoscope_ray_struct;

extern const gui_window_struct app_window_moreinfo_kaleidoscope;

#endif
