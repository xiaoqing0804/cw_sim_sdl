#ifndef _DATA_MANAGER_SENSOR_H
#define _DATA_MANAGER_SENSOR_H

#include "data_transfer.h"
#include "data_common.h"

#define SENSOR_TAG_BACKUP_FLAG		0xAA

typedef enum
{
	TAG_FLAG_START = 0,
	TAG_FLAG_END,
	TAG_FLAG_LEN
}tag_backup_flag_pos;

typedef enum
{
	READ_SENSOR_RAM = 0,
	READ_SENSOR_FLASH,
	READ_SENSOR_EMPTY,
	READ_SENSOR_ERROR
}READ_SENSOR_STATUS;

typedef enum
{
	STORE_RAM_TYPE = 0,
	STORE_FLASH_TYPE,
}STORE_TYPE;

typedef enum
{
	FLASH_CMD_SENSOR_READ = 0,
	FLASH_CMD_SENSOR_WRITE,
	FLASH_CMD_SENSOR_ERASE,
	FLASH_CMD_SENSOR_CLEAR_ALL,
	FLASH_CMD_SENSOR_INIT,
	FLASH_CMD_SENSOR_ITEM_NUM,
}FLASH_CMD_SENSOR;

typedef struct
{
	unsigned int read_index;		//sensor flash read index.
	unsigned int write_index;	//sensor flash write index.
	unsigned int erase_index;	//sensor flash erase index.
	unsigned char ram_num;		//sensor ram save number.
	const DATA_TYPE data_type; //sensor data type , see DATA_TYPE.
	const STORE_TYPE store;		//sensor item data store type.
	const unsigned int start_addr;	//sensor flash start address.
	unsigned char *const ram_addr;	//ram sensor item addr value.
	const unsigned int max_size;		//sensor flash max size.
	const unsigned int item_size;		//sensor flash item size.
}flash_sensor_item_info_struct;

typedef struct
{
	const unsigned int start_addr;	//the tag info flash start address.
	const unsigned int end_addr;	//the tag info flash end address.
	const unsigned int backup_size;	//the tag info backup size.
	unsigned int write_addr;		//the tag info write address.
}flash_sensor_tag_info_struct;

typedef struct
{
	unsigned char type;		//the sensor tag type.
	unsigned char write_index[4]; //the sensor write_index value.
	unsigned char erase_index[4]; //the sensor erase_index value.
	unsigned char check_flag;	//the sensor check flag value.
}sensor_tag_item_struct;

typedef struct
{
	unsigned char all_items[2];	//all sensor items number.
	unsigned char items;		//current sensor items number.
	unsigned char data[1];		//sensor items data point.
}read_sensor_item_struct;

typedef struct
{
	DATA_TYPE data_type;
	unsigned char *data;
	unsigned int max_size;
}flash_sensor_item_read_struct;

typedef struct
{
	DATA_TYPE data_type;
	unsigned char *data;
}flash_sensor_item_save_struct;

typedef struct
{
	DATA_TYPE data_type;
}flash_sensor_item_erase_struct;

typedef struct
{
	DATA_TYPE data_type;
}flash_sensor_item_num_struct;

extern flash_sensor_item_info_struct *const p_sensor_info;
extern const unsigned int SENSOR_INFO_NUM;
extern sport_info_struct ram_sport_info;
extern heart_item_struct hr_ram_info;
extern unsigned int last_hour_steps; //the last hour steps num.
extern unsigned short steps_hour_table[24];

extern unsigned int data_manager_sensor_handler(unsigned int cmd, void *argument);
extern unsigned int block_get_sensor_item_num(DATA_TYPE data_type);
extern unsigned char block_save_sensor_item(
					DATA_TYPE data_type,
					unsigned char *data);
extern unsigned int block_read_sensor_data(
					DATA_TYPE data_type,
					unsigned char *data,
					unsigned int max_size);
extern unsigned char block_erase_sensor_item(DATA_TYPE data_type);
extern void block_clear_all_sensor_item_info(void);
extern void block_init_sensor_info(void);
extern void check_sensor_data_timer_handler(void *argument);
extern void save_history_sport_data(void);
extern void save_real_sport_data(void);
extern void save_activity_info_data(void);
extern void save_sport_heart_data(unsigned char value, unsigned char sync);


#endif //_DATA_MANAGER_SENSOR_H

