﻿
#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "data_common.h"

#include "application.h"
#include "gui_window.h"


static const unsigned char pic_low_power_icon_data[40*50*2] = 
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x03, 0x08, 0x05, 0x08, 0x05, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x05, 
	0x18, 0x0E, 0x20, 0x11, 0x10, 0x0C, 0x08, 0x05, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x18, 0x0F, 
	0x30, 0x1B, 0x30, 0x1C, 0x20, 0x11, 0x08, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x08, 0x06, 0x18, 0x0E, 0x30, 0x19, 
	0x38, 0x1F, 0x30, 0x1C, 0x18, 0x0E, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x20, 0x12, 0x30, 0x1A, 0x38, 0x1E, 
	0x30, 0x1C, 0x20, 0x12, 0x08, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x10, 0x09, 0x20, 0x12, 0x30, 0x1B, 0x40, 0x1F, 0x38, 0x1E, 
	0x20, 0x13, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x10, 0x0D, 0x28, 0x16, 0x38, 0x1C, 0x40, 0x1F, 0x40, 0x1F, 0x28, 0x19, 
	0x10, 0x0A, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x08, 0x05, 0x18, 0x0D, 0x28, 0x17, 0x38, 0x1E, 0x40, 0x1F, 0x40, 0x1F, 0x30, 0x1B, 0x18, 0x10, 
	0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x06, 
	0x20, 0x11, 0x30, 0x1A, 0x38, 0x1D, 0x40, 0x1F, 0x40, 0x1F, 0x38, 0x1D, 0x20, 0x12, 0x08, 0x07, 
	0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x08, 0x08, 0x18, 0x11, 
	0x30, 0x1A, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1E, 0x28, 0x18, 0x10, 0x0A, 0x00, 0x02, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x10, 0x0B, 0x28, 0x15, 0x30, 0x1C, 
	0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x30, 0x1A, 0x18, 0x11, 0x08, 0x05, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x08, 0x05, 0x10, 0x0C, 0x20, 0x15, 0x38, 0x1E, 0x38, 0x1F, 
	0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x30, 0x1D, 0x20, 0x13, 0x08, 0x09, 0x00, 0x02, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x08, 0x06, 0x18, 0x0F, 0x28, 0x19, 0x38, 0x1E, 0x38, 0x1F, 0x38, 0x1F, 
	0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x28, 0x19, 0x10, 0x0A, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x02, 0x08, 0x07, 0x18, 0x10, 0x28, 0x19, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1E, 
	0x38, 0x1F, 0x38, 0x1F, 0x30, 0x1B, 0x18, 0x11, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x10, 0x0A, 0x20, 0x13, 0x30, 0x1B, 0x38, 0x1E, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1E, 0x38, 0x1F, 
	0x38, 0x1F, 0x38, 0x1D, 0x20, 0x13, 0x08, 0x08, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x10, 0x0A, 
	0x20, 0x14, 0x30, 0x1C, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x30, 0x1E, 0x38, 0x1E, 0x38, 0x1F, 
	0x38, 0x1F, 0x28, 0x19, 0x10, 0x0B, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x18, 0x0E, 0x28, 0x17, 
	0x38, 0x1D, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1E, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 
	0x30, 0x1B, 0x18, 0x11, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x08, 0x06, 0x18, 0x0E, 0x28, 0x18, 0x38, 0x1F, 
	0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x30, 0x1E, 0x38, 0x1E, 0x38, 0x1F, 0x38, 0x1F, 0x30, 0x1B, 
	0x20, 0x12, 0x08, 0x09, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x07, 0x20, 0x12, 0x30, 0x1A, 0x38, 0x1E, 0x38, 0x1F, 
	0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1E, 0x28, 0x16, 
	0x08, 0x09, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x10, 0x09, 0x20, 0x12, 0x30, 0x1B, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 
	0x38, 0x1E, 0x30, 0x1E, 0x30, 0x1E, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x30, 0x1C, 0x20, 0x12, 
	0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x03, 0x10, 0x0C, 0x28, 0x16, 0x30, 0x1C, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 
	0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x30, 0x1A, 0x18, 0x11, 
	0x08, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x08, 0x06, 
	0x18, 0x0D, 0x28, 0x16, 0x38, 0x1E, 0x40, 0x1F, 0x38, 0x1F, 0x38, 0x1E, 0x38, 0x1E, 0x38, 0x1F, 
	0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x30, 0x1B, 0x28, 0x16, 
	0x18, 0x0F, 0x10, 0x09, 0x08, 0x06, 0x08, 0x05, 0x00, 0x03, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x08, 0x08, 0x20, 0x11, 
	0x30, 0x1A, 0x38, 0x1D, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1E, 0x38, 0x1E, 0x38, 0x1E, 0x38, 0x1E, 
	0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1E, 0x30, 0x1D, 
	0x30, 0x1B, 0x28, 0x19, 0x20, 0x15, 0x20, 0x12, 0x18, 0x0E, 0x10, 0x0A, 0x08, 0x05, 0x00, 0x02, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x10, 0x0B, 0x28, 0x16, 
	0x38, 0x1E, 0x40, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 
	0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 
	0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x30, 0x1C, 0x28, 0x17, 0x20, 0x14, 0x18, 0x10, 0x10, 0x0C, 
	0x08, 0x08, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x10, 0x0A, 0x20, 0x12, 
	0x30, 0x19, 0x38, 0x1D, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 
	0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 
	0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1D, 0x38, 0x1C, 0x38, 0x1B, 0x30, 0x1A, 
	0x20, 0x14, 0x10, 0x0B, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x08, 0x05, 0x10, 0x09, 
	0x18, 0x0E, 0x20, 0x12, 0x28, 0x16, 0x28, 0x19, 0x30, 0x1B, 0x30, 0x1C, 0x38, 0x1E, 0x38, 0x1F, 
	0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 
	0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x40, 0x1F, 0x40, 0x1F, 0x38, 0x1F, 
	0x28, 0x16, 0x10, 0x0C, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 
	0x00, 0x03, 0x08, 0x04, 0x08, 0x07, 0x10, 0x0A, 0x18, 0x0F, 0x20, 0x12, 0x28, 0x16, 0x30, 0x1A, 
	0x30, 0x1D, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 
	0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1E, 0x38, 0x1F, 0x38, 0x1F, 0x40, 0x1F, 0x38, 0x1F, 0x30, 0x19, 
	0x18, 0x0E, 0x08, 0x05, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x08, 0x05, 0x08, 0x08, 0x10, 0x0C, 0x18, 0x11, 
	0x28, 0x18, 0x30, 0x1D, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 
	0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x30, 0x1C, 0x28, 0x16, 0x18, 0x0E, 
	0x08, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x02, 0x08, 0x07, 
	0x18, 0x11, 0x30, 0x1A, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 
	0x30, 0x1E, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x30, 0x1C, 0x20, 0x13, 0x10, 0x09, 0x00, 0x03, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 
	0x18, 0x11, 0x30, 0x1B, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1E, 0x38, 0x1F, 0x38, 0x1F, 
	0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1E, 0x30, 0x1B, 0x20, 0x13, 0x10, 0x0A, 0x00, 0x01, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x0A, 
	0x28, 0x18, 0x38, 0x1E, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1E, 0x38, 0x1E, 0x38, 0x1F, 
	0x38, 0x1F, 0x38, 0x1F, 0x28, 0x18, 0x18, 0x0F, 0x08, 0x07, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x09, 0x20, 0x14, 
	0x38, 0x1D, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1E, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 
	0x38, 0x1D, 0x28, 0x19, 0x18, 0x0F, 0x08, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x05, 0x20, 0x12, 0x30, 0x1C, 
	0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x30, 0x1E, 0x38, 0x1E, 0x38, 0x1F, 0x40, 0x1F, 0x38, 0x1D, 
	0x20, 0x15, 0x10, 0x0C, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x0B, 0x30, 0x19, 0x38, 0x1F, 
	0x38, 0x1F, 0x38, 0x1E, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x30, 0x1C, 0x20, 0x15, 
	0x10, 0x0B, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x09, 0x20, 0x14, 0x38, 0x1D, 0x38, 0x1F, 
	0x38, 0x1F, 0x30, 0x1E, 0x38, 0x1F, 0x40, 0x1F, 0x38, 0x1F, 0x30, 0x1A, 0x18, 0x11, 0x08, 0x08, 
	0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x05, 0x20, 0x12, 0x30, 0x1B, 0x38, 0x1F, 0x38, 0x1F, 
	0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1E, 0x30, 0x19, 0x18, 0x11, 0x08, 0x06, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x10, 0x0B, 0x28, 0x19, 0x38, 0x1E, 0x38, 0x1F, 0x38, 0x1E, 
	0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1E, 0x28, 0x17, 0x10, 0x0D, 0x08, 0x05, 0x00, 0x01, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0x08, 0x09, 0x20, 0x13, 0x38, 0x1D, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 
	0x38, 0x1F, 0x38, 0x1C, 0x28, 0x16, 0x10, 0x0D, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x08, 0x05, 0x20, 0x12, 0x30, 0x1B, 0x38, 0x1F, 0x38, 0x1F, 0x40, 0x1F, 0x38, 0x1F, 
	0x30, 0x1B, 0x20, 0x13, 0x10, 0x09, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0x10, 0x0B, 0x30, 0x19, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1F, 0x38, 0x1E, 0x30, 0x1A, 
	0x20, 0x12, 0x08, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 
	0x08, 0x09, 0x20, 0x13, 0x38, 0x1C, 0x40, 0x1F, 0x40, 0x1F, 0x38, 0x1E, 0x28, 0x17, 0x18, 0x0F, 
	0x08, 0x06, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x05, 
	0x20, 0x12, 0x30, 0x1B, 0x38, 0x1F, 0x40, 0x1F, 0x38, 0x1D, 0x28, 0x17, 0x18, 0x0E, 0x08, 0x05, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x0A, 
	0x28, 0x18, 0x40, 0x1F, 0x40, 0x1F, 0x30, 0x1B, 0x20, 0x13, 0x10, 0x0B, 0x00, 0x04, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x08, 0x09, 0x20, 0x13, 
	0x38, 0x1E, 0x40, 0x1F, 0x30, 0x1C, 0x20, 0x13, 0x08, 0x09, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x06, 0x20, 0x13, 0x38, 0x1D, 
	0x38, 0x1F, 0x30, 0x19, 0x18, 0x10, 0x08, 0x07, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x18, 0x0D, 0x30, 0x1B, 0x38, 0x1F, 
	0x30, 0x1A, 0x18, 0x0F, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x08, 0x06, 0x20, 0x12, 0x30, 0x1B, 0x28, 0x19, 
	0x18, 0x0D, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x08, 0x07, 0x18, 0x0F, 0x20, 0x13, 0x18, 0x0E, 
	0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x08, 0x05, 0x08, 0x06, 0x00, 0x04, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};


