#include "debug_info.h"

#include "system_util_all.h"
#include "language.h"
#include "font_lang.h"
#include "font_bound.h"
#include "font_convert.h"
#include "feature_all.h"

#include "gui_surface_box_label.h"
#include "gui_surface_box_label_scroll.h"
#include "gui_surface_cache.h"
#include "gui_surface_box.h"
#include "gui_surface_node.h"
#include "gui_util_text_string.h"

// text-box与box、node的关系
//  +----------------------------------+
//  |box                               |
//  |  +---------------------------+   |
//  |  |root node(text box)        |   |
//  |  |  {                        |   |
//  |  |    char node 0            |   |
//  |  |     char node 1           |   |
//  |  |      char node 2          |   |
//  |  |       char node 3         |   |
//  |  |        char node 4        |   |
//  |  |  }                        |   |
//  |  +---------------------------+   |
//  |                                  |
//  +----------------------------------+
//


static unsigned short g_font_lang_unicode[FONT_UTF8_TO_UNICODE_SIZE];

void gui_surface_box_label_check_scroll(gui_box_struct* box, gui_node_struct* text_box, const gui_font_struct* text, short text_width)
{
    if (box != NULL && text_box != NULL)
    {
        gui_widget_struct* widget = box->widget;
        if (widget != NULL && widget->clip)
        {
            if (text_box->is_scroll)
            {
                if (text->auto_wrap == 1)
                {
                    text_box->is_scroll = 0;
                }
                else
                {
                    if (text_width <= text_box->width)
                    {
                        text_box->is_scroll = 0;
                    }
                }
            }
        }
		else
		{
			text_box->is_scroll = 0;
		}
    }
}

void gui_surface_box_label_check_clip(gui_box_struct* box,gui_node_struct* text_box)
{
    if (box != NULL && text_box != NULL)
    {
        gui_node_struct* node = text_box->child;
        while (node != NULL)
        {
            if (node->type == TYPE_GUI_DRAW_TEXT)
            {
                gui_surface_node_compose_check_clip(box, text_box, node, node->width, node->height);
            }
            node = node->child;
        }
    }
}

short gui_surface_box_label_get_text_box_offset_x(gui_box_struct* box,const gui_font_struct* text,short width)
{
    short offset_x = 0;
    if (GUI_ALIGN_IS_HCENTER(text->align))
    {
        offset_x = (box->width - width) / 2;
    }
    else if (GUI_ALIGN_IS_RIGHT(text->align))
    {
        offset_x = box->width - width;
    }
    else if (GUI_ALIGN_IS_LEFT(text->align))
    {
        offset_x = 0;
    }
    else
    {
        offset_x = text->x;
    }
    return offset_x;
}

short gui_surface_box_label_get_text_box_offset_y(gui_box_struct* box,const gui_font_struct* text,short height)
{
    short offset_y = 0;
    if (GUI_ALIGN_IS_VCENTER(text->align))
    {
        offset_y = (box->height - height) / 2;
    }
    else if (GUI_ALIGN_IS_BOTTOM(text->align))
    {
        offset_y = box->height - height;
    }
    else if (GUI_ALIGN_IS_TOP(text->align))
    {
        offset_y = 0;
    }
    else
    {
        offset_y = text->y;
    }
	return offset_y;
}



short gui_surface_box_label_get_row_offset_x(gui_node_struct* text_box, const gui_font_struct* text, short width)
{
	short offset_x = 0;

    if (width > text_box->width)
    {
        if (font_lang_is_right_to_left())
        {
            offset_x = text_box->width;
        }
        else
        {
            offset_x = 0;
        }
        return offset_x;
    }

	if(GUI_ALIGN_IS_HCENTER(text->value_align))
	{
		offset_x = (text_box->width - width) / 2;
	}
	else if(GUI_ALIGN_IS_RIGHT(text->value_align))
	{
		if(font_lang_is_right_to_left())
			offset_x = 0;
		else
			offset_x = text_box->width - width;
	}
	else if(GUI_ALIGN_IS_LEFT(text->value_align))
	{
		if(font_lang_is_right_to_left())
			offset_x = text_box->width - width;
		else
			offset_x = 0;
	}
	else
	{
		if(font_lang_is_right_to_left())
		{
			offset_x = text_box->width - width;
		}
	}
	return offset_x;
}

