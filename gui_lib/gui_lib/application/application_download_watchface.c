
#include "picture.h"
#include "language.h"
#include "bsp_includes.h"

#include "app_task_main.h"
#include "data_common.h"
#include "data_manager.h"
#include "data_manager_flash.h"
#include "watchface.h"
#include "arithmetic_common.h"
#include "arithmetic_sleep.h"

#include "font_convert.h"
#include "gui_surface_cache.h"
#include "gui_surface_box_pointer.h"
#include "gui_drivers_display.h"
#include "gui_surface_control_base.h"
#include "gui_surface_control_animation.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_canvas.h"
#include "gui_surface_node.h"

#include "application_download_watchface.h"
#include "application_config_main_window.h"
#include "get_data.h"

#define DLWF_OK     0
#define DLWF_ERR    1

// [-128 ~ 127]
//#define APP_WATCH_HOUR_ORDER  100
//#define APP_WATCH_MINUTE_ORDER  101
//#define APP_WATCH_SECOND_ORDER  102

static const gui_widget_struct app_dlwf_common_widget =
{
    .type = TYPE_GUI_DRAW_NONE,
};

static const char* month_string[12] =
{
	"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
};

static const char* week_string[7] =
{
	"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"
};


// pointer define var.
static picture_info_struct app_dlwf_pics_hour[8];
static picture_info_struct app_dlwf_pics_min[8];
static picture_info_struct app_dlwf_pics_sec[8];
static gui_pointer_struct app_dlwf_pointers_info[3];    // h, m, s

// ani
#define GUI_DLWF_ANI_MAX_FRAMES     10
static picture_info_struct app_dlwf_ani_pics[GUI_DLWF_ANI_MAX_FRAMES];
static gui_animation_frame_struct app_dlwf_ani_frams[GUI_DLWF_ANI_MAX_FRAMES] =
{
    PIC_ANIMATION_FRAME(300, 0, &app_dlwf_ani_pics[0]),
    PIC_ANIMATION_FRAME(300, 0, &app_dlwf_ani_pics[1]),
    PIC_ANIMATION_FRAME(300, 0, &app_dlwf_ani_pics[2]),
    PIC_ANIMATION_FRAME(300, 0, &app_dlwf_ani_pics[3]),
    PIC_ANIMATION_FRAME(300, 0, &app_dlwf_ani_pics[4]),
    PIC_ANIMATION_FRAME(300, 0, &app_dlwf_ani_pics[5]),
    PIC_ANIMATION_FRAME(300, 0, &app_dlwf_ani_pics[6]),
    PIC_ANIMATION_FRAME(300, 0, &app_dlwf_ani_pics[7]),
    PIC_ANIMATION_FRAME(300, 0, &app_dlwf_ani_pics[8]),
    PIC_ANIMATION_FRAME(300, 0, &app_dlwf_ani_pics[9]),
};

static gui_animation_struct app_dlwf_ani =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .frames_num = countof(app_dlwf_ani_frams),
    .frames = app_dlwf_ani_frams,
};
static const gui_widget_struct app_dlwf_ani_widget =
{
    .id = TABLE_ROW_ANI,
    .type = TYPE_GUI_CONTROL_ANIMATION,
    .width = LCD_SIZE_WIDTH,
    .height = LCD_SIZE_HEIGHT,
    .visible= 1,
    .child_num = 1,
    .children = &app_dlwf_ani,
};

//
short g_dlwf_hour_pos[4];
short g_dlwf_min_pos[4];
short g_dlwf_sec_pos[4];


static time_struct app_dlwf_time;
static unsigned char app_dlwf_ampm;
static unsigned char app_dlwf_ampm_pic_num;
static unsigned char app_dlwf_time_cmd_id;


//
static unsigned int app_dlwf_build_ani_nodes(gui_box_struct* box, cmd_struct *cmd_info)
{
    pic_struct      pic_info;
    unsigned int    frame_idx;
    unsigned int    addr;
    unsigned short  width, height;
    unsigned short  period;
    short x, y;

    SYS_DEBUG("app: dlwf_build_ani_nodes, frame_num=%d", cmd_info->act_num);

    app_dlwf_ani.frames_num = cmd_info->act_num;
    period = cmd_info->period[0] + (cmd_info->period[1] << 8);
    x = cmd_info->pos_x[0] + (cmd_info->pos_x[1] << 8);
    y = cmd_info->pos_y[0] + (cmd_info->pos_y[1] << 8);

    for (frame_idx=0; frame_idx<app_dlwf_ani.frames_num; frame_idx++) {
        // 20220808 Taylor.Le,
        //watchface_get_pic_info(cmd_info->act_pic[frame_idx][0], cmd_info->act_pic[frame_idx][1], &pic_info);
        watchface_get_pic_info(cmd_info->pic_type, cmd_info->act_pic[frame_idx], &pic_info);
        addr   = (pic_info.offset[0] + (pic_info.offset[1]<<8) + (pic_info.offset[2]<<16) + PICTURE_BASE - PICTURE_BASE_ADDR);
        width  = (pic_info.width[0]+(pic_info.width[1] << 8));
        height = (pic_info.height[0]+(pic_info.height[1] << 8));

        app_dlwf_ani_frams[frame_idx].duration = period;
        app_dlwf_ani_frams[frame_idx].x = x;
        app_dlwf_ani_frams[frame_idx].y = y;

		const picture_info_struct bitmap = {
			.addr = (unsigned char*)addr,
			.width = width,
			.height = height,
			.alpha = pic_info.depth,
			.external_flag = 1,
		};
        memcpy(&app_dlwf_ani_pics[frame_idx], &bitmap, sizeof(picture_info_struct));
    }

    box->id = TABLE_ROW_ANI;
    box->type = TYPE_GUI_CONTROL_ANIMATION;
    box->widget = (gui_widget_struct*)&app_dlwf_ani_widget;
    gui_surface_control_animation_create(box);
    return DLWF_OK;
}

static unsigned int app_dlwf_build_nodes(gui_box_struct* box, cmd_struct *cmd_info, unsigned size, unsigned char* temp)
{
    gui_node_struct* node = NULL;
    pic_struct      pic_info;
    unsigned int    index;
    unsigned short  w, h;
    short           x, y;
    unsigned char   pic_type, gap, align;

    SYS_DEBUG("dlwf_picture(s: %d, n:%d)", size, temp[0]);

    x = cmd_info->pos_x[0] + (cmd_info->pos_x[1] << 8);
    y = cmd_info->pos_y[0] + (cmd_info->pos_y[1] << 8);
    pic_type = cmd_info->pic_type;
    gap = cmd_info->pic_x_interval;
    align = cmd_info->pos_dir;

    if ((align == POS_DIR_RIGHT) || (align == POS_DIR_CENTER)) {
        unsigned short tw = 0;
        for (index=0; index < size; index++) {
            watchface_get_pic_info(pic_type, temp[index], &pic_info);
            w = (pic_info.width[0]+(pic_info.width[1] << 8));
            tw += (w + gap);
        }
        tw -= gap;

        if (align == POS_DIR_RIGHT) {
            x -= tw;
        }
        else {
            x -= tw/2;  // POS_DIR_CENTER
        }
    }

    for (index = 0; index < size; index ++) {
        watchface_get_pic_info(pic_type, temp[index], &pic_info);
        w = pic_info.width[0] +(pic_info.width[1] << 8);
        h = pic_info.height[0]+(pic_info.height[1] << 8);

        node = gui_surface_cache_add_node();
        node->type = TYPE_GUI_DRAW_DLWF_PICTURE;
        node->x = x;
        node->y = y;
        node->clip_x = 0;   // node->x; // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
        node->clip_y = 0;   // node->y; // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
        node->clip_width  = w;
        node->clip_height = h;
        node->data = (void*)(pic_info.offset[0] + (pic_info.offset[1]<<8) + (pic_info.offset[2]<<16) + PICTURE_BASE - PICTURE_BASE_ADDR);
        //node->value = (w << 16) + h;
        //if (pic_info.depth) node->value |= 0x80000000;
        node->value = (h & 0x00000FFF) + ((w << 12) & 0x00FFF000) + ((pic_info.depth << 24) & 0xFF000000);
        x += (w+gap);

        SYS_DEBUG("dlwf_picture(d: %x, x: %d, y: %d, w: %d, h:%d)", (unsigned int)node->data, x, y, w, h);
        gui_surface_box_add_node(box, node);
		box->type = TYPE_GUI_DRAW_DLWF_PICTURE;
    }
    return DLWF_OK;
}

