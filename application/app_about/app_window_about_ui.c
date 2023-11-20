#include "app_window_about_ui.h"
#include "app_window_about_layout.h"

#include "sys_init.h"
#include "data_common.h"
#include "bsp_includes.h"

#include "gui_surface_box_label.h"
#include "gui_surface_box_image.h"
#include "app_flashlight\app_window_tptest.h"
#include "app_test\app_window_pwrloss.h"

/*********************************************************************************************************/

/// @brief 屏幕
/// @param tpInfo
static void app_window_about_ui_show_tp(TP_info_struct *tpInfo)
{
	char temp[40] = {0};
	snprintf(temp, sizeof(temp), "%c-%d-%04X", tpInfo->type, tpInfo->id, tpInfo->checksum);
	gui_box_struct *tp = gui_surface_get_box(&gui_screen_about, (unsigned short)ABOUT_LAYOUT_ID_TP);
	gui_surface_box_label_change_string(tp, (unsigned char *)temp);
}

/// @brief 硬件id
/// @param devInfo
static void app_window_about_ui_show_hardware_id(dev_info_struct *devInfo)
{
	char temp[40] = {0};

	/* 2. draw hardware version. */
	unsigned char hardware_id = devInfo->dev_id.hardware_id;
	if (!bsp_gsensor_is_ready())
	{
		hardware_id &= ~(1 << 1);
	}

	if (get_config_file_flag() > 0)
	{
		snprintf(temp, sizeof(temp), "%d.%02X.%d.%d.%d",
				 devInfo->dev_id.customer_id + (devInfo->dev_id.customer_id_h << 8),
				 hardware_id,
				 devInfo->dev_id.code_id,
				 devInfo->dev_id.picture_id,
				 devInfo->dev_id.font_id);
	}
	else
	{
		snprintf(temp, sizeof(temp), "%d.FF.FF.FF.FF", devInfo->dev_id.customer_id);
	}
	gui_box_struct *devsion = gui_surface_get_box(&gui_screen_about, (unsigned short)ABOUT_LAYOUT_ID_BLUETOOTH);
	gui_surface_box_label_change_string(devsion, (unsigned char *)temp);
}

/// @brief 地址
/// @param devInfo
void app_window_about_ui_show_mac(dev_info_struct *devInfo)
{
	char temp[40] = {0};
	snprintf(temp, sizeof(temp), "%02X:%02X:%02X:%02X:%02X:%02X",
			 devInfo->mac_addr[5],
			 devInfo->mac_addr[4],
			 devInfo->mac_addr[3],
			 devInfo->mac_addr[2],
			 devInfo->mac_addr[1],
			 devInfo->mac_addr[0]);

	gui_box_struct *mac = gui_surface_get_box(&gui_screen_about, (unsigned short)ABOUT_LAYOUT_ID_MAC);
	gui_surface_box_label_change_string(mac, (unsigned char *)temp);
}

/// @brief 显示项目ID号
/// @param devInfo 开发信息
void app_window_about_ui_show_crc_id(dev_info_struct *devInfo)
{
	/* 4. draw ID. */
	unsigned short crc16 = calculate_crc16(0, devInfo->mac_addr, sizeof(devInfo->mac_addr));

	char temp[40] = {0};
	snprintf(temp, sizeof(temp), "%04X", crc16);

	gui_box_struct *box = gui_surface_get_box(&gui_screen_about, (unsigned short)ABOUT_LAYOUT_ID_CRC_ID);
	if (box != NULL)
	{
		gui_surface_box_label_change_string(box, (unsigned char *)temp);
	}
}

/**********************************************导出***********************************************************/

/// @brief 显示
static void app_window_about_ui_show()
{
	application_titlebar_create(&gui_screen_about, STRING_ABOUT);

	app_window_about_ui_show_tp(&g_TP_info);
	app_window_about_ui_show_hardware_id(&g_devInfo);
	app_window_about_ui_show_mac(&g_devInfo);
	app_window_about_ui_show_crc_id(&g_devInfo);
}
