#include "os_mem.h"
#include "debug_info.h"
#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_transfer.h"

#include "system_util_math_geometry.h"
#include "gui_window.h"
#include "gui_surface_cache.h"
#include "gui_surface_node.h"
#include "gui_surface_box_canvas.h"

#include "app_window_tptest.h"


#define TPTEST_GRID_CELL_COLOR  COLOR_RGB(255, 255, 255)

#define RECT_HSIZE          (LCD_SIZE_HEIGHT/4)
#define RECT_YPOS(line)     (line * RECT_HSIZE)

#define CANVAS_RECT(x, y, w, h) {       \
    .type = TYPE_GUI_DRAW_SHAPE_RECT,   \
    .penSize = 1,                       \
    .penColor = TPTEST_GRID_CELL_COLOR, \
    .canvas.rect.x0 = x,                \
    .canvas.rect.y0 = y,                \
    .canvas.rect.x1 = x+w-1,            \
    .canvas.rect.y1 = y+h-1,            \
}



#if (LCD_SIZE_WIDTH==454)|| (LCD_SIZE_WIDTH==466)
static const geometry_rect mTouchRect[] =
{
    #if (LCD_SHAPE == LCD_CIRCLE)
    	{0, 0,   182, 91}, {182, 0,   91, 91}, {273, 0,   182, 91},
    	{0, 91,  91,  91}, {91,  91,  91, 91}, {182, 91,  91,  91}, {273, 91,  91, 91}, {364, 91,  91, 91},
    	{0, 182, 91,  91}, {91,  182, 91, 91}, {182, 182, 91,  91}, {273, 182, 91, 91}, {364, 182, 91, 91},
    	{0, 273, 91,  91}, {91,  273, 91, 91}, {182, 273, 91,  91}, {273, 273, 91, 91}, {364, 273, 91, 91},
    	{0, 364, 182, 91}, {182, 364, 91, 91}, {273, 364, 182, 91},
    #else
		{0,   0, 91,  91}, {91,  0,   91, 91}, {182, 0,   91,  91}, {273,   0, 91, 91}, {364,   0, 91, 91},
		{0,  91, 91,  91}, {91,  91,  91, 91}, {182, 91,  91,  91}, {273,  91, 91, 91}, {364,  91, 91, 91},
		{0, 182, 91,  91}, {91,  182, 91, 91}, {182, 182, 91,  91}, {273, 182, 91, 91}, {364, 182, 91, 91},
		{0, 273, 91,  91}, {91,  273, 91, 91}, {182, 273, 91,  91}, {273, 273, 91, 91}, {364, 273, 91, 91},
		{0, 364, 91,  91}, {91,  364, 91, 91}, {182, 364, 91,  91}, {273, 364, 91, 91}, {364, 364, 91, 91},
    #endif
};

#elif (LCD_SIZE_WIDTH==360)

static const geometry_rect mTouchRect[] =
{
    #if (LCD_SHAPE == LCD_CIRCLE)
    	{0, 0,   135, 90}, {135, 0,   90, 90}, {225, 0,   135, 90},
    	{0, 90,  90,  90}, {90,  90,  90, 90}, {180, 90,  90,  90}, {270, 90,  90, 90},
    	{0, 180, 90,  90}, {90,  180, 90, 90}, {180, 180, 90,  90}, {270, 180, 90, 90},
    	{0, 270, 135, 90}, {135, 270, 90, 90}, {225, 270, 135, 90},
    #else
		{0,   0,  90,  90}, {90,   0, 90, 90}, {180,   0, 90,  90}, {270,  0,  90, 90},
		{0,  90,  90,  90}, {90,  90, 90, 90}, {180,  90, 90,  90}, {270, 90,  90, 90},
		{0, 180,  90,  90}, {90, 180, 90, 90}, {180, 180, 90,  90}, {270, 180, 90, 90},
		{0, 270,  90,  90}, {90, 270, 90, 90}, {180, 270, 90,  90}, {270, 270, 90, 90},
    #endif
};

#elif (LCD_SIZE_WIDTH==320)

