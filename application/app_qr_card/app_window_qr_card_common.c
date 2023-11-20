#include "debug_info.h"
#include "bsp_includes.h"
#include "os_mem.h"
#include "data_common.h"
#include "data_manager_qr_info.h"
#include "storage_qr_info.h"

picture_info_struct* app_qr_card_get_picture_by_type(int type)
{
    const picture_info_struct *pic =NULL;
    switch (type)
    {
    case QR_TYPE_WECHAT:
        pic = &pic_msg_wechat_info;
        break;
    case QR_TYPE_QQ:
        pic = &pic_msg_qq_info;
        break;
    case QR_TYPE_ALIPAY:
        //pic = &pic_msg_Alipay_info;
        break;
    case QR_TYPE_WHATSAPP:
        pic = &pic_msg_whatsapp_info;
        break;
    case QR_TYPE_TWITTER:
        pic = &pic_msg_twitter_info;
        break;
    case QR_TYPE_LINKEDIN:
        //pic = &pic_msg_in_info;
        break;
    case QR_TYPE_INSTAGRAM:
        pic = &pic_msg_Instagram_info;
        break;
    case QR_TYPE_FACEBOOK:
        pic = &pic_msg_facebook_info;
        break;
    case QR_TYPE_WEIBO:
        //pic = &pic_msg_weibo_info;
        break;
    case QR_TYPE_LINE:
        pic = &pic_msg_Line_info;
        break;
    case QR_TYPE_TIM:
        //pic = &pic_msg_Tim_info;
        break;
    case QR_TYPE_SNAPCHAT:
        //pic = &pic_msg_Snapchat_info;
        break;
    case QR_TYPE_VIBER:
        //pic = &pic_msg_Viber_info;
        break;
    case QR_TYPE_PAYPAL:
        //pic = &pic_msg_paypal_info;
        break;
    case QR_TYPE_OTHER:
        pic = &pic_msg_other_info;
        break;
    default:
        pic = NULL;
        break;
    }
    if (pic == NULL) {
        pic = &pic_msg_other_info;
    }

    return (picture_info_struct *)pic;
}

