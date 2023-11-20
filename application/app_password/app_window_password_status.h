#ifndef __APP_WINDOW_PASSWORD_STATUS_H__
#define __APP_WINDOW_PASSWORD_STATUS_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

#define PASSWORD_STATUS_LENGTH (5)
#define PASSWORD_STATUS_INPUT_TOTAL (PASSWORD_STATUS_LENGTH - 1)

enum
{
    PASSWORD_STATUS_NONE,
    PASSWORD_STATUS_ADD_PASSWORD,
    PASSWORD_STATUS_REMOVE_PASSWORD,
    PASSWORD_STATUS_CHANGE_PASSWORD,
    PASSWORD_STATUS_UNLOCK,
};

enum
{
    PASSWORD_ERROR_NONE,

    PASSWORD_ERROR_INPUT_CHAR,
    PASSWORD_ERROR_INPUT_CHAR_AGAIN,

    PASSWORD_ERROR_WRONG,
    PASSWORD_ERROR_NO_MATCH,
};

typedef struct _password_info_struct password_info_struct;
typedef void (*password_input_step_callback)(password_info_struct *info);

struct _password_info_struct
{
    unsigned char orgin_password[PASSWORD_STATUS_LENGTH];
    unsigned char frist_password[PASSWORD_STATUS_LENGTH];
    unsigned char second_password[PASSWORD_STATUS_LENGTH];
    unsigned char password[PASSWORD_STATUS_LENGTH];
    unsigned char step;
    unsigned char error; // PASSWORD_ERROR_NONE
    password_input_step_callback step_callback;
};

extern password_info_struct *app_window_password_status_init(password_input_step_callback step_callback);
extern void app_window_password_status_init_for_unlock(void);
extern password_info_struct *app_window_password_status_get_info(void);
extern unsigned char *app_window_password_status_get_value(void);
extern unsigned char app_window_password_status_get_input_length(void);
extern unsigned char app_window_password_status_is_input_max(void);
extern unsigned char app_window_password_status_get_error(void);
extern unsigned char app_window_password_status_check_right(void);
extern unsigned char app_window_password_status_check_match(void);
extern void app_window_password_status_add(unsigned char input_char);
extern void app_window_password_status_remove(void);
extern void app_window_password_status_swap(unsigned char *to);
extern void app_window_password_status_complete_step(void);

#endif
