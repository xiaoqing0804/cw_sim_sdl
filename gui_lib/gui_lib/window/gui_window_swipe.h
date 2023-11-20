#ifndef __GUI_WINDOW_SWIPE_H__
#define __GUI_WINDOW_SWIPE_H__

#include "feature_all.h"
#include "gui_core_all.h"

typedef struct
{
    const gui_window_struct *window;
    const gui_window_struct *next_window;
    unsigned char direction;
    unsigned char success;//成功，就是滑动到下一页了
}gui_window_swiping_struct;

/**********************************************执行**************************************************************/
extern void gui_window_swipe_deinit(void);

/*显示副屏内容，一般是拖拽时触发，会显示双屏内容，也仅只是显示*/
extern void gui_window_swipe_start(const gui_window_struct *window,const gui_window_struct *next_window,unsigned char direction);

/*双屏在拖拽时显示*/
extern void gui_window_swipe_offset(int main_offset_x, int main_offset_y, int vice_offset_x, int vice_offset_y);
extern void gui_window_swipe_offset_main(int main_offset_x, int main_offset_y);
extern void gui_window_swipe_offset_vice(int vice_offset_x, int vice_offset_y);

/*双屏在拖拽时显示缩放*/
extern void gui_window_swipe_scale(int main_offset_x, int vice_offset_x);

extern void gui_window_swipe_end(void);

extern void gui_window_swipe_cancle(void);

extern const gui_window_struct *gui_window_swipe_get_vice(void); // 20230513 Taylor.Le, +  ui bug-fixed
extern gui_window_swiping_struct *gui_window_swipe_get_swiping(void);
extern unsigned char gui_window_swipe_is_swiping(void);

#endif
