#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "font_convert.h"
#include "os_mem.h"

#include "app_task_main.h"
#include "data_common.h"
#include "data_manager.h"
#include "data_manager_flash.h"
#include "data_manager_message.h"

picture_info_struct* app_message_get_picture_by_type(int type)
{
    const picture_info_struct* pic;

    if(type == MESSAGE_TYPE_FACEBOOK)
        pic = &pic_msg_facebook_info;
    else if(type == MESSAGE_TYPE_LINE)
        pic = &pic_msg_Line_info;
    else if(type == MESSAGE_TYPE_MESSAGE)
        pic = &pic_msg_message_info;
    else if(type == MESSAGE_TYPE_SKYPE)
        pic = &pic_msg_Skype_info;
    else if(type == MESSAGE_TYPE_TWITTER)
        pic = &pic_msg_twitter_info;
    else if(type == MESSAGE_TYPE_WHATSAPP)
        pic = &pic_msg_whatsapp_info;
    else if(type == MESSAGE_TYPE_WECHAT)
        pic = &pic_msg_wechat_info;
    else if(type == MESSAGE_TYPE_QQ)
        pic = &pic_msg_qq_info;
    else if(type == MESSAGE_TYPE_MAIL)
        pic = &pic_msg_mail_info;
    else if(type == MESSAGE_TYPE_INSTAGRAM)
        pic = &pic_msg_Instagram_info;
    else if(type == MESSAGE_TYPE_LINKED_IN)
        pic = &pic_msg_Linkedin_info;
    else if(type == MESSAGE_TYPE_KAKAO)
        pic = &pic_msg_kakaotalk_info;
    else if(type == MESSAGE_TYPE_TELEGRAM)
        pic = &pic_msg_telegram_info;
    else
        pic = &pic_msg_other_info;

    return (picture_info_struct*)pic;
}


