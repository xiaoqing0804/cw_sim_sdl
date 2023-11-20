#include "dev_version.h"
#include "debug_info.h"
#include "ota.h"

#define DEV_CODE_ID		1				//code ID.
#define DEV_PIC_ID      0			    //picture ID.


#define VECTOR_TABLE_BASE	(OTA_TMP_ADDR)		//124*1024
#define VECTOR_TABLE_END		(OTA_TMP_ADDR+OTA_TMP_SIZE)		//this is application end address.

#ifdef __CW_APP_TEST__
unsigned char g_cust_ble_name[DEV_BLE_NAME_MAX + 1];
unsigned char g_cust_edr_name[DEV_EDR_NAME_MAX + 1];
#endif

unsigned char g_hardware_version = HW_TYPE_NULL;

//#pragma location = ".dev_version"			//0x20000 , the offset address is 0x1000.
//__root
const dev_version_struct g_dev_version =
{
	.flag = 0x1A2B3C4D,
	.base_addr = VECTOR_TABLE_BASE,
	.end_addr = VECTOR_TABLE_END,
	.items = 4,

	.customer =
	{
		.start_addr = 0,
		.end_addr = 0,
		.type = FILE_TYPE_CUSTOMER,
		.id = DEV_CUSTOMER_ID,
	},


	.code =
	{
		.start_addr = VECTOR_TABLE_BASE,
		.end_addr = VECTOR_TABLE_END,
		.type = FILE_TYPE_CODE,
		.id = DEV_CODE_ID,
	},

	.pic =
	{
		.start_addr = 0,
		.end_addr = 0,
		.type = FILE_TYPE_PIC,
		.id = DEV_PIC_ID,
	},

	.font =
	{
		.start_addr = 0,
		.end_addr = 0,
		.type = FILE_TYPE_FONT,
		.id = DEV_FONT_ID,
	},
};

void init_hardware_version(void)
{
#if 0
	unsigned char version[1] = { 0 };

	nrf_gpio_cfg_input(HW_PIN, NRF_GPIO_PIN_NOPULL);
	version[0] = nrf_gpio_pin_read(HW_PIN);
	nrf_gpio_cfg_default(HW_PIN);

	SYS_DEBUG("hardware version data : %d\r\n", version[0]);

	if (version[0] == 0)
	{
		SYS_DEBUG("hardware version is HW_TYPE_V10\r\n");
		g_hardware_version = HW_TYPE_V10;
	}
	else {
		SYS_DEBUG("hardware version is HW_TYPE_V11\r\n");
		g_hardware_version = HW_TYPE_V11;
	}
#endif
}


