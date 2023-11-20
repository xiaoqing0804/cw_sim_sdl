#include "gui_event_core_list.h"
#include "gui_surface_control.h"

#if GUI_SIDEBAR_SUPPORT
extern const gui_static_event_struct g_app_sidebar_on_datetime;
extern const gui_static_event_struct g_app_sidebar_on_sync_datetime;
extern const gui_static_event_struct g_app_sidebar_on_ble_connect;
extern const gui_static_event_struct g_app_sidebar_on_unit_setting;
#endif

/*------------------EVENT_ID_TIME_STEP_SECOND------------------------------*/
static const gui_static_event_struct* const g_event_time_step_second_list[] =
{
	&g_gui_control_time,
};

/*------------------EVENT_ID_TIME_STEP_MINUTE------------------------------*/
static const gui_static_event_struct* const g_event_time_step_minute_list[] =
{
	&g_gui_control_time,
	&g_gui_control_time_hour,
	&g_gui_control_time_min,
	&g_gui_control_date,
#if GUI_SIDEBAR_SUPPORT
    &g_app_sidebar_on_datetime,
#endif
};

/*------------------EVENT_UPDATE_SYS_TIME--------------------------------*/
static const gui_static_event_struct* const g_event_time_sync_list[] =
{
#if GUI_SIDEBAR_SUPPORT
    &g_app_sidebar_on_sync_datetime,
#endif
};

/*------------------EVENT_ID_TIME_STEP_HOUR------------------------------*/
static const gui_static_event_struct* const g_event_time_step_hour_list[] =
{
//    NULL
	&g_gui_control_time_hour,
};

/*------------------EVENT_ID_TIME_STEP_DAY------------------------------*/
static const gui_static_event_struct* const g_event_time_step_day_list[] =
{
    NULL
};


/*------------------EVENT_BLE_CONNECT_STATUS------------------------------*/
static const gui_static_event_struct* const g_event_bt_status_list[] =
{
    &g_gui_control_bt_icon,
#if GUI_SIDEBAR_SUPPORT
    &g_app_sidebar_on_ble_connect,
#endif
};

/*------------------EVENT_UPDATE_UNIT_SETTING------------------------------*/
static const gui_static_event_struct* const g_event_unit_sync_list[] =
{
#if GUI_SIDEBAR_SUPPORT
    &g_app_sidebar_on_unit_setting,
#endif
};



static const gui_static_event_struct* const g_event_batt_status_list[] = 
{
    &g_gui_control_batt_icon_evt,
    &g_gui_control_batt_label_evt,
};


extern const gui_static_event_struct g_application_touch_window_exit_event;
static const gui_static_event_struct* const g_event_window_exit_list[] = 
{
    &g_application_touch_window_exit_event,
};


/////////////////////////////////////////////////////////////////////////////////////////////
// 灭屏时，停止scroll-text
extern const gui_static_event_struct g_suface_scroll_text_suspend_event;
extern const gui_static_event_struct g_suface_scroll_text_resume_event;
static const gui_static_event_struct* const g_event_gui_suspend_list[] = 
{
    &g_suface_scroll_text_suspend_event,
};
static const gui_static_event_struct* const g_event_gui_resume_list[] = 
{
    &g_suface_scroll_text_resume_event,
};


/*--------------------MAP LIST------------------------------*/
/*注意: 必须按顺序排列*/
const gui_static_event_map_struct g_event_map_list[] =
{
	{EVENT_RTC_SECOND_IND, countof(g_event_time_step_second_list), g_event_time_step_second_list },
	{EVENT_RTC_MINUTE_IND, countof(g_event_time_step_minute_list), g_event_time_step_minute_list },
    {EVENT_UPDATE_SYS_TIME, countof(g_event_time_sync_list), g_event_time_sync_list },
	{EVENT_RTC_HOUR_IND, countof(g_event_time_step_hour_list), g_event_time_step_hour_list },
	{EVENT_RTC_DAY_IND, countof(g_event_time_step_day_list), g_event_time_step_day_list },
    {EVENT_BLE_CONNECT_STATUS, countof(g_event_bt_status_list), g_event_bt_status_list },   
    {EVENT_BATTERY_CHARGER, countof(g_event_batt_status_list), g_event_batt_status_list },  
	{GUI_EVENT_WINDOW_EXIT, countof(g_event_window_exit_list), g_event_window_exit_list },	
	{EVENT_UPDATE_UNIT_SETTING, countof(g_event_unit_sync_list), g_event_unit_sync_list },

	// 灭屏时，停止scroll-text
    {EVENT_GUI_SUSPENDED, countof(g_event_gui_suspend_list), g_event_gui_suspend_list}, 
    {EVENT_GUI_RESUMED, countof(g_event_gui_resume_list), g_event_gui_resume_list},
};



const gui_static_event_map_struct* get_gui_event_by_index(short index)
{
	if(index < 0 || index >= countof(g_event_map_list))
		return NULL;
	return &g_event_map_list[index];
}

const gui_static_event_map_struct* get_gui_event_by_id(short id)
{
	if(id >= 0 || id < EVENT_ALL)
	{
		const gui_static_event_map_struct* event_map = get_gui_event_by_index(0);
		for(short i = 0; i < countof(g_event_map_list); i++)
		{
			if(event_map->id == id)
				return event_map;
			event_map++;
		}		
	}
	return NULL;
}