static const picture_info_struct pic_low_power_icon_info = {
	.addr = (const unsigned char *)pic_low_power_icon_data,
	.width = 40,
	.height = 50,
	.alpha = 0,
	.external_flag = 0,
};

static const gui_image_struct gui_lowpower_icon_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_low_power_icon_info,
};


static gui_canvas_struct gui_lowpower_circle_shape =
{
    .type = TYPE_GUI_DRAW_SHAPE_CIRCLE,
    .AA = 1,
    .penSize = 5,
    .penColor = COLOR_RGB(255, 0, 56),
    .canvas.circle.cx = LCD_SIZE_HALF_WIDTH,
    .canvas.circle.cy = LCD_SIZE_HALF_HEIGHT,
    .canvas.circle.r = 64,
};

static const gui_number_image_list_struct gui_lp_number_images =
{
	.number = 
	{
		&pic_ota_num_0_info,
		&pic_ota_num_1_info,
		&pic_ota_num_2_info,
		&pic_ota_num_3_info,
		&pic_ota_num_4_info,
		&pic_ota_num_5_info,
		&pic_ota_num_6_info,
		&pic_ota_num_7_info,
		&pic_ota_num_8_info,
		&pic_ota_num_9_info,
	},
	.dot = &pic_ota_num_dot_info,
	.colon = &pic_ota_num_col_info,
	.percent = &pic_ota_num_010_info,
};

