
#include "feature_gui.h"
#include "data_common.h"
#include "application_password.h"

#if defined(GUI_PASSWORD_SUPPORT) && GUI_PASSWORD_SUPPORT

static unsigned char g_pwd_unlock_temp; // 1: 临时解锁状态..

unsigned int application_password_isLocked(void)
{
    if (g_password.flag && g_password.lock_stat && (g_pwd_unlock_temp == 0)) {
        return 1;
    }
    return 0;
}

unsigned int application_password_verify(unsigned char* pwd)
{
    if ((0 == memcmp(pwd, g_password.password_indx, sizeof(g_password.password_indx)))
        ||(0 == memcmp(pwd, g_password.ultimate_password_indx, sizeof(g_password.ultimate_password_indx))))
    {
        return 1;
    }
    return 0;
}

void application_password_setLock(unsigned int lock)
{
    if (g_password.flag) {
        g_password.lock_stat = lock;
    }
}


void application_password_setOnoff(unsigned int onoff)
{
    g_password.flag = onoff;
    g_password.lock_stat = 0;   // unlocked
    block_save_user_info(&g_password);
}


unsigned int application_password_getOnoff(void)
{
    return g_password.flag;
}


void application_password_setTempLock(unsigned int tempLock)
{
    g_pwd_unlock_temp = tempLock;
}

void application_password_ste(unsigned char* pwd)
{
    SYS_DEBUG("application_password_ste!!!!!!!!");
    memcpy(g_password.password_indx,pwd,sizeof(g_password.password_indx));
}

#endif

