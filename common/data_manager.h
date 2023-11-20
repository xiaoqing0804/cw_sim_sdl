#ifndef _DATA_MANAGER_H
#define _DATA_MANAGER_H

#include "data_transfer.h"
#include "data_manager_message.h"
#include "data_manager_user_info.h"

#ifdef __C_NVDM_ENABLE__
#include "nvdm.h"
#endif

#define SPI_FLASH_SECTOR_SIZE	4096

typedef enum{
	//flash base cmd .
	FLASH_CMD_BASE_READ = 0,
	FLASH_CMD_BASE_WRITE,
	FLASH_CMD_BASE_ERASE,
	FLASH_CMD_BASE_CRC16,
}BLOCK_FLASH_CMD_TYPE;

typedef enum{
	FILE_NULL = 0,
	FILE_DATA_MANAGER,
	FILE_DATA_MANAGER_SENSOR,
	FILE_DATA_MANAGER_MESSAGE,
	FILE_DATA_MANAGER_USER_INFO,
	FILE_DATA_MANAGER_OTA,

    //#ifdef __PHONE_BOOK_SYNC_SUPPORTED__
    FILE_DATA_MANAGER_CONTACT,
    //#endif

	FILE_SUM
}FILE_TYPE;

typedef struct
{
	const FILE_TYPE type;
	unsigned int (* const fun)(unsigned int cmd, void *argument);
}flash_file_cmd_struct;

typedef struct
{
    unsigned int addr;
    unsigned char *data;
    unsigned int len;
}spi_flash_read_struct;

typedef struct
{
    unsigned int addr;
    unsigned char *data;
    unsigned int len;
}spi_flash_write_struct;

typedef struct
{
    unsigned int addr;
    unsigned int num;
}spi_flash_erase_struct;

typedef struct
{
	unsigned short crc16;
	unsigned int addr;
	unsigned int len;
}spi_flash_crc16_struct;


extern unsigned short spi_flash_crc16(unsigned short crc16, unsigned int addr, unsigned int len);
extern unsigned short block_spi_flash_crc16(unsigned short crc16, unsigned int addr, unsigned int len);
extern unsigned int block_flash_handler(FILE_TYPE file_type,unsigned int cmd,void *argument);
extern unsigned char block_spi_flash_read(unsigned int addr,unsigned char * data,unsigned int len);
extern unsigned char block_spi_flash_read_high_speed(unsigned int addr,unsigned char * data,unsigned int len);
extern unsigned char block_spi_flash_write(unsigned int addr,unsigned char * data,unsigned int len);
extern unsigned char block_spi_flash_erase_4k(unsigned int addr,unsigned int num);
extern void reset_factory_timer_handler(void *argument);
extern void software_reset_timer_handler(void *argument);
extern void init_data_manager(void);
extern void init_ram_struct(void);
extern void init_dev_mac_addr(unsigned char* edr_addr, unsigned char* ble_addr);
extern void flash_mutex_take(void);
extern void flash_mutex_give(void);
extern void block_save_sys_info(void);

extern void init_data_manager_early(void);

#endif //_DATA_MANAGER_H