static const gui_image_number_struct gui_lp_number =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.number_image_list = &gui_lp_number_images,
	.value.string = "100%",
};

//
static const gui_widget_struct gui_lowpower_icon_widget[] =
{
	{
		.type = TYPE_GUI_CONTROL_IMAGE,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
		.visible= 1,
        .child_num = 1,
        .children = &gui_lowpower_icon_image,
	},
    {
        .type = TYPE_GUI_CONTROL_CANVAS,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = 1,
        .children = &gui_lowpower_circle_shape,
    },

    {
        .id = 5,
        .type = TYPE_GUI_CONTROL_IMAGE_NUMBER,
        .y = LCD_SIZE_HALF_HEIGHT+80,
        .width = LCD_SIZE_WIDTH,
        .height = 40,
        .visible= 1,
        .child_num = 1,
        .children = &gui_lp_number,
    },
};

static const gui_screen_struct gui_lowpower_icon_screen =
{
	.children = gui_lowpower_icon_widget,
	.child_num = countof(gui_lowpower_icon_widget),
};


static void app_lowpower_update(void)
{
    app_battery_info_struct* batt_info = application_get_battery_info();
    gui_box_struct* box = gui_surface_get_box(&gui_lowpower_icon_screen, 5);
    if (box != NULL) {
        char temp[20];
        snprintf(temp, sizeof(temp), "%d%%", batt_info->percent);
        gui_surface_box_image_number_change_string(box, (unsigned char*)temp);
    }
}