static const geometry_rect mTouchRect[] =
{
    #if (LCD_SHAPE == LCD_CIRCLE)
    	{0, RECT_YPOS(0), 120, RECT_HSIZE}, {120, RECT_YPOS(0), 80, RECT_HSIZE}, {200, RECT_YPOS(0), 120, RECT_HSIZE},
    	{0, RECT_YPOS(1), 80,  RECT_HSIZE}, {80,  RECT_YPOS(1), 80, RECT_HSIZE}, {160, RECT_YPOS(1), 80,  RECT_HSIZE}, {240, RECT_YPOS(1), 80, RECT_HSIZE},
    	{0, RECT_YPOS(2), 80,  RECT_HSIZE}, {80,  RECT_YPOS(2), 80, RECT_HSIZE}, {160, RECT_YPOS(2), 80,  RECT_HSIZE}, {240, RECT_YPOS(2), 80, RECT_HSIZE},
    	{0, RECT_YPOS(3), 120, RECT_HSIZE}, {120, RECT_YPOS(3), 80, RECT_HSIZE}, {200, RECT_YPOS(3), 120, RECT_HSIZE},
    #elif (LCD_SIZE_HEIGHT == 386)
        {0, RECT_YPOS(0),  80,  RECT_HSIZE}, {80, RECT_YPOS(0), 80, RECT_HSIZE}, {160, RECT_YPOS(0), 80,  RECT_HSIZE}, {240, RECT_YPOS(0), 80, RECT_HSIZE},
        {0, RECT_YPOS(1),  80,  RECT_HSIZE}, {80, RECT_YPOS(1), 80, RECT_HSIZE}, {160, RECT_YPOS(1), 80,  RECT_HSIZE}, {240, RECT_YPOS(1), 80, RECT_HSIZE},
        {0, RECT_YPOS(2),  80,  RECT_HSIZE}, {80, RECT_YPOS(2), 80, RECT_HSIZE}, {160, RECT_YPOS(2), 80,  RECT_HSIZE}, {240, RECT_YPOS(2), 80, RECT_HSIZE},
        {0, RECT_YPOS(3),  80,  RECT_HSIZE+2}, {80, RECT_YPOS(3), 80, RECT_HSIZE+2}, {160, RECT_YPOS(3), 80,  RECT_HSIZE+2}, {240, RECT_YPOS(3), 80, RECT_HSIZE+2},
    #else
		{0, RECT_YPOS(0),  80,  RECT_HSIZE}, {80, RECT_YPOS(0), 80, RECT_HSIZE}, {160, RECT_YPOS(0), 80,  RECT_HSIZE}, {240, RECT_YPOS(0), 80, RECT_HSIZE},
		{0, RECT_YPOS(1),  80,  RECT_HSIZE}, {80, RECT_YPOS(1), 80, RECT_HSIZE}, {160, RECT_YPOS(1), 80,  RECT_HSIZE}, {240, RECT_YPOS(1), 80, RECT_HSIZE},
		{0, RECT_YPOS(2),  80,  RECT_HSIZE}, {80, RECT_YPOS(2), 80, RECT_HSIZE}, {160, RECT_YPOS(2), 80,  RECT_HSIZE}, {240, RECT_YPOS(2), 80, RECT_HSIZE},
		{0, RECT_YPOS(3),  80,  RECT_HSIZE}, {80, RECT_YPOS(3), 80, RECT_HSIZE}, {160, RECT_YPOS(3), 80,  RECT_HSIZE}, {240, RECT_YPOS(3), 80, RECT_HSIZE},
    #endif
};

#elif (LCD_SIZE_WIDTH==240)

static const geometry_rect mTouchRect[] =
{
    #if (LCD_SHAPE==LCD_CIRCLE) // 240x240
    	{0, RECT_YPOS(0), 90, RECT_HSIZE}, {90, RECT_YPOS(0), 60, RECT_HSIZE}, {150, RECT_YPOS(0), 90, RECT_HSIZE},
    	{0, RECT_YPOS(1), 60, RECT_HSIZE}, {60, RECT_YPOS(1), 60, RECT_HSIZE}, {120, RECT_YPOS(1), 60, RECT_HSIZE}, {180, RECT_YPOS(1), 60, RECT_HSIZE},
    	{0, RECT_YPOS(2), 60, RECT_HSIZE}, {60, RECT_YPOS(2), 60, RECT_HSIZE}, {120, RECT_YPOS(2), 60, RECT_HSIZE}, {180, RECT_YPOS(2), 60, RECT_HSIZE},
    	{0, RECT_YPOS(3), 90, RECT_HSIZE}, {90, RECT_YPOS(3), 60, RECT_HSIZE}, {150, RECT_YPOS(3), 90, RECT_HSIZE},
    #elif (LCD_SIZE_WIDTH == 286)
        {0, RECT_YPOS(0), 60, RECT_HSIZE},  {60, RECT_YPOS(0), 60, RECT_HSIZE},  {120, RECT_YPOS(0), 60, RECT_HSIZE},   {180, RECT_YPOS(0), 60, RECT_HSIZE},
        {0, RECT_YPOS(1), 60, RECT_HSIZE},  {60, RECT_YPOS(1), 60, RECT_HSIZE},  {120, RECT_YPOS(1), 60, RECT_HSIZE},   {180, RECT_YPOS(1), 60, RECT_HSIZE},
        {0, RECT_YPOS(2), 60, RECT_HSIZE},  {60, RECT_YPOS(2), 60, RECT_HSIZE},  {120, RECT_YPOS(2), 60, RECT_HSIZE},   {180, RECT_YPOS(2), 60, RECT_HSIZE},
        {0, RECT_YPOS(3), 60, RECT_HSIZE+2},{60, RECT_YPOS(3), 60, RECT_HSIZE+2},{120, RECT_YPOS(3), 60, RECT_HSIZE+2}, {180, RECT_YPOS(3), 60, RECT_HSIZE+2},
    #else
    	{0, RECT_YPOS(0), 60, RECT_HSIZE},  {60, RECT_YPOS(0), 60, RECT_HSIZE}, {120, RECT_YPOS(0), 60, RECT_HSIZE}, {180, RECT_YPOS(0), 60, RECT_HSIZE},
    	{0, RECT_YPOS(1), 60, RECT_HSIZE},  {60, RECT_YPOS(1), 60, RECT_HSIZE}, {120, RECT_YPOS(1), 60, RECT_HSIZE}, {180, RECT_YPOS(1), 60, RECT_HSIZE},
    	{0, RECT_YPOS(2), 60, RECT_HSIZE},  {60, RECT_YPOS(2), 60, RECT_HSIZE}, {120, RECT_YPOS(2), 60, RECT_HSIZE}, {180, RECT_YPOS(2), 60, RECT_HSIZE},
    	{0, RECT_YPOS(3), 60, RECT_HSIZE},  {60, RECT_YPOS(3), 60, RECT_HSIZE}, {120, RECT_YPOS(3), 60, RECT_HSIZE}, {180, RECT_YPOS(3), 60, RECT_HSIZE},
    #endif
};