short gui_surface_box_label_get_offset_y(gui_node_struct* text_box, const gui_font_struct* text, short height)
{
	short offset_y = 0;
	if(GUI_ALIGN_IS_VCENTER(text->value_align))
		offset_y = (text_box->height - height) / 2;     // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
	else if(GUI_ALIGN_IS_BOTTOM(text->value_align))
		offset_y = text_box->height - height;           // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
	else if(GUI_ALIGN_IS_TOP(text->value_align))
		offset_y = 0;
	return offset_y;
}

void gui_surface_box_label_align_row_offset(gui_node_struct* row_start_node,gui_node_struct* row_end_node, short offset_x)
{
	while(row_start_node != row_end_node)
	{				
		row_start_node->x += offset_x;
		row_start_node = row_start_node->child;
	}
}

void gui_surface_box_label_align_vertical_offset(gui_node_struct* row_start_node,gui_node_struct* row_end_node, short offset_y)
{
	while(row_start_node != row_end_node)
	{				
		row_start_node->y += offset_y;
		row_start_node = row_start_node->child;
	}
}

void gui_surface_box_label_adjust_position(gui_node_struct* row_start_node, gui_node_struct* row_end_node)
{
    while (row_start_node != NULL && row_start_node != row_end_node)
    {
        row_start_node->x += row_start_node->clip_x;
        row_start_node->y += row_start_node->clip_y;
        row_start_node->width = row_start_node->clip_width;
        row_start_node->height = row_start_node->clip_height;

        row_start_node->clip_x = 0;
        row_start_node->clip_y = 0;

        row_start_node = row_start_node->child;
    }
}

//排列顺序为右到左的，把它切换到左到右
void gui_surface_box_label_change_right2left_to_left2right(gui_node_struct* right2left_start_node, gui_node_struct* right2left_end_node)
{
	if(right2left_start_node != NULL && right2left_end_node != NULL)
	{
		short number_start_x = right2left_end_node->x;
		while(right2left_start_node != right2left_end_node->child)
		{
			right2left_start_node->x = number_start_x;
			number_start_x += right2left_start_node->width;
			right2left_start_node = right2left_start_node->child;
		}
	}
}

//切换排列顺序
void gui_surface_box_label_switch_order_direct(gui_node_struct* start_node, gui_node_struct* end_node, short frist_show_x, unsigned char direct_right2left)
{
	gui_node_struct* number_start_node = NULL;
	gui_node_struct* number_end_node = NULL;
	
	while(start_node != end_node)
	{
		if(direct_right2left == 1)
		{
			frist_show_x -= start_node->width;
			start_node->x = frist_show_x;
		}
		else
		{
			start_node->x = frist_show_x;
			frist_show_x += start_node->width;
		}

		//从右到左显示时，数字要从左到右显示
		if(direct_right2left == 1)
		{
			if(font_bound_is_number(start_node->value))
			{
				if(number_start_node == NULL)
					number_start_node = start_node;
				number_end_node = start_node;
			}
			else if(number_start_node != NULL)
			{
				if(font_bound_is_dot(start_node->value))
				{
					number_end_node = start_node;
				}
				else
				{
					gui_surface_box_label_change_right2left_to_left2right(number_start_node,number_end_node);
					number_start_node = NULL;
					number_end_node = NULL;
				}
			}
		}
		start_node = start_node->child;
	}
	gui_surface_box_label_change_right2left_to_left2right(number_start_node,number_end_node);
}


