#include "gui_touch_layout_rebound.h"
#include "gui_window_history.h"
#include "app_task_main.h"
#include "gui_surface.h"
#include "gui_surface_layout.h"
#include "middleware_rtc.h"
#include "system_util_math.h"

//
//#define AUTO_MOVE_METHOD_EQUAL_RATIO    1   // �ȱ�˥�������������ϴ�        Equal ratio attenuation
//#define AUTO_MOVE_METHOD_ISOCHRONOUS    0   // �Ȳ�˥����        Isochronous attenuation


// Equal ratio attenuation
#define AUTO_MOVE_DEC_NUM       4.0f        // 4��˥��,   ��������г�ʱ��˥���������ɸ��ݻ���ƽ�������ʵ����� (>= 4.0f)...
#define AUTO_MOVE_SPEED_DFT_A   0.95f       // ȱʡ�ٶ�˥�� (˥������0.95)....
#define AUTO_MOVE_SPED_TO_STOP  3.1f        // ֹͣ���������ٶ�˥���� ������Χ��ʱֹͣ ...
#define AUTO_MOVE_SPED_TO_STOP1 4.0f        // ��������г̶��˥��ʱ��ֹͣ�ٶ�, ( < AUTO_MOVE_SPED_TO_STOP) ...

static DIRECTION_TYPE g_layout_rebound_direction = DIRECTION_TYPE_NONE;
static const gui_window_struct* g_layout_rebound_window = NULL;

static unsigned int g_touch_auto_move_timer_id;

static float g_layout_auto_move_speed = 0.0f;
static float g_layout_auto_speed_a    = AUTO_MOVE_SPEED_DFT_A;

/// �����г̾��룬�����ٶ�˥��ϵ��..
static float gui_touch_layout_get_dlta4(float dlt)
{
    float tmp;
    float a = 0.9f;

    do{
        tmp = (1.0f - 1.0f/pow(a, AUTO_MOVE_DEC_NUM)) / (a - 1.0f);
        if (tmp >= dlt) {
            break;
        }
        a -= 0.05f;
    }while(1);

    return a;
}


static int gui_touch_layout_handle_freemove(gui_layout_header_struct* layout, short offset)
{
    short   temp = offset;

    offset += (short)g_layout_auto_move_speed;
    GUI_DEBUG("offsetg_layou=%d",offset);

    if (offset < layout->min_offset && layout->loop_flag == 0) {
        // ���ϻ�λ ...
        g_layout_auto_move_speed = (layout->min_offset - offset) / 2.0f;
    }
    else if (offset > layout->max_offset && layout->loop_flag == 0) {
        // ���»�λ....
        g_layout_auto_move_speed = -1 * (offset - layout->max_offset) / 2.0f;
    }
    else {
        // �ٶ�˥�� (˥������0.95)....
        g_layout_auto_move_speed = g_layout_auto_move_speed * g_layout_auto_speed_a;    //  * 95 / 100;
    }

    //if ((g_layout_auto_move_speed <= AUTO_MOVE_SPED_TO_STOP) && (g_layout_auto_move_speed >= -AUTO_MOVE_SPED_TO_STOP)) {
    if ((g_layout_auto_move_speed < layout->item_gap/4.0f) && (g_layout_auto_move_speed >= -layout->item_gap/4.0f)) {
        // �ٶ�˥������Сʱ��ֹͣ����, ���ҽ�listֹͣ�ڵ�ǰitem ....
        g_layout_auto_move_speed = 0.0f;
        if (layout->item_gap == 0) {
        }
        else if (offset < 0) {
            offset = ((offset - layout->item_gap/2) / layout->item_gap) * layout->item_gap;
        }
        else {
            offset = ((offset + layout->item_gap/2) / layout->item_gap) * layout->item_gap;
        }

        // �ж����½��� ...
        if (offset > layout->max_offset  && layout->loop_flag == 0) {
            offset = layout->max_offset;
        }
        if (offset < layout->min_offset && layout->loop_flag == 0) {
            offset = layout->min_offset;
        }

        // stop
        if (g_touch_auto_move_timer_id != 0) {
            application_stop_user_timer(g_touch_auto_move_timer_id);
            g_touch_auto_move_timer_id = 0;
        }
        GUI_DEBUG("gui: touch_layout_handle_freemove, end%d",offset);
    }

    return (offset - temp);
}