static unsigned int app_dlwf_change_nodes(gui_box_struct* box, unsigned size, unsigned char* temp)
{
    if (box == NULL || box->type != TYPE_GUI_DRAW_DLWF_PICTURE) return DLWF_ERR;

    /* get cmd info. */
    cmd_struct cmd_info;
    watchface_data_get((unsigned int)box->data, (unsigned char *)&cmd_info, sizeof(cmd_info));
    if((0 == cmd_info.pic_type)&&(0 == cmd_info.pic_num)) {
        //if pic id is 0, so don't display picture.
        return DLWF_ERR;
    }

    // remove child nodes
    gui_surface_cache_remove_nodes(box->child);
    box->child = NULL;

    // rebuild node chain.
    return app_dlwf_build_nodes(box, &cmd_info, size, temp);
}

static unsigned int app_dlwf_picture_nodes(gui_box_struct* box, cmd_struct *cmd_info, unsigned int size, unsigned char* temp)
{
    if((0 == cmd_info->pic_type)&&(0 == cmd_info->pic_num)) {
        //if pic id is 0, so don't display picture.
        return DLWF_ERR;
    }

    return app_dlwf_build_nodes(box, cmd_info, size, temp);
}

static void app_dlwf_pointer_pictures(cmd_struct* cmd_info, picture_info_struct* pics, unsigned char pic_num)
{
    pic_struct pic_info;
    unsigned int idx, addr;
    unsigned short width, height;

    for (idx=0; idx<8; idx++, pic_num++) {
        watchface_get_pic_info(cmd_info->pic_type, pic_num, &pic_info);//得到图片信息
        addr = (pic_info.offset[0] + (pic_info.offset[1]<<8) + (pic_info.offset[2]<<16) + PICTURE_BASE - PICTURE_BASE_ADDR);
        width = pic_info.width[0] | (pic_info.width[1]<<8);
        height = pic_info.height[0] | (pic_info.height[1]<<8);
        if (width > 0xFFF) {
			width = (pic_info.width[0]<<8) | (pic_info.width[1]<<0); //width[0]: x, width[1]: y.
        }
		const picture_info_struct bitmap = {
			.addr = (unsigned char*)addr,
			.width = width,
			.height = height,
			.alpha = pic_info.depth,
			.external_flag = 1,
		};
        memcpy(pics, &bitmap, sizeof(picture_info_struct));
        pics ++;
    }
}

static unsigned int app_dlwf_pointers_nodes(gui_box_struct* box, cmd_struct* cmd_info, unsigned int is360)
{
	gui_node_struct* node;
    gui_pointer_struct* pointer = NULL;
    unsigned int index;

    // hour
    node = gui_surface_cache_add_node();
    if (node != NULL) {
        SYS_DEBUG("dlwf_pointer: hour");
        pointer = &app_dlwf_pointers_info[0];
        pointer->value = (app_dlwf_time.hour % 12)*5 + app_dlwf_time.min/12;
        pointer->type = TYPE_GUI_DRAW_POINTER_8IMAGES;
        pointer->center_x = LCD_SIZE_WIDTH/2;
        pointer->center_y = LCD_SIZE_HEIGHT/2;
        pointer->hand_lenth = LCD_SIZE_WIDTH/2;
        pointer->hilt_lenth = LCD_SIZE_WIDTH/8;
        pointer->hand_width = 20;
        app_dlwf_pointer_pictures(cmd_info, app_dlwf_pics_hour, 0x80);
        for (index=0; index<8; index++) {
            pointer->shape.pics[index] = &app_dlwf_pics_hour[index];
        }

        node->type = TYPE_GUI_DRAW_POINTER;
        node->id   = TABLE_ROW_TIME_POINT_HOUR;
        node->x    = 0;
        node->y    = 0;
        node->width= LCD_SIZE_WIDTH;
        node->height=LCD_SIZE_HEIGHT;
        node->data = pointer;
        node->value = pointer->value;
        gui_surface_box_pointer_arrange(node);
        gui_surface_box_add_node(box, node);
    }

    // min
    node = gui_surface_cache_add_node();
    if (node != NULL) {
        SYS_DEBUG("dlwf_pointer: minute");
        pointer = &app_dlwf_pointers_info[1];
        pointer->value = app_dlwf_time.min;
        pointer->type = TYPE_GUI_DRAW_POINTER_8IMAGES;
        pointer->center_x = LCD_SIZE_WIDTH/2;
        pointer->center_y = LCD_SIZE_HEIGHT/2;
        pointer->hand_lenth = LCD_SIZE_WIDTH/2;
        pointer->hilt_lenth = LCD_SIZE_WIDTH/8;
        pointer->hand_width = 20;
        app_dlwf_pointer_pictures(cmd_info, app_dlwf_pics_min, 0x90);
        for (index=0; index<8; index++) {
            pointer->shape.pics[index] = &app_dlwf_pics_min[index];
        }

        node->type = TYPE_GUI_DRAW_POINTER;
        node->id   = TABLE_ROW_TIME_POINT_MIN;
        node->x    = 0;
        node->y    = 0;
        node->width= LCD_SIZE_WIDTH;
        node->height=LCD_SIZE_HEIGHT;
        node->data = pointer;
        node->value = pointer->value;
        gui_surface_box_pointer_arrange(node);
        gui_surface_box_add_node(box, node);
    }

    // sec
    node = gui_surface_cache_add_node();
    if (node != NULL) {
        SYS_DEBUG("dlwf_pointer: second");
        pointer = &app_dlwf_pointers_info[2];
        if (is360) {
            pointer->value = application_main_window_get_ang360(&app_dlwf_time);
            pointer->type = TYPE_GUI_DRAW_POINTER_LINE_360;
            pointer->center_x = LCD_SIZE_WIDTH/2;
            pointer->center_y = LCD_SIZE_HEIGHT/2;
            pointer->hand_lenth = (cmd_info->line_size[0] + (cmd_info->line_size[1]<<8));
            pointer->hilt_lenth = (cmd_info->start_pos[0] + (cmd_info->start_pos[1]<<8));
            pointer->hand_width = cmd_info->line_width;
            if (pointer->hand_width == 0) pointer->hand_width = 3;
            if (pointer->hilt_lenth != 0) pointer->hilt_lenth = -pointer->hilt_lenth;
            pointer->shape.line.color = COLOR_RGB(cmd_info->r, cmd_info->g, cmd_info->b),
            pointer->shape.line.position = g_dlwf_sec_pos;
        }
        else {
            pointer->value = app_dlwf_time.sec;
            pointer->type = TYPE_GUI_DRAW_POINTER_8IMAGES;
            pointer->center_x = LCD_SIZE_WIDTH/2;
            pointer->center_y = LCD_SIZE_HEIGHT/2;
            pointer->hand_lenth = LCD_SIZE_WIDTH/2;
            pointer->hilt_lenth = LCD_SIZE_WIDTH/8;
            pointer->hand_width = 20;
            app_dlwf_pointer_pictures(cmd_info, app_dlwf_pics_sec, 0xA0);
            for (index=0; index<8; index++) {
                pointer->shape.pics[index] = &app_dlwf_pics_sec[index];
            }
        }
        node->type = TYPE_GUI_DRAW_POINTER;
        node->id   = TABLE_ROW_TIME_POINT_SEC;
        node->x    = 0;
        node->y    = 0;
        node->width= LCD_SIZE_WIDTH;
        node->height=LCD_SIZE_HEIGHT;
        node->data = pointer;
        node->value = pointer->value;
        gui_surface_box_pointer_arrange(node);
        gui_surface_box_add_node(box, node);
    }

    // center point
    node = gui_surface_cache_add_node();
    if (node != NULL) {
        pic_struct pic_info;
        unsigned int width, height;

        watchface_get_pic_info(cmd_info->pic_type, 0xB0, &pic_info);//得到图片信息
        width = pic_info.width[0]+(pic_info.width[1] << 8);
        height = pic_info.height[0]+(pic_info.height[1] << 8);

        node->type = TYPE_GUI_DRAW_DLWF_PICTURE;
        node->id = 0;
        node->x = (LCD_SIZE_WIDTH-width)/2;
        node->y = (LCD_SIZE_HEIGHT-height)/2;
        node->width = width;
        node->height = height;
        node->clip_x = 0;//node->x; // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
        node->clip_y = 0;//node->y;// 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
        node->clip_width  = width;
        node->clip_height = height;
        node->data = (void*)(pic_info.offset[0] + (pic_info.offset[1]<<8) + (pic_info.offset[2]<<16) + PICTURE_BASE - PICTURE_BASE_ADDR);
        //node->value = (width << 16) + height;
        //if (pic_info.depth) node->value |= 0x80000000;
        node->value = (height & 0x00000FFF) + ((width << 12) & 0x00FFF000) + ((pic_info.depth << 24) & 0xFF000000);
        gui_surface_box_add_node(box, node);
    }
	box->type = TYPE_GUI_DRAW_POINTER;
    return DLWF_OK;
}

