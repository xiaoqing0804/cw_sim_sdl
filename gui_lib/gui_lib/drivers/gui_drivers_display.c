/*
 * file: virtual rendering task
 *
 */
#include "os/os_api.h"
#include "debug.h"
#include "debug_info.h"
#include "bsp_includes.h"
#include "clock_cfg.h"
#include "asm/power_interface.h"

#include "sys_timer_thread.h"

#include "gui_display.h"
#include "gui_display_draw_lib.h"
#include "gui_surface.h"
#include "gui_drivers_display.h"
#include "font_cfont.h"

//#undef SYS_DEBUG
//#define SYS_DEBUG(format, ...)   log_print(2,0,format "\r\n", ## __VA_ARGS__)

//
#define RENDERING_TIME_INTERVAL     30  // 30      // ms interval

volatile unsigned char teRequested;     // 0: don't wait te;            1: must wait te;
volatile unsigned char pendRequested;   // 0: none;                     1: suspend req.
volatile unsigned char dispSuspended;   // 0: display task is runging;  1: task is suspended.
volatile unsigned char dispIsReady;
volatile unsigned char resumRequested;  // 0: none;                     1: resume req.
volatile unsigned char display_pendflg; // 0: none;                     1: dialpay pended.

#if defined(LCD_TE_HOT_SWAP_SUPPORT) && LCD_TE_HOT_SWAP_SUPPORT
static unsigned char te_reset_flg;  //te热插拔标志位
#endif // defined
static void*    g_task_disp = NULL;
static OS_SEM   g_task_runing_semphone;
static OS_SEM   g_task_render_mutex;
static OS_SEM   g_task_te_semphone;
unsigned int    g_dma_ts;
unsigned int    g_start_stamp;
unsigned int    g_te_counter;

#ifdef __CW_JL_VLT_MEM__
extern void gui_driver_flash_memory_init(void);
extern void gui_driver_flash_memory_deinit(void);
extern void gui_display_screen_memory_init(void);
extern void gui_display_screen_memory_deinit(void);
extern void gui_display_render_init(void);
extern void gui_display_render_deinit(void);

static void gui_display_memory_init(void)
{
    gui_display_render_init();
    gui_display_screen_memory_init();
    gui_driver_flash_memory_init();
}
static void gui_display_memory_deinit(void)
{
    gui_display_render_deinit();
    gui_display_screen_memory_deinit();
    gui_driver_flash_memory_deinit();
}
#endif


//
static void gui_display_task_init(void)
{
    teRequested = BOOL_FALSE_FLAG;
    pendRequested = BOOL_FALSE_FLAG;
    resumRequested = BOOL_FALSE_FLAG;
    dispSuspended = BOOL_FALSE_FLAG;
    dispIsReady = BOOL_FALSE_FLAG;
    display_pendflg = BOOL_FALSE_FLAG;

    if (SYS_MODE_NORMAL_TYPE == get_system_mode()) {
        //0: init font
        font_init();
    }

    // gdi:
    gui_initContext();

    // init gui
    gui_display_init();

    // set gdi's default color.
    gui_set_color(COLOR_WHITE);

    // TP
    //TP_Init();

    /* hal: oled init. */
    oled_init();

    /* hal: open lcd backlight. */
    //oled_backlight_set();

    //
    SYS_DEBUG("gui: inited!");
}

static void gui_display_task_suspend(void)
{
    if (SYS_MODE_NORMAL_TYPE == get_system_mode()) {
        /* hal: TP enter deep sleep mode. */
        TP_Sleep();
    }
#if defined(KEY_KTH5763_SUPPORT)
     kth5763_close();  //关闭编码器
#endif // defined

    // hal: turn off backlight & lcd
    oled_backlight_off();
    oled_deinit();

#ifdef __CW_JL_VLT_MEM__
    //SYS_DEBUG("gui: vlt_memory_deinit\n");
    gui_display_memory_deinit();
#endif

    #if TCFG_RDEC_KEY_ENABLE
    rdec_key_sleep();
    #endif

    power_analysis_handler(POWER_TYPE_OLED, 0);
}