void gui_surface_box_label_align_row_right_to_left(gui_node_struct* row_start_node, gui_node_struct* row_end_node, short max_width)
{
	//倒序语言显示
	if(font_lang_is_right_to_left())
	{
		gui_node_struct* right_to_left_start_node = NULL;
		gui_node_struct* right_to_left_end_node = NULL;
		while(row_start_node != row_end_node)
		{
			max_width -= row_start_node->width;
			row_start_node->x = max_width;
			
			if(font_bound_is_alphabet_right_to_left(row_start_node->value))
			{
				if(right_to_left_start_node != NULL)
				{
					//在同一文字中的尾部符号
					if(font_bound_is_latin_symbol(right_to_left_end_node->value))
						gui_surface_box_label_switch_order_direct(right_to_left_start_node, right_to_left_end_node, right_to_left_end_node->x+right_to_left_end_node->width, 0);
					else
						gui_surface_box_label_switch_order_direct(right_to_left_start_node, row_start_node, right_to_left_end_node->x, 0);
					right_to_left_start_node = NULL;
					right_to_left_end_node = NULL;
				}
			}
			else
			{
				if(right_to_left_start_node == NULL)
				{
					//在同一文字中的符号和数字不需要切换
					if(!font_bound_is_latin_symbol(row_start_node->value))
					{
						right_to_left_start_node = row_start_node;
					}
				}
				if(right_to_left_start_node != NULL)
				{
					right_to_left_end_node = row_start_node;
				}
			}
			row_start_node = row_start_node->child;
		}
		if(right_to_left_start_node != NULL && right_to_left_end_node != NULL)
		{
			//在同一文字中的尾部符号
			if(font_bound_is_latin_symbol(right_to_left_end_node->value))
				gui_surface_box_label_switch_order_direct(right_to_left_start_node, right_to_left_end_node, right_to_left_end_node->x+right_to_left_end_node->width, 0);
			else
				gui_surface_box_label_switch_order_direct(right_to_left_start_node, row_end_node,right_to_left_end_node->x, 0);
		}

	}
	//正序语言中夹杂倒序语言
	else
	{
		gui_node_struct* right_to_left_start_node = NULL;
		gui_node_struct* right_to_left_end_node = NULL;
		while(row_start_node != row_end_node)
		{
			if(font_bound_is_alphabet_right_to_left(row_start_node->value))
			{
				if(right_to_left_start_node == NULL)
					right_to_left_start_node = row_start_node;
				right_to_left_end_node = row_start_node;
			}
			else
			{
				if(right_to_left_start_node != NULL)
				{
					//在同一文字中的符号和数字不需要切换
					if(font_bound_is_latin_symbol(row_start_node->value) || font_bound_is_number(row_start_node->value))
					{
						right_to_left_end_node = row_start_node;
					}
					else
					{
						//在同一文字中的尾部符号
						if(font_bound_is_latin_symbol(right_to_left_end_node->value))
							gui_surface_box_label_switch_order_direct(right_to_left_start_node, right_to_left_end_node,right_to_left_end_node->x, 1);
						else
							gui_surface_box_label_switch_order_direct(right_to_left_start_node, row_start_node, row_start_node->x, 1);
						right_to_left_start_node = NULL;
						right_to_left_end_node = NULL;
					}
				}
			}
			row_start_node = row_start_node->child;
		}
		if(right_to_left_start_node != NULL && right_to_left_end_node != NULL)
		{
			gui_surface_box_label_switch_order_direct(right_to_left_start_node, NULL,right_to_left_end_node->x + right_to_left_end_node->width, 1);
		}

	}

}

