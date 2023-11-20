#ifndef _PID_TYPE_H
#define _PID_TYPE_H

// 把language
// type的定义放这里来，避免各软件版本分别修改时，不能与app同步修改!!!!
typedef enum
{
    LANGUAGE_TYPE_ENGLISH = 0,
    LANGUAGE_TYPE_CHINESE,
    LANGUAGE_TYPE_SPAIN,
    LANGUAGE_TYPE_ITALIAN,
    LANGUAGE_TYPE_PORTUGUESE,

    LANGUAGE_TYPE_FRANCE,    // 5
    LANGUAGE_TYPE_JAPAN,
    LANGUAGE_TYPE_RUSSIAN,
    LANGUAGE_TYPE_KOREAN,
    LANGUAGE_TYPE_GERMAN,

    LANGUAGE_TYPE_CHINESE_TRADITIONAL,    // 10
    LANGUAGE_TYPE_ARABIC,
    LANGUAGE_TYPE_INDONESIA,
    LANGUAGE_TYPE_TURKISH,
    LANGUAGE_TYPE_UKRAINIAN,

    LANGUAGE_TYPE_JEWISH,    // Hebrew   // 15
    LANGUAGE_TYPE_HEBREW = LANGUAGE_TYPE_JEWISH,
    LANGUAGE_TYPE_POLAND,    // Polski
    LANGUAGE_TYPE_HINDI,     // Hindi
    LANGUAGE_TYPE_CROATIA,
    LANGUAGE_TYPE_GREEK,

    LANGUAGE_TYPE_THAI,          // 泰语   //20
    LANGUAGE_TYPE_VIETNAMESE,    // 越南�?
    LANGUAGE_TYPE_PERSIAR,       // 波斯�?
    LANGUAGE_TYPE_DUTCH,         // 荷兰语
    LANGUAGE_TYPE_ROMANIA,       // 罗马尼亚语

    LANGUAGE_TYPE_GALLEGO,       // 加利西亚语(gallego) //25
    LANGUAGE_TYPE_EUSKERA,       // 巴斯克语(euskera)
    LANGUAGE_TYPE_CATALAN,       // 加泰罗尼亚语(catalán)
    LANGUAGE_TYPE_DANISH,        //	丹麦语(Danish)
    LANGUAGE_TYPE_SWEDISH,       //	瑞典语(Swedish)

    LANGUAGE_TYPE_NORWEGIAN,     //	挪威语(Norwegian) //30
    LANGUAGE_TYPE_URDU,     //	乌尔都语(Urdu) //31
    LANGUAGE_TYPE_BENGALESE,     //	孟加拉语(Bengalese)
	LANGUAGE_TYPE_MALAYSIA,     //	马来西亚(Malaysia)

    LANGUAGE_TYPE_ALL
} LANGUAGE_TYPE;