static void gui_display_task_resume(void)
{
#ifdef __CW_JL_VLT_MEM__
    gui_display_memory_init();
#endif

#if defined(__CW_JL_G2D_IMB__)||defined(__CW_JL_G2D_IMB_EXT__)  // 唤醒后 g2d 硬件刷屏需要操作一次，已确保flash电源为开启状态..
    gui_drivers_flash_read_image_to_buff(0, 4);
#endif

    power_analysis_handler(POWER_TYPE_OLED, 1);

    SYS_DEBUG("gui: task_resume");
    /* hal: TP wakeup. */
    // 20220901 Taylor.Le, TP唤醒放到亮背光之后，防止亮背光时，导致TP失效!!!!!TP_Wakeup();

    // hal: turn on lcd
    oled_open();

#if defined(KEY_KTH5763_SUPPORT)
    kth5763_open();  //打开编码器
#endif // defined
    // gui: refreash ui
    //osDelay(20);
    g_start_stamp = sys_timer_get_tick();
    lcd_dma_single_block_init();
    application_window_event_handler(EVENT_GUI_RESUMED, NULL);
    gui_surface_force_update();
    gui_display_update();

    // !!!以下延时需要根据不同的lcd做调整, 避免亮屏时，背光先亮的问题!!!
    osDelay(lcd_get_render_delay());
    //

    // hal: turn on backlight
    oled_backlight_on();

    #if TCFG_RDEC_KEY_ENABLE
    rdec_key_wakeup();
    #endif

    if (SYS_MODE_NORMAL_TYPE == get_system_mode()) {
        /* hal: TP wakeup. */
        TP_Wakeup();
    }
}
extern void lcd_Int_wakeup_callback(void);
static void gui_display_task(void* param)
{
    unsigned int time_stamp2, time_dur;
    unsigned int time_sleep;
    unsigned int time_cycle;

    SYS_DEBUG("gui: display_task()!");

#ifdef __CW_JL_VLT_MEM__
    gui_display_memory_init();
#endif

    #if TCFG_RDEC_KEY_ENABLE
    rdec_key_wakeup();
    #endif

    power_analysis_handler(POWER_TYPE_OLED, 1);

    gui_display_give_mutex();

    dispIsReady = BOOL_TRUE_FLAG;
    time_cycle = sys_timer_ms_to_tick(GUI_DISPLAY_RENDERING_TIME_INTERVAL);

    // render first frame.
    //while(!gui_surface_is_update());

    lcd_debug_pinstate(0);
    lcd_debug_pinstate2(0);
    lcd_dma_single_block_init();
    gui_display_update();
#if !defined(LCD_TE_SYNC_BY_SOFT)||!LCD_TE_SYNC_BY_SOFT
	power_wakeup_index_enable(9, 1);
#endif

    osDelay(lcd_get_render_delay());

    /* hal: open lcd backlight. */
    oled_backlight_set();

    g_start_stamp = sys_timer_get_tick();

    while(1) {
        #if !defined(LCD_TE_SYNC_BY_SOFT)||!LCD_TE_SYNC_BY_SOFT
        os_sem_set(&g_task_te_semphone,0);		// rzy
		os_sem_pend(&g_task_te_semphone, 2);

		g_te_counter = 0;
        #endif

        teRequested = BOOL_TRUE_FLAG;                 //
        lcd_dma_single_block_init();
        //putchar('[');
        gui_display_update();
        //putchar(']');

        if (display_pendflg == BOOL_TRUE_FLAG) {        // 通知gui，重新刷屏.
            display_pendflg = BOOL_FALSE_FLAG;
            //application_send_event(EVENT_GUI_RENDER_REQ, NULL);
        }

        if (pendRequested == BOOL_TRUE_FLAG) {
            SYS_DEBUG("gui0: Suspend requested!");
            //lcd_wait_lcd_control_transfer(0);
            dispSuspended = BOOL_TRUE_FLAG;

            // suspend
            gui_display_task_suspend();
            SYS_DEBUG("gui0: Suspend requested  ------- ... zzz ZZZ --------");
            #if !defined(LCD_TE_SYNC_BY_SOFT)||!LCD_TE_SYNC_BY_SOFT
			power_wakeup_index_enable(9, 0);
            #endif
            pendRequested = BOOL_FALSE_FLAG;
            os_sem_pend(&g_task_runing_semphone, OS_MAX_DELAY);



            // resume
            resumRequested = BOOL_TRUE_FLAG;
            SYS_DEBUG("gui0: Resume requested!");
            gui_display_task_resume();
            SYS_DEBUG("gui0: Resume requested ------- --- ooo OOO --------");

            #if !defined(LCD_TE_SYNC_BY_SOFT)||!LCD_TE_SYNC_BY_SOFT
			power_wakeup_index_enable(9, 1);
            #endif
            dispSuspended = BOOL_FALSE_FLAG;
            resumRequested = BOOL_FALSE_FLAG;
        }

#if defined(LCD_TE_HOT_SWAP_SUPPORT) && LCD_TE_HOT_SWAP_SUPPORT
        if(te_reset_flg<150)
            te_reset_flg++;
        if((te_reset_flg>30)&&(oled_get_must_reinit_flag()))
        {
//            cpu_reset();
            TP_Init();
            lcd_drv_reinit();  // lcd init
        }
#endif
    }
}


