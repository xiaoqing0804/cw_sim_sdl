#ifndef __FEATURE_ALL_H__
#define __FEATURE_ALL_H__

// #include <stdio.h>
#include <string.h>

#include "feature.h"
#include "feature_define.h"
#include "feature_color.h"
#include "feature_debug.h"
#include "feature_define.h"
#include "feature_flash.h"
#include "feature_math.h"
#include "feature_verno.h"
#include "feature_gui.h"
#include "feature_gui_ids.h"

#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "system_util_all.h"

#ifdef __CW_JL__
#include "system/generic/typedef.h" // JL
#define DATA_RAM_FUNCTION           // SEC(.volatile_ram_code)
#define SHARE_CACHE_RAM_FUNCTION    // SEC(.volatile_ram_code)
#define SHARE_CACHE_RAM_SECTION     // SEC(.volatile_ram_code)

#define PSRAM_CODE_SECTION SEC(.psram_code)
#define PSRAM_DATA_SECTION SEC(.psram_data)
#define PSRAM_BSS_SECTION SEC(.psram_bss)
#define PSRAM_NOINIT_SECTION SEC(.psram_noinit)

#else // RTL
//#include "app_section.h"
#endif

#endif