static void gui_touch_layout_start_freemove(gui_layout_header_struct* layout, short end_offset, short offset)
{
    short   y_end;

    //SYS_DEBUG("gui: layout_start_freemove(speed: %f, end: %d, offset: %d) min=%d, max=%d", g_layout_auto_move_speed, end_offset, offset, layout->min_offset, layout->max_offset);

    if (g_layout_auto_move_speed == 0) {
        if (end_offset != 0) {
            g_layout_auto_move_speed = (float)ABS(end_offset);
        }
        else if (offset < layout->min_offset && layout->loop_flag == 0) {
            // ���ϻ�λ ...
        }
        else if (offset > layout->max_offset && layout->loop_flag == 0) {
            // ���»�λ....
            g_layout_auto_move_speed = -g_layout_auto_move_speed;
        }
        else {
            // �ҵ���ǰitem��λ��...
            if (layout->item_gap == 0) {
            }
            else if (offset < 0) {
                y_end = ((offset - layout->item_gap/2) / layout->item_gap) * layout->item_gap;
            }
            else {
                y_end = ((offset + layout->item_gap/2) / layout->item_gap) * layout->item_gap;
            }

            // �����ƶ�����ǰitem���ƶ�����...
            g_layout_auto_move_speed = (float)(y_end - offset);
        }

        // ���ݾ�����ٶ�˥�����Ӽ����ٶ�(4��˥��)....
        g_layout_auto_move_speed /= AUTO_MOVE_SPED_TO_STOP1;
        g_layout_auto_speed_a    = gui_touch_layout_get_dlta4(g_layout_auto_move_speed);
        g_layout_auto_move_speed = AUTO_MOVE_SPED_TO_STOP1/pow(g_layout_auto_speed_a, AUTO_MOVE_DEC_NUM) * ((end_offset >= 0) ? 1.0f : -1.0f);
        SYS_DEBUG("gui: layout_start_freemove, speed=%f, a=%f", g_layout_auto_move_speed, g_layout_auto_speed_a);
    }
    else {
        g_layout_auto_speed_a    = AUTO_MOVE_SPEED_DFT_A;
    }
}



static void gui_touch_layout_rebound_loop_moving(unsigned int timer_id, void *argument)
{
    if (g_touch_auto_move_timer_id == 0 || g_touch_auto_move_timer_id != timer_id) {
        return;
    }

	gui_surface_struct* surface = gui_surface_get_surface(g_layout_rebound_window->screen);
    gui_layout_header_struct* layout = &surface->layout.header;
    short offset, move_dlt;


	//SYS_DEBUG("gui: touch_layout_rebound_loop_moving, speed=%f, a=%f", g_layout_auto_move_speed, g_layout_auto_speed_a);

    if ((g_layout_rebound_direction == DIRECTION_TYPE_LEFT) || (g_layout_rebound_direction == DIRECTION_TYPE_RIGHT)) {
        offset = layout->offset_x;
    }
    else if ((g_layout_rebound_direction == DIRECTION_TYPE_UP) || (g_layout_rebound_direction == DIRECTION_TYPE_DOWN)) {
        offset = layout->offset_y;
    }
    else {
        return;
    }
    GUI_DEBUG("gui_touch_layout_rebound_loop_moving, offset=%d",offset);
    move_dlt = gui_touch_layout_handle_freemove(layout, offset);

    if ((g_layout_rebound_direction == DIRECTION_TYPE_LEFT) || (g_layout_rebound_direction == DIRECTION_TYPE_RIGHT)) {
        SYS_DEBUG("gui_surface_layout_move=");
        gui_surface_layout_move(surface, move_dlt, 0);
    }
    else if ((g_layout_rebound_direction == DIRECTION_TYPE_UP) || (g_layout_rebound_direction == DIRECTION_TYPE_DOWN)) {

        gui_surface_layout_move(surface, 0, move_dlt);
    }

    if (g_touch_auto_move_timer_id == 0) {
        gui_surface_layout_move_end(surface);
    }

	gui_surface_force_update();
	//SYS_DEBUG("gui: touch_layout_rebound_loop_moving, surface(%d, %d)", layout->offset_x, layout->offset_y);
}


