#include "debug_info.h"
#include "bsp_includes.h"
#include "os_mem.h"
#include "storage_qr_info.h"

#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_qrcode.h"
#include "gui_surface_box_scale.h"

#include "app_window_qr_card.h"
#include "app_window_qr_card_ui.h"
#include "app_window_qr_card_layout.h"

#if defined(GUI_QR_INFO_SUPPORT)&&GUI_QR_INFO_SUPPORT

static unsigned int g_qr_card_indx;
static qr_code_info_struct* g_qr_card_info;


static void app_window_qr_card_init(void *buf)
{
	g_qr_card_indx = *((unsigned int*)buf);
	if (g_qr_card_info == NULL) {
		g_qr_card_info = os_mem_alloc(RAM_TYPE_DATA_ON, sizeof(qr_code_info_struct));
	}
}

static void app_window_qr_card_load(void *buf)
{
	app_window_qr_card_ui_load(g_qr_card_info, g_qr_card_indx);
}

static void app_window_qr_card_entry(void *buf)
{

}

static void app_window_qr_card_exit()
{
}

static void app_window_qr_card_destroy()
{
	if (g_qr_card_info != NULL) {
        os_mem_free(g_qr_card_info);
        g_qr_card_info = NULL;
    }
}

/*-----------------------------配置--------------------------------------*/


const gui_window_struct app_window_qr_card =
{
	.screen = &gui_screen_qr_card,

	.init = app_window_qr_card_init,
	.load = app_window_qr_card_load,
	.entry = app_window_qr_card_entry,
	.exit = app_window_qr_card_exit,
	.destroy = app_window_qr_card_destroy,

};

#endif
