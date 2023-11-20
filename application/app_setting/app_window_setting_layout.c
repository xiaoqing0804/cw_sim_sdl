#include "app_window_setting_layout.h"

#define SETTING_LIST_LEFT (GUI_CONTENT_GAP_LEFT)
#define SETTING_LIST_TOP (GUI_CONTENT_GAP_TOP)
#define SETTING_LIST_BOTTOM (GUI_CONTENT_GAP_BOTTOM)
#define SETTING_LIST_WIDTH (GUI_CONTENT_WIDTH)

/***************FRIST AREA****************/

#define SETTING_FRIST_AREA_START_ID (SETTING_LAYOUT_ID_PERSONNAL)
#define SETTING_FRIST_AREA_END_ID (SETTING_LAYOUT_ID_PERSONNAL)

#define SETTING_FRIST_AREA_ITEM_HEIGHT (GUI_ITEM_HEIGHT_WITH_INFO)
#define SETTING_FRIST_AREA_ITEM_GAP (GUI_ITEM_SPACE)
#define SETTING_FRIST_AREA_ROW_HEIGHT (SETTING_FRIST_AREA_ITEM_HEIGHT + SETTING_FRIST_AREA_ITEM_GAP)

#define SETTING_FRIST_AREA_ITEM_ICON_X (GUI_ITEM_PIC_AND_TXT_FRIST_WIDTH)
#define SETTING_FRIST_AREA_ITEM_ICON_Y (22)
#define SETTING_FRIST_AREA_ITEM_TEXT_X (133)
#define SETTING_FRIST_AREA_ITEM_TEXT_WIDTH (300)

#define SETTING_FRIST_AREA_TOP (SETTING_LIST_TOP)
#define SETTING_FRIST_AREA_ITEM_Y(id) (SETTING_FRIST_AREA_TOP + ((id)-SETTING_FRIST_AREA_START_ID) * (SETTING_FRIST_AREA_ROW_HEIGHT))
#define SETTING_FRIST_AREA_BOTTOM (SETTING_FRIST_AREA_ITEM_Y(SETTING_FRIST_AREA_END_ID) + SETTING_FRIST_AREA_ITEM_HEIGHT + SETTING_FRIST_AREA_ITEM_GAP)

#define SETTING_FRIST_TO_SECOND_GAP (12)

/***************SECOND AREA****************/

#define SETTING_SECOND_AREA_START_ID (SETTING_LAYOUT_ID_NOTICE)
#define SETTING_SECOND_AREA_END_ID (SETTING_LAYOUT_ID_BATTRY)

#define SETTING_SECOND_AREA_ITEM_HEIGHT (GUI_ITEM_HEIGHT)
#define SETTING_SECOND_AREA_ITEM_GAP (GUI_ITEM_SPACE)
#define SETTING_SECOND_AREA_ROW_HEIGHT (SETTING_SECOND_AREA_ITEM_HEIGHT + SETTING_SECOND_AREA_ITEM_GAP)

#define SETTING_SECOND_AREA_ITEM_ICON_X (GUI_ITEM_PIC_AND_TXT_FRIST_WIDTH)
#define SETTING_SECOND_AREA_ITEM_ICON_Y (22)
#define SETTING_SECOND_AREA_ITEM_TEXT_X (GUI_ITEM_PIC_AND_TXT_SECOND_WIDTH)
#define SETTING_SECOND_AREA_ITEM_TEXT_WIDTH (330)

#define SETTING_SECOND_AREA_TOP (SETTING_FRIST_AREA_BOTTOM + SETTING_FRIST_TO_SECOND_GAP)
#define SETTING_SECOND_AREA_ITEM_Y(id) (SETTING_SECOND_AREA_TOP + ((id)-SETTING_SECOND_AREA_START_ID) * (SETTING_SECOND_AREA_ROW_HEIGHT))
#define SETTING_SECOND_AREA_BOTTOM (SETTING_SECOND_AREA_ITEM_Y(SETTING_SECOND_AREA_END_ID) + SETTING_SECOND_AREA_ITEM_HEIGHT + SETTING_LIST_BOTTOM)

/**************************个人信息********************************/

