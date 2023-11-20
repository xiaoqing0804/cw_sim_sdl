
#ifndef __APPLICATION_PASSWORD_H__
#define __APPLICATION_PASSWORD_H__


unsigned int application_password_isLocked(void);

unsigned int application_password_verify(unsigned char* pwd);


void application_password_setLock(unsigned int lock);

void application_password_setTempLock(unsigned int tempLock);


void application_password_setOnoff(unsigned int onoff);

unsigned int application_password_getOnoff(void);

void application_password_ste(unsigned char* pwd);

#endif