void gui_display_task_create(void)
{
    SYS_DEBUG("gui_display_task_create()");

    if (SYS_MODE_NORMAL_TYPE == get_system_mode()) {
        // TP
        TP_Init();
    }

    os_sem_create(&g_task_runing_semphone, 0);
	os_sem_create(&g_task_te_semphone, 0);
    os_sem_create(&g_task_render_mutex, 0);
#if GUI_RENDER_BUFFER_TOTAL_SUPPORT >= 3
    gui_display_render_init_data();
#endif
    gui_display_task_init();    // 因为ctp用的是软件IIC，要先初始化，否则探测不到ctp模块!!!

    //os_task_create(gui_display_task, NULL, 2, 1024, 512, "disp");
    task_create(gui_display_task, NULL, "disp");
    g_task_disp = os_task_get_handle("disp");

}

//
int gui_display_suspend(unsigned char bypass)
{
    void* currTask = NULL;

    SYS_DEBUG("gui: suspend! dispSuspended=%d", dispSuspended);
    if (g_task_disp == NULL) {
        SYS_DEBUG("gui: Suspend requested!");
        gui_display_task_suspend();
        dispSuspended = BOOL_TRUE_FLAG;       // set suspend request flag.
        SYS_DEBUG("gui: suspend success!");
        return 0;
    }

    currTask = sys_timer_get_current();
    if (currTask == g_task_disp) {
        SYS_DEBUG("gui: suspend error1!");
        return -1;
    }

    if ((g_task_disp != NULL) && (dispSuspended == BOOL_FALSE_FLAG)) {
        pendRequested = BOOL_TRUE_FLAG;       // set suspend request flag.
        while(!bypass && (pendRequested == BOOL_TRUE_FLAG)) {
            osDelay(1);
        }
        SYS_DEBUG("gui: suspend success!");
        return 0;
    }
    return -1;
}

int gui_display_resume(void)
{
    void *currTask = NULL;

    SYS_DEBUG("gui: resume! dispSuspended=%d", dispSuspended);

    currTask = sys_timer_get_current();
    if (currTask == g_task_disp) {
        SYS_DEBUG("gui: resume error1!");
        return -1;
    }

    if ((g_task_disp != NULL) && (dispSuspended == BOOL_TRUE_FLAG)) {
        os_sem_post(&g_task_runing_semphone);
        while(dispSuspended == BOOL_TRUE_FLAG) {
            osDelay(1);
        }
        SYS_DEBUG("gui: resume success!");
        return 0;
    }
    else {
        SYS_DEBUG("gui: resume error2!");
    }
    return -1;
}

bool gui_display_isSuspended(void)
{
    return ((dispSuspended == BOOL_TRUE_FLAG) && (resumRequested == BOOL_FALSE_FLAG));
}

bool gui_display_isReady(void)
{
    return (dispIsReady == BOOL_TRUE_FLAG);
}

bool gui_display_isRenderPended(void)
{
    return (display_pendflg == BOOL_TRUE_FLAG);
}


// 获取刷屏信号量 ....
// 参数： wait - 是否要等待
// 返回： 0 - 失败； 1 - 成功...
unsigned int gui_display_take_mutex(unsigned int wait)
{
    int timeout = ((wait==1) ? OS_MAX_DELAY : 3);
    int ret = 1;

    ret = os_sem_pend(&g_task_render_mutex, timeout);
    //SYS_DEBUG("gui: display_take_mutex(%d), os_sem_pend, ret=%d", wait, ret);
    if (wait == 0) {
        lcd_swap_pinstate();
        if ((ret==OS_TRUE) || (ret==OS_NO_ERR)) {
            // os_sem_pend, ok
            display_pendflg = BOOL_FALSE_FLAG;
            return 1;
        }
        // OS_TIMEOUT
        display_pendflg = BOOL_TRUE_FLAG;
        return 0;
    }
    return 1;
}

void gui_display_give_mutex(void)
{
    os_sem_post(&g_task_render_mutex);
}

void gui_display_idle_set(unsigned char onoff)
{
    if (gui_display_isSuspended())  return;

    gui_display_take_mutex(1);

    if (onoff) {
        oled_idle_set();
    }
    else {
        oled_idle_reset();
    }

    gui_display_give_mutex();
}


void gui_display_te_single(void)
{
#if !defined(LCD_TE_SYNC_BY_SOFT)||!LCD_TE_SYNC_BY_SOFT
	os_sem_post(&g_task_te_semphone);
    g_te_counter ++;
    #if defined(LCD_TE_HOT_SWAP_SUPPORT) && LCD_TE_HOT_SWAP_SUPPORT
        te_reset_flg = 0;
    #endif
#endif
}




#ifdef __CW_JL_VLT_MEM__
// 因为使用了 vlt 区域的ram，所以在系统将要进入lp模式时，增加保护!!!!
static u8 gui_display_lp_query(void)
{
    return (dispSuspended == BOOL_TRUE_FLAG);
}

REGISTER_LP_TARGET(gui_lp_target) = {
    .name = "gui",
    .is_idle = gui_display_lp_query,
};
#endif