typedef enum
{
    DATA_TYPE_NULL = 0,

    /* 1.dev to app cmd (1-100) */
    DEV_TO_APP_START_TYPE = 1,
    DATA_TYPE_DEVINFO,
    DATA_TYPE_BATTERY_INFO,
    DATA_TYPE_REAL_SPORT,
    DATA_TYPE_HISTORY_SPORT,    // 5
    DATA_TYPE_SLEEP,
    DATA_TYPE_REAL_HEART,
    DATA_TYPE_HISTORY_HEART,
    DATA_TYPE_DEV_SYNC,
    DATA_TYPE_MIX_SPORT,    // 10
    DATA_TYPE_FIND_PHONE_OR_DEVICE,
    DATA_TYPE_BLE_PAIR_STATUS,
    DATA_TYPE_USER_CHANGE,
    DATA_TYPE_MUSIC_CONTROL,
    DATA_TYPE_CALL_CONTROL_TO_APP,    // 15
    DATA_TYPE_GSENSOR_TEST,
    DATA_TYPE_EXERCISE_HEART,
    DATA_TYPE_REAL_BP,
    DATA_TYPE_REAL_ECG,
    DATA_TYPE_REAL_O2,    // 20
    DATA_TYPE_HR_CONTROL,
    DATA_TYPE_FUNCTION_CONTROL,
    DATA_TYPE_HARDWARE_INFO,
    DATA_TYPE_REAL_HR,
    DATA_TYPE_BTEDR_ADDR,           // 25
    DATA_TYPE_QR_CODE_INFO,
    DATA_TYPE_QR_CODE_DEL,          // 二维码删�?
    DATA_TYPE_QR_CODE_CLEAR,        // 维码全部清除
    DATA_TYPE_PHNONE_RESOLUTION,    // 获取手机分辨�?
    DATA_TYPE_SMS_REPLY,            // 30     // 短信回复
    DATA_TYPE_ALIPAY_RAW_DATA,      // 阿里云-支付宝数据
    DATA_TYPE_ALIPAY_BIND_FLAG,     // 支付宝绑定开始信号，APP收到后，需要停止app与手表的数据通信!!!
                                    // (由于JL平台多连接问题，会导致APP主动断连重连，从而影响支付宝绑定)
    DEV_TO_APP_END_TYPE = 100,

    /* 2.app to dev cmd (101-200) */
    APP_TO_DEV_START_TYPE = 101,
    DATA_TYPE_USERINFO,
    DATA_TYPE_LANGUAGE_SETTING,
    DATA_TYPE_TIME,
    DATA_TYPE_WEATHER,    // 105
    DATA_TYPE_ALARM,
    DATA_TYPE_MESSAGE_NOTICE,
    DATA_TYPE_APP_CLOSE,
    DATA_TYPE_SET_DATA_SWITCH,
    DATA_TYPE_APP_SYNC,    // 110
    DATA_TYPE_SET_TARGET,
    DATA_TYPE_OPEN_BLE_PAIR,
    DATA_TYPE_MUSIC_CONTENT,
    DATA_TYPE_SITTING_REMIND,
    DATA_TYPE_FORGET_DISTURB,    // 115
    DATA_TYPE_PHOTOGRAPH_ONOFF,
    DATA_TYPE_CALL_CONTROL_TO_DEV,
    DATA_TYPE_RESET,
    DATA_TYPE_SHUTDOWN,
    DATA_TYPE_PAIR_FINISH,    // 120
    DATA_TYPE_UNIT_SETTING,
    DATA_TYPE_CALL_ALARM,
    DATA_TYPE_MESSAGE_ALARM,
    DATA_TYPE_MESSAGE_SWITCH,
    DATA_TYPE_TARGET_ALARM,    // 125
    DATA_TYPE_DRINK_ALARM,
    DATA_TYPE_HAND_RISE_SWITCH,
    DATA_TYPE_HEART_AUTO_SWITCH,
    DATA_TYPE_WATCH_SETTING,
    DATA_TYPE_APP_SPORT,    // 130
    DATA_TYPE_WATCHFACE_SYNC,
    DATA_TYPE_WATCHFACE_INFO,
    DATA_TYPE_WOMAN_STAGE_INFO,
    DATA_TYPE_WATCHFACE_START,

    DATA_TYPE_CONTACT_ADD,            // 135		// 增加联系�?
    DATA_TYPE_CONTACT_DELETE,         // 删除指定索引的联系人
    DATA_TYPE_CONTACT_CLEAN,          // 清空�?有联系人
    DATA_TYPE_CONTACT_SYNC,           // 同步联系�?
    DATA_TYPE_REAL_TIME_WEATHER,      // 实时天气类型
    DATA_TYPE_WATCHFACE_PHOTO_DEL,    // 140
    DATA_TYPE_POWER_LOGO_DEL,         // 删除自定义logo
    DATA_TYPE_TEST_TOOL,              // 测试APP
    DATA_TYPE_MOTION_GAME,            // 体感游戏开关
    DATA_TYPE_MOTION_DATA,            // 体感Sensor数据

    APP_TO_DEV_END_TYPE = 200,

    /* 3.No use (201-255) */
    DATA_TYPE_OTA_STATUS = 201,
    DATA_TYPE_OTA_DATA,
    DATA_TYPE_TEST_DEBUG,
    DATA_TYPE_APP_TEST,

} DATA_TYPE;