//阿拉伯语和英语等左向右混和排列时处理，将node以x坐标最大到最小排列
void gui_surface_box_label_arrange_child_sort(gui_node_struct* text_box) 
{
	gui_node_struct* boot_node = NULL;
	gui_node_struct* frist_node = NULL;

	gui_node_struct* node = NULL;
	gui_node_struct* pre_node = NULL;

	gui_node_struct* min_node = NULL;
	gui_node_struct* min_pre_node = NULL;

	if (text_box != NULL && text_box->type == TYPE_GUI_DRAW_TEXT_BOX)
    {
		while (text_box->child != NULL)
		{
			node = text_box->child;
			pre_node = NULL;

			min_node = NULL;
			min_pre_node = NULL;
			while (node != NULL)
			{
				if(min_node == NULL)
				{
					min_pre_node = pre_node;
					min_node = node;
				}
				else
				{
					if (font_lang_is_right_to_left())
					{
						if(node->x > min_node->x)
						{
							min_pre_node = pre_node;
							min_node = node;
						}
					}
					else
					{
						if(node->x < min_node->x)
						{
							min_pre_node = pre_node;
							min_node = node;
						}
					}
				}
				pre_node = node;
				node = node->child;
			}

			if(min_pre_node == NULL)
			{
				text_box->child = min_node->child;
				min_node->child = NULL;
			}
			else
			{
				min_pre_node->child = min_node->child;
				min_node->child = NULL;
			}

			if(frist_node == NULL)
			{
				frist_node = min_node;
				boot_node = frist_node;
			}
			else
			{
				frist_node->child = min_node;
				frist_node = frist_node->child;
			}
		}
		text_box->child = boot_node;
    }
}
gui_node_struct* gui_surface_box_label_arrange_child_content(gui_box_struct* box,gui_node_struct* text_box, const gui_font_struct* text,unsigned char* str)
{
	//处理字符串
	memset(g_font_lang_unicode, 0, FONT_UTF8_TO_UNICODE_SIZE);
	unsigned int unicode_len = font_lang_utf8_to_unicode((const char*)str,g_font_lang_unicode);
	unsigned int letter_shape_len = font_lang_letter_shape(g_font_lang_unicode, unicode_len);
	unsigned short* font_lang_unicode = g_font_lang_unicode;
	
    unsigned char old_size = set_font_size(text->size);
	unsigned int font_height = get_font_height();
	
	gui_node_struct* curr_node = text_box;
	gui_node_struct* row_start_node = NULL;
	gui_node_struct* word_start_node = NULL;

	short curr_x = 0;
	short curr_y = text->space_y;
	short line_real_width = 0;
	font_char_info_struct char_info;
	unsigned char is_alphabet_symbol = 0;

	//now start calculate the data & display it.
	while(letter_shape_len > 0)
	{
		/* 0.handler the enter_key. */
		if(*font_lang_unicode == '\n')
		{
			//把上一行的先做对齐处理
			line_real_width = curr_x;
			gui_surface_box_label_align_row_right_to_left(row_start_node, NULL, line_real_width);
			short offset_x = gui_surface_box_label_get_row_offset_x(text_box, text, line_real_width);
			gui_surface_box_label_align_row_offset(row_start_node,NULL,offset_x);
			
			curr_x = 0;
			curr_y += font_height + text->space_y;
			
			word_start_node = NULL;
			row_start_node = NULL;
			
			font_lang_unicode++;
			letter_shape_len--;
            text_box->is_scroll = 0;
			continue;
		}
		
		int char_addr = font_get_char(get_font_size(), *font_lang_unicode, &char_info);
		if (char_addr < 0) {
			char_addr = font_get_char(get_font_size(), UCS16_INVALID_CODE, &char_info);
		}
		
		/* 3.get index unicode data. */
		if(char_addr > 0)
		{
			gui_node_struct* node = gui_surface_cache_add_node();
			node->type = TYPE_GUI_DRAW_TEXT;	// TYPE_GUI_CONTROL_LABEL => TYPE_GUI_DRAW_TEXT
			node->id = text->id;
			node->value = char_info.code;
			node->data = (void*)text;		// gui_font_struct
			node->x = curr_x;
			node->y = curr_y;
			node->width = char_info.xDist;
			node->height = font_height;
            node->tag = 0;

            node->clip_x = char_info.xPos;
            node->clip_y = char_info.yPos;
            node->clip_width  = char_info.xSize;
            node->clip_height = char_info.ySize;
            
			curr_node->child = node;

			//每行起始节点
			if(row_start_node == NULL)
			{
				row_start_node = node;
			}

			//碰到符号，表示一个单词结束了
			if(font_bound_is_alphabet_symbol(*font_lang_unicode))
			{
				word_start_node = NULL;
				line_real_width = curr_x;
				is_alphabet_symbol = 1;
			}
			else if(font_bound_is_ideogram(*font_lang_unicode))
			{
				word_start_node = NULL;
				line_real_width = curr_x;
				is_alphabet_symbol = 1;
			}
			else
			{
				if(word_start_node == NULL)
				{
					word_start_node = node;
					line_real_width = curr_x;
				}
				is_alphabet_symbol = 0;
			}

            short width = curr_x + char_info.xDist;

				//超出时换行
				if(text->auto_wrap == 1 && width > text_box->width)
				{
					curr_y += font_height + text->space_y;
					
					//单词起始与行起始不是同一个字符，把整个单词往下移，不能把单词从中间断开了
					if(word_start_node != NULL && word_start_node != row_start_node)
					{
						//把上一行的先做对齐处理
						gui_surface_box_label_align_row_right_to_left(row_start_node,word_start_node,line_real_width);
						short offset_x = gui_surface_box_label_get_row_offset_x(text_box,text,line_real_width);
						gui_surface_box_label_align_row_offset(row_start_node,word_start_node,offset_x);

						//把当前单词移到下一行
						curr_x = 0;
						gui_node_struct* offset_node = word_start_node;
						while(offset_node != NULL)
						{
							offset_node->x = curr_x;
							offset_node->y = curr_y;
							curr_x += offset_node->width;
							offset_node = offset_node->child;
						}
						row_start_node = word_start_node;
					}
					else
					{
						//把上一行的先做对齐处理
						gui_surface_box_label_align_row_right_to_left(row_start_node,node,curr_x);
						short offset_x = gui_surface_box_label_get_row_offset_x(text_box,text,line_real_width);
						gui_surface_box_label_align_row_offset(row_start_node,node,offset_x);
						
						node->x = 0;
						node->y = curr_y;
						curr_x = char_info.xDist;

						if(is_alphabet_symbol)
							word_start_node = NULL;
						else
							word_start_node = node;
						row_start_node = node;
					}
					
				}
				else
				{
					curr_x += char_info.xDist;
				}

			curr_node = node;
		}
        
        font_lang_unicode++;
        letter_shape_len--;
	}

	//把最后一行的做对齐处理
	if(row_start_node != NULL)
	{
		line_real_width = curr_x;
		gui_surface_box_label_align_row_right_to_left(row_start_node, NULL, line_real_width);
		short offset_x = gui_surface_box_label_get_row_offset_x(text_box, text, line_real_width);
		gui_surface_box_label_align_row_offset(row_start_node, NULL, offset_x);
	}

	//对Y轴进行对齐
	short max_height = curr_node->y + font_height + text->space_y;
	short offset_y = gui_surface_box_label_get_offset_y(text_box, text, max_height);
	gui_surface_box_label_align_vertical_offset(text_box->child, NULL, offset_y);

    // 坐标调整(把外框的坐标缩到字体上)
    gui_surface_box_label_adjust_position(text_box->child, NULL);

    // 启动文字滚动
	gui_surface_box_label_check_scroll(box, text_box, text, line_real_width);
	if (text_box->is_scroll)
	{
		gui_surface_box_label_arrange_child_sort(text_box);
		gui_surface_box_label_scroll_start(text_box);
	}

	// 重置剪切区
    gui_surface_box_label_check_clip(box, text_box);

    set_font_size(old_size);

	text_box->value = max_height;		// 20230609 Taylor.Le 携带会文本显示的实际高度
	return text_box;
}


