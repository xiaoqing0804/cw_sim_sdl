
/***************************************************************************************/
//      date            auth            note
//--------------------------------------------------------------------------------------
//   2022-11-28       Taylor.Le         支持屏幕剪切区
//
/***************************************************************************************/

#include <math.h>

#include "picture.h"
#include "debug_info.h"

#include "gui_drivers_flash.h"
#include "gui_display_draw_lib.h"

#if PICTURE_ALPHA_POINT_FAST_SUPPORT

#pragma push
#pragma Otime

static const unsigned char c_pointer16_area[] = 
{
    0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,      // [0 ~ 15]
    1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1,         // [16 ~ 30]
    2, 2, 2, 2,  2, 2, 2, 2,  2, 2, 2, 2,  2, 2,            // [31 ~ 44]
    3, 3, 3, 3,  3, 3, 3, 3,  3, 3, 3, 3,  3, 3, 3          // [45 ~ 59]
};
static const unsigned char c_pointer16_table[60] = {
    0, 1, 2, 3,  4, 5, 6, 7,  8, 9, 10, 11,  12, 13, 14, 15,  14, 13, 12, 11,  10, 9, 8, 7,  6, 5, 4, 3,  2, 1,     // [0 ~ 29]
    0, 1, 2, 3,  4, 5, 6, 7,  8, 9, 10, 11,  12, 13, 14, 15,  14, 13, 12, 11,  10, 9, 8, 7,  6, 5, 4, 3,  2, 1,     // [30 ~ 59]
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// x, y, w, h  - 绘图区域(原点为中心点)
// cx, cy      - 图片中心点(旋转锚点)
SHARE_CACHE_RAM_FUNCTION void GUI_DrawPointer16(picture_info_struct* pics[], int x, int y, int w, int h, int cx, int cy, short value)
{
    picture_info_struct* picture_info = pics[c_pointer16_table[value]];
    if (picture_info->alpha != 9) {
        // not .apf format.
        return;
    }
	
	picture_alpha_piont_fast_struct* config = (picture_alpha_piont_fast_struct*)picture_info->config;
	unsigned int area = c_pointer16_area[value];
    
    unsigned int addr = (unsigned int)picture_info->addr;
    unsigned int scale_idx = 0;
    int disp_cx=x + w/2, disp_cy=y + h/2;       // 指针显示区的中心坐标.

#if defined(__CW_JL_G2D_IMB__)||defined(__CW_JL_G2D_IMB_EXT__)
    if (!FLOAT_EQUAL_ONE(gui_lib_ctx->scale)) {
        if (FLOAT_EQUAL_ONE(gui_lib_ctx->scale) || gui_lib_ctx->scale > 1.0f) {
        }
        else if (gui_lib_ctx->scale >= 0.9f) {
            scale_idx = 1;
        }
        else if (gui_lib_ctx->scale >= 0.75f) {
            scale_idx = 2;
        }
        else if (gui_lib_ctx->scale >= 0.55f) {
            scale_idx = 3;
        }
        else if (gui_lib_ctx->scale >= 0.25f) {
            scale_idx = 4;
        }
        else {
            return;
        }
        if (scale_idx >= picture_info->zoom_count) {
			//printf("gui: draw_pointer16, zoom exit(%d, %f)", scale_idx, gui_lib_ctx->scale);
            return;
        }
        config += scale_idx;
        addr   += config->data_offset;
    }
#endif
    //SYS_DEBUG("gui: draw_pointer16, x:%d, y:%d, w:%d, h:%d, dcx:%d, dcy:%d, cx:%d, cy:%d", x, y, w, h, disp_cx, disp_cy, cx, cy);
    
	//指针图片的显示位置
	short real_pic_start_y;
	short real_pic_end_y;
	if(area == 1 || area == 2)
	{
		real_pic_start_y = disp_cy - (config->end_y - cy);
		real_pic_end_y   = disp_cy + (cy - config->start_y);
	}
    else {
        real_pic_start_y = disp_cy - (cy - config->start_y);
        real_pic_end_y   = disp_cy + (config->end_y - cy);
    }
	if(real_pic_start_y > gui_lib_ctx->y1 || real_pic_end_y < gui_lib_ctx->y0) {
		return; // 显示位置不在当前截切区
    }
    short draw_pic_start_y = real_pic_start_y > gui_lib_ctx->y0 ? real_pic_start_y : gui_lib_ctx->y0;
    short draw_pic_end_y   = real_pic_end_y < gui_lib_ctx->y1 ? real_pic_end_y : gui_lib_ctx->y1;
    //SYS_DEBUG("gui: draw_pointer16, draw y0:%d, y1:%d", draw_pic_start_y, draw_pic_end_y);
    
    // 由显示区，找到图片数据位置
    short read_pic_start_y;
    short read_pic_end_y;
 	if(area == 1 || area == 2)
	{
        read_pic_start_y = cy - (draw_pic_end_y - disp_cy);
        read_pic_end_y   = cy + (disp_cy - draw_pic_start_y);
	}
    else {
        read_pic_start_y = cy - (disp_cy - draw_pic_start_y);
        read_pic_end_y   = cy + (draw_pic_end_y - disp_cy);
    }
	if((read_pic_start_y < config->start_y) || ((read_pic_end_y - read_pic_start_y) < 0)) {
		return;
    }
    //SYS_DEBUG("gui: draw_pointer16, read y0:%d, y1:%d", read_pic_start_y, read_pic_end_y);

	//原始图片中，读取图片时的起始地址
	unsigned int org_pic_addr_offset_y = read_pic_start_y - config->start_y;
	
	unsigned int org_pic_addr_row = 2 + config->max_width * COLOR_ARGB_PIXEL;
	unsigned int org_pic_addr_offset = org_pic_addr_offset_y * org_pic_addr_row;
	unsigned int org_pic_addr = addr + org_pic_addr_offset; 
	

	//原始图片中，图的真实数据
	unsigned int org_pic_data_len = (read_pic_end_y - read_pic_start_y + 1) * org_pic_addr_row;
	unsigned char* org_pic_buf = picture_info->external_flag ? gui_drivers_flash_read_image_to_buff(org_pic_addr, org_pic_data_len) :(unsigned char*)org_pic_addr;
	
	unsigned char frame_offset,pic_offset;
	
	short org_pic_data_start_x,org_pic_data_end_x;
	short real_pic_start_x,real_pic_end_x;
	
	unsigned char* curr_frame_buf;

	short org_pic_curr_y = draw_pic_start_y;
	short real_pic_curr_y;

	//把图上的数据按不同的象限刷出来
    while(org_pic_curr_y <= draw_pic_end_y) 
	{
		//取出数据的开始X坐标
		org_pic_data_start_x = disp_cx - cx;        // = x;
		org_pic_data_start_x += (short)(*org_pic_buf++);
		org_pic_data_start_x += (short)((*org_pic_buf++)<<8);
		org_pic_data_end_x = org_pic_data_start_x + config->max_width;

		if(area == 0)
		{
			//根据数据得到对称的映射坐标
			real_pic_start_x = org_pic_data_start_x;
			real_pic_end_x = org_pic_data_end_x;
			real_pic_curr_y = org_pic_curr_y;

            //屏幕截切区[x0 : x1] 2022-11-28
            if (real_pic_end_x < gui_lib_ctx->x0 || real_pic_start_x > gui_lib_ctx->x1) {
                org_pic_buf += (config->max_width*COLOR_ARGB_PIXEL);
                org_pic_curr_y++;
                continue;       // 下一行
            }

			//屏幕buff的偏移
			curr_frame_buf = gui_lib_ctx->frame_buffer + (real_pic_curr_y - gui_lib_ctx->y0) * gui_lib_ctx->bw;
			curr_frame_buf += (real_pic_start_x >= gui_lib_ctx->x0) ? (real_pic_start_x-gui_lib_ctx->x0) * COLOR_RGB_PIXEL : 0;
				
			while(real_pic_start_x < real_pic_end_x) 
			{
				if (real_pic_start_x >= gui_lib_ctx->x0 && real_pic_start_x <= gui_lib_ctx->x1)
				{
					gui_draw_alpha_pixel(curr_frame_buf,org_pic_buf,&frame_offset,&pic_offset);
					curr_frame_buf += frame_offset;
				}
				org_pic_buf += COLOR_ARGB_PIXEL;
				real_pic_start_x++;
			}
		}
		else if(area == 1)
		{
			real_pic_start_x = org_pic_data_start_x;
			real_pic_end_x = org_pic_data_end_x;
			real_pic_curr_y = draw_pic_end_y - (org_pic_curr_y - draw_pic_start_y);
			
            //屏幕截切区[x0 : x1] 2022-11-28
            if (real_pic_end_x < gui_lib_ctx->x0 || real_pic_start_x > gui_lib_ctx->x1) {
                org_pic_buf += (config->max_width*COLOR_ARGB_PIXEL);
                org_pic_curr_y++;
                continue;       // 下一行
            }

			//屏幕buff的偏移
			curr_frame_buf = gui_lib_ctx->frame_buffer + (real_pic_curr_y - gui_lib_ctx->y0) * gui_lib_ctx->bw;
			curr_frame_buf += (real_pic_start_x >= gui_lib_ctx->x0) ? (real_pic_start_x-gui_lib_ctx->x0) * COLOR_RGB_PIXEL : 0;
						
			while(real_pic_start_x < real_pic_end_x) 
			{
				if (real_pic_start_x >= gui_lib_ctx->x0 && real_pic_start_x <= gui_lib_ctx->x1)
				{
					gui_draw_alpha_pixel(curr_frame_buf,org_pic_buf,&frame_offset,&pic_offset);
					curr_frame_buf += frame_offset;
				}
				org_pic_buf += COLOR_ARGB_PIXEL;
				real_pic_start_x++;
			}
			
		}
		else if(area == 2)
		{
			real_pic_start_x = disp_cx - (org_pic_data_start_x - disp_cx);
			real_pic_end_x = real_pic_start_x - config->max_width;
			real_pic_curr_y = draw_pic_end_y - (org_pic_curr_y - draw_pic_start_y);   //   cy + (cy - org_pic_curr_y);

            //屏幕截切区[x0 : x1] 2022-11-28
            if (real_pic_start_x < gui_lib_ctx->x0 || real_pic_end_x > gui_lib_ctx->x1) {
                org_pic_buf += (config->max_width*COLOR_ARGB_PIXEL);
                org_pic_curr_y++;
                continue;       // 下一行
            }

			//屏幕buff的偏移
			curr_frame_buf = gui_lib_ctx->frame_buffer + (real_pic_curr_y - gui_lib_ctx->y0) * gui_lib_ctx->bw;
			curr_frame_buf += (real_pic_start_x <= gui_lib_ctx->x1) ? (real_pic_start_x-gui_lib_ctx->x0) * COLOR_RGB_PIXEL : (gui_lib_ctx->x1-gui_lib_ctx->x0) * COLOR_RGB_PIXEL;
			
			while(real_pic_start_x > real_pic_end_x ) 
			{
				if (real_pic_start_x >= gui_lib_ctx->x0 && real_pic_start_x <= gui_lib_ctx->x1)
				{
					gui_draw_alpha_pixel(curr_frame_buf,org_pic_buf,&frame_offset,&pic_offset);
					curr_frame_buf -= frame_offset;
				}
				org_pic_buf += COLOR_ARGB_PIXEL;
				real_pic_start_x--;
			}
				
		}		
		else if(area == 3)
		{
			real_pic_start_x = disp_cx - (org_pic_data_start_x - disp_cx);
			real_pic_end_x = real_pic_start_x - config->max_width;
			real_pic_curr_y = org_pic_curr_y;

            //屏幕截切区[x0 : x1] 2022-11-28
            if (real_pic_start_x < gui_lib_ctx->x0 || real_pic_end_x > gui_lib_ctx->x1) {
                org_pic_buf += (config->max_width*COLOR_ARGB_PIXEL);
                org_pic_curr_y++;
                continue;       // 下一行
            }

			//屏幕buff的偏移
			curr_frame_buf = gui_lib_ctx->frame_buffer + (real_pic_curr_y - gui_lib_ctx->y0) * gui_lib_ctx->bw;
			curr_frame_buf += (real_pic_start_x <= gui_lib_ctx->x1) ? (real_pic_start_x-gui_lib_ctx->x0) * COLOR_RGB_PIXEL : (gui_lib_ctx->x1-gui_lib_ctx->x0) * COLOR_RGB_PIXEL;
			
			while(real_pic_start_x > real_pic_end_x) 
			{
				if (real_pic_start_x >= gui_lib_ctx->x0 && real_pic_start_x <= gui_lib_ctx->x1)
				{
					gui_draw_alpha_pixel(curr_frame_buf,org_pic_buf,&frame_offset,&pic_offset);
					curr_frame_buf -= frame_offset;
				}
				org_pic_buf += COLOR_ARGB_PIXEL;
				real_pic_start_x--;
			}

		}

		org_pic_curr_y++;
		
    }
}

#pragma pop
#endif


