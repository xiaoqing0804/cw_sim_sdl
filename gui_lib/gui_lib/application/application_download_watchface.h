#ifndef __APPLICATION_DOWNLOAD_WATCHFACE_H__
#define __APPLICATION_DOWNLOAD_WATCHFACE_H__



unsigned int app_dlwf_init(const gui_screen_struct* screen);

unsigned int app_dlwf_load_data_item(const gui_screen_struct* screen, unsigned int cmd_id);
unsigned int app_dlwf_load_data(const gui_screen_struct* screen);

unsigned int app_dlwf_update_sportinfo(const gui_screen_struct* screen);

unsigned int app_dlwf_update_time(const gui_screen_struct* screen);

unsigned int app_dlwf_update_second(const gui_screen_struct* screen);

unsigned int app_dlwf_update_sync_systime(const gui_screen_struct* screen);

unsigned int app_dlwf_is_second_ind(void);

unsigned int app_dlwf_is_second_360(void);


#endif

