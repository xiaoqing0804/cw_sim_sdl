
#include "app_window_call.h"

/// @brief 调节音量判断
/// @param int buf
/// @param int call_volum
int app_adjust_call_volume(int buf, int call_volum)
{
    if (buf == 2)
    {
        call_volum++;
        if (call_volum >= 15)
        {
            call_volum = 15;
        }
    }
    else if (buf == 3)
    {
        call_volum--;
        if (call_volum <= 1)
        {
            call_volum = 1;
        }
    }
    return call_volum;
}