gui_node_struct* gui_surface_box_label_arrange_textbox(gui_box_struct* box, const gui_font_struct* text,unsigned char* str,short x,short y,short width,short height)
{
	//主节点
	gui_node_struct* boot_node = gui_surface_cache_add_node();
    boot_node->type = TYPE_GUI_DRAW_TEXT_BOX;    // TYPE_GUI_CONTROL_LABEL => TYPE_GUI_DRAW_TEXT
    boot_node->id = text->id;
    boot_node->tag = 0;
    boot_node->value = 0;
	boot_node->draw = text;
    boot_node->data = (void*)text;       // gui_font_struct
    boot_node->x = x;
    boot_node->y = y;
	boot_node->width = width;
    boot_node->height = ((height == 0) ? font_get_height(text->size) : height);
	boot_node->clip_x = 0;  // x;   // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
    boot_node->clip_y = 0;  // y;   // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
	boot_node->clip_width = width;
    boot_node->clip_height = height;
    boot_node->is_scroll = text->scroll;
	boot_node->scale = GUI_INIT_SCALE(text->scale);

	//SYS_DEBUG("gui_surface_box_label_arrange_textbox boot_node->is_scroll = %d",boot_node->is_scroll);

	return gui_surface_box_label_arrange_child_content(box, boot_node, text, str);
}


