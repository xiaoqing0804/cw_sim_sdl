#ifndef _DATA_RECEIVE_PACKAGE_H
#define	_DATA_RECEIVE_PACKAGE_H

#include "data_transfer.h"
#include "data_common.h"

extern unsigned char g_call_cmd;
extern unsigned char g_call_comming_flag; //0: no comming, 1: call comming.

extern unsigned char get_ble_appconnect(void);
extern unsigned char get_ble_dataconnect(void);
extern unsigned char get_dev_pair_flag(void);
extern void set_ble_dataconnect(unsigned char onoff);
extern void set_ble_appconnect(unsigned char onoff);
extern void set_dev_pair_flag(unsigned char onoff);
extern unsigned char handler_receive_cmd(cmd_package_struct *argument);
extern unsigned char receive_messageInfo_from_ancs(unsigned char *data,unsigned int len);
extern unsigned char receive_call_control_from_ancs(CALL_CMD_TYPE call_type);

#endif //_DATA_RECEIVE_PACKAGE_H

