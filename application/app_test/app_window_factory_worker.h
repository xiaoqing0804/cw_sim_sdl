#ifndef __APP_WINDOW_FACTORY_WORKER_H__
#define __APP_WINDOW_FACTORY_WORKER_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

typedef enum {
    FACT_CHECK_TYPE_NONE,
    FACT_CHECK_TYPE_KEY,
    FACT_CHECK_TYPE_TP,
    FACT_CHECK_TYPE_GSENSOR,
    FACT_CHECK_TYPE_HR,
    FACT_CHECK_TYPE_ONOFF,
    FACT_CHECK_TYPE_TIMER,
    FACT_CHECK_TYPE_PASS,
    FACT_CHECK_TYPE_EXIT,
}fact_check_type;

typedef struct _factory_test_item
{
    char* name;
    int (*start)(void);
    int (*check)(fact_check_type type, int param, void* param_p);
}factory_test_item_struct;

extern unsigned short factory_test_get_count(void);
extern factory_test_item_struct* factory_test_get_item(int index);
extern unsigned int factory_test_get_pass_flags(void);



extern const gui_window_struct app_window_factory_worker;


#endif