gui_node_struct* gui_surface_box_label_arrange_content(gui_box_struct* box, const gui_font_struct* text,unsigned char* str)
{
	short width = text->width == 0 ? box->width : text->width;
	short height = text->height == 0 ? box->height : text->height;

	short x = gui_surface_box_label_get_text_box_offset_x(box,text,width);
	short y = gui_surface_box_label_get_text_box_offset_y(box,text,height);

	return gui_surface_box_label_arrange_textbox(box,text,str,x,y,width,height);
}

gui_node_struct* gui_surface_box_label_arrange_children(gui_box_struct* box, const gui_font_struct* text)
{
	unsigned char num_buff[16] = {0};
	unsigned char* str = gui_util_text_string_get_string_from_font(text,num_buff,16);
	if(str == NULL)
		return NULL;

	return gui_surface_box_label_arrange_content(box,text,str);
}


gui_node_struct* gui_surface_box_label_arrange(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;
	gui_font_struct* text = (gui_font_struct*)widget->children;
	return gui_surface_box_label_arrange_children(box,text);
}


//屏幕数组转化---------------------------------------------------------------------

void gui_surface_box_label_create(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;
	if (widget != NULL && widget->child_num > 0) 
        box->child = gui_surface_box_label_arrange(box);
	else
		box->child = NULL;
}



//界面改变--------------------------------------------------------------------------

void gui_surface_box_label_change_content(gui_box_struct* box,const gui_font_struct* text,unsigned char* str)
{
	if(box == NULL)
		return;

	gui_surface_cache_remove_nodes(box->child);
	box->child = gui_surface_box_label_arrange_content(box,text,str);
}

void gui_surface_box_label_change_position(gui_box_struct* box,const gui_font_struct* text,unsigned char* str)
{
	if(box == NULL)
		return;

	gui_surface_cache_remove_nodes(box->child);
	box->child = gui_surface_box_label_arrange_content(box,text,str);
}


void gui_surface_box_label_change_string(gui_box_struct* box,unsigned char* str)
{
	if(box == NULL)
		return;
	
	gui_widget_struct* widget = box->widget;
	const gui_font_struct* text = (const gui_font_struct*)widget->children;
	gui_surface_box_label_change_content(box,text,str);
}

void gui_surface_box_label_change_string_id(gui_box_struct* box,int string_id)
{
	if(box == NULL)
		return;
	
	unsigned char* str = (unsigned char*)GUI_Get_ID_String((STRING_ID_TYPE)string_id);
	gui_surface_box_label_change_string(box,str);
}

void gui_surface_box_label_change_number(gui_box_struct* box,int number)
{
	if(box == NULL)
		return;
	
	unsigned char buff[16] = {0};
	get_string_from_number(buff,16,number);
	gui_surface_box_label_change_string(box,buff);
}

void gui_surface_box_label_change_x(gui_box_struct* box,gui_node_struct* node,short x)
{
	if(box == NULL || node == NULL)
		return;

	node->x = x;
	//node->clip_x = x; // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
}

void gui_surface_box_label_change_y(gui_box_struct* box,gui_node_struct* node,short y)
{
	if(box == NULL || node == NULL)
		return;

	node->y = y;
	//node->clip_y = y; // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域

}

