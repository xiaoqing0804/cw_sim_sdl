#ifndef _SYS_INIT_H
#define _SYS_INIT_H

extern unsigned char SysInitStatus_Query(void);
extern void SysInitStatus_Set(void);
extern void sys_delay(unsigned int ms);
extern void sys_delay_us(unsigned int usec);
extern void system_shutdown_int(void);
extern void system_shutdown(void);
extern void system_reset(void);
extern void system_reboot(void);
extern void system_reset_fouce(void);
extern void sys_init(void);

#define SYS_POWER_FLAG_REBOOT       0
#define SYS_POWER_FLAG_SHUTDOWN     0xA5
extern void system_set_power_flag(unsigned char flag);

#endif //_SYS_INIT_H

