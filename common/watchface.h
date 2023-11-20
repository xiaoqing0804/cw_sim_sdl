#ifndef _WATCHFACE_H
#define _WATCHFACE_H

#define CMD_MCU_RAM_EN			1

#define PICTURE_BASE_ADDR		(PIC_OFFSET + SECTOR_1_FONT_BASE)

#define WATCHFACE_SETTING_BASE_ADDR	    (SECTOR_02_WATCHFACE_SET_BASE)
#define WATCHFACE_USER_DEF_BASE_ADDR	(SECTOR_02_WATCHFACE_DEFINE_BASE)

#define FLAG_OFFSET				    (4)
#define CMD_BASE					(WATCHFACE_USER_DEF_BASE_ADDR + FLAG_OFFSET + 16)
#define PIC_BASE					(WATCHFACE_USER_DEF_BASE_ADDR + FLAG_OFFSET + 2048)
#define PIC_END					    (WATCHFACE_USER_DEF_BASE_ADDR + FLAG_OFFSET + 4096)
#define PICTURE_BASE				(WATCHFACE_USER_DEF_BASE_ADDR + FLAG_OFFSET + 4096)

typedef enum
{
    TABLE_COLUMN_CMD = 0,
    TABLE_COLUMN_POSITION,
    TABLE_COLUMN_COLOR,
    TABLE_COLUMN_PICTURE,
    TABLE_COLUMN_ACT,
    TABLE_COLUMN_CIRCLE,

    TABLE_COLUMN_SETTING,

    TABLE_COLUMN_SUM
}TABLE_COLUMN_TYPE;

typedef enum
{
	TABLE_ROW_PICTURE = 0 ,

	TABLE_ROW_TIME_DIGIT_HOUR_H ,
	TABLE_ROW_TIME_DIGIT_HOUR_L ,
	TABLE_ROW_TIME_DIGIT_MIN_H ,
	TABLE_ROW_TIME_DIGIT_MIN_L ,
	TABLE_ROW_TIME_DIGIT_AM_PM ,    // 5
	TABLE_ROW_TIME_POINT_HOUR ,
	TABLE_ROW_TIME_POINT_MIN ,
	TABLE_ROW_TIME_POINT_SEC ,
	TABLE_ROW_DATE_DIGIT_MONTH ,
	TABLE_ROW_DATE_FONT_MONTH ,     // 10
	TABLE_ROW_DATE_PIC_MONTH ,
	TABLE_ROW_DATE_DIGIT_DAY ,
	TABLE_ROW_YEAR_DIGIT ,
	TABLE_ROW_WEEK_DIGIT ,
	TABLE_ROW_WEEK_FONT ,           // 15
	TABLE_ROW_WEEK_PIC ,
	TABLE_ROW_POWER_PIC ,
	TABLE_ROW_POWER_DIGIT ,
	TABLE_ROW_BLE_PIC ,

	TABLE_ROW_STEP_DATA ,           // 20
	TABLE_ROW_STEP_CIRCLE_BAR ,
	TABLE_ROW_STEP_LINE_BAR ,
	TABLE_ROW_STEP_PIC_BAR ,
	TABLE_ROW_STEP_TARGET ,

	TABLE_ROW_DISTANCE_DATA ,       // 25
	TABLE_ROW_DISTANCE_CIRCLE_BAR ,
	TABLE_ROW_DISTANCE_LINE_BAR ,
	TABLE_ROW_DISTANCE_PIC_BAR ,
	TABLE_ROW_DISTANCE_TARGET ,

	TABLE_ROW_CALORIE_DATA ,        // 30
	TABLE_ROW_CALORIE_CIRCLE_BAR ,
	TABLE_ROW_CALORIE_LINE_BAR ,
	TABLE_ROW_CALORIE_PIC_BAR ,
	TABLE_ROW_CALORIE_TARGET ,

	TABLE_ROW_HEART_DATA ,          // 35
	TABLE_ROW_HEART_CIRCLE_BAR ,
	TABLE_ROW_HEART_LINE_BAR ,
	TABLE_ROW_HEART_PIC_BAR ,
	TABLE_ROW_HEART_TARGET ,

	TABLE_ROW_RECTANGLE ,           // 40
	TABLE_ROW_CIRCLE ,

	TABLE_ROW_TIME_DIGIT_HOUR_MIN_POINT,
	TABLE_ROW_TIME_DIGIT_HOUR,
	TABLE_ROW_TIME_DIGIT_MIN,
	TABLE_ROW_DATE_DIGIT_MONTH_DAY,     // 45
	TABLE_ROW_DATE_DIGIT_DAY_MONTH,
	TABLE_ROW_TIME_POINT_HMS_360,
	TABLE_ROW_DATE_DIGIT_MONTH_DAY_2,
	TABLE_ROW_DATE_DIGIT_DAY_MONTH_2,
	TABLE_ROW_TIME_POINT_HMS_1S,        // 50
	TABLE_ROW_DATE_PIC_DAY,

	TABLE_ROW_SUM,

    TABLE_ROW_ANI,
}TABLE_ROW_TYPE;

