#include "gui_core.h"
#include "gui_drivers_display.h"

static GUI_COLOR   g_current_color;
static GUI_COLOR   g_bg_color;


GUI_COLOR gui_set_color(GUI_COLOR color)
{
    GUI_COLOR old_color;

    old_color = g_current_color;

    g_current_color = color;

    return old_color;
}

GUI_COLOR gui_get_color(void)
{
	GUI_COLOR color;

	color = g_current_color;

	return color;
}

GUI_COLOR gui_set_bg_color(GUI_COLOR bg_color)
{
	GUI_COLOR old_bg_color;

	old_bg_color = g_bg_color;
	g_bg_color = bg_color;

	return old_bg_color;
}

GUI_COLOR gui_get_bg_color(void)
{
	GUI_COLOR bg_color;

	bg_color = g_bg_color;

	return bg_color;
}


unsigned char gui_run_time_lock()
{
	static short count = 0;
	if(count < 5)
	{
		count++;
		return 1;
	}
	count = 0;
	return 0;
}

SHARE_CACHE_RAM_FUNCTION unsigned short gui_get_alpha_color(unsigned char* frame_buf,unsigned char* pic_buf,unsigned char alpha)
{
#if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
	unsigned short bg_color_hi = ((*frame_buf++) << 8);
	unsigned short bg_color = bg_color_hi + (*frame_buf++);
	unsigned short r_b = (bg_color >> 0)&0x1F;
	unsigned short g_b = (bg_color >> 5)&0x3F;
	unsigned short b_b = (bg_color >> 11)&0x1F;

	unsigned short pic_color_hi = ((*pic_buf++) << 8);
	unsigned short pic_color = pic_color_hi + (*pic_buf++);
	unsigned short r = (pic_color >> 0)&0x1F;
	unsigned short g = (pic_color >> 5)&0x3F;
	unsigned short b = (pic_color >> 11)&0x1F;
	r = (r*alpha + r_b*(0xFF-alpha))/0xFF;
	g = (g*alpha + g_b*(0xFF-alpha))/0xFF;
	b = (b*alpha + b_b*(0xFF-alpha))/0xFF;
	if(r > 0x1F) r = 0x1F;
	if(g > 0x3F) g = 0x3F;
	if(b > 0x1F) b = 0x1F;
	return (r << 0)+(g << 5)+(b << 11);
#else
	unsigned short b = ((*pic_buf++)*alpha + (*frame_buf++)*(0xFF-alpha))/0xFF;	 // b
	unsigned short g = ((*pic_buf++)*alpha + (*frame_buf++)*(0xFF-alpha))/0xFF;	 // g
	unsigned short r = ((*pic_buf++)*alpha + (*frame_buf++)*(0xFF-alpha))/0xFF;	 // r
	return ((r&0xFF) << 0)+((g&0xFF) << 8)+((b&0xFF) << 16);
#endif

}


SHARE_CACHE_RAM_FUNCTION void gui_draw_alpha_pixel(unsigned char* frame_buf,unsigned char* pic_buf,unsigned char* frame_offset,unsigned char* pic_offset)
{
	unsigned char alpha = *pic_buf++;
	
#if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
	if (alpha == 0xFF) 
	{
		*frame_buf++ = *pic_buf++;
		*frame_buf++ = *pic_buf++;
	}
	else if (alpha != 0) 
	{
		unsigned short pic_color = gui_get_alpha_color(frame_buf,pic_buf,alpha);
		*frame_buf++ = (pic_color >> 8)&0xFF;
		*frame_buf++ = pic_color & 0xFF;
	}
#else
	if (alpha == 0xFF) {
		*frame_buf++ = *pic_buf++;
		*frame_buf++ = *pic_buf++;
		*frame_buf++ = *pic_buf++;
	}
	else if (alpha != 0) {
		*frame_buf++ = ((*pic_buf++)*alpha + (*frame_buf)*(0xFF-alpha))/0xFF;	 // b
		*frame_buf++ = ((*pic_buf++)*alpha + (*frame_buf)*(0xFF-alpha))/0xFF;	 // g
		*frame_buf++ = ((*pic_buf++)*alpha + (*frame_buf)*(0xFF-alpha))/0xFF;	 // r
	}
#endif
	*frame_offset = COLOR_RGB_PIXEL;
	*pic_offset = COLOR_RGB_PIXEL+1;
}


unsigned char gui_display_mutex_create()
{
    return 0;
}

// ��ȡˢ���ź��� ....
// ������ wait - �Ƿ�Ҫ�ȴ�
// ���أ� 0 - ʧ�ܣ� 1 - �ɹ�...
unsigned char gui_display_mutex_lock(unsigned int wait)
{
#if GUI_RENDER_BUFFER_TOTAL_SUPPORT >= 3
	return 1;
#else
	return gui_display_take_mutex(wait);
#endif
}

unsigned char gui_display_mutex_unlock()
{
#if GUI_RENDER_BUFFER_TOTAL_SUPPORT >= 3
	return 0;
#else
	gui_display_give_mutex();
	return 0;
#endif
}