#define PID_0000_NULL                   0
#define PID_0001_S2                     1
#define PID_0002_S3                     2
#define PID_0003_RT729                  3
#define PID_0004_RT822                  4
#define PID_0005_Q8                     5
#define PID_0006_D3                     6
#define PID_0007_M4X                    7
#define PID_0008_H28                    8
#define PID_0009_T11                    9
#define PID_0010_M4                     10
#define PID_0011_SW06s                  11
#define PID_0012_SW05                   12
#define PID_0013_Y18                    13
#define PID_0014_S7                     14
#define PID_0015_S3_ABYX                15

//=========================================================
// 十年产品�?18�?�?
#define PID_0018_SN82                   18
#define PID_0019_SN80                   19
#define PID_0020_SN70_N                 20
#define PID_0021_SN85                   21
#define PID_0022_FM5                    22
#define PID_0023_SN86                   23
#define PID_0024_SN59                   24
#define PID_0025_SN72                   25
#define PID_0026_W15                    26
#define PID_0027_SN82_ZWATCH            27
#define PID_0028_SN82_GS20              28
#define PID_0029_SN87                   29
#define PID_0030_SN88                   30
#define PID_0032_SN_82                  32
#define PID_0033_SN82_SPECTRE           33
#define PID_0034_SN82_SW91              34
#define PID_0035_SN80Y                  35
#define PID_0036_SN_87                  36
#define PID_0037_SN_M2                  37
#define PID_0038_C1                     38
#define PID_0039_SN__82                 39    // PID_0000_SN-82
#define PID_0040_F3                     40
#define PID_0041_WS2348                 41
#define PID_0042_SN90                   42
#define PID_0043_LIUJO                  43
#define PID_0044_RS                     44
#define PID_0045_M1                     45
#define PID_0046_VERVE                  46
#define PID_0047_SN91                   47
#define PID_0048_CB_TRAK                48
#define PID_0049_SILK                   49
#define PID_0050_SN_OZONE               50
#define PID_0051_NEXTFIT                51
#define PID_0052_W14                    52
#define PID_0053_W__15                  53
#define PID_0054_W11                    54
#define PID_0055_CF22                   55
#define PID_0056_GW20                   56
#define PID_0057_PA86                   57
#define PID_0058_RUNNER                 58
#define PID_0059_WS__2346               59
#define PID_0060_ECLIPSE                60
#define PID_0061_GHOST                  61
#define PID_0062_BIP                    62
#define PID_0063_SPORT                  63
#define PID_0064_PULSE                  64
#define PID_0065_AMAZE                  65
#define PID_0066_FLASH                  66
#define PID_0067_AVIATE                 67
#define PID_0068_SP_V2                  68
#define PID_0069_CF60                   69
#define PID_0070_SN_TM_TWX              70
#define PID_0071_MS02                   71
#define PID_0072_GIZFIT                 72
#define PID_0073_SN93                   73
#define PID_0074_W__11                  74
#define PID_0075_LUNAR                  75
#define PID_0077_SN80Y_HANYU            77
#define PID_0078_ORBIT                  78
#define PID_0079_PA86_PRO               79
#define PID_0080_SN_82_PAH8007          80

