#include "app_window_sound_touch_layout.h"
#include "application_config_app_info.h"

#define SETTING_SCREEN_ITEM_SOUND_Y (GUI_CONTENT_GAP_TOP)
#define SETTING_SCREEN_ITEM_TOUCH_Y (SETTING_SCREEN_ITEM_SOUND_Y + GUI_ITEM_HEIGHT + GUI_ITEM_SPACE)

static const gui_image_struct gui_sound_touch_item_bg =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = 0,
        .y = 0,
        .data = &pic_setting_list_icon_bg_2_info,
};

static const gui_image_struct gui_sound_touch_item_bg_3 =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = 0,
        .y = 0,
        .data = &pic_setting_list_icon_bg_3_info,
};

static const gui_image_struct gui_sound_touch_item_arrow =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = GUI_CONTENT_WIDTH - GUI_ITEM_GAP_RIGHT - 23,
        .y = (GUI_ITEM_HEIGHT - 46) / 2,
        .data = &pic_setting_list_hint_arrow_info,
};

static const gui_image_struct gui_sound_touch_item_status =
    {
        .id = SOUND_TOUCH_LAYOUT_ID_TOUCH_OPEN,
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = GUI_CONTENT_WIDTH - GUI_ITEM_GAP_RIGHT - 88,
        .y = (GUI_ITEM_HEIGHT - 52) / 2,
        .data = &pic_setting_list_status_open_info,
};

/**********************************touch***************************************/

const gui_font_struct gui_text_screen_touch =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .x = GUI_ITEM_GAP_LEFT,
        .y = 0,
        .width = GUI_ITEM_TITLE_AND_VALUE_FRIST_WIDTH,
        .height = GUI_ITEM_HEIGHT,
        .scroll = 1,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_VCENTER,
        .value.string_id = STRING_TACTILE_REMINDER,
};

const gui_font_struct gui_text_screen_touch_1 =
    {
        .id = SOUND_TOUCH_LAYOUT_ID_TEXT_1,
        .type = TYPE_GUI_DRAW_TEXT,
        .x = GUI_ITEM_GAP_LEFT,
        .y = 95,
        .width = GUI_ITEM_TITLE_AND_VALUE_FRIST_WIDTH,
        .height = 80,
        .scroll = 1,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_VCENTER,
        .value.string_id = STRING_DEFAULT,
};

const gui_font_struct gui_text_screen_touch_1_gray =
    {
        .id = SOUND_TOUCH_LAYOUT_ID_TEXT_1_GRAY,
        .type = TYPE_GUI_DRAW_TEXT,
        .x = GUI_ITEM_GAP_LEFT,
        .y = 95,
        .width = GUI_ITEM_TITLE_AND_VALUE_FRIST_WIDTH,
        .height = 80,
        .scroll = 1,
        .color = COLOR_RGB(128, 128, 128),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_VCENTER,
        .value.string_id = STRING_DEFAULT,
};

const gui_font_struct gui_text_screen_touch_2 =
    {
        .id = SOUND_TOUCH_LAYOUT_ID_TEXT_2,
        .type = TYPE_GUI_DRAW_TEXT,
        .x = GUI_ITEM_GAP_LEFT,
        .y = 175,
        .width = GUI_ITEM_TITLE_AND_VALUE_FRIST_WIDTH,
        .height = 80,
        .scroll = 1,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_VCENTER,
        .value.string_id = STRING_STRONG,
};

const gui_font_struct gui_text_screen_touch_2_gray =
    {
        .id = SOUND_TOUCH_LAYOUT_ID_TEXT_2_GRAY,
        .type = TYPE_GUI_DRAW_TEXT,
        .x = GUI_ITEM_GAP_LEFT,
        .y = 175,
        .width = GUI_ITEM_TITLE_AND_VALUE_FRIST_WIDTH,
        .height = 80,
        .scroll = 1,
        .color = COLOR_RGB(128, 128, 128),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_VCENTER,
        .value.string_id = STRING_STRONG,
};

static const gui_image_struct gui_sound_touch_item_checked_1 =
    {
        .id = SOUND_TOUCH_LAYOUT_ID_CHECKED_1,
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = GUI_CONTENT_WIDTH - GUI_ITEM_GAP_RIGHT - 44,
        .y = 113,
        .data = &pic_setting_list_status_checked_info,
};