#else   // 240 X 240

// ...

#endif


static const gui_widget_struct gui_widget_tptest[] =
{
    {
        .id = 3,
        .type = TYPE_GUI_CONTROL_CANVAS,
        .x = 0,
        .y = 0,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = 0,
        .children = NULL,
    },
};

const gui_screen_struct gui_screen_tptest =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.space_x = 0,
	.space_y = 0,
	.order = 0,
	.children = gui_widget_tptest,
	.child_num = countof(gui_widget_tptest),
};


#define TPTEST_CELL_NUM     (sizeof(mTouchRect)/sizeof(geometry_rect))


static gui_canvas_struct* g_canvas_info = NULL;
//static gui_canvas_struct g_canvas_info[TPTEST_CELL_NUM];

static unsigned int  g_tptest_cell_flag;

#if defined(__EXT_BT_AUDIO__)
#define TPTEST_AUD_IDLE     0
#define TPTEST_AUD_MUSIC    1
#define TPTEST_AUD_MIC      2
static unsigned int  g_tptest_aud_flag;     // 0: idle; 1: music play test;  2: mic-spk loop test;
#endif


/*-----------------------------系统事件--------------------------------------*/

static void app_window_tptest_init(void *buf)
{
	unsigned int index;

    //SYS_DEBUG("app_window_tptest_init(iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii)");
#if defined(__EXT_BT_AUDIO__)
    g_tptest_aud_flag  = TPTEST_AUD_IDLE;
#endif
    g_tptest_cell_flag = 0;
	if (g_canvas_info == NULL) {
        g_canvas_info = os_mem_alloc(RAM_TYPE_DATA_ON,TPTEST_CELL_NUM*sizeof(gui_canvas_struct));
    }
    if (g_canvas_info != NULL) {
        memset(g_canvas_info, 0, TPTEST_CELL_NUM*sizeof(gui_canvas_struct));
        for (index=0; index<TPTEST_CELL_NUM; index++) {
            g_canvas_info[index].type = TYPE_GUI_DRAW_SHAPE_RECT;
            g_canvas_info[index].penColor = TPTEST_GRID_CELL_COLOR;
            g_canvas_info[index].penSize = 1;
            g_canvas_info[index].canvas.rect.x0 = mTouchRect[index].x;
            g_canvas_info[index].canvas.rect.x1 = mTouchRect[index].x+mTouchRect[index].width-1;
            g_canvas_info[index].canvas.rect.y0 = mTouchRect[index].y;
            g_canvas_info[index].canvas.rect.y1 = mTouchRect[index].y+mTouchRect[index].height-1;
        }
    }
}

