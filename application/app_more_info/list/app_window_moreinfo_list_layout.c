//#include "app_window_moreinfo_list_layout.h"
//#include "picture.h"
//#include "language.h"
//#include "application_config_app_info.h"
//
////RUN
//static const gui_image_struct gui_pic_sport =
//{
//	.type = TYPE_GUI_DRAW_PICTURE,
//	.id = 0,
//	.x = 20,
//	.y = 0,
//	.anchor_x = 0,
//	.anchor_y = 0,
//	.data = &pic_app_sport_outdoor_60_info,
//};
//
//static const gui_font_struct gui_text_sport =
//{
//	.type = TYPE_GUI_DRAW_TEXT,
//	.id = 0,
//	.x = 95,
//    .y = 10+3,
//    .width = 150 ,
//    .anchor_x = 0,
//    .anchor_y = 0,
//    .color = COLOR_RGB(255, 255, 255),
//    .size = SYS_FONT_MEDIUM,
//    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
//    .value.string_id = STRING_SPORT,
//};
//
//
//static const gui_mix_struct gui_item_sport[] =
//{
//	{
//		.data = &gui_pic_sport
//	},
//	{
//		.data = &gui_text_sport,
//	},
//};
//
////WALK
//static const gui_image_struct gui_pic_sleep =
//{
//	.type = TYPE_GUI_DRAW_PICTURE,
//	.id = 0,
//	.x = 20,
//	.y = 0,
//	.anchor_x = 0,
//	.anchor_y = 0,
//	.data = &pic_app_sleep_60_info,
//};
//
//static const gui_font_struct gui_text_sleep =
//{
//	.type = TYPE_GUI_DRAW_TEXT,
//	.id = 0,
//	.x = 95,
//    .y = 10+3,
//     .width = 150 ,
//    .anchor_x = 0,
//    .anchor_y = 0,
//    .color = COLOR_RGB(255, 255, 255),
//    .size = SYS_FONT_MEDIUM,
//    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
//    .value.string_id = STRING_SLEEP,
//};
//
//
//static const gui_mix_struct gui_item_sleep[] =
//{
//	{
//		.data = &gui_pic_sleep,
//	},
//	{
//		.data = &gui_text_sleep,
//	},
//};
//
//
//static const gui_image_struct gui_pic_photograph =
//{
//	.type = TYPE_GUI_DRAW_PICTURE,
//	.id = 0,
//	.x = 20,
//	.y = 0,
//	.anchor_x = 0,
//	.anchor_y = 0,
//	.data = &pic_app_photograph_60_info,
//};
//
//static const gui_font_struct gui_text_photograph =
//{
//	.type = TYPE_GUI_DRAW_TEXT,
//	.id = 0,
//	.x = 95,
//    .y = 10+3,
//     .width = 150 ,
//    .anchor_x = 0,
//    .anchor_y = 0,
//    .color = COLOR_RGB(255, 255, 255),
//    .size = SYS_FONT_MEDIUM,
//    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
//    .value.string_id = STRING_PHOTOGRAPH,
//};
//
//
//static const gui_mix_struct gui_item_photograph[] =
//{
//	{
//		.data = &gui_pic_photograph,
//	},
//	{
//		.data = &gui_text_photograph,
//	},
//};
//
//
//static const gui_image_struct gui_pic_find_phone =
//{
//	.type = TYPE_GUI_DRAW_PICTURE,
//	.id = 0,
//	.x = 20,
//	.y = 0,
//	.anchor_x = 0,
//	.anchor_y = 0,
//	.data = &pic_app_findphone_60_info,
//};
//
//static const gui_font_struct gui_text_find_phone =
//{
//	.type = TYPE_GUI_DRAW_TEXT,
//	.id = 0,
//	.x = 95,
//    .y = 10+3,
//     .width = 150 ,
//    .anchor_x = 0,
//    .anchor_y = 0,
//    .color = COLOR_RGB(255, 255, 255),
//    .size = SYS_FONT_MEDIUM,
//    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
//    .value.string_id = STRING_FIND_PHONE,
//};
//
//
//static const gui_mix_struct gui_item_find_phone[] =
//{
//	{
//		.data = &gui_pic_find_phone,
//	},
//	{
//		.data = &gui_text_find_phone,
//	},
//};
//
//static const gui_image_struct gui_pic_calendar =
//{
//	.type = TYPE_GUI_DRAW_PICTURE,
//	.id = 0,
//	.x = 20,
//	.y = 0,
//	.anchor_x = 0,
//	.anchor_y = 0,
//	.data = &pic_app_calendar_60_info,
//};
//
//static const gui_font_struct gui_text_calendar =
//{
//	.type = TYPE_GUI_DRAW_TEXT,
//	.id = 0,
//	.x = 95,
//    .y = 10+3,
//     .width = 150 ,
//    .anchor_x = 0,
//    .anchor_y = 0,
//    .color = COLOR_RGB(255, 255, 255),
//    .size = SYS_FONT_MEDIUM,
//    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
//    .value.string_id = STRING_CALENDAR,
//};
//
//
//static const gui_mix_struct gui_item_calendar[] =
//{
//	{
//		.data = &gui_pic_calendar,
//	},
//	{
//		.data = &gui_text_calendar,
//	},
//};
//
//static const gui_image_struct gui_pic_O2 =
//{
//	.type = TYPE_GUI_DRAW_PICTURE,
//	.id = 0,
//	.x = 20,
//	.y = 0,
//	.anchor_x = 0,
//	.anchor_y = 0,
//	.data = &pic_app_O2_60_info,
//};
//
//static const gui_font_struct gui_text_O2 =
//{
//	.type = TYPE_GUI_DRAW_TEXT,
//	.id = 0,
//	.x = 95,
//    .y = 10+3,
//     .width = 150 ,
//    .anchor_x = 0,
//    .anchor_y = 0,
//    .color = COLOR_RGB(255, 255, 255),
//    .size = SYS_FONT_MEDIUM,
//    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
//    .value.string_id = STRING_O2,
//};
//
//
//static const gui_mix_struct gui_item_O2[] =
//{
//	{
//		.data = &gui_pic_O2,
//	},
//	{
//		.data = &gui_text_O2,
//	},
//};
//
//
//static const gui_image_struct gui_pic_stopwatch =
//{
//	.type = TYPE_GUI_DRAW_PICTURE,
//	.id = 0,
//	.x = 20,
//	.y = 0,
//	.anchor_x = 0,
//	.anchor_y = 0,
//	.data = &pic_app_stopwatch_60_info,
//};
//
//static const gui_font_struct gui_text_stopwatch =
//{
//	.type = TYPE_GUI_DRAW_TEXT,
//	.id = 0,
//	.x = 95,
//    .y = 10+3,
//     .width = 150 ,
//    .anchor_x = 0,
//    .anchor_y = 0,
//    .color = COLOR_RGB(255, 255, 255),
//    .size = SYS_FONT_MEDIUM,
//    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
//    .value.string_id = STRING_STOPWATCH,
//};
//
//
//static const gui_mix_struct gui_item_stopwatch[] =
//{
//	{
//		.data = &gui_pic_stopwatch,
//	},
//	{
//		.data = &gui_text_stopwatch,
//	},
//};
//
//static const gui_image_struct gui_pic_countdown =
//{
//	.type = TYPE_GUI_DRAW_PICTURE,
//	.id = 0,
//	.x = 20,
//	.y = 0,
//	.anchor_x = 0,
//	.anchor_y = 0,
//	.data = &pic_app_counter_60_info,
//};
//
//static const gui_font_struct gui_text_countdown =
//{
//	.type = TYPE_GUI_DRAW_TEXT,
//	.id = 0,
//	.x = 95,
//    .y = 10+3,
//     .width = 150 ,
//    .anchor_x = 0,
//    .anchor_y = 0,
//    .color = COLOR_RGB(255, 255, 255),
//    .size = SYS_FONT_MEDIUM,
//    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
//    .value.string_id = STRING_COUNTER,
//};
//
//
//static const gui_mix_struct gui_item_countdown[] =
//{
//	{
//		.data = &gui_pic_countdown,
//	},
//	{
//		.data = &gui_text_countdown,
//	},
//};
//
//
//static const gui_image_struct gui_pic_breath =
//{
//	.type = TYPE_GUI_DRAW_PICTURE,
//	.id = 0,
//	.x = 20,
//	.y = 0,
//	.anchor_x = 0,
//	.anchor_y = 0,
//	.data = &pic_app_breath_60_info,
//};
//
//static const gui_font_struct gui_text_breath =
//{
//	.type = TYPE_GUI_DRAW_TEXT,
//	.id = 0,
//	.x = 95,
//    .y = 10+3,
//    .width = 150 ,
//    .anchor_x = 0,
//    .anchor_y = 0,
//    .color = COLOR_RGB(255, 255, 255),
//    .size = SYS_FONT_MEDIUM,
//    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
//    .value.string_id = STRING_BREATH,
//};
//
//
//static const gui_mix_struct gui_item_breath[] =
//{
//	{
//		.data = &gui_pic_breath,
//	},
//	{
//		.data = &gui_text_breath,
//	},
//};
//
//
//static const gui_image_struct gui_pic_seeting =
//{
//	.type = TYPE_GUI_DRAW_PICTURE,
//	.id = 0,
//	.x = 20,
//	.y = 0,
//	.anchor_x = 0,
//	.anchor_y = 0,
//	.data = &pic_app_setting_60_info,
//};
//
//static const gui_font_struct gui_text_seeting =
//{
//	.type = TYPE_GUI_DRAW_TEXT,
//	.id = 0,
//	.x = 95,
//    .y = 10+3,
//     .width = 150 ,
//    .anchor_x = 0,
//    .anchor_y = 0,
//    .color = COLOR_RGB(255, 255, 255),
//    .size = SYS_FONT_MEDIUM,
//    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
//    .value.string_id = STRING_SETTING,
//};
//
//
//static const gui_mix_struct gui_item_seeting[] =
//{
//	{
//		.data = &gui_pic_seeting,
//	},
//	{
//		.data = &gui_text_seeting,
//	},
//};
//
//
//static const gui_image_struct gui_pic_msg =
//{
//	.type = TYPE_GUI_DRAW_PICTURE,
//	.id = 0,
//	.x = 20,
//	.y = 0,
//	.anchor_x = 0,
//	.anchor_y = 0,
//	.data = &pic_app_message_60_info,
//};
//
//static const gui_font_struct gui_text_msg =
//{
//	.type = TYPE_GUI_DRAW_TEXT,
//	.id = 0,
//	.x = 95,
//    .y = 10+3,
//     .width = 150 ,
//    .anchor_x = 0,
//    .anchor_y = 0,
//    .color = COLOR_RGB(255, 255, 255),
//    .size = SYS_FONT_MEDIUM,
//    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
//    .value.string_id = STRING_MESSAGE,
//};
//
//
//static const gui_mix_struct gui_item_msg[] =
//{
//	{
//		.data = &gui_pic_msg,
//	},
//	{
//		.data = &gui_text_msg,
//	},
//};
//
//
//static const gui_image_struct gui_pic_music =
//{
//	.type = TYPE_GUI_DRAW_PICTURE,
//	.id = 0,
//	.x = 20,
//	.y = 0,
//	.anchor_x = 0,
//	.anchor_y = 0,
//	.data = &pic_app_music_60_info,
//};
//
//static const gui_font_struct gui_text_music =
//{
//	.type = TYPE_GUI_DRAW_TEXT,
//	.id = 0,
//	.x = 95,
//    .y = 10+3,
//     .width = 150 ,
//    .anchor_x = 0,
//    .anchor_y = 0,
//    .color = COLOR_RGB(255, 255, 255),
//    .size = SYS_FONT_MEDIUM,
//    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
//    .value.string_id = STRING_MUSIC,
//};
//
//
//static const gui_mix_struct gui_item_music[] =
//{
//	{
//		.data = &gui_pic_music,
//	},
//	{
//		.data = &gui_text_music,
//	},
//};
//
//static const gui_image_struct gui_pic_contacts =
//{
//	.type = TYPE_GUI_DRAW_PICTURE,
//	.id = 0,
//	.x = 20,
//	.y = 0,
//	.anchor_x = 0,
//	.anchor_y = 0,
//	.data = &pic_app_telephone_60_info,
//};
//
//static const gui_font_struct gui_text_contacts =
//{
//	.type = TYPE_GUI_DRAW_TEXT,
//	.id = 0,
//	.x = 95,
//    .y = 10+3,
//     .width = 150 ,
//    .anchor_x = 0,
//    .anchor_y = 0,
//    .color = COLOR_RGB(255, 255, 255),
//    .size = SYS_FONT_MEDIUM,
//    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
//    .value.string_id = STRING_CONTACT,
//};
//
//
//static const gui_mix_struct gui_item_contacts[] =
//{
//	{
//		.data = &gui_pic_contacts,
//	},
//	{
//		.data = &gui_text_contacts,
//	},
//};
//
//static const gui_image_struct gui_pic_call_log =
//{
//	.type = TYPE_GUI_DRAW_PICTURE,
//	.id = 0,
//	.x = 20,
//	.y = 0,
//	.anchor_x = 0,
//	.anchor_y = 0,
//	.data = &pic_app_telephone_60_info,
//};
//
//static const gui_font_struct gui_text_call_log =
//{
//	.type = TYPE_GUI_DRAW_TEXT,
//	.id = 0,
//	.x = 95,
//    .y = 10+3,
//     .width = 150 ,
//    .anchor_x = 0,
//    .anchor_y = 0,
//    .color = COLOR_RGB(255, 255, 255),
//    .size = SYS_FONT_MEDIUM,
//    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
//    .value.string_id = STRING_ID_CALLLOG,
//};
//
//
//static const gui_mix_struct gui_item_call_log[] =
//{
//	{
//		.data = &gui_pic_call_log,
//	},
//	{
//		.data = &gui_text_call_log,
//	},
//};
//
//static const gui_widget_struct gui_widget_more_list[] =
//{
//
//	{
//		.id = APP_INFO_ID_SPORT,//  MORE_LIST_LAYOUT_ID_SPORT,
//		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
//		.x = 0,
//		.y = 0,
//		.width = 240,
//		.height = 64,
//		.rotate = 0,
//		.visible= 1,
//		.clip = 0,
//		.space_x = 0,
//		.space_y = 0,
//		.child_num = countof(gui_item_sport),
//		.children = gui_item_sport,
//	},
//	{
//		.id = APP_INFO_ID_SLEEP,
//		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
//		.x = 0,
//		.y = 0,
//		.width = 240,
//		.height = 64,
//		.rotate = 0,
//		.visible= 1,
//		.clip = 0,
//		.space_x = 0,
//		.space_y = 0,
//		.child_num = countof(gui_item_sleep),
//		.children = gui_item_sleep,
//
//	},
//
//    {
//			.id = APP_INFO_ID_PHOTO,
//			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
//			.x = 0,
//			.y = 0,
//			.width = 240,
//			.height = 64,
//			.rotate = 0,
//			.visible= 1,
//			.clip = 0,
//			.space_x = 0,
//			.space_y = 0,
//			.child_num = countof(gui_item_photograph),
//			.children = gui_item_photograph,
//    },
//
//	{
//		.id = APP_INFO_ID_FIND,
//		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
//		.x = 0,
//		.y = 0,
//		.width = 240,
//		.height = 64,
//		.rotate = 0,
//		.visible= 1,
//		.clip = 0,
//		.space_x = 0,
//		.space_y = 0,
//		.child_num = countof(gui_item_find_phone),
//		.children = gui_item_find_phone,
//	},
//
//	{
//		.id = APP_INFO_ID_O2,
//		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
//		.x = 0,
//		.y = 0,
//		.width = 240,
//		.height = 64,
//		.rotate = 0,
//		.visible= 1,
//		.clip = 0,
//		.space_x = 0,
//		.space_y = 0,
//		.child_num = countof(gui_item_O2),
//		.children = gui_item_O2,
//	},
//
//	{
//		.id = APP_INFO_ID_STOPWATCH,
//		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
//		.x = 0,
//		.y = 0,
//		.width = 240,
//		.height = 64,
//		.rotate = 0,
//		.visible= 1,
//		.clip = 0,
//		.space_x = 0,
//		.space_y = 0,
//		.child_num = countof(gui_item_stopwatch),
//		.children = gui_item_stopwatch,
//	},
//
//    {
//		.id = APP_INFO_ID_CALENDAR,
//		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
//		.x = 0,
//		.y = 0,
//		.width = 240,
//		.height = 64,
//		.rotate = 0,
//		.visible= 1,
//		.clip = 0,
//		.space_x = 0,
//		.space_y = 0,
//		.child_num = countof(gui_item_calendar),
//		.children = gui_item_calendar,
//	},
//
//	{
//		.id = APP_INFO_ID_COUNTER,
//		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
//		.x = 0,
//		.y = 0,
//		.width = 240,
//		.height = 64,
//		.rotate = 0,
//		.visible= 1,
//		.clip = 0,
//		.space_x = 0,
//		.space_y = 0,
//		.child_num = countof(gui_item_countdown),
//		.children = gui_item_countdown,
//	},
//
//
//	{
//		.id = APP_INFO_ID_BREATHE,
//		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
//		.x = 0,
//		.y = 0,
//		.width = 240,
//		.height = 64,
//		.rotate = 0,
//		.visible= 1,
//		.clip = 0,
//		.space_x = 0,
//		.space_y = 0,
//		.child_num = countof(gui_item_breath),
//		.children = gui_item_breath,
//	},
//
//	{
//		.id = APP_INFO_ID_SETTING,
//		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
//		.x = 0,
//		.y = 0,
//		.width = 240,
//		.height = 64,
//		.rotate = 0,
//		.visible= 1,
//		.clip = 0,
//		.space_x = 0,
//		.space_y = 0,
//		.child_num = countof(gui_item_seeting),
//		.children = gui_item_seeting,
//	},
//
//		{
//		.id = APP_INFO_ID_MESSAGE,
//		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
//		.x = 0,
//		.y = 0,
//		.width = 240,
//		.height = 64,
//		.rotate = 0,
//		.visible= 1,
//		.clip = 0,
//		.space_x = 0,
//		.space_y = 0,
//		.child_num = countof(gui_item_msg),
//		.children = gui_item_msg,
//	},
//
//    {
//		.id = APP_INFO_ID_MUSIC,
//		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
//		.x = 0,
//		.y = 0,
//		.width = 240,
//		.height = 64,
//		.rotate = 0,
//		.visible= 1,
//		.clip = 0,
//		.space_x = 0,
//		.space_y = 0,
//		.child_num = countof(gui_item_music),
//		.children = gui_item_music,
//	},
//
//
//    {
//		.id = APP_INFO_ID_CONTACTS,
//		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
//		.x = 0,
//		.y = 0,
//		.width = 240,
//		.height = 64,
//		.rotate = 0,
//		.visible= 1,
//		.clip = 0,
//		.space_x = 0,
//		.space_y = 0,
//		.child_num = countof(gui_item_contacts),
//		.children = gui_item_contacts,
//	},
//
//    {
//		.id = APP_INFO_ID_CALL_LOG,
//		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
//		.x = 0,
//		.y = 0,
//		.width = 240,
//		.height = 64,
//		.rotate = 0,
//		.visible= 1,
//		.clip = 0,
//		.space_x = 0,
//		.space_y = 0,
//		.child_num = countof(gui_item_call_log),
//		.children = gui_item_call_log,
//	},
//};
//
//
//const gui_layout_list_struct gui_layout_more_list =
//{
//	.row_height = 64,
//
//	.top = 15,
//	.bottom = 15,
//	.space = 8,
//    .arc_flag = 1,
//	.scroll = 1,
//};
//
//
//const gui_screen_struct gui_screen_moreinfo_list =
//{
//	.type = TYPE_GUI_LAYOUT_LIST,
//	.space_x = 0,
//	.space_y = 0,
//	.order = 0,
//	.children = gui_widget_more_list,
//	.child_num = countof(gui_widget_more_list),
//	.layout_config = &gui_layout_more_list,
//};
//
//