static const gui_image_struct gui_widget_setting_personnal_bg =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = 0,
        .y = 0,
        .data = &pic_setting_list_icon_bg_1_info,
};

static const gui_image_struct gui_widget_setting_personnal_icon =
    {
        .id = SETTING_LAYOUT_ID_PERSONNAL_ICON,
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = SETTING_FRIST_AREA_ITEM_ICON_X,
        .y = SETTING_FRIST_AREA_ITEM_ICON_Y,
        .data = &pic_setting_list_icon_personal_info,
};

static const gui_font_struct gui_widget_setting_personnal_title =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .x = SETTING_FRIST_AREA_ITEM_TEXT_X,
        .y = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .width = SETTING_FRIST_AREA_ITEM_TEXT_WIDTH,
        .height = SETTING_FRIST_AREA_ITEM_HEIGHT,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_VCENTER,
        .value.string_id = STRING_PERSONAL_INFORMATION,
};

static const gui_mix_struct gui_widget_setting_personnal[] =
    {
        {
            .data = &gui_widget_setting_personnal_bg,
        },
        {
            .data = &gui_widget_setting_personnal_icon,
        },
        {
            .data = &gui_widget_setting_personnal_title,
        },
};

/**************************通知********************************/

static const gui_image_struct gui_text_setting_notice_bg =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = 0,
        .y = 0,
        .data = &pic_setting_list_icon_bg_2_info,
};

static const gui_image_struct gui_text_setting_notice_icon =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = SETTING_SECOND_AREA_ITEM_ICON_X,
        .y = SETTING_SECOND_AREA_ITEM_ICON_Y,
        .data = &pic_setting_list_icon_notice_info,
};

static const gui_font_struct gui_text_setting_notice_title =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .x = SETTING_SECOND_AREA_ITEM_TEXT_X,
        .y = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .width = SETTING_SECOND_AREA_ITEM_TEXT_WIDTH,
        .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_VCENTER,
        .value.string_id = STRING_NOTICE,
};

static const gui_mix_struct gui_widget_setting_notice[] =
    {
        {
            .data = &gui_text_setting_notice_bg,
        },
        {
            .data = &gui_text_setting_notice_icon,
        },
        {
            .data = &gui_text_setting_notice_title,
        },
};
/**************************通用设置********************************/
static const gui_image_struct gui_setting_general_bg =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = 0,
        .y = 0,
        .data = &pic_setting_list_icon_bg_2_info,
};

static const gui_image_struct gui_text_setting_general_icon =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = SETTING_SECOND_AREA_ITEM_ICON_X,
        .y = SETTING_SECOND_AREA_ITEM_ICON_Y,
        .data = &pic_setting_list_icon_setting_info,
};

static const gui_font_struct gui_setting_general_text_value =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .x = SETTING_SECOND_AREA_ITEM_TEXT_X,
        .y = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .width = SETTING_SECOND_AREA_ITEM_TEXT_WIDTH,
        .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_VCENTER,
        .value.string_id = STRING_GENERAL,
};

static const gui_mix_struct gui_widget_setting_common[] =
    {
        {
            .data = &gui_setting_general_bg,
        },
        {
            .data = &gui_text_setting_general_icon,
        },
        {
            .data = &gui_setting_general_text_value,
        },
};
/**************************勿扰模式********************************/
static const gui_image_struct gui_setting_weight_bmi =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = 0,
        .y = 0,
        .data = &pic_setting_list_icon_bg_2_info,
};

static const gui_image_struct gui_personnal_bmi_text_name =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = SETTING_SECOND_AREA_ITEM_ICON_X,
        .y = SETTING_SECOND_AREA_ITEM_ICON_Y,
        .data = &pic_setting_list_icon_disturb_info,
};

static const gui_font_struct gui_personnal_bmi_text_value =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .x = SETTING_SECOND_AREA_ITEM_TEXT_X,
        .y = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .width = SETTING_SECOND_AREA_ITEM_TEXT_WIDTH,
        .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_VCENTER,
        .value.string_id = STRING_DISTURB,
};