// ...
static unsigned int app_dlwf_picture(gui_box_struct* box, cmd_struct *cmd_info)
{
    //00000050h: 00 01 69 00 8A 00 00 00 00 03 80 00 00 00 00 00 ; ..i.?....?....
    //00000060h: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ; ................
    unsigned char temp[1];
    temp[0] = cmd_info->pic_num;
    if (cmd_info->act_num > 1) {
        return app_dlwf_build_ani_nodes(box, cmd_info);
    }
    return app_dlwf_picture_nodes(box, cmd_info, 1, temp);
}

//
static unsigned int app_dlwf_hh_mm(gui_box_struct* box, cmd_struct *cmd_info)
{
    //00000030h: 2A 01 15 00 C9 00 00 00 00 02 30 02 00 00 00 00 ; *...?....0.....
    //00000040h: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ; ................
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%02d:%02d", app_dlwf_time.hour, app_dlwf_time.min);
    return app_dlwf_picture_nodes(box, cmd_info, 5, temp);
}
static unsigned int app_dlwf_hh_mm_load(gui_box_struct* box)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%02d:%02d", app_dlwf_time.hour, app_dlwf_time.min);
    return app_dlwf_change_nodes(box, 5, temp);
}

//
static unsigned int app_dlwf_hour(gui_box_struct* box, cmd_struct *cmd_info)
{
    //00000010h: 2B 01 14 00 0E 00 00 00 00 01 30 00 00 00 00 00 ; +.........0.....
    //00000020h: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ; ................
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%02d", app_dlwf_time.hour);
    return app_dlwf_picture_nodes(box, cmd_info, 2, temp);
}
static unsigned int app_dlwf_hour_load(gui_box_struct* box)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%02d", app_dlwf_time.hour);
    return app_dlwf_change_nodes(box, 2, temp);
}

//
static unsigned int app_dlwf_minute(gui_box_struct* box, cmd_struct *cmd_info)
{
    //00000030h: 2C 01 14 00 96 00 00 00 00 02 30 00 00 00 00 00 ; ,...?....0.....
    //00000040h: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ; ................
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%02d", app_dlwf_time.min);
    return app_dlwf_picture_nodes(box, cmd_info, 2, temp);
}
static unsigned int app_dlwf_minute_load(gui_box_struct* box)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%02d", app_dlwf_time.min);
    return app_dlwf_change_nodes(box, 2, temp);
}

//
static unsigned int app_dlwf_hour_h(gui_box_struct* box, cmd_struct *cmd_info)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%d", app_dlwf_time.hour/10);
    return app_dlwf_picture_nodes(box, cmd_info, 1, temp);
}
static unsigned int app_dlwf_hour_h_load(gui_box_struct* box)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%d", app_dlwf_time.hour/10);
    return app_dlwf_change_nodes(box, 1, temp);
}

//
static unsigned int app_dlwf_hour_l(gui_box_struct* box, cmd_struct *cmd_info)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%d", app_dlwf_time.hour%10);
    return app_dlwf_picture_nodes(box, cmd_info, 1, temp);
}
static unsigned int app_dlwf_hour_l_load(gui_box_struct* box)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%d", app_dlwf_time.hour%10);
    return app_dlwf_change_nodes(box, 1, temp);
}

//
static unsigned int app_dlwf_minute_h(gui_box_struct* box, cmd_struct *cmd_info)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%d", app_dlwf_time.min/10);
    return app_dlwf_picture_nodes(box, cmd_info, 1, temp);
}
static unsigned int app_dlwf_minute_h_load(gui_box_struct* box)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%d", app_dlwf_time.min/10);
    return app_dlwf_change_nodes(box, 1, temp);
}

//
static unsigned int app_dlwf_minute_l(gui_box_struct* box, cmd_struct *cmd_info)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%d", app_dlwf_time.min%10);
    return app_dlwf_picture_nodes(box, cmd_info, 1, temp);
}
static unsigned int app_dlwf_minute_l_load(gui_box_struct* box)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%d", app_dlwf_time.min%10);
    return app_dlwf_change_nodes(box, 1, temp);
}

//
static unsigned int app_dlwf_am_pm(gui_box_struct* box, cmd_struct* cmd_info)
{
    unsigned char temp[1];
    app_dlwf_ampm_pic_num = cmd_info->pic_num;
    if (app_dlwf_ampm) {
        temp[0] = app_dlwf_ampm_pic_num + 0x81;
    }
    else {
        temp[0] = app_dlwf_ampm_pic_num + 0x80;
    }
    return app_dlwf_picture_nodes(box, cmd_info, 1, temp);
}
static unsigned int app_dlwf_am_pm_load(gui_box_struct* box)
{
    unsigned char temp[1];
    if (app_dlwf_ampm) {
        temp[0] = app_dlwf_ampm_pic_num + 0x81;
    }
    else {
        temp[0] = app_dlwf_ampm_pic_num + 0x80;
    }
    return app_dlwf_change_nodes(box, 1, temp);
}

