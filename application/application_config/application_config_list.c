#include "application_config_list.h"
#include "application_config_main_window.h"
#include "app_more_info/app_window_moreinfo.h"
/*-----------A��A--------------*/
extern gui_window_struct app_window_sport;
extern gui_window_struct app_window_quick;
extern gui_window_struct app_window_moreinfo_icon_list;
extern gui_window_struct app_window_message_list;
extern gui_window_struct app_window_message_delete_all;
extern gui_window_struct app_window_heartrate;
extern gui_window_struct app_window_widget;
extern gui_window_struct app_window_o2;
extern gui_window_struct app_window_o2_measur;
extern gui_window_struct app_window_alarm_target_finish;

extern gui_window_struct app_window_widget_delete;
extern gui_window_struct app_window_flashlight;

extern gui_window_struct app_window_weather;

extern gui_window_struct app_window_more_info_list;
extern gui_window_struct app_window_language_list;
extern gui_window_struct app_siri_window;


gui_window_swipe_struct g_window_swipe_list[C_WINDOW_SWIPE_LIST_SZ] =
{
	{
		.window = APP_MAIN_WINDOW_MAGIC,
		.type = WINDOW_SWIPE_TYPE_MOVE,
        .dont_pull_empty = 1,
		.left = NULL,//APP_FUNC_WINDOW_MAGIC/*APP_FUNC_WINDOW_MAGIC*/,
		.right = NULL,
		.up = &app_window_quick,
		.down = &app_window_message_list,
	},
    {
        .window = APP_FUNC_WINDOW_MAGIC,
        .type = WINDOW_SWIPE_TYPE_MOVE,
        .left = NULL,
        .right = APP_MAIN_WINDOW_MAGIC,
        .up = NULL,
        .down = NULL,
    },
    {
		.window = &app_window_quick,
		.type = WINDOW_SWIPE_TYPE_COVER,
        .dont_pull_empty = 1,
		.left = NULL,
		.right = NULL,
		.up = NULL,
		.down = APP_MAIN_WINDOW_MAGIC,
	},
    {
		.window = &app_window_message_list,
		.type = WINDOW_SWIPE_TYPE_COVER,
        .dont_pull_empty = 1,
		.left = NULL ,
		.right =NULL,
		.up = APP_MAIN_WINDOW_MAGIC,
		.down = NULL,
    },

    {
        .window = &app_window_heartrate,
        .type = WINDOW_SWIPE_TYPE_MOVE,
        .down = NULL,
    },
//    {
//        .window = &app_window_o2,
//        .type = WINDOW_SWIPE_TYPE_MOVE,
//        .down = &app_window_o2_measur,
//    },
//    {
//        .window = &app_window_o2_measur,
//        .type = WINDOW_SWIPE_TYPE_MOVE,
//        .up = &app_window_o2,
//    },
};


const gui_window_swipe_struct* application_list_get_swipe_window(const gui_window_struct* window)
{
	if(window == NULL)
		return NULL;

    if (window == application_main_window_get_curr_window()) {
        window = APP_MAIN_WINDOW_MAGIC;
    }
	if (window == app_window_moreinfo_get()) {
        window = APP_FUNC_WINDOW_MAGIC;
    }

	for(unsigned char i = 0; i < countof(g_window_swipe_list) ; i++ )
	{
		if(g_window_swipe_list[i].window == window)
			return &g_window_swipe_list[i];
	}
	return NULL;
}

void application_list_change(const gui_window_struct* window, const gui_window_struct* up, const gui_window_struct* down, const gui_window_struct* left, const gui_window_struct* right)
{
    gui_window_swipe_struct* swipe = (gui_window_swipe_struct*)application_list_get_swipe_window(window);
    if (swipe == NULL) {
        // add
        unsigned int idx;
        for (idx=0; idx<C_WINDOW_SWIPE_LIST_SZ; idx++) {
            if (g_window_swipe_list[idx].window == NULL) {
                swipe = &g_window_swipe_list[idx];
                swipe->type = WINDOW_SWIPE_TYPE_MOVE;
                swipe->window = window;
                swipe->up = NULL;
                swipe->down = NULL;
                swipe->left = NULL;
                swipe->right = NULL;
                break;
            }
        }
    }
    if (swipe != NULL) {
        if (up != NULL)     swipe->up = up;
        if (down != NULL)   swipe->down = down;
        if (left != NULL)   swipe->left = left;
        //if (right != NULL)
        swipe->right = right;
    }
}

void application_list_clean_window(const gui_window_struct* window)
{
    gui_window_swipe_struct* swipe = (gui_window_swipe_struct*)application_list_get_swipe_window(window);
    if (swipe != NULL) {
        swipe->left = NULL;
        swipe->right = NULL;
    }
}




