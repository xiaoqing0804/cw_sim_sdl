#ifndef __APP_WINDOW_CALL_H__
#define __APP_WINDOW_CALL_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

extern const gui_window_struct app_window_call;

extern const gui_window_struct app_window_call_comming;

extern const gui_window_struct app_window_call_outgoing;

extern const gui_window_struct app_window_call_vol;

extern const gui_window_struct app_window_call_reply;

extern const gui_window_struct app_window_call_phonebook;

extern const gui_window_struct app_window_call_clog;

extern const gui_window_struct app_window_call_dial;

extern int app_adjust_call_volume(int buf, int call_volum);

#endif

