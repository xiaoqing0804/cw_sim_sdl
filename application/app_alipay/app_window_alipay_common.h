#ifndef __APP_WND_ALIPAY_COMMON_H__
#define __APP_WND_ALIPAY_COMMON_H__

#include "sys_init.h"
#include "bsp_includes.h"
#include "feature_all.h"


// title text -------------------------------------------------------------------------------
#if (LCD_SIZE_WIDTH == 412)
#define ALIPAY_TITLE_TEXT_Y_POS  37
#define ALIPAY_TITLE_TEXT_H      40

#elif (LCD_SIZE_WIDTH == 466)
#define ALIPAY_TITLE_TEXT_Y_POS  37
#define ALIPAY_TITLE_TEXT_H      40

#else

#endif

// binding-ani -------------------------------------------------------------------------------
#if (LCD_SIZE_WIDTH == 412)
#define ALIPAY_ANI_SIZE  126

#elif (LCD_SIZE_WIDTH == 466)
#define ALIPAY_ANI_SIZE  142

#else

#endif



// info text -------------------------------------------------------------------------------
#if (LCD_SIZE_WIDTH == 412)
#define ALIPAY_INFO_TEXT_X_POS  29
#define ALIPAY_INFO_TEXT_Y_POS  100
#define ALIPAY_INFO_TEXT_H      188

#elif (LCD_SIZE_WIDTH == 466)
#define ALIPAY_INFO_TEXT_X_POS  29
#define ALIPAY_INFO_TEXT_Y_POS  100
#define ALIPAY_INFO_TEXT_H      188

#else

#endif


// op1 - bar -------------------------------------------------------------------------------
#if (LCD_SIZE_WIDTH == 412)
#define ALIPAY_OP1_BAR_Y_POS    300
#define ALIPAY_OP1_BAR_W        192
#define ALIPAY_OP1_BAR_H        66

#elif (LCD_SIZE_WIDTH == 466)
#define ALIPAY_OP1_BAR_Y_POS    316
#define ALIPAY_OP1_BAR_W        217
#define ALIPAY_OP1_BAR_H        75
#else

#endif

// op2 - bar -------------------------------------------------------------------------------
#if (LCD_SIZE_WIDTH == 412)
#define ALIPAY_OP2_BAR_Y_POS        300
#define ALIPAY_OP2_BAR_GAP      12
#define ALIPAY_OP2_BAR_W        145
#define ALIPAY_OP2_BAR_H        69

#elif (LCD_SIZE_WIDTH == 466)
#define ALIPAY_OP2_BAR_Y_POS        316
#define ALIPAY_OP2_BAR_GAP      14
#define ALIPAY_OP2_BAR_W        164
#define ALIPAY_OP2_BAR_H        78
#else

#endif


// pay-code ---------------------------------------------------------------------------------------
#define ALIPAY_ROUND_PEN_SIZE   5
#define ALIPAY_ROUND_R0         12
#define ALIPAY_COLOR_BG     COLOR_RGB(0, 100, 255)


#if (LCD_SIZE_WIDTH == 412)
#define PAYCODE_SWT_TEXT_Y          397
#define PAYCODE_SWT_DOT_Y           14
#define PAYCODE_SWT_DOT_R           7
#elif (LCD_SIZE_WIDTH == 466)
#define PAYCODE_SWT_TEXT_Y          397
#define PAYCODE_SWT_DOT_Y           14
#define PAYCODE_SWT_DOT_R           7
#else
#endif

// qr-code -------------------------------------------------------------------------------
#if (LCD_SHAPE == LCD_CIRCLE)
#if (LCD_SIZE_WIDTH == 320)
#define QRCODE_TITLE_TEXT_Y        29
#define QRCODE_TITLE_TEXT_H        30
#define QRCODE_MARGIN       15
#define QRCODE_Y_POS        78
#define QRCODE_SIZE         200

#elif (LCD_SIZE_WIDTH == 360)
#define QRCODE_TITLE_TEXT_Y        29
#define QRCODE_TITLE_TEXT_H        30
#define QRCODE_MARGIN       15
#define QRCODE_Y_POS        80
#define QRCODE_SIZE         220

#elif (LCD_SIZE_WIDTH == 390)
#define QRCODE_TITLE_TEXT_Y        29
#define QRCODE_TITLE_TEXT_H        30
#define QRCODE_MARGIN       15
#define QRCODE_Y_POS        90
#define QRCODE_SIZE         240