static const gui_mix_struct gui_widget_setting_disturb[] =
    {
        {
            .data = &gui_setting_weight_bmi,
        },
        {
            .data = &gui_personnal_bmi_text_name,
        },
        {
            .data = &gui_personnal_bmi_text_value,
        },
};
/**************************屏幕设置********************************/
static const gui_image_struct gui_bg_app_screen_set =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = 0,
        .y = 0,
        .data = &pic_setting_list_icon_bg_2_info,
};

static const gui_image_struct gui_appic_screen_set =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = SETTING_SECOND_AREA_ITEM_ICON_X,
        .y = SETTING_SECOND_AREA_ITEM_ICON_Y,
        .data = &pic_setting_list_icon_screen_info,
};

static const gui_font_struct gui_app_text_screen_set =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .x = SETTING_SECOND_AREA_ITEM_TEXT_X,
        .y = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .width = SETTING_SECOND_AREA_ITEM_TEXT_WIDTH,
        .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_VCENTER,
        .value.string_id = STRING_SCREEN_SET,
};

static const gui_mix_struct gui_widget_setting_screen[] =
    {
        {
            .data = &gui_bg_app_screen_set,
        },
        {
            .data = &gui_appic_screen_set,
        },
        {
            .data = &gui_app_text_screen_set,
        },
};
/**************************APP视图********************************/

static const gui_image_struct gui_widget_app_view_bg =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = 0,
        .y = 0,
        .data = &pic_setting_list_icon_bg_2_info,
};

static const gui_image_struct gui_appic_app_view_icon =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = SETTING_SECOND_AREA_ITEM_ICON_X,
        .y = SETTING_SECOND_AREA_ITEM_ICON_Y,
        .data = &pic_setting_list_icon_app_view_info,
};

static const gui_font_struct gui_app_text_app_view_title =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .x = SETTING_SECOND_AREA_ITEM_TEXT_X,
        .y = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .width = SETTING_SECOND_AREA_ITEM_TEXT_WIDTH,
        .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_VCENTER,
        .value.string_id = STRING_APP_VIEW,
};

static const gui_mix_struct gui_widget_app_view[] =
    {
        {
            .data = &gui_widget_app_view_bg,
        },
        {
            .data = &gui_appic_app_view_icon,
        },
        {
            .data = &gui_app_text_app_view_title,
        },
};

/**************************按键设置********************************/
#if !GUI_SINGLE_KEY_SUPPORT
static const gui_image_struct gui_bg_key_setting =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = 0,
        .y = 0,
        .data = &pic_setting_list_icon_bg_2_info,
};

static const gui_image_struct gui_appic_key_setting =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = SETTING_SECOND_AREA_ITEM_ICON_X,
        .y = SETTING_SECOND_AREA_ITEM_ICON_Y,
        .data = &pic_setting_list_icon_key_setting_info,
};

static const gui_font_struct gui_app_text_key_setting =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .x = SETTING_SECOND_AREA_ITEM_TEXT_X,
        .y = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .width = SETTING_SECOND_AREA_ITEM_TEXT_WIDTH,
        .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_VCENTER,
        .value.string_id = STRING_KEY_SETTING,
};

static const gui_mix_struct gui_widget_setting_key[] =
    {
        {
            .data = &gui_bg_key_setting,
        },
        {
            .data = &gui_appic_key_setting,
        },
        {
            .data = &gui_app_text_key_setting,
        },
};
#endif
/**************************声音和触摸********************************/

static const gui_image_struct gui_bg_sound_touch_bg =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = 0,
        .y = 0,
        .data = &pic_setting_list_icon_bg_2_info,
};

static const gui_image_struct gui_appic_sound_touch =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = SETTING_SECOND_AREA_ITEM_ICON_X,
        .y = SETTING_SECOND_AREA_ITEM_ICON_Y,
        .data = &pic_setting_list_icon_sound_and_touch_info,
};

static const gui_font_struct gui_text_app_sound_touch =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .x = SETTING_SECOND_AREA_ITEM_TEXT_X,
        .y = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .width = SETTING_SECOND_AREA_ITEM_TEXT_WIDTH,
        .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_VCENTER,
        .value.string_id = STRING_SOUND_AND_TOUCH,
};

