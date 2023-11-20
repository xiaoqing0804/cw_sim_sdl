#ifndef __GUI_DISPLAY_INTERNAL_H__
#define __GUI_DISPLAY_INTERNAL_H__

#define BOOL_TRUE_FLAG  0x5A
#define BOOL_FALSE_FLAG 0xA5

void gui_display_task_create(void);

bool gui_display_isSuspended(void);
bool gui_display_isReady(void);
bool gui_display_isRenderPended(void);

int  gui_display_suspend(unsigned char bypass);
int  gui_display_resume(void);

unsigned int gui_display_take_mutex(unsigned int wait);
void gui_display_give_mutex(void);

void gui_display_te_single(void);

void gui_display_idle_set(unsigned char onoff);

void gui_driver_dbg_systick(char* infoFmt);

#endif