//
static unsigned int app_dlwf_pointers(gui_box_struct* box, cmd_struct* cmd_info)
{
	gui_node_struct* node;
    gui_pointer_struct* pointer = NULL;

	if(POS_DIR_POINTER != cmd_info->pos_dir) return DLWF_ERR;

    if (cmd_info->id == TABLE_ROW_TIME_POINT_HOUR) {
        //box->order = APP_WATCH_HOUR_ORDER;
        pointer = &app_dlwf_pointers_info[0];
        pointer->shape.line.position = g_dlwf_hour_pos;
        pointer->value = (app_dlwf_time.hour % 12)*5 + app_dlwf_time.min/12;
        pointer->type = TYPE_GUI_DRAW_POINTER_LINE_60;
    }
    else if (cmd_info->id == TABLE_ROW_TIME_POINT_MIN) {
        //box->order = APP_WATCH_MINUTE_ORDER;
        pointer = &app_dlwf_pointers_info[1];
        pointer->shape.line.position = g_dlwf_min_pos;
        pointer->value = app_dlwf_time.min;
        pointer->type = TYPE_GUI_DRAW_POINTER_LINE_60;
    }
    else if (cmd_info->id == TABLE_ROW_TIME_POINT_SEC) {
        //box->order = APP_WATCH_SECOND_ORDER;
        pointer = &app_dlwf_pointers_info[2];
        pointer->shape.line.position = g_dlwf_sec_pos;
        pointer->value = app_dlwf_time.sec;
        pointer->type = TYPE_GUI_DRAW_POINTER_LINE_60;
    }
    else {
        return DLWF_ERR;
    }

    node = gui_surface_cache_add_node();
    if (node != NULL) {
        pointer->shape.line.color = COLOR_RGB(cmd_info->r, cmd_info->g, cmd_info->b),
        pointer->center_x = cmd_info->pos_x[0] + (cmd_info->pos_x[1]<<8);
        pointer->center_y = cmd_info->pos_y[0] + (cmd_info->pos_y[1]<<8);
        pointer->hand_width = cmd_info->line_width;
        pointer->hand_lenth = cmd_info->line_size[0] + (cmd_info->line_size[1]<<8);
        pointer->hilt_lenth = cmd_info->start_pos[0] + (cmd_info->start_pos[1]<<8);
        if (pointer->hand_width == 0) pointer->hand_width = 3;
        if (pointer->hilt_lenth != 0) pointer->hilt_lenth = -pointer->hilt_lenth;

        node->type = TYPE_GUI_DRAW_POINTER;
        node->id = cmd_info->id;
        node->data = pointer;
        node->value = pointer->value;
        gui_surface_box_pointer_arrange(node);

        gui_surface_box_add_node(box, node);
        app_dlwf_time_cmd_id = TABLE_ROW_TIME_POINT_HOUR;
		box->type = TYPE_GUI_DRAW_POINTER;
        return DLWF_OK;
    }
    pointer->type = TYPE_GUI_DRAW_POINTER;
    return DLWF_ERR;
}
static unsigned int app_dlwf_pointers_load(gui_box_struct* box)
{
    unsigned int value;
    if (box->id == TABLE_ROW_TIME_POINT_HOUR) {
        value = (app_dlwf_time.hour % 12)*5 + app_dlwf_time.min/12;
    }
    else if (box->id == TABLE_ROW_TIME_POINT_MIN) {
        value = app_dlwf_time.min;
    }
    else if (box->id == TABLE_ROW_TIME_POINT_SEC) {
        value = app_dlwf_time.sec;
    }
    else {
        return DLWF_ERR;
    }
    gui_surface_box_pointer_change(box, value);
    return DLWF_OK;
}

//
static unsigned int app_dlwf_pointer_360(gui_box_struct* box, cmd_struct *cmd_info)
{
    //00000030h: 2F 01 00 00 00 00 F5 F5 F5 02 80 00 00 00 00 00 ; /........
    //00000040h: 00 00 00 00 00 00 00 00 00 00 64 00 DD FF 64 00 ; ..........d.?d.
    app_dlwf_time_cmd_id = TABLE_ROW_TIME_POINT_HMS_360;
    //box->order = APP_WATCH_SECOND_ORDER;
    return app_dlwf_pointers_nodes(box, cmd_info, 1);
}
static unsigned int app_dlwf_pointer_1S(gui_box_struct* box, cmd_struct *cmd_info)
{
    SYS_DEBUG("app_dlwf_pointer_1S(box: %x)", (unsigned int)box);
    app_dlwf_time_cmd_id = TABLE_ROW_TIME_POINT_HMS_1S;
    //box->order = APP_WATCH_SECOND_ORDER;
    return app_dlwf_pointers_nodes(box, cmd_info, 0);
}
static unsigned int app_dlwf_pointer_1S_360_load(gui_box_struct* box)
{
    gui_node_struct* node;

    SYS_DEBUG("app_dlwf_pointer_1S_360_load(box: %x)", (unsigned int)box);

    node = gui_surface_box_find_node(box, TABLE_ROW_TIME_POINT_HOUR);
    if (node != NULL) {
        node->value = (app_dlwf_time.hour % 12)*5 + app_dlwf_time.min/12;
        gui_surface_box_pointer_arrange(node);
    }
    else {
        SYS_DEBUG("pointer: hour error");
    }
    node = gui_surface_box_find_node(box, TABLE_ROW_TIME_POINT_MIN);
    if (node != NULL) {
        node->value = app_dlwf_time.min;
        gui_surface_box_pointer_arrange(node);
    }
    else {
        SYS_DEBUG("pointer: min error");
    }
    node = gui_surface_box_find_node(box, TABLE_ROW_TIME_POINT_SEC);
    if (node != NULL) {
        unsigned int value;
        if (app_dlwf_pointers_info[2].type == TYPE_GUI_DRAW_POINTER_LINE_360) {
            value  = application_main_window_get_ang360(&app_dlwf_time);
        }
        else {
            value = app_dlwf_time.sec;
        }
        node->value = value;
        gui_surface_box_pointer_arrange(node);
    }
    else {
        SYS_DEBUG("pointer: sec error");
    }
    return DLWF_OK;
}

//
static unsigned int app_dlwf_digit_month(gui_box_struct* box, cmd_struct *cmd_info)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%02d", app_dlwf_time.mon);
    return app_dlwf_picture_nodes(box, cmd_info, 2, temp);
}
static unsigned int app_dlwf_digit_month_load(gui_box_struct* box)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%02d", app_dlwf_time.mon);
    return app_dlwf_change_nodes(box, 2, temp);
}

//
static unsigned int app_dlwf_font_month(gui_box_struct* box, cmd_struct *cmd_info)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%s", month_string[app_dlwf_time.mon-1]);
    return app_dlwf_picture_nodes(box, cmd_info, 3, temp);
}
static unsigned int app_dlwf_font_month_load(gui_box_struct* box)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%s", month_string[app_dlwf_time.mon-1]);
    return app_dlwf_change_nodes(box, 3, temp);
}

//
static unsigned int app_dlwf_pic_month(gui_box_struct* box, cmd_struct *cmd_info)
{
    unsigned char temp[1];
    temp[0] = 0x80 + app_dlwf_time.mon;
    return app_dlwf_picture_nodes(box, cmd_info, 1, temp);
}
static unsigned int app_dlwf_pic_month_load(gui_box_struct* box)
{
    unsigned char temp[1];
    temp[0] = 0x80 + app_dlwf_time.mon;
    return app_dlwf_change_nodes(box, 1, temp);
}

//
static unsigned int app_dlwf_digit_day(gui_box_struct* box, cmd_struct *cmd_info)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%02d", app_dlwf_time.day);
    return app_dlwf_picture_nodes(box, cmd_info, 2, temp);
}
static unsigned int app_dlwf_digit_day_load(gui_box_struct* box)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%02d", app_dlwf_time.day);
    return app_dlwf_change_nodes(box, 2, temp);
}

//
static unsigned int app_dlwf_pic_day(gui_box_struct* box, cmd_struct *cmd_info)
{
    unsigned char temp[1];
    temp[0] = 0x80 + app_dlwf_time.day;
    return app_dlwf_picture_nodes(box, cmd_info, 1, temp);
}
static unsigned int app_dlwf_pic_day_load(gui_box_struct* box)
{
    unsigned char temp[1];
    temp[0] = 0x80 + app_dlwf_time.day;
    return app_dlwf_change_nodes(box, 1, temp);
}

//
static unsigned int app_dlwf_digit_month_day(gui_box_struct* box, cmd_struct *cmd_info)
{
    unsigned char temp[8];
    if(0 == g_timeSync.format.bit.mon_day) { // 0: mon-day, 1: day-mon.
        snprintf((char*)temp, sizeof(temp), "%02d-%02d", app_dlwf_time.mon, app_dlwf_time.day);
    }
    else {
        snprintf((char*)temp, sizeof(temp), "%02d-%02d", app_dlwf_time.day, app_dlwf_time.mon);
    }
    return app_dlwf_picture_nodes(box, cmd_info, 5, temp);
}
static unsigned int app_dlwf_digit_month_day_load(gui_box_struct* box)
{
    unsigned char temp[8];
    if(0 == g_timeSync.format.bit.mon_day) { // 0: mon-day, 1: day-mon.
        snprintf((char*)temp, sizeof(temp), "%02d-%02d", app_dlwf_time.mon, app_dlwf_time.day);
    }
    else {
        snprintf((char*)temp, sizeof(temp), "%02d-%02d", app_dlwf_time.day, app_dlwf_time.mon);
    }
    return app_dlwf_change_nodes(box, 5, temp);
}

