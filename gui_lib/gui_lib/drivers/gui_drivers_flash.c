#include "gui_drivers_flash.h"
#include "data_manager_flash.h"
#include "data_manager.h"
#include "picture.h"


#ifdef __CW_JL_VLT_MEM__
#include "os_mem.h"

static unsigned char* g_gui_drivers_flash_buff;
void gui_driver_flash_memory_init(void)
{
#if (TCFG_PSRAM_DEV_ENABLE == ENABLE_THIS_MOUDLE)
    unsigned int mem_type = RAM_TYPE_PSRAM_ON;
#else
    unsigned int mem_type = RAM_TYPE_BUFFER_ON;
#endif

    g_gui_drivers_flash_buff = os_mem_alloc(mem_type, GUI_SCREEN_BUF_SIZE);
    if (g_gui_drivers_flash_buff == NULL) {
        DBG_DIRECT("gui: flash_memory_init, error!!!");
    }
}
void gui_driver_flash_memory_deinit(void)
{
    os_mem_free(g_gui_drivers_flash_buff);
    g_gui_drivers_flash_buff = NULL;
}
#else
static unsigned int g_gui_drivers_flash_buff[GUI_SCREEN_BUF_SIZE/4] ={0};
#endif


static unsigned char* gui_drivers_flash_read_to_buff(unsigned int addr, int len, unsigned char* buff)
{
#if (TCFG_NOR_RES_INTER&&TCFG_NOR_RES)
    if (addr & 0x40000000) {
        // nothing
    }
    else {
        addr += (PIC_OFFSET + SECTOR_1_FONT_BASE);
    }
#else
    addr += (PIC_OFFSET + SECTOR_1_FONT_BASE);
#endif
	block_spi_flash_read_high_speed((unsigned int)addr, buff, (unsigned int)len);
	return buff;
}

unsigned char* gui_drivers_flash_read_image_to_buff(unsigned int addr, int len)
{
	if(len > GUI_SCREEN_BUF_SIZE)
		len = GUI_SCREEN_BUF_SIZE;

	return gui_drivers_flash_read_to_buff((unsigned int)addr, (unsigned int)len, (unsigned char*)g_gui_drivers_flash_buff);
}

unsigned char*  gui_drivers_flash_read_image_to(unsigned char* buff,unsigned int addr, int len)
{
    if (buff != NULL) {
    	return gui_drivers_flash_read_to_buff((unsigned int)addr, (unsigned int)len, buff);
    }
    return NULL;
}