static void app_lowpoer_update_info(void* buf)
{
    app_lowpower_update();
    gui_surface_commit();
}

/*-----------------------------系统事件--------------------------------------*/

static unsigned int g_lp_timer_id;

static void app_lowpoer_icon_user_timer(unsigned int timer_id, void* param)
{
    SYS_DEBUG("app: lowpoer_timer");
    app_lowpoer_update_info(NULL);
}



static void app_lowpower_icon_init(void *buf)
{

}

static void app_lowpower_icon_load(void *buf)
{
    app_lowpower_update();
}


static void app_lowpower_icon_entry(void *buf)
{
    SYS_DEBUG("app: lowpoer_entry");
    if (g_lp_timer_id != 0) {
        application_stop_user_timer(g_lp_timer_id);
        g_lp_timer_id = 0;
    }
    g_lp_timer_id = application_start_user_timer(10000, app_lowpoer_icon_user_timer, NULL);
}


static void app_lowpower_icon_exit()
{

}

static void app_lowpower_icon_destroy()
{
    if (g_lp_timer_id != 0) {
        application_stop_user_timer(g_lp_timer_id);
        g_lp_timer_id = 0;
    }
}

/*-----------------------------配置--------------------------------------*/
static const app_window_event_struct app_lowpower_icon_static_events[] =
{
    {.id = EVENT_GUI_RESUMED,   .handler = app_lowpoer_update_info},
    {.id = EVENT_ALL}
};

static const gui_window_config_struct app_lowpower_icon_cfg =
{
    .forbid_gesture_back = 1,
    .forbid_key_back = 1,
};

const gui_window_struct app_window_lowpower_icon =
{
	.screen = &gui_lowpower_icon_screen,
    .config = &app_lowpower_icon_cfg,

	.init = app_lowpower_icon_init,
	.load = app_lowpower_icon_load,
	.entry = app_lowpower_icon_entry,
	.exit = app_lowpower_icon_exit,
	.destroy = app_lowpower_icon_destroy,

    .event_num = countof(app_lowpower_icon_static_events),
    .events = app_lowpower_icon_static_events,
};