//
static unsigned int app_dlwf_digit_month_day_2(gui_box_struct* box, cmd_struct *cmd_info)
{
    //00000070h: 30 01 8C 00 87 00 00 00 00 04 30 00 00 00 00 00 ; 0.??....0.....
    //00000080h: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ; ................
    unsigned char temp[8];
    if(0 == g_timeSync.format.bit.mon_day) { // 0: mon-day, 1: day-mon.
        snprintf((char*)temp, sizeof(temp), "%02d/%02d", app_dlwf_time.mon, app_dlwf_time.day);
    }
    else {
        snprintf((char*)temp, sizeof(temp), "%02d/%02d", app_dlwf_time.day, app_dlwf_time.mon);
    }
    return app_dlwf_picture_nodes(box, cmd_info, 5, temp);
}
static unsigned int app_dlwf_digit_month_day_2_load(gui_box_struct* box)
{
    unsigned char temp[8];
    if(0 == g_timeSync.format.bit.mon_day) { // 0: mon-day, 1: day-mon.
        snprintf((char*)temp, sizeof(temp), "%02d/%02d", app_dlwf_time.mon, app_dlwf_time.day);
    }
    else {
        snprintf((char*)temp, sizeof(temp), "%02d/%02d", app_dlwf_time.day, app_dlwf_time.mon);
    }
    return app_dlwf_change_nodes(box, 5, temp);
}

//
static unsigned int app_dlwf_digit_year(gui_box_struct* box, cmd_struct *cmd_info)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%d", app_dlwf_time.year);
    return app_dlwf_picture_nodes(box, cmd_info, strlen((char*)temp), temp);
}
static unsigned int app_dlwf_digit_year_load(gui_box_struct* box)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%d", app_dlwf_time.year);
    return app_dlwf_change_nodes(box, strlen((char*)temp), temp);
}

//
static unsigned int app_dlwf_digit_week(gui_box_struct* box, cmd_struct *cmd_info)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%d", app_dlwf_time.wed);
    return app_dlwf_picture_nodes(box, cmd_info, 1, temp);
}
static unsigned int app_dlwf_digit_week_load(gui_box_struct* box)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%d", app_dlwf_time.wed);
    return app_dlwf_change_nodes(box, 1, temp);
}

//
static unsigned int app_dlwf_font_week(gui_box_struct* box, cmd_struct *cmd_info)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%s", week_string[app_dlwf_time.wed]);
    return app_dlwf_picture_nodes(box, cmd_info, 3, temp);
}
static unsigned int app_dlwf_font_week_load(gui_box_struct* box)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%s", week_string[app_dlwf_time.wed]);
    return app_dlwf_change_nodes(box, 3, temp);
}

//
static unsigned int app_dlwf_pic_week(gui_box_struct* box, cmd_struct *cmd_info)
{
    //00000050h: 10 01 4D 00 87 00 00 00 00 03 80 00 00 00 00 00 ; ..M.?....?....
    //00000060h: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ; ................
    unsigned char temp[1];
    temp[0] = 0x80 + app_dlwf_time.wed;
    return app_dlwf_picture_nodes(box, cmd_info, 1, temp);
}
static unsigned int app_dlwf_pic_week_load(gui_box_struct* box)
{
    unsigned char temp[1];
    temp[0] = 0x80 + app_dlwf_time.wed;
    return app_dlwf_change_nodes(box, 1, temp);
}

//
static unsigned int app_dlwf_power_pic(gui_box_struct* box, cmd_struct *cmd_info)
{
    unsigned char temp[1];
    int value = get_battery_capacity();
    value = (value + 13)/25;
    if(value > 3)
        value = 3;
    temp[0] = 0x80 + value;
    return app_dlwf_picture_nodes(box, cmd_info, 1, temp);
}
static unsigned int app_dlwf_power_pic_load(gui_box_struct* box)
{
    unsigned char temp[1];
    int value = get_battery_capacity();
    value = (value + 13)/25;
    if(value > 3)
        value = 3;
    temp[0] = 0x80 + value;
    return app_dlwf_change_nodes(box, 1, temp);
}

//
static unsigned int app_dlwf_power_digit(gui_box_struct* box, cmd_struct *cmd_info)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%d%%", get_battery_capacity());
    return app_dlwf_picture_nodes(box, cmd_info, strlen((char*)temp), temp);
}
static unsigned int app_dlwf_power_digit_load(gui_box_struct* box)
{
    unsigned char temp[8];
    snprintf((char*)temp, sizeof(temp), "%d%%", get_battery_capacity());
    return app_dlwf_change_nodes(box, strlen((char*)temp), temp);
}

//
static unsigned int app_dlwf_ble_pic(gui_box_struct* box, cmd_struct *cmd_info)
{
    unsigned char temp[1];
    if(0 == get_ble_connect_flag())
        temp[0] = 0x80; //disconnect
    else
        temp[0] = 0x81; //connect.
    return app_dlwf_picture_nodes(box, cmd_info, 1, temp);
}
static unsigned int app_dlwf_ble_pic_load(gui_box_struct* box)
{
    unsigned char temp[1];
    if(0 == get_ble_connect_flag())
        temp[0] = 0x80; //disconnect
    else
        temp[0] = 0x81; //connect.
    return app_dlwf_change_nodes(box, 1, temp);
}

//
static unsigned int app_dlwf_step_data(gui_box_struct* box, cmd_struct *cmd_info)
{
    //000000b0h: 14 02 D0 00 E2 00 00 00 00 06 30 00 00 00 00 00 ; ..??....0.....
    //000000c0h: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ; ................
    unsigned char temp[16];
    int value = get_sport_info()->walkSteps;
    snprintf((char*)temp, sizeof(temp), "%d", value);
    return app_dlwf_picture_nodes(box, cmd_info, strlen((char*)temp), temp);
}
static unsigned int app_dlwf_step_data_load(gui_box_struct* box)
{
    unsigned char temp[16];
    int value = get_sport_info()->walkSteps;
    snprintf((char*)temp, sizeof(temp), "%d", value);
    return app_dlwf_change_nodes(box, strlen((char*)temp), temp);
}

//
static unsigned int app_dlwf_distance_data(gui_box_struct* box, cmd_struct *cmd_info)
{
    //00000070h: 19 02 19 00 15 00 00 00 00 04 30 00 00 00 00 00 ; ..........0.....
    //00000080h: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ; ................
    unsigned char temp[16];
    int value = get_sport_info()->distance;
    if(g_unit_setting.select.bit.distance)
    {
        //1mile = 1609.3m , mile
        snprintf((char*)temp, sizeof(temp), "%d.%d", value*10/16093, (value*10*10)/16093%10);
    }
    else{ //km
        snprintf((char*)temp, sizeof(temp), "%d.%d%d", value/1000, (value/100)%10, (value/10)%10);
    }
    return app_dlwf_picture_nodes(box, cmd_info, strlen((char*)temp), temp);
}
static unsigned int app_dlwf_distance_data_load(gui_box_struct* box)
{
    unsigned char temp[16];
    int value = get_sport_info()->distance;
    if(g_unit_setting.select.bit.distance)
    {
        //1mile = 1609.3m , mile
        snprintf((char*)temp, sizeof(temp), "%d.%d", value*10/16093, (value*10*10)/16093%10);
    }
    else{ //km
        snprintf((char*)temp, sizeof(temp), "%d.%d%d", value/1000, (value/100)%10, (value/10)%10);
    }
    return app_dlwf_change_nodes(box, strlen((char*)temp), temp);
}