static const gui_mix_struct gui_widget_setting_sound_touch[] =
    {
        {
            .data = &gui_bg_sound_touch_bg,
        },
        {
            .data = &gui_appic_sound_touch,
        },
        {
            .data = &gui_text_app_sound_touch,
        },
};
/**************************密码********************************/

static const gui_image_struct gui_bg_password =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = 0,
        .y = 0,
        .data = &pic_setting_list_icon_bg_2_info,
};

static const gui_image_struct gui_appic_password =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = SETTING_SECOND_AREA_ITEM_ICON_X,
        .y = SETTING_SECOND_AREA_ITEM_ICON_Y,
        .data = &pic_setting_list_icon_password_info,
};

static const gui_font_struct gui_app_text_password =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .x = SETTING_SECOND_AREA_ITEM_TEXT_X,
        .y = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .width = SETTING_SECOND_AREA_ITEM_TEXT_WIDTH,
        .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_VCENTER,
        .value.string_id = STRING_PASSWORD,
};

static const gui_mix_struct gui_widget_setting_password[] =
    {
        {
            .data = &gui_bg_password,
        },
        {
            .data = &gui_appic_password,
        },
        {
            .data = &gui_app_text_password,
        },
};

/**************************sos********************************/

static const gui_image_struct gui_bg_sos_ =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = 0,
        .y = 0,
        .data = &pic_setting_list_icon_bg_2_info,
};

static const gui_image_struct gui_appic_sos_icon =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = SETTING_SECOND_AREA_ITEM_ICON_X,
        .y = SETTING_SECOND_AREA_ITEM_ICON_Y,
        .data = &pic_setting_list_icon_sos_info,
};

static const gui_font_struct gui_app_text_sos_title =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .x = SETTING_SECOND_AREA_ITEM_TEXT_X,
        .y = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .width = SETTING_SECOND_AREA_ITEM_TEXT_WIDTH,
        .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_VCENTER,
        .value.string_id = STRING_SOS,
};

static const gui_mix_struct gui_widget_setting_sos[] =
    {
        {
            .data = &gui_bg_sos_,
        },
        {
            .data = &gui_appic_sos_icon,
        },
        {
            .data = &gui_app_text_sos_title,
        },
};
/**************************电池********************************/

static const gui_image_struct gui_widget_setting_battry_bg =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = 0,
        .y = 0,
        .data = &pic_setting_list_icon_bg_2_info,
};

static const gui_image_struct gui_appic_battry_icon =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = SETTING_SECOND_AREA_ITEM_ICON_X,
        .y = SETTING_SECOND_AREA_ITEM_ICON_Y,
        .data = &pic_setting_list_icon_battry_info,
};

static const gui_font_struct gui_app_text_battry_title =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .x = SETTING_SECOND_AREA_ITEM_TEXT_X,
        .y = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .width = SETTING_SECOND_AREA_ITEM_TEXT_WIDTH,
        .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_VCENTER,
        .value.string_id = STRING_BATTRY,
};

static const gui_mix_struct gui_widget_setting_battry[] =
    {
        {
            .data = &gui_widget_setting_battry_bg,
        },
        {
            .data = &gui_appic_battry_icon,
        },
        {
            .data = &gui_app_text_battry_title,
        },
};

/**************************睡眠********************************/
static const gui_image_struct gui_bg_sleep =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = 0,
        .y = 0,
        .data = &pic_setting_list_icon_bg_2_info,
};

static const gui_image_struct gui_appic_sleep =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = SETTING_SECOND_AREA_ITEM_ICON_X,
        .y = SETTING_SECOND_AREA_ITEM_ICON_Y,
        .data = &pic_setting_list_icon_sleep_info,
};

static const gui_font_struct gui_app_text_app_sleep =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .x = SETTING_SECOND_AREA_ITEM_TEXT_X,
        .y = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .width = SETTING_SECOND_AREA_ITEM_TEXT_WIDTH,
        .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_VCENTER,
        .value.string_id = STRING_SLEEP,
};

