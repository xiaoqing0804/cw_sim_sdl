
#ifndef __DATA_MANAGER_QR_INFO_H__
#define __DATA_MANAGER_QR_INFO_H__


typedef enum
{
    QR_TYPE_NULL = 0,
    
    QR_TYPE_WECHAT,
    QR_TYPE_QQ,
    QR_TYPE_ALIPAY,
    QR_TYPE_WHATSAPP,
    QR_TYPE_TWITTER,  //5
    QR_TYPE_LINKEDIN,
    QR_TYPE_INSTAGRAM,
    QR_TYPE_FACEBOOK,
    QR_TYPE_WEIBO,
    QR_TYPE_LINE,   //10
    QR_TYPE_TIM,
    QR_TYPE_SNAPCHAT,
    QR_TYPE_VIBER,
    QR_TYPE_PAYPAL,
    QR_TYPE_OTHER ,  //15

}QR_TYPE;


extern unsigned char qr_code_data_handler(unsigned char *data, unsigned int len);

extern unsigned char qr_code_delete_handler(unsigned char *data, unsigned int len);

extern unsigned char qr_code_clear_handler(unsigned char *data, unsigned int len);

#endif