//
static unsigned int app_dlwf_calorie_data(gui_box_struct* box, cmd_struct *cmd_info)
{
    //00000050h: 1E 02 D1 00 13 00 00 00 00 03 30 00 00 00 00 00 ; ..?......0.....
    //00000060h: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ; ................
    unsigned char temp[8];
    int value = get_sport_info()->calories;
    snprintf((char*)temp, sizeof(temp), "%d", value/1000);
    return app_dlwf_picture_nodes(box, cmd_info, strlen((char*)temp), temp);
}
static unsigned int app_dlwf_calorie_data_load(gui_box_struct* box)
{
    unsigned char temp[8];
    int value = get_sport_info()->calories;
    snprintf((char*)temp, sizeof(temp), "%d", value/1000);
    return app_dlwf_change_nodes(box, strlen((char*)temp), temp);
}

//
static unsigned int app_dlwf_heart_data(gui_box_struct* box, cmd_struct *cmd_info)
{
    //00000090h: 23 02 1C 00 E2 00 00 00 00 05 30 00 00 00 00 00 ; #...?....0.....
    //000000a0h: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ; ................
    unsigned char temp[8];
    int value = get_hr_result()->hr;
    snprintf((char*)temp, sizeof(temp), "%d", value);
    return app_dlwf_picture_nodes(box, cmd_info, strlen((char*)temp), temp);
}
static unsigned int app_dlwf_heart_data_load(gui_box_struct* box)
{
    unsigned char temp[8];
    int value = get_hr_result()->hr;
    snprintf((char*)temp, sizeof(temp), "%d", value);
    return app_dlwf_change_nodes(box, strlen((char*)temp), temp);
}

static unsigned int app_dlwf_fill_rect(gui_box_struct* box, cmd_struct *cmd_info)
{
    static gui_canvas_struct    rect_info;

	int x, y, x2, y2, line_width, line_size, start_pos, end_pos;

	//if circle start pos & end pos is 0, so don't display picture.
	if((TABLE_ROW_RECTANGLE != cmd_info->id)||(POS_DIR_RECTANGLE != cmd_info->pos_dir))
		return DLWF_ERR;

	//get x,y value.
	x = cmd_info->pos_x[0] + (cmd_info->pos_x[1]<<8);
	y = cmd_info->pos_y[0] + (cmd_info->pos_y[1]<<8);

	//get line info.
	line_width = cmd_info->line_width;
	line_size = cmd_info->line_size[0] + (cmd_info->line_size[1]<<8);
	start_pos = cmd_info->start_pos[0] + (cmd_info->start_pos[1]<<8);
	end_pos = cmd_info->end_pos[0] + (cmd_info->end_pos[1]<<8);

	if(line_width >= line_size)
	{   // fill rect
        x2 = x+(end_pos-start_pos);
        y2 = y+line_width;
        rect_info.type = TYPE_GUI_DRAW_SHAPE_RECT_FILL;
	}
	else{
        // draw rect
        x2 = x+(end_pos-start_pos);
        y2 = y+line_size;
        rect_info.type = TYPE_GUI_DRAW_SHAPE_RECT;
	}
    rect_info.penColor = COLOR_RGB(cmd_info->r, cmd_info->g, cmd_info->b);
    rect_info.penSize = line_width;
    rect_info.opacity = 0;
    rect_info.canvas.rect.x0 = x;
    rect_info.canvas.rect.x1 = x2;
    rect_info.canvas.rect.y0 = y;
    rect_info.canvas.rect.y1 = y2;

    gui_node_struct* first_node = gui_surface_cache_add_node();
    if (first_node != NULL) {
        first_node->id = cmd_info->id;
        first_node->type = TYPE_GUI_CONTROL_CANVAS;
        first_node->x = 0;
        first_node->y = 0;
        first_node->clip_x = 0;
        first_node->clip_y = 0;
        first_node->data = &rect_info;
        first_node = gui_surface_box_canvas_init(first_node);

        gui_surface_box_add_node(box, first_node);
		box->type = TYPE_GUI_CONTROL_CANVAS;
        return DLWF_OK;
    }
    return DLWF_ERR;
}


typedef struct
{
    unsigned int cmd_id;    // TABLE_ROW_TYPE

    // return: 0 - error;  other - success
    unsigned int (*cmd_parse_func)(gui_box_struct* box, cmd_struct* cmd_info);

    // return: 0 - error;  other - success
    unsigned int (*data_load_func)(gui_box_struct* box);
}app_dlwf_cmd_map;

static const app_dlwf_cmd_map   g_dlwf_cmd_maps[] =
{

    {TABLE_ROW_PICTURE, app_dlwf_picture, NULL},
    {TABLE_ROW_TIME_DIGIT_HOUR_MIN_POINT, app_dlwf_hh_mm, app_dlwf_hh_mm_load},
    {TABLE_ROW_TIME_DIGIT_HOUR, app_dlwf_hour, app_dlwf_hour_load},
    {TABLE_ROW_TIME_DIGIT_MIN, app_dlwf_minute, app_dlwf_minute_load},
    {TABLE_ROW_TIME_DIGIT_HOUR_H, app_dlwf_hour_h, app_dlwf_hour_h_load},
    {TABLE_ROW_TIME_DIGIT_HOUR_L, app_dlwf_hour_l, app_dlwf_hour_l_load},
    {TABLE_ROW_TIME_DIGIT_MIN_H, app_dlwf_minute_h, app_dlwf_minute_h_load},
    {TABLE_ROW_TIME_DIGIT_MIN_L, app_dlwf_minute_l, app_dlwf_minute_l_load},
    {TABLE_ROW_TIME_DIGIT_AM_PM, app_dlwf_am_pm, app_dlwf_am_pm_load},
    {TABLE_ROW_TIME_POINT_HOUR, app_dlwf_pointers, app_dlwf_pointers_load},
    {TABLE_ROW_TIME_POINT_MIN, app_dlwf_pointers, app_dlwf_pointers_load},
    {TABLE_ROW_TIME_POINT_SEC, app_dlwf_pointers, app_dlwf_pointers_load},
    {TABLE_ROW_TIME_POINT_HMS_360, app_dlwf_pointer_360, app_dlwf_pointer_1S_360_load},
    {TABLE_ROW_TIME_POINT_HMS_1S, app_dlwf_pointer_1S, app_dlwf_pointer_1S_360_load},
    {TABLE_ROW_DATE_DIGIT_MONTH, app_dlwf_digit_month, app_dlwf_digit_month_load},
    {TABLE_ROW_DATE_FONT_MONTH, app_dlwf_font_month, app_dlwf_font_month_load},
    {TABLE_ROW_DATE_PIC_MONTH, app_dlwf_pic_month, app_dlwf_pic_month_load},
    {TABLE_ROW_DATE_DIGIT_DAY, app_dlwf_digit_day, app_dlwf_digit_day_load},
    {TABLE_ROW_DATE_PIC_DAY, app_dlwf_pic_day, app_dlwf_pic_day_load},
    {TABLE_ROW_DATE_DIGIT_MONTH_DAY, app_dlwf_digit_month_day, app_dlwf_digit_month_day_load},
    {TABLE_ROW_DATE_DIGIT_DAY_MONTH, app_dlwf_digit_month_day, app_dlwf_digit_month_day_load},
    {TABLE_ROW_DATE_DIGIT_MONTH_DAY_2, app_dlwf_digit_month_day_2, app_dlwf_digit_month_day_2_load},
    {TABLE_ROW_DATE_DIGIT_DAY_MONTH_2, app_dlwf_digit_month_day_2, app_dlwf_digit_month_day_2_load},
    {TABLE_ROW_YEAR_DIGIT, app_dlwf_digit_year, app_dlwf_digit_year_load},
    {TABLE_ROW_WEEK_DIGIT, app_dlwf_digit_week, app_dlwf_digit_week_load},
    {TABLE_ROW_WEEK_FONT, app_dlwf_font_week, app_dlwf_font_week_load},
    {TABLE_ROW_WEEK_PIC, app_dlwf_pic_week, app_dlwf_pic_week_load},
    {TABLE_ROW_POWER_PIC, app_dlwf_power_pic, app_dlwf_power_pic_load},
    {TABLE_ROW_POWER_DIGIT, app_dlwf_power_digit, app_dlwf_power_digit_load},
    {TABLE_ROW_BLE_PIC, app_dlwf_ble_pic, app_dlwf_ble_pic_load},

    {TABLE_ROW_STEP_DATA, app_dlwf_step_data, app_dlwf_step_data_load},
	{TABLE_ROW_STEP_CIRCLE_BAR, NULL},
	{TABLE_ROW_STEP_LINE_BAR, NULL},
	{TABLE_ROW_STEP_PIC_BAR, NULL},
    {TABLE_ROW_STEP_TARGET, NULL},

    {TABLE_ROW_DISTANCE_DATA, app_dlwf_distance_data, app_dlwf_distance_data_load},
	{TABLE_ROW_DISTANCE_CIRCLE_BAR, NULL},
	{TABLE_ROW_DISTANCE_LINE_BAR, NULL},
	{TABLE_ROW_DISTANCE_PIC_BAR, NULL},
	{TABLE_ROW_DISTANCE_TARGET, NULL},

	{TABLE_ROW_CALORIE_DATA, app_dlwf_calorie_data, app_dlwf_calorie_data_load},
	{TABLE_ROW_CALORIE_CIRCLE_BAR, NULL},
	{TABLE_ROW_CALORIE_LINE_BAR, NULL},
	{TABLE_ROW_CALORIE_PIC_BAR, NULL},
	{TABLE_ROW_CALORIE_TARGET, NULL},

	{TABLE_ROW_HEART_DATA, app_dlwf_heart_data, app_dlwf_heart_data_load},
	{TABLE_ROW_HEART_CIRCLE_BAR, NULL},
	{TABLE_ROW_HEART_LINE_BAR, NULL},
	{TABLE_ROW_HEART_PIC_BAR, NULL},
	{TABLE_ROW_HEART_TARGET, NULL},

	{TABLE_ROW_RECTANGLE, app_dlwf_fill_rect, NULL},
	{TABLE_ROW_CIRCLE, NULL},
};
#define C_DLWF_CMD_MAP_SZ   (sizeof(g_dlwf_cmd_maps)/sizeof(g_dlwf_cmd_maps[0]))

