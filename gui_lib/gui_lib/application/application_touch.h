#ifndef __APPLICATION_TOUCH_H__
#define __APPLICATION_TOUCH_H__

#include "feature_all.h"
#include "gui_core_all.h"

extern void application_touch_down(int x,int y,uint32_t time);
extern void application_touch_move(int x,int y,uint32_t time);
extern void application_touch_up(int x,int y,uint32_t time);
extern void application_touch_cancle(void);
extern void application_touch_finish(void);
extern unsigned char application_touch_event_is_active(void);
extern unsigned char application_touch_is_runing(void);

#endif