static void app_window_tptest_load(void *buf)
{
    gui_box_struct* box;
    gui_node_struct* node;
	unsigned int index;

    //SYS_DEBUG("app_window_tptest_load(lllllllllllllllllllll)");

    box = gui_surface_get_box(&gui_screen_tptest, 3);
    if ((box == NULL) || (g_canvas_info == NULL)) {
        SYS_DEBUG("app_window_tptest_load(error)");
        return;
    }

    for (index=0; index<TPTEST_CELL_NUM; index++) {
        node = gui_surface_cache_add_node();
        if (node != NULL) {
            node->id = index+1;
            node->type = g_canvas_info[index].type;
            node->data = &g_canvas_info[index];
            gui_surface_box_canvas_init(node);
            gui_surface_box_add_node(box, node);
        }
    }
}


static void app_window_tptest_entry(void *buf)
{
#if defined(__EXT_BT_AUDIO__)
    g_tptest_aud_flag = TPTEST_AUD_MUSIC;

    ext_btaud_test_speaker_music(1);

    application_open_act_timer(APPLICATION_TIMER_ACT, 5000);
#endif
}


static void app_window_tptest_exit()
{
#if defined(__EXT_BT_AUDIO__)
    application_close_act_timer(APPLICATION_TIMER_ACT);

    if (g_tptest_aud_flag == TPTEST_AUD_MUSIC) {
        ext_btaud_test_speaker_music(0);
    }
    else if (g_tptest_aud_flag == TPTEST_AUD_MIC) {
        ext_btaud_test_speaker_mic(0);
    }
    g_tptest_aud_flag = TPTEST_AUD_IDLE;
#endif
}

#if defined(__EXT_BT_AUDIO__)
static void app_window_tptest_act_timer_handler(void* buf)
{
    if (g_tptest_aud_flag == TPTEST_AUD_MUSIC) {
        ext_btaud_test_speaker_music(0);
        g_tptest_aud_flag = TPTEST_AUD_MIC;
        ext_btaud_test_speaker_mic(1);
    }
    else {
        ext_btaud_test_speaker_mic(0);
        g_tptest_aud_flag = TPTEST_AUD_IDLE;
        application_close_act_timer(APPLICATION_TIMER_ACT);
    }
}
#endif

static void app_window_tptest_destroy()
{
    //SYS_DEBUG("app_window_tptest_destroy(ddddddddddddddddddddddddddddddddd)");
	if (g_canvas_info != NULL) {
        os_mem_free(g_canvas_info);
        g_canvas_info = NULL;
    }
}

/*-----------------------------响应事件--------------------------------------*/
static void app_window_tptest_click(gui_click_struct *event)
{
    gui_box_struct* box;
    gui_node_struct* node;
    unsigned int index;

    //SYS_DEBUG("app_window_tptest_click(%d, %d)", event->x, event->y);

    box = gui_surface_get_box(&gui_screen_tptest, 3);
    if ((box == NULL) || (g_canvas_info == NULL)) return;

    for (index=0; index<TPTEST_CELL_NUM; index++) {
        if (1==check_rect_contain_point_xy((geometry_rect*)&mTouchRect[index], event->x, event->y)) {
            //SYS_DEBUG("app_window_tptest_click(index=%d)", index);

            g_tptest_cell_flag |= (1 << index);
            if(g_tptest_cell_flag == ((1 << TPTEST_CELL_NUM) - 1)) {
                application_go_back();
            }
            else {
                g_canvas_info[index].type = TYPE_GUI_DRAW_SHAPE_RECT_FILL;

                node = gui_surface_box_find_node(box, index+1);
                if (node != NULL) {
                    node->type = TYPE_GUI_DRAW_SHAPE_RECT_FILL;
                    gui_surface_commit();
                }
            }
            break;
        }
    }
}



/*-----------------------------配置--------------------------------------*/

static const gui_touch_event_struct app_window_tptest_touch_events[] =
{
    {
        .id = 3,
        .click = app_window_tptest_click,
    },
};

static const app_window_event_struct app_window_tptest_evnets[] =
{
    {
        .id = EVENT_BL_TIMEOUT,
    },
    {
        .id = EVENT_BACKLIGHT_OFF,
    },
#if defined(__EXT_BT_AUDIO__)
    {
        .id = EVENT_ACT,
        .handler = app_window_tptest_act_timer_handler,
    },
#endif
};

static const gui_window_config_struct app_window_tptest_config =
{
	.forbid_gesture_back = 1,
    .entry_back_to_destory = 1,
};

const gui_window_struct app_window_tptest =
{
	.screen = &gui_screen_tptest,
    .config = &app_window_tptest_config,
	.init = app_window_tptest_init,
	.load = app_window_tptest_load,
	.entry = app_window_tptest_entry,
	.exit = app_window_tptest_exit,
	.destroy = app_window_tptest_destroy,

	.touch_event_num = countof(app_window_tptest_touch_events),
	.touch_events = app_window_tptest_touch_events,
	.event_num = countof(app_window_tptest_evnets),
	.events = app_window_tptest_evnets,
};