//=========================================================
// 新产品从100�?�?
#define PID_0100_SN92                   100
#define PID_0101_MAXPRO                 101
#define PID_0102_TAGG_VERVE             102
#define PID_0103_ZT__1                  103
#define PID_0104_GZ910                  104
#define PID_0105_R2                     105
#define PID_0106_ZT__1A                 106
#define PID_0107_W13                    107
#define PID_0108_R1                     108
#define PID_0109_PA80                   109
#define PID_0110_AMAZE_PRO              110
#define PID_0111_FP_R1                  111
#define PID_0112_SN_88                  112
#define PID_0113_SN_93                  113
#define PID_0114_SN__91                 114
#define PID_0115_M3                     115
#define PID_0116_SW2                    116
#define PID_0117_AQFIT_W12              117
#define PID_0118_SW93                   118
#define PID_0119_SN82__S                119
#define PID_0120_USPRT                  120
#define PID_0121_SN93_CLAS2             121
#define PID_0122_GP__SW002              122
#define PID_0123_M10                    123
#define PID_0124_SN92_TK68              124
#define PID_0125_SN88__Y                125
#define PID_0126_SN93__Y                126
#define PID_0127_SN88__M                127
#define PID_0128_SN93__M                128
#define PID_0129_M1_L_S85               129
#define PID_0130_SN90_L_S88             130
#define PID_0131_SN93_L_S80             131
#define PID_0132_M5                     132
#define PID_0133_SN__87                 133
#define PID_0134_LIUJOR                 134
#define PID_0135_CALK__S2               135
#define PID_0136_SN90P                  136
#define PID_0137_SN90_SPORT             137
#define PID_0138_NS17                   138
#define PID_0139_M2__PRO                139
#define PID_0140_T8                     140
#define PID_0141_PARIGI                 141
#define PID_0142_MAXPRO_X4              142
#define PID_0143_LIUJO                  143
#define PID_0144_PA__80                 144
#define PID_0145_M15__S                 145
#define PID_0146_SN87                   146
#define PID_0147_M12                    147
#define PID_0148_M6                     148
#define PID_0149_M15                    149
#define PID_0150_SN088                  150
#define PID_0151_TM__TWX                151
#define PID_0152_GP_SW002               152
#define PID_0153_LIU_JO                 153
#define PID_0154_W_PLUS                 154
#define PID_0155_GZ910                  155
#define PID_0156_XT80                   156
#define PID_0157_MAXPRO_X4              157
#define PID_0158_JMS_VOICE              158
#define PID_0159_C__1                   159
#define PID_0160_PA88                   160
#define PID_0161_908_PRO                161
#define PID_0162_WS__2362               162
#define PID_0163_MAXPRO_X2              163
#define PID_0164_SN92_WT30              164
#define PID_0165_BSW__1                 165
#define PID_0166_PRIME                  166
#define PID_0167_M8                     167
#define PID_0168_R__2                   168
#define PID_0169_FLASH                  169
#define PID_0170_VERVE_NEO              170
#define PID_0171_SN92_KAVVO             171
#define PID_0172_LANOS                  172
#define PID_0173_K07                    173
#define PID_0174_SN_93                  174
#define PID_0175_PA86_PRO               175
#define PID_0176_GW_M5                  176
#define PID_0177_URB_FITX               177
#define PID_0178_GW__M5                 178
#define PID_0179_VERVE                  179
#define PID_0180_M10_KH60               180
#define PID_0181_A1PRO                  181
#define PID_0182_A2                     182
#define PID_0183_SPACE                  183
#define PID_0184_SW78                   184
#define PID_0185_W_PLUS                 185
#define PID_0186_M5_MAXPRO_X5           186
#define PID_0187_MAXPRO_X2              187
#define PID_0188_LIU__JO                188
#define PID_0189_FLASH                  189
#define PID_0190_M9                     190
#define PID_0191_A3PRO                  191
#define PID_0192_LIU_JO                 192
#define PID_0193_MAXPRO_X4              193
#define PID_0194_SN92_TK69              194
#define PID_0195_SN92_TK70              195
#define PID_0196_FLASH                  196
#define PID_0197_W_11                   197
#define PID_0198_M5_MAXPRO_X5           198
#define PID_0199_M5_S                   199
#define PID_0200_PBL_LEAP               200
#define PID_0201_PA88                   201
#define PID_0202_SN93_ZATEC_FLEX        202
#define PID_0203_M1_GP_SW002            203
#define PID_0204_M5_W6                  204
#define PID_0205_W_11                   205
#define PID_0206_MORELLATO_M01          206
#define PID_0207_SECTOR_S_04            207
#define PID_0208_VERVE_NEO              208
#define PID_0209_SN88_R1                209
#define PID_0210_JMS_VOICE              210
#define PID_0211_GZ910                  211
#define PID_0212_MAXPRO_X4              212
#define PID_0213_M5_W6                  213
#define PID_0214_M1_KOSPETGTO           214
#define PID_0215_SN92_SKYCAL_T68        215
#define PID_0216_M6_M6S                 216
#define PID_0217_M5_S1_PRO              217
#define PID_0218_M5                     218
#define PID_0219_M9                     219
#define PID_0220_SN93                   220
#define PID_0221_A3PRO                  221
#define PID_0222_KH62                   222
#define PID_0223_W11                    223
#define PID_0224_AMAZE_PRO              224
#define PID_0225_SN90_SPORT             225
#define PID_0226_VERVE_LITE             226
#define PID_0227_RUNNER                 227
#define PID_0228_SN88                   228
#define PID_0229_M2                     229
#define PID_0230_SN92_SENS4             230
#define PID_0231_NS17_A4                231
#define PID_0232_M19                    232
#define PID_0233_URB_FITX               233
#define PID_0234_MIAMA                  234
#define PID_0235_M23                    235
#define PID_0236_SN90_USPRT             236
#define PID_0237_M5_LANOS               237
#define PID_0238_LITE_X                 238
#define PID_0239_RUNNER                 239
#define PID_0240_MAXPRO_X2_V2           240
#define PID_0241_PT70                   241
#define PID_0242_PA86_PRO               242
#define PID_0243_R2_PRO                 243
#define PID_0244_M5_K1                  244
#define PID_0245_DEVIA_M5               245
#define PID_0246_DEVIA_SN93             246
#define PID_0247_VERVE_NEO              247
#define PID_0248_SN88S_BOE              248
#define PID_0248_SN88S_HANCAI           249
#define PID_0250_DEVIA_SN93_HANCAI      250
#define PID_0251_C1                     251
#define PID_0252_VERVE_NEO              252
#define PID_0253_SN90                   253
#define PID_0254_M4                     254
#define PID_0255_VERVE_NEO              255
#define PID_0256_SN92                   256
#define PID_0257_SN90_L_88              257
#define PID_0258_SN88_COOL              258
#define PID_0259_M5_SPACE_LC11S         259
#define PID_0260_M5_NEO_RS45            260
#define PID_0261_M25                    261
#define PID_0262_M2_PACTICK             262
#define PID_0263_M10_SWT06BP            263
#define PID_0264_M25S                   264
#define PID_0265_SN93_Kronos_Air        265
#define PID_0266_SN93_Kronos_Vevo       266
#define PID_0267_SN93_Kronos_Lite       267
#define PID_0268_M5_URB                 268
#define PID_0269_M4_S1_Pro              269
#define PID_0270_M5_SPACE               270
#define PID_0271_SN92_Army_Force        271
#define PID_0272_M9_L_SN89              272
#define PID_0273_M5_RED                 273
#define PID_0274_M6_GUI                 274
#define PID_0275_M5_GREEN               275
#define PID_0276_M15_S_OctaFit          276
#define PID_0277_XT80                   277
#define PID_0278_SN90_SPORT             278
#define PID_0279_SN93_WK                279
#define PID_0280_M6_OZONE3              280
#define PID_0281_SECTOR_S_04            281
#define PID_0282_SN90_BK                282
#define PID_0283_SN90_M15S_BK           283
#define PID_0284_M5_VERVE_NEO           284
#define PID_0285_M_01_CRYSTAL           285
#define PID_0286_M19_TK16               286
#define PID_0287_M31                    287
#define PID_0288_SN93_LC11S_RED         288
#define PID_0289_FLASH                  289
#define PID_0290_M8_GUI                 290
#define PID_0291_M21                    291
#define PID_0292_M21S                   292
#define PID_0293_W_PLUS                 293
#define PID_0294_HANCAI_FLASH           294
#define PID_0295_M25P                   295
#define PID_0296_M6_MORELLATO_M_03      296
#define PID_0297_SN90_LIU               297
#define PID_0298_M5_NEO_2048            298
#define PID_0299_M25SP                  299
#define PID_0300_M21SE                  300
#define PID_0301_M25SE                  301
#define PID_0302_M23_B_SMART            302
#define PID_0303_M23_SECTOR_S_05        303
#define PID_0304_SN93_CURV              304
#define PID_0305_M28                    305
#define PID_0306_M6_MUSTARD_TEMPO       306
#define PID_0307_M1_PA86_PRE            307
#define PID_0308_SN80_PA80              308
#define PID_0309_M6_OZONE3              309
#define PID_0310_M1_01                  310
#define PID_0311_M5_RED_128M            311
#define PID_0312_M5_GREEN_128M          312
#define PID_0313_M25_MUSTARD_ROCK       313
#define PID_0314_M5_VP60A2_128M         314
#define PID_0315_M6_MUSTARD_TEMPO       315
#define PID_0316_M15_S_KH038_OCTAFIT    316
#define PID_0317_SN90_KH038_LUNAR       317
#define PID_0318_M23_PLUS               318
#define PID_0319_M26                    319
#define PID_0320_M30                    320
#define PID_0321_M5S_KH051              321
#define PID_0322_M35                    322
#define PID_0323_GW41                   323
#define PID_0324_M25SP_C078             324
#define PID_0325_GW8Ultra               325
#define PID_0326_S8_MAX                 326
#define PID_0327_M29                    327
#define PID_0328_C_1                    328
#define PID_0329_TC8_Ultra              329
#define PID_0330_TC8_MAX                330
#define PID_0331_DEVIA_M5               331
#define PID_0332_DEVIA_SN93             332
#define PID_0333_M40                    333
#define PID_0334_S_Ultra                334
#define PID_0335_ELECTRA                335
#define PID_0336_W_PLUS                 336
#define PID_0337_SN91                   337
#define PID_0338_SN85_C_1               338
#define PID_0339_GW8MAX_SPAIN           339
#define PID_0340_S8_MAX_BATT2           340
#define PID_0341_DMS8                   341
#define PID_0342_M36                    342
#define PID_0343_DM10_PRO               343
#define PID_0344_JOYEN_M41              344
#define PID_0345_M2_W_PLUS              345
#define PID_0346_M25SP_A                346
#define PID_0347_SN__87                 347
#define PID_0348_M41_PHOTO              348
#define PID_0349_M25SP_AC               349
#define PID_0350_M31_GM8ULTRA           350
#define PID_0351_M4_S1_Pro              351
#define PID_0352_XT80                   352
#define PID_0353_SN88                   353
#define PID_0354_SN88                   354
#define PID_0355_SN88S                  355
#define PID_0356_M25_LG208              356
#define PID_0357_M21A                   357
#define PID_0358_SN90                   358
#define PID_0359_M32                    359
#define PID_0360_M31_LC207              360
#define PID_0361_M25_GW45               361
#define PID_0362_M25SE_ARCADE_A         362
#define PID_0363_M29_B                  363
#define PID_0364_M4                     364
#define PID_0365_M25SE_ELECTRA_C        365
#define PID_0366_M1S                    366
#define PID_0367_M1L                    367
#define PID_0368_M5_OZONE4              368
#define PID_0369_M31_MINONE8_MAX        369
#define PID_0370_M41_MINONE8_ULTRA      370
#define PID_0371_S8_MAX_BATT2           371
#define PID_0372_M41_RV9                372
#define PID_0373_M42                    373
#define PID_0374_M41_L_S90              374
#define PID_0375_M1_PA86_PRE            375
#define PID_0376_M8_GUI                 376
#define PID_0377_M31_GW8MAX             377
#define PID_0378_S8_MAX_logo            378
#define PID_0379_M38                    379
#define PID_0380_M41_MINONE8_ULTRA_BATT 380
#define PID_0381_RUNNER                 381
#define PID_0382_LUNAR_PRIME            382
#define PID_0383_LUNAR_PRIME_64M        383
#define PID_0384_LUNAR_PRIME_64M        384
#define PID_0385_GW41                   385
#define PID_0386_M6_OZONE3              386
#define PID_0387_M6_OZONE3_128M         387
#define PID_0388_M5_DZ245_64M           388
#define PID_0389_M40_VIBEZ_64M          389
#define PID_0390_M29_G2D                390
#define PID_0391_M36_MZ                 391
#define PID_0392_M26_G2D                392
#define PID_0393_M40_G2D                393
#define PID_0394_CW041                  394
#define PID_0395_M28_G2D                395
#define PID_0396_LC208_ZHONGXIN         396
#define PID_0397_CW041_MT85A            397