#elif (LCD_SIZE_WIDTH == 412)
#define QRCODE_TITLE_TEXT_Y        50
#define QRCODE_TITLE_TEXT_H        30
#define QRCODE_MARGIN       12
#define QRCODE_Y_POS        88
#define QRCODE_SIZE         250

#elif (LCD_SIZE_WIDTH == 454)
#define QRCODE_TITLE_TEXT_Y        29
#define QRCODE_TITLE_TEXT_H        30
#define QRCODE_MARGIN       15
#define QRCODE_Y_POS        90
#define QRCODE_SIZE         250

#elif (LCD_SIZE_WIDTH == 466)
#define QRCODE_TITLE_TEXT_Y        31
#define QRCODE_TITLE_TEXT_H        30
#define QRCODE_MARGIN       16
#define QRCODE_Y_POS        84
#define QRCODE_SIZE         298

#else   // 240
#define QRCODE_TITLE_TEXT_Y        29
#define QRCODE_TITLE_TEXT_H        30
#define QRCODE_Y_POS        60
#define QRCODE_SIZE         150
#endif

#define QRCODE_X_POS        ((LCD_SIZE_WIDTH-QRCODE_SIZE)/2)

#else

#if (LCD_SIZE_WIDTH == 320)
#define QRCODE_TITLE_TEXT_Y        29
#define QRCODE_TITLE_TEXT_H        30
#define QRCODE_MARGIN       24
#define QRCODE_SIZE         240

#else   // 240
#define QRCODE_TITLE_TEXT_Y        29
#define QRCODE_TITLE_TEXT_H        30
#define QRCODE_MARGIN       24
#define QRCODE_SIZE         200
#endif

#define QRCODE_X_POS        ((LCD_SIZE_WIDTH-QRCODE_SIZE)/2)
#define QRCODE_Y_POS        (((LCD_SIZE_HEIGHT-QRCODE_SIZE)/2) + (LCD_SIZE_HEIGHT-LCD_SIZE_WIDTH)/3)
#endif



// bar-code ---------------------------------------------------------------------------------------------
#if (LCD_SIZE_WIDTH == 320)
#define BARCODE_TITLE_TEXT_Y        29
#define BARCODE_TITLE_TEXT_H        30
#define BARCODE_MARGIN      24
#define BARCODE_SIZE_W      270
#define BARCODE_SIZE_H      128

#elif (LCD_SIZE_WIDTH == 360)
#define BARCODE_TITLE_TEXT_Y        29
#define BARCODE_TITLE_TEXT_H        30
#define BARCODE_MARGIN      24
#define BARCODE_SIZE_W      300
#define BARCODE_SIZE_H      140

#elif (LCD_SIZE_WIDTH == 390)
#define BARCODE_TITLE_TEXT_Y        29
#define BARCODE_TITLE_TEXT_H        30
#define BARCODE_MARGIN      24
#define BARCODE_SIZE_W      327
#define BARCODE_SIZE_H      150

#elif (LCD_SIZE_WIDTH == 412)
#define BARCODE_TITLE_TEXT_Y        22
#define BARCODE_TITLE_TEXT_H        30
#define BARCODE_MARGIN_V    8
#define BARCODE_MARGIN      15
#define BARCODE_SIZE_W      370
#define BARCODE_SIZE_H      120

#elif (LCD_SIZE_WIDTH == 454)
#define BARCODE_TITLE_TEXT_Y        29
#define BARCODE_TITLE_TEXT_H        30
#define BARCODE_MARGIN      24
#define BARCODE_SIZE_W      390
#define BARCODE_SIZE_H      180

#elif (LCD_SIZE_WIDTH == 466)
#define BARCODE_TITLE_TEXT_Y        31
#define BARCODE_TITLE_TEXT_H        30
#define BARCODE_MARGIN_V    8
#define BARCODE_MARGIN      16
#define BARCODE_SIZE_W      410
#define BARCODE_SIZE_H      136

#else   // 240
#define BARCODE_TITLE_TEXT_Y        29
#define BARCODE_TITLE_TEXT_H        30
#define BARCODE_MARGIN      24
#define BARCODE_SIZE_W      220
#define BARCODE_SIZE_H      80
#endif


#endif