static void gui_touch_layout_rebound_init(const gui_window_struct* window,DIRECTION_TYPE direction, int speed)
{
	g_layout_rebound_window    = window;
    g_layout_rebound_direction = direction;
    g_layout_auto_move_speed = (float)speed;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// param������ �� �ص� �����layout�� min_offset �� max_offset, �����������ƹ�ң�ֹͣʱ���� layout �� item_gap ����λ ...
//        direction   -  ֻ��Ҫ���������£�ˮƽ�� ���� ���� ����ֱ������ά��;
//        end_offset  -  ָ���г̾��룬�����Զ�����
//        speed       -  ָ����ʼ�ٶȣ������Զ�����
//        ע�⣺        !!! ָ���г� �� ָ����ʼ�ٶ� ����ͬʱ��Ч !!!!!!!
//
void gui_touch_layout_rebound_auto_moving(const gui_window_struct* window,DIRECTION_TYPE direction, short end_offset, int speed)
{
	gui_surface_struct* surface;
    gui_layout_header_struct* layout;
    short offset, mov_speed;

    if (window == NULL) {
        return;
    }
    surface = gui_surface_get_surface(window->screen);

    if (surface == NULL) {
        return;
    }
    layout = &surface->layout.header;

    if ((direction == DIRECTION_TYPE_LEFT) || (direction == DIRECTION_TYPE_RIGHT)) {
        offset = layout->offset_x;
    }
    else if ((direction == DIRECTION_TYPE_UP) || (direction == DIRECTION_TYPE_DOWN)) {
        offset = layout->offset_y;
    }
    else {
        return;
    }

    //SYS_DEBUG("gui: touch_layout_rebound_auto_moving, dir=%d, end=%d, speed=%d\n", direction, end_offset, speed);

    if (g_touch_auto_move_timer_id != 0) {
        application_stop_user_timer(g_touch_auto_move_timer_id);
        g_touch_auto_move_timer_id = 0;
    }

    mov_speed = speed * TOUCH_AUTO_MOVE_GAP_MS / 1000;
    if (end_offset != 0) {
        mov_speed = 0;
    }
    gui_touch_layout_rebound_init(window, direction, mov_speed);

    gui_touch_layout_start_freemove(layout, end_offset, offset);

    g_touch_auto_move_timer_id = application_start_user_timer(TOUCH_AUTO_MOVE_GAP_MS, gui_touch_layout_rebound_loop_moving, NULL);
}


void gui_touch_layout_rebound_cancle()
{
    // SYS_DEBUG("gui: touch_layout_rebound_cancle, %d\n", g_touch_auto_move_timer_id);
    application_stop_user_timer(g_touch_auto_move_timer_id);
    g_touch_auto_move_timer_id = 0;

    gui_touch_layout_rebound_init(NULL, DIRECTION_TYPE_NONE, 0);
}

unsigned char gui_touch_layout_rebound_is_moving()
{
    // SYS_DEBUG("gui: touch_layout_rebound_is_moving, %d\n", g_touch_auto_move_timer_id);
    if (g_touch_auto_move_timer_id != 0) {
        return 1;
    }
    return 0;
}



