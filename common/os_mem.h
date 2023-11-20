#ifndef __OS_MEM_H__
#define __OS_MEM_H__

#include "system/generic/typedef.h"
#include "app_config.h"

#define RAM_TYPE_DATA_ON        0
#define RAM_TYPE_BUFFER_ON      1       // vlt memory for JL;  buffer ram for RTL.
#define RAM_TYPE_PSRAM_ON       2

void* os_mem_alloc(unsigned int ram_type, unsigned int size);
void* os_mem_zalloc(unsigned int ram_type, unsigned int size);
void  os_mem_free(void *p_block);


#endif