static const app_dlwf_cmd_map* app_dlwf_get_cmd_map(unsigned char cmd_id)
{
    const app_dlwf_cmd_map* cmd_map = NULL;
    unsigned int index;

    for (index=0; index<C_DLWF_CMD_MAP_SZ; index++) {
        if (g_dlwf_cmd_maps[index].cmd_id == cmd_id) {
            cmd_map = &g_dlwf_cmd_maps[index];
        }
    }
    return cmd_map;
}

static gui_box_struct* app_dlwf_parse_cmd(cmd_struct* cmd_info, unsigned int cmd_addr)
{
    const app_dlwf_cmd_map* cmd_map;
    gui_box_struct* box = NULL;
    unsigned int ret = DLWF_ERR;

    SYS_DEBUG("app_dlwf_parse_cmd: id=%d", cmd_info->id);

    cmd_map = app_dlwf_get_cmd_map(cmd_info->id);
    if ((cmd_map != NULL) && (cmd_map->cmd_parse_func != NULL)) {
        box = gui_surface_cache_add_box();
        if (box != NULL) {
            box->id = cmd_info->id;
            box->x = 0;
            box->y = 0;
            box->width = LCD_SIZE_WIDTH;
            box->height = LCD_SIZE_HEIGHT;
            box->widget = (gui_widget_struct*)&app_dlwf_common_widget;
            box->data = (void*)cmd_addr;
            ret = cmd_map->cmd_parse_func(box, cmd_info);
            if (ret == DLWF_ERR) {
                SYS_DEBUG("app_dlwf_parse_cmd: error");
                gui_surface_cache_remove_box_and_children(box);
                box = NULL;
            }
        }
    }
    else {
        SYS_DEBUG("app_dlwf_parse_cmd: error2");
    }
    return box;
}


unsigned int app_dlwf_init(const gui_screen_struct* screen)
{
    gui_surface_struct* surface;
    gui_box_struct* box = NULL;
    cmd_struct      cmd_info;
    unsigned int    value, addr;

    if (screen == NULL) {
        SYS_DEBUG("app_dlwf_init: error0");
        return 0;
    }

    surface = gui_surface_get_surface(screen);

    memset(app_dlwf_pics_hour, 0, 8*sizeof(picture_info_struct));
    memset(app_dlwf_pics_min, 0, 8*sizeof(picture_info_struct));
    memset(app_dlwf_pics_min, 0, 8*sizeof(picture_info_struct));
    memset(app_dlwf_pointers_info, 0, 3*sizeof(gui_pointer_struct));
    memset(app_dlwf_ani_pics, 0, 5*sizeof(picture_info_struct));

    // set default.
    app_dlwf_pointers_info[0].type = TYPE_GUI_DRAW_POINTER;
    app_dlwf_pointers_info[1].type = TYPE_GUI_DRAW_POINTER;
    app_dlwf_pointers_info[2].type = TYPE_GUI_DRAW_POINTER;
    app_dlwf_time_cmd_id = TABLE_ROW_SUM;

    app_dlwf_ampm = sys_time_get_12h(&app_dlwf_time, &value);

    for(addr = CMD_BASE; addr < PIC_BASE; addr+=sizeof(cmd_struct)) {

        /* get cmd info. */
        watchface_data_get(addr, (unsigned char *)&cmd_info, sizeof(cmd_info));

        /* check cmd is ok. */
        if(POS_DIR_NULL == cmd_info.pos_dir) {
            SYS_DEBUG("POS_DIR_NULL");
            break;
        }

        box = app_dlwf_parse_cmd(&cmd_info, addr);
        if (box != NULL) {
            SYS_DEBUG("dlwf: add box=%x", (unsigned int)box);
            gui_surface_add_box(surface, box);
        }
    }

    SYS_DEBUG("app_dlwf_time_cmd_id = %d", app_dlwf_time_cmd_id);
    //#ifndef APP_WATCH_HOUR_ORDER
    if (app_dlwf_time_cmd_id == TABLE_ROW_TIME_POINT_HOUR) {
        // take hour, min, sec
        box = gui_surface_get_box(screen, TABLE_ROW_TIME_POINT_HOUR);
        gui_surface_take_box_to_finally(surface, box);
        box = gui_surface_get_box(screen, TABLE_ROW_TIME_POINT_MIN);
        gui_surface_take_box_to_finally(surface, box);
        box = gui_surface_get_box(screen, TABLE_ROW_TIME_POINT_SEC);
        gui_surface_take_box_to_finally(surface, box);
    }
    else if (app_dlwf_time_cmd_id == TABLE_ROW_TIME_POINT_HMS_360) {
        box = gui_surface_get_box(screen, TABLE_ROW_TIME_POINT_HMS_360);
        gui_surface_take_box_to_finally(surface, box);
    }
    else if (app_dlwf_time_cmd_id == TABLE_ROW_TIME_POINT_HMS_1S) {
        box = gui_surface_get_box(screen, TABLE_ROW_TIME_POINT_HMS_1S);
        SYS_DEBUG("take box = %x", (unsigned int)box);

        gui_surface_take_box_to_finally(surface, box);

        box = gui_surface_get_box(screen, TABLE_ROW_TIME_POINT_HMS_1S);
        SYS_DEBUG("take box = %x", (unsigned int)box);
    }
    //#endif
    return 1;
}


