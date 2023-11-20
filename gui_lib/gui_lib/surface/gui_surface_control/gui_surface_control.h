#ifndef __GUI_SURFACE_CONTROL_H__
#define __GUI_SURFACE_CONTROL_H__

#include "feature_all.h"
#include "gui_core_screen.h"
#include "gui_core_screen_control.h"
#include "gui_surface_control_date.h"
#include "gui_surface_control_time.h"
#include "gui_surface_control_bt_icon.h"
#include "gui_surface_control_animation.h"
#include "gui_surface_control_batt_icon.h"
#include "gui_surface_control_batt_label.h"
#include "gui_surface_control_switch.h"
#include "gui_surface_control_ring.h"
#include "gui_surface_control_chart.h"
#include "gui_surface_control_scrolltext.h"

extern void gui_surface_control_parse(gui_box_struct* box);
extern void gui_surface_control_exit(gui_box_struct* box);

#endif