typedef enum
{
	POS_DIR_NULL = 0,
	POS_DIR_LEFT,
	POS_DIR_CENTER,
	POS_DIR_RIGHT,
	POS_DIR_CIRCLE,
	POS_DIR_RECTANGLE,
	POS_DIR_POINTER,
}POS_DIR_TYPE;


typedef struct
{
	unsigned char *addr;
	unsigned short width;
	unsigned short height;
	unsigned char alpha;//0: no alpha, 1: has alpha(.alpha), 2: point display(.point), 3: 8bit(256 color), 4: alpha point(.pAA), 5: zip without alpha(.pz), 6: zip with alpha(pAz), 7: xy divide no alpha(.x1y1), 8: XY dividy with alpha(.X1Y1).
	unsigned char external_flag;//0: mcu flash, 1: external spi flash or emmc.
}ram_picture_info_struct;

// 32Bytes
typedef struct
{
	unsigned char id; //命令ID

	unsigned char pos_dir; //1: 左对齐，2：居中，3：右对齐，4：圆心，5：矩形左顶点, see POS_DIR_TYPE.
	unsigned char pos_x[2]; //X轴坐标，考虑到以后可能会用320x320的屏，所以这里用两字节
	unsigned char pos_y[2]; //Y轴坐标，考虑到以后可能会用320x320的屏，所以这里用两字节

	unsigned char r; //颜色值R
	unsigned char g; //颜色值G
	unsigned char b; //颜色值B

	unsigned char pic_type; //图片类型
	unsigned char pic_num; //图标数字，ascii必须对应0~127，128以后的对应小图标
	unsigned char pic_x_interval; //图标X轴的间隔

	unsigned char period[2]; //动画周期(ms)
	unsigned char act_num; //动画图片总数
	unsigned char act_pic[10];  // 20220808 Taylor.Le, [5][2]; //动画图片条目，每个条目占两个字节(类型+数字)

	unsigned char line_width; //线条厚度
	unsigned char line_size[2];  //线的长度，对于圆是半径，对于直线则是矩形高度
	unsigned char start_pos[2]; //线条起点，对于圆则是角度0~720
	unsigned char end_pos[2]; //线条终点，对于圆则是角度0~720
}cmd_struct;

typedef struct
{
    unsigned char id[2]; //[0]:type, [1]:num.
    unsigned char width[2];
    unsigned char height[2];
    unsigned char offset[3];
    unsigned char depth;
}pic_struct;

typedef struct
{
	unsigned char time_pos; // 0: 时间在上方，1：时间在下方
	unsigned char time_up; // bit0: 日期，bit1：睡眠，bit2：心率，bit3：计步
	unsigned char time_down; // bit0: 日期，bit1：睡眠，bit2：心率，bit3：计步
	unsigned char color[2]; // 文字颜色
	unsigned char picture; // 0: 默认背影图片，1：系统背影图片, 2：自定义背影图片
	unsigned char pic_data[4]; //自定义图片的数据，若是默认图片则不无此
							//数据，格式为: width[2] + height[2] + pixel[2]….
							//每个像素点占两字节
}watchface_setting_struct;


extern watchface_setting_struct g_watchface_setting_info;

extern unsigned char watchface_setting_flag_check(void);
extern unsigned char watchface_user_define_flag_check(void);

extern void watchface_data_get(unsigned int addr, unsigned char *data, unsigned int len);
extern void watchface_get_pic_info(unsigned char pic_type, unsigned char pic_num, pic_struct *info);




#endif //_WATCHFACE_H