unsigned int app_dlwf_load_data_item(const gui_screen_struct* screen, unsigned int cmd_id)
{
    const app_dlwf_cmd_map* cmd_map;
    unsigned int commit = 0;
    gui_box_struct* box = NULL;

    if (screen == NULL) {
        SYS_DEBUG("app_dlwf_load_data_item: error0");
        return 0;
    }

    SYS_DEBUG("app_dlwf_load_data_item(%d)", cmd_id);
    cmd_map = app_dlwf_get_cmd_map(cmd_id);
    if ((cmd_map != NULL) && (cmd_map->data_load_func != NULL)) {
        box = gui_surface_get_box(screen, cmd_id);
        if ((box != NULL) && (DLWF_OK == cmd_map->data_load_func(box))) {
            commit ++;
        }
        else {
            SYS_DEBUG("app_dlwf_load_data_item(error 1)");
        }
    }
    else {
        SYS_DEBUG("app_dlwf_load_data_item(error 2)");
    }
    return commit;
}

unsigned int app_dlwf_load_data(const gui_screen_struct* screen)
{
    const app_dlwf_cmd_map* cmd_map;
    gui_box_struct* box;
    unsigned int    value;
    unsigned int    commit = 0;

    if (screen == NULL) {
        SYS_DEBUG("app_dlwf_load_data_item: error0");
        return 0;
    }

    app_dlwf_ampm = sys_time_get_12h(&app_dlwf_time, &value);

	commit += app_dlwf_load_data_item(screen, TABLE_ROW_TIME_DIGIT_AM_PM);

    box = gui_surface_get_box_by_index(screen, 0);
    while(box) {
        SYS_DEBUG("app_dlwf_load_data(%d)", box->id);
        cmd_map = app_dlwf_get_cmd_map(box->id);
        if ((cmd_map != NULL) && (cmd_map->data_load_func != NULL)) {
            if (DLWF_OK == cmd_map->data_load_func(box)) {
                commit ++;
            }
        }
        box = box->brother;
    }
    return commit;
}

unsigned int app_dlwf_update_sportinfo(const gui_screen_struct* screen)
{
    unsigned int commit = 0;

    if (screen == NULL) {
        SYS_DEBUG("app_dlwf_load_data_item: error0");
        return 0;
    }

    commit += app_dlwf_load_data_item(screen, TABLE_ROW_STEP_DATA);
    commit += app_dlwf_load_data_item(screen, TABLE_ROW_CALORIE_DATA);
    commit += app_dlwf_load_data_item(screen, TABLE_ROW_DISTANCE_DATA);
    return commit;
}

unsigned int app_dlwf_update_time(const gui_screen_struct* screen)
{
    unsigned int value;
    unsigned int commit = 0;

    if (screen == NULL) {
        SYS_DEBUG("app_dlwf_update_time: error0");
        return 0;
    }

	app_dlwf_ampm = sys_time_get_12h(&app_dlwf_time, &value);

	commit += app_dlwf_load_data_item(screen, TABLE_ROW_TIME_DIGIT_AM_PM);

    SYS_DEBUG("app_dlwf_update_time(%d)", app_dlwf_pointers_info[2].type);
    if ((app_dlwf_pointers_info[2].type == TYPE_GUI_DRAW_POINTER_LINE_360)
	 || (app_dlwf_pointers_info[2].type == TYPE_GUI_DRAW_POINTER_LINE_60)
     || (app_dlwf_pointers_info[2].type == TYPE_GUI_DRAW_POINTER_8IMAGES)
     || (app_dlwf_pointers_info[2].type == TYPE_GUI_DRAW_POINTER_16IMAGES))
     {
        if (app_dlwf_time_cmd_id == TABLE_ROW_TIME_POINT_HMS_360) {
            commit += app_dlwf_load_data_item(screen, TABLE_ROW_TIME_POINT_HMS_360);
        }
        else if (app_dlwf_time_cmd_id == TABLE_ROW_TIME_POINT_HMS_1S) {
            commit += app_dlwf_load_data_item(screen, TABLE_ROW_TIME_POINT_HMS_1S);
        }
        else if (app_dlwf_time_cmd_id == TABLE_ROW_TIME_POINT_HOUR) {
            commit += app_dlwf_load_data_item(screen, TABLE_ROW_TIME_POINT_HOUR);
            commit += app_dlwf_load_data_item(screen, TABLE_ROW_TIME_POINT_MIN);
            commit += app_dlwf_load_data_item(screen, TABLE_ROW_TIME_POINT_SEC);
        }
    }
	SYS_DEBUG("app_dlwf_update_time: commit=%d",commit);
    return commit;
}

unsigned int app_dlwf_update_second(const gui_screen_struct* screen)
{
    unsigned int value;
    unsigned int commit = 0;

    if (screen == NULL) {
        SYS_DEBUG("app_dlwf_update_second: error0");
        return 0;
    }

    app_dlwf_ampm = sys_time_get_12h(&app_dlwf_time, &value);

	commit += app_dlwf_load_data_item(screen, TABLE_ROW_TIME_DIGIT_AM_PM);

    SYS_DEBUG("app_dlwf_update_second(%d)", app_dlwf_pointers_info[2].type);
    if ((app_dlwf_pointers_info[2].type == TYPE_GUI_DRAW_POINTER_LINE_60)
     || (app_dlwf_pointers_info[2].type == TYPE_GUI_DRAW_POINTER_8IMAGES)
     || (app_dlwf_pointers_info[2].type == TYPE_GUI_DRAW_POINTER_16IMAGES)
     ){
        if (app_dlwf_time_cmd_id == TABLE_ROW_TIME_POINT_HMS_360) {
            commit += app_dlwf_load_data_item(screen, TABLE_ROW_TIME_POINT_HMS_360);
        }
        else if (app_dlwf_time_cmd_id == TABLE_ROW_TIME_POINT_HMS_1S) {
            commit += app_dlwf_load_data_item(screen, TABLE_ROW_TIME_POINT_HMS_1S);
        }
        else if (app_dlwf_time_cmd_id == TABLE_ROW_TIME_POINT_HOUR) {
            commit += app_dlwf_load_data_item(screen, TABLE_ROW_TIME_POINT_HOUR);
            commit += app_dlwf_load_data_item(screen, TABLE_ROW_TIME_POINT_MIN);
            commit += app_dlwf_load_data_item(screen, TABLE_ROW_TIME_POINT_SEC);
        }

    }
    return commit;
}


unsigned int app_dlwf_is_second_ind(void)
{
    SYS_DEBUG("app_dlwf_is_second_ind(%d)", app_dlwf_pointers_info[2].type);
    if (app_dlwf_pointers_info[2].type == TYPE_GUI_DRAW_POINTER_LINE_60
     || app_dlwf_pointers_info[2].type == TYPE_GUI_DRAW_POINTER_8IMAGES
     || app_dlwf_pointers_info[2].type == TYPE_GUI_DRAW_POINTER_16IMAGES
     ){
        return 1;
    }
    return 0;
}

unsigned int app_dlwf_is_second_360(void)
{
    SYS_DEBUG("app_dlwf_is_second_360(%d)", app_dlwf_pointers_info[2].type);
    if (app_dlwf_pointers_info[2].type == TYPE_GUI_DRAW_POINTER_LINE_360) {
        return 1;
    }
    return 0;
}


unsigned int app_dlwf_update_sync_systime(const gui_screen_struct* screen)
{
    unsigned int commit = 0;
	commit += app_dlwf_load_data_item(screen, TABLE_ROW_DATE_DIGIT_MONTH_DAY);
	commit += app_dlwf_load_data_item(screen, TABLE_ROW_DATE_DIGIT_DAY_MONTH);
	commit += app_dlwf_load_data_item(screen, TABLE_ROW_DATE_DIGIT_MONTH_DAY_2);
	commit += app_dlwf_load_data_item(screen, TABLE_ROW_DATE_DIGIT_DAY_MONTH_2);
    commit += app_dlwf_update_time(screen);
    return commit;
}

