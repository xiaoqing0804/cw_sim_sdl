#ifndef _DATA_MANAGER_FLASH_H
#define _DATA_MANAGER_FLASH_H

#if defined(__CW_JL_M25SP_CF19__)   //����Ŀ�ѳ���������ͬ�ռ䲻��
#include "data_manager_flash_CF19.h"

#elif defined(__CW_JL_FLASH_8M__)
#include "data_manager_flash_8M.h"

#else
#include "data_manager_flash_16M.h"
#endif

#endif //_DATA_MANAGER_FLASH_H