static const gui_image_struct gui_sound_touch_item_checked_2 =
    {
        .id = SOUND_TOUCH_LAYOUT_ID_CHECKED_2,
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = GUI_CONTENT_WIDTH - GUI_ITEM_GAP_RIGHT - 44,
        .y = 192,
        .data = &pic_setting_list_status_checked_info,
};

static const gui_mix_struct gui_sound_touch_touch[] =
    {
        {
            .data = &gui_sound_touch_item_bg_3,
        },

        {
            .data = &gui_text_screen_touch,
        },
        {
            .data = &gui_sound_touch_item_status,
        },

        {
            .data = &gui_text_screen_touch_1,
        },
        {
            .data = &gui_text_screen_touch_1_gray,
        },
        {
            .data = &gui_sound_touch_item_checked_1,
        },

        {
            .data = &gui_text_screen_touch_2,
        },
        {
            .data = &gui_text_screen_touch_2_gray,
        },
        {
            .data = &gui_sound_touch_item_checked_2,
        },
};

/**********************************touch***************************************/

static const gui_image_struct gui_sound_touch_pic_sub =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = GUI_ITEM_GAP_LEFT,
        .y = (GUI_ITEM_HEIGHT - 46) / 2,
        .data = &pic_sound_touch_bg_small_info,
};

static const gui_image_struct gui_sound_touch_pic_add =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = GUI_CONTENT_WIDTH - GUI_ITEM_GAP_RIGHT - 63,
        .y = (GUI_ITEM_HEIGHT - 48) / 2,
        .data = &pic_sound_touch_bg_big_info,
};

static const gui_image_struct gui_sound_touch_pic_progress_bg =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = (GUI_CONTENT_WIDTH - 246) / 2 - 16,
        .y = (GUI_ITEM_HEIGHT - 18) / 2,
        .data = &pic_setting_list_icon_progress_bg_info,
};

static const gui_image_struct gui_sound_touch_pic_progress_bar =
    {
        .id = SOUND_TOUCH_LAYOUT_ID_SOUND_PROGRESS,
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = (GUI_CONTENT_WIDTH - 246) / 2 - 16,
        .y = (GUI_ITEM_HEIGHT - 18) / 2,
        .data = &pic_setting_list_icon_progress_bar_info,
};

static const gui_mix_struct gui_sound_touch_sound[] =
    {
        {
            .data = &gui_sound_touch_item_bg,
        },
        {
            .data = &gui_sound_touch_pic_sub,
        },
        {
            .data = &gui_sound_touch_pic_add,
        },
        {
            .data = &gui_sound_touch_pic_progress_bg,
        },
        {
            .data = &gui_sound_touch_pic_progress_bar,
        },
};

/*************************************************************************/

static const gui_widget_struct gui_widget_sound_touch_list[] =
    {
        {
            .id = SOUND_TOUCH_LAYOUT_ID_SOUND,
            .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
            .x = GUI_CONTENT_GAP_LEFT,
            .y = SETTING_SCREEN_ITEM_SOUND_Y,
            .width = GUI_CONTENT_WIDTH,
            .height = GUI_ITEM_HEIGHT,
            .visible = 1,
            .clip = 1,
            .child_num = countof(gui_sound_touch_sound),
            .children = gui_sound_touch_sound,
        },

        {
            .id = SOUND_TOUCH_LAYOUT_ID_TOUCH,
            .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
            .x = GUI_CONTENT_GAP_LEFT,
            .y = SETTING_SCREEN_ITEM_TOUCH_Y,
            .width = GUI_CONTENT_WIDTH,
            .height = GUI_ITEM_HEIGHT_3,
            .visible = 1,
            .clip = 1,
            .child_num = countof(gui_sound_touch_touch),
            .children = gui_sound_touch_touch,
        },
};

const gui_layout_scroll_struct gui_layout_config_sound_touch =
    {
        .height = 620,
        .scroll = 1,
};

const gui_screen_struct gui_screen_sound_touch =
    {
        .type = TYPE_GUI_LAYOUT_SCROLL,
        .children = gui_widget_sound_touch_list,
        .child_num = countof(gui_widget_sound_touch_list),
        .layout_config = &gui_layout_config_sound_touch,
};
