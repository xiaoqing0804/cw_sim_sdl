#ifndef _DATA_MANAGER_MESSAGE_H
#define _DATA_MANAGER_MESSAGE_H

#define MES_RETAIN_TIME		(0)//(5*60)

#define ITEM_W_FLAG			0xAA
#define ITEM_E_FLAG			0xAA

#define MESSAGE_ITEM_SIZE	240

typedef enum
{
	ITEM_WRITE_S = 0,
	ITEM_WRITE_E,
	ITEM_ERASE_S,
	ITEM_NONE,
	ITEM_FLAG_LEN
}item_flag_pos;

typedef enum
{
	FLASH_CMD_MESSAGE_INIT = 0,
	FLASH_CMD_MESSAGE_SAVE,
	FLASH_CMD_MESSAGE_READ,
	FLASH_CMD_MESSAGE_ERASE,
	FLASH_CMD_MESSAGE_GET_ITEMS,
	FLASH_CMD_MESSAGE_CLEAR_ALL,
}FLASH_CMD_MESSAGE;

typedef enum
{
	MESSAGE_TYPE_NULL = 0,
	MESSAGE_TYPE_CALL,
	MESSAGE_TYPE_MESSAGE,
	MESSAGE_TYPE_QQ,
	MESSAGE_TYPE_WECHAT,
	MESSAGE_TYPE_MAIL,          // 5
	MESSAGE_TYPE_FACEBOOK,
	MESSAGE_TYPE_TWITTER,
	MESSAGE_TYPE_WHATSAPP,
	MESSAGE_TYPE_SKYPE,
	MESSAGE_TYPE_LINKED_IN,         // 10
	MESSAGE_TYPE_LINE,
	MESSAGE_TYPE_GOOGLE_MESSAGE,
	MESSAGE_TYPE_GOOGLE_CALENDAR,
	MESSAGE_TYPE_NATIVE_CALENDAR,
	MESSAGE_TYPE_GOOGLE_GMAIL,      // 15
    
	MESSAGE_TYPE_OTHER,

	// ANCS_NEW
    MESSAGE_TYPE_KAKAO,
    MESSAGE_TYPE_INSTAGRAM,
    MESSAGE_TYPE_TELEGRAM,

	MESSAGE_TYPE_ALL,
}MSG_TYPE;


typedef struct
{
	const unsigned int type;	//message type, see MESSAGE_TYPE.
	const unsigned int start_addr; //message save start address.
	const unsigned int max_size;	//message save max size.
	const unsigned int item_size;	//message item size.
	unsigned int write_index;		//message save item index.
}uumessage_item_info_struct;

typedef struct
{
	const unsigned int type;	//message type, see MESSAGE_TYPE.
	const unsigned int start_addr; //message save start address.
	const unsigned int max_size;	//message save max size.
	const unsigned int item_size;	//message item size.
	unsigned int write_addr;		//message save pos address.
	unsigned int read_addr;			//message read end address , it maybe equal write_addr.
	unsigned int item_num;			//message item active number.
	unsigned char * const index;	//message item index number point , it save item flag (write or erase flag).
	const unsigned int index_num;	//message item index number.
}message_item_info_struct;

typedef struct
{
	unsigned int type;
	unsigned char *data;
	unsigned int len;
}save_message_info_struct;

typedef struct
{
	unsigned int type;
	unsigned int item;
	unsigned char *data;
	unsigned int len;
}read_message_info_struct;

typedef struct
{
	unsigned int type;
	unsigned int item;
}erase_message_info_struct;

typedef struct
{
	unsigned int type;
}get_message_info_struct;

typedef struct
{
	unsigned int type;
}clear_message_info_struct;

extern void block_init_message_info(void);
extern unsigned int block_save_message_item(MSG_TYPE type, unsigned char *data, unsigned int len);
extern unsigned int block_read_message_item(MSG_TYPE type, unsigned int item, unsigned char *data, unsigned int len);
extern unsigned int block_erase_message_item(MSG_TYPE type, unsigned int item);
extern unsigned int block_get_message_items(MSG_TYPE type);
extern void block_clear_message_item(MSG_TYPE type);
extern void block_clear_all_message_item(void);
extern unsigned int data_manager_message_handler(unsigned int cmd,void *argument);

extern unsigned char g_message_buf[256];
extern unsigned char AU_call_num[40];

#endif //_DATA_MANAGER_MESSAGE_H