static const gui_mix_struct gui_widget_setting_sleep[] =
    {
        {
            .data = &gui_bg_sleep,
        },
        {
            .data = &gui_appic_sleep,
        },
        {
            .data = &gui_app_text_app_sleep,
        },
};

/**************************运动********************************/

static const gui_image_struct gui_bg_sport =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = 0,
        .y = 0,
        .data = &pic_setting_list_icon_bg_2_info,
};

static const gui_image_struct gui_appic_app_sport =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = SETTING_SECOND_AREA_ITEM_ICON_X,
        .y = SETTING_SECOND_AREA_ITEM_ICON_Y,
        .data = &pic_setting_list_icon_sport_info,
};

static const gui_font_struct gui_app_text_app_sport =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .x = SETTING_SECOND_AREA_ITEM_TEXT_X,
        .y = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .width = SETTING_SECOND_AREA_ITEM_TEXT_WIDTH,
        .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_VCENTER,
        .value.string_id = STRING_SPORT,
};

static const gui_mix_struct gui_widget_setting_sport[] =
    {
        {
            .data = &gui_bg_sport,
        },
        {
            .data = &gui_appic_app_sport,
        },
        {
            .data = &gui_app_text_app_sport,
        },
};

/**********************************************************/

static const gui_widget_struct gui_widget_setting[] =
    {
        // 个人信息
        {
            .id = SETTING_LAYOUT_ID_PERSONNAL,
            .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
            .x = SETTING_LIST_LEFT,
            .y = SETTING_FRIST_AREA_ITEM_Y(SETTING_LAYOUT_ID_PERSONNAL),
            .width = SETTING_LIST_WIDTH,
            .height = SETTING_FRIST_AREA_ITEM_HEIGHT,
            .visible = 1,
            .clip = 1,
            .child_num = countof(gui_widget_setting_personnal),
            .children = gui_widget_setting_personnal,
        },
        // 通知
        {
            .id = SETTING_LAYOUT_ID_NOTICE,
            .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
            .x = SETTING_LIST_LEFT,
            .y = SETTING_SECOND_AREA_ITEM_Y(SETTING_LAYOUT_ID_NOTICE),
            .width = SETTING_LIST_WIDTH,
            .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
            .visible = 1,
            .clip = 1,
            .child_num = countof(gui_widget_setting_notice),
            .children = gui_widget_setting_notice,
        },
        // 通用设置
        {
            .id = SETTING_LAYOUT_ID_SETTING,
            .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
            .x = SETTING_LIST_LEFT,
            .y = SETTING_SECOND_AREA_ITEM_Y(SETTING_LAYOUT_ID_SETTING),
            .width = SETTING_LIST_WIDTH,
            .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
            .visible = 1,
            .clip = 1,
            .child_num = countof(gui_widget_setting_common),
            .children = gui_widget_setting_common,
        },
        // 勿扰模式
        {
            .id = SETTING_LAYOUT_ID_DISTURB,
            .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
            .x = SETTING_LIST_LEFT,
            .y = SETTING_SECOND_AREA_ITEM_Y(SETTING_LAYOUT_ID_DISTURB),
            .width = SETTING_LIST_WIDTH,
            .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
            .visible = 1,
            .clip = 1,
            .child_num = countof(gui_widget_setting_disturb),
            .children = gui_widget_setting_disturb,
        },
        // 屏幕设置
        {
            .id = SETTING_LAYOUT_ID_SCREEN,
            .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
            .x = SETTING_LIST_LEFT,
            .y = SETTING_SECOND_AREA_ITEM_Y(SETTING_LAYOUT_ID_SCREEN),
            .width = SETTING_LIST_WIDTH,
            .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
            .visible = 1,
            .clip = 1,
            .child_num = countof(gui_widget_setting_screen),
            .children = gui_widget_setting_screen,
        },
        // app视图
        {
            .id = SETTING_LAYOUT_ID_APP_VIEW,
            .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
            .x = SETTING_LIST_LEFT,
            .y = SETTING_SECOND_AREA_ITEM_Y(SETTING_LAYOUT_ID_APP_VIEW),
            .width = SETTING_LIST_WIDTH,
            .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
            .visible = 1,
            .clip = 1,
            .child_num = countof(gui_widget_app_view),
            .children = gui_widget_app_view,
        },
        // 按键设置
        #if !GUI_SINGLE_KEY_SUPPORT
        {
            .id = SETTING_LAYOUT_ID_KEY_SETTING,
            .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
            .x = SETTING_LIST_LEFT,
            .y = SETTING_SECOND_AREA_ITEM_Y(SETTING_LAYOUT_ID_KEY_SETTING),
            .width = SETTING_LIST_WIDTH,
            .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
            .visible = 1,
            .clip = 1,
            .child_num = countof(gui_widget_setting_key),
            .children = gui_widget_setting_key,
        },
        #endif
        // 声音和触摸
        {
            .id = SETTING_LAYOUT_ID_SOUND_AND_TOUCH,
            .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
            .x = SETTING_LIST_LEFT,
            .y = SETTING_SECOND_AREA_ITEM_Y(SETTING_LAYOUT_ID_SOUND_AND_TOUCH),
            .width = SETTING_LIST_WIDTH,
            .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
            .visible = 1,
            .clip = 1,
            .child_num = countof(gui_widget_setting_sound_touch),
            .children = gui_widget_setting_sound_touch,
        },
        // 密码
        {
            .id = SETTING_LAYOUT_ID_PASSWORD,
            .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
            .x = SETTING_LIST_LEFT,
            .y = SETTING_SECOND_AREA_ITEM_Y(SETTING_LAYOUT_ID_PASSWORD),
            .width = SETTING_LIST_WIDTH,
            .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
            .visible = 1,
            .clip = 1,
            .child_num = countof(gui_widget_setting_password),
            .children = gui_widget_setting_password,
        },
        // sos
        {
            .id = SETTING_LAYOUT_ID_SOS,
            .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
            .x = SETTING_LIST_LEFT,
            .y = SETTING_SECOND_AREA_ITEM_Y(SETTING_LAYOUT_ID_SOS),
            .width = SETTING_LIST_WIDTH,
            .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
            .visible = 1,
            .clip = 1,
            .child_num = countof(gui_widget_setting_sos),
            .children = gui_widget_setting_sos,
        },
        // 电池
        {
            .id = SETTING_LAYOUT_ID_BATTRY,
            .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
            .x = SETTING_LIST_LEFT,
            .y = SETTING_SECOND_AREA_ITEM_Y(SETTING_LAYOUT_ID_BATTRY),
            .width = SETTING_LIST_WIDTH,
            .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
            .visible = 1,
            .clip = 1,
            .child_num = countof(gui_widget_setting_battry),
            .children = gui_widget_setting_battry,
        },
        /*
        // 睡眠
        {
            .id = SETTING_LAYOUT_ID_SLEEP,
            .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
            .x = SETTING_LIST_LEFT,
            .y = SETTING_SECOND_AREA_ITEM_Y(SETTING_LAYOUT_ID_SLEEP),
            .width = SETTING_LIST_WIDTH,
            .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
            .visible = 1,
            .clip = 1,
            .child_num = countof(gui_widget_setting_sleep),
            .children = gui_widget_setting_sleep,
        },
        // 运动模式
        {
            .id = SETTING_LAYOUT_ID_SPORT,
            .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
            .x = SETTING_LIST_LEFT,
            .y = SETTING_SECOND_AREA_ITEM_Y(SETTING_LAYOUT_ID_SPORT),
            .width = SETTING_LIST_WIDTH,
            .height = SETTING_SECOND_AREA_ITEM_HEIGHT,
            .visible = 1,
            .clip = 1,
            .child_num = countof(gui_widget_setting_sport),
            .children = gui_widget_setting_sport,
        },
        */

};

const gui_layout_scroll_struct gui_layout_scroll_setting =
    {
        .height = SETTING_SECOND_AREA_BOTTOM,
        .scroll = 1,
};

const gui_screen_struct gui_screen_setting =
    {
        .type = TYPE_GUI_LAYOUT_SCROLL,
        .children = gui_widget_setting,
        .child_num = countof(gui_widget_setting),
        .layout_config = (const void *)&gui_layout_scroll_setting,
};
