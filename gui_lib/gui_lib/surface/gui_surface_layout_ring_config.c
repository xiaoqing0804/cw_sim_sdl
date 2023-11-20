#include "gui_surface_layout_ring_config.h" 
#include "system_util_math.h"
#include "gui_surface_node.h"

#if 0   // ·ÏÆú
static const gui_ring_position_struct* gui_ring_position_list = NULL;
static short gui_ring_position_list_num = 0;
static short gui_ring_position_real_list_num = 0;


void gui_surface_layout_ring_config_set(const gui_ring_position_struct* list,short num)
{
	gui_ring_position_list = list;
	gui_ring_position_list_num = num;
	gui_ring_position_real_list_num = num -1;
}


short gui_surface_layout_ring_config_check_index(short index)
{
	if(index < 0)
		index = (index % gui_ring_position_real_list_num) + gui_ring_position_real_list_num;
	if(index >= gui_ring_position_real_list_num)
		index = index % gui_ring_position_real_list_num;
	return index;
}


const gui_ring_position_struct* gui_surface_layout_ring_config_get(short index)
{
	if(index < 0)
		index = (index % gui_ring_position_list_num) + gui_ring_position_list_num;
	if(index >= gui_ring_position_list_num)
		index = index % gui_ring_position_list_num;
	return gui_ring_position_list + index;
}

const gui_ring_position_struct* gui_surface_layout_ring_config_get_frist()
{
	return gui_ring_position_list;
}

short gui_surface_layout_ring_config_real_count()
{
	return gui_ring_position_real_list_num;
}

short gui_surface_layout_ring_config_count()
{
	return gui_ring_position_list_num;
}

short gui_surface_layout_ring_config_get_index(short angle)
{
	const gui_ring_position_struct* curr_pos = gui_ring_position_list;
	const gui_ring_position_struct* next_pos = gui_ring_position_list + 1;
	for(short i = 0;i < gui_ring_position_real_list_num;i++)
	{
		if(angle >= curr_pos->angle && angle < next_pos->angle)
			return i;
		curr_pos++;
		next_pos++;
	}
	return 0;
}
#endif

