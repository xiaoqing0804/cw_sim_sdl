#ifndef __GUI_SURFACE_BOX_CLOCK_H__
#define __GUI_SURFACE_BOX_CLOCK_H__


enum gui_clock_item_type
{
    GUI_CLOCK_ITEM_NONE,
    GUI_CLOCK_ITEM_IMAGE,
    GUI_CLOCK_ITEM_HR_VALUE,
    GUI_CLOCK_ITEM_HR_
};






extern void gui_surface_box_clock_create(gui_box_struct* box);
extern void gui_surface_box_clock_commit(gui_box_struct* box);
extern void gui_surface_box_clock_update_time(gui_box_struct* box, int hour, int minute, int second);



#endif