#define PID_0398_M21                    398
#define PID_0399_M38PLUS                399
#define PID_0400_M45                    400
#define PID_0401_GW41                   401
#define PID_0402_T_FASHION              402
#define PID_0403_GW41_PA86              403
#define PID_0404_M46                    404
#define PID_0405_MY26                   405
#define PID_0406_M10_MT60               406
#define PID_0407_MY88_M40_G2D           407
#define PID_0408_GW43_COOLWEAR          408
#define PID_0409_M21_G2D                409
#define PID_0410_GW45_GW50_G2D          410
#define PID_0411_GW45_GW51_G2D          411
#define PID_0412_GW45_FBT62max_G2D      412
#define PID_0413_CW043_HUAMEI           413

#define PID_0414_GW41_FBW17Pro          414
#define PID_0415_M45_XINHUO             415
#define PID_0416_M39                    416
#define PID_0417_M6_OZONE               417
#define PID_0418_M26_BYSL_S20           418
#define PID_0419_M49                    419
#define PID_0420_M36_JXJS_M36           420
#define PID_0421_M40_G2D                421
#define PID_0422_M26_S58_SPORT          422
#define PID_0423_M60                    423
#define PID_0424_M38_S58_MAX            424
#define PID_0425_M37_S58_MINI           425
#define PID_0426_M40_MY88               426
#define PID_0427_M45_S58_ULTRA_PRO_MAX  427
#define PID_0428_GW45_428               428
#define PID_0429_L_S90_429              429
#define PID_0430_L_S89_430              430
#define PID_0431_M26_431                431
#define PID_0432_M28_432                432
#define PID_0433_M29_433                433
#define PID_0434_M1S_434                434
#define PID_0435_M1_CRYSTAL_435         435
#define PID_0436_M1_L_436               436
#define PID_0437_GW41_AMOLED_437        437
#define PID_0438_M8_JP                  438
#define PID_0439_M2_CKVD                439
#define PID_0440_GW52_PLUS              440
#define PID_0441_M1_CKVD                441
#define PID_0442_M36A                   442
#define PID_0443_M2_W_PLUS              443
#define PID_0444_SN93_WK                444
#define PID_0445_ABYX                   445
#define PID_0446_GW43_ALIPAY            446
#define PID_0447_M25SP_R                447
#define PID_0448_M26_488                448
#define PID_0449_M40_ELITE              449
#define PID_0450_M29_BOLD               450
#define PID_0451_M8_JP_BATT             451
#define PID_0452_M6_CKVD                452
#define PID_0453_M39                    453
#define PID_0454_SN93_DE007_02          454
#define PID_0455_M6_128M_CKVD           455
#define PID_0456_M1_S04_COLOURS_CKVD    456
#define PID_0457_M2_W_PLUS              457
#define PID_0458_M36_DEVIA              458
#define PID_0459_M2_W_PLUS              459
#define PID_0460_GW50_T1                460
#define PID_0460_GW51_T2                461
#define PID_0462_MY88_M40_G2D           462
#define PID_0463_MY26                   463
#define PID_0464_M2POR_ckvd             464
#define PID_0465_SN88S                  465
#define PID_0466_M6                     466
#define PID_0467_M1Z_CKVD               467
#define PID_0468_M1L_CKVD               468
#define PID_0469_M40_VIBEZ_64M          469
#define PID_0470_GW56_T_FLY             470
#define PID_0471_M36_DEVIA              471
#define PID_0472_M36_ALPINE             472
#define PID_0473_M8_SAKURA              473
#define PID_0474_M41_NIcex              474
#define PID_0475_GW52_GOALTAGE          475
#define PID_0476_M5_OZONE_LITE          476
#define PID_0477_SN93_LESW32_CKVD       477
#define PID_0478_GW52PLUS               478
#define PID_0479_GW41_PA86S             479
#define PID_0480_M36_MZ                 480
#define PID_0481_G8_ULTRA_481           481
#define PID_0482_DG0502_JLK_V8ProMax    482
#define PID_0483_M5_OZONE_LITE          483
#define PID_0484_M62                    484
#define PID_0485_SN93_MAXPROX4          485
#define PID_0486_M36                    486
#define PID_0487_M65                    487
#define PID_0488_M49_DG0015             488
#define PID_0489_M36_IMAGEVIEW          489
#define PID_0490_GW43_DG0101            490
#define PID_0491_M42_LS92_DG0020        491
#define PID_0492_M42_TEMPO_DG0020A      492
#define PID_0493_M36_TOP_3              493
#define PID_0494_M61_DG0015_1           494
#define PID_0495_JT11_DG0503            495
#define PID_0496_M31_DM10ProPlus        496
#define PID_0497_M52                    497
#define PID_0498_M2_W_PLUS              498
#define PID_0499_M40_VIBEZ_64M          499
#define PID_0500_JT9                    500
#define PID_0501_T1_OA90_DG0106         501
#define PID_0502_K2_DG0026              502
#define PID_0503_M6_SXL2500             503
#define PID_0504_M28_SW064              504
#define PID_0505_M29_PE019              505
#define PID_0506_M2_RUNNER              506
#define PID_0507_SN_87                  507
#define PID_0508_M36S                   508
#define PID_0509_M60                    509
#define PID_0510_MORELLATO_M01          510
#define PID_0511_SXL2500_M6             511
#define PID_0512_DG0505_HS02            512
#define PID_0513_SN90_SXL2700           513
#define PID_0514_M30_SXL2800            514
#define PID_0515_M36L                   515
#define PID_0516_M36_SPORTS_MOTION      516
#define PID_0517_M41_S8_MAX             517
#define PID_0518_SXL2500_M6             518
#define PID_0519_DG0107_GW45            519
#define PID_0520_DG0506_HS01            520
#define PID_0521_DG0508_V8PRO           521
#define PID_0522_M41_Fortune            522
#define PID_0523_M36_A                  523
#define PID_0524_M2_W_plus_CKVD         524
#define PID_0525_MY26                   525
#define PID_0526_V15                    526
#define PID_0527_M55                    527
#define PID_0528_DG0046_LESW39			528
#define PID_0529_M25_LG208_CH            529
#define PID_0530_SN93_LESW32_CKVD        530
#define PID_0531_BASE_M62               531
#define PID_0532_M53                    532
#define PID_0533_DG0509_D15             533
#define PID_0534_LG_LC308               534
#define PID_0535_LG_LC601               535
#define PID_0536_SN_87                  536
#define PID_0537_LG_LC208S				537
#define PID_0538_LG_LC604				538
#define PID_0539_LG_LC303               539
#define PID_0540_LG_LC602              	540
#define PID_0541_LG_LC305              	541
#define PID_0542_LG_LC603              	542
#define PID_0543_LG_LC608              	543
#define PID_0544_LG_LC310              	544
#define PID_0545_M28_MAX_PRO_UW01		545
#define PID_0546_M2_W_plus_CKVD         546
#define PID_0547_SN93_LESW32_CKVD       547
#define PID_0548_M6_OZONE               548
#define PID_0549_M1_L                   549
#define PID_0550_M45_EXTREAME           550
#define PID_0551_MORELLATO_M01          551
#define PID_0552_BASE_M62_APPLE         552
#define PID_0553_D17      			    553
#define PID_0554_M42_AUDIO      	    554
#define PID_0555_M42_MATRIX             555
#define PID_0556_DG0051_MY88            556
#define PID_0557_M1_CRYSTAL             557
#define PID_0558_M28_SAKURA             558
#define PID_0559_DK_W003                559
#define PID_0560_DG0523_HS03            560
#define PID_0561_RING            		561
#define PID_0562_M5_128M                562
#define PID_0563_DG0524_LC203K          563
#define PID_0564_DG0069_TOP8            564
#define PID_0565_DG0070_M42             565
#define PID_0566_DG0067_M42             566
#define PID_0567_DG0068_TOP        		 567
#define PID_0568_DG0525_MT800CW         568
#define PID_0569_DG0525_M35L_AN88       569
#endif    //_PID_TYPE_H
