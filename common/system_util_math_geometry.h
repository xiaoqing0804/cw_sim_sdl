#ifndef __SYSTEM_UTIL_MATH_GEOMETRY_H__
#define __SYSTEM_UTIL_MATH_GEOMETRY_H__

#include "feature_all.h"

/*通过点来设置矩形框*/
extern void set_rect_form_point(geometry_rect* rect,short x,short y,short width,short height);

/*通过矩形来设置矩形框*/
extern void set_rect_form_rect(geometry_rect* rect, geometry_rect* src_rect);

/*0不相交  1相交  2重合*/
extern char check_rect_intersect_rect(geometry_rect* rect1,geometry_rect* rect2);

/*0不包含  1包含*/
extern char check_rect_contain_point(geometry_rect* rect,geometry_point* point);

/*0不包含  1包含*/
extern char check_rect_contain_point_xy(geometry_rect* rect,short x, short y);

/*0不包含  1包含*/
extern char check_rect_contain_xy(short rect_x,short rect_y,short rect_width,short rect_height,short x,short y);


#endif

