#ifndef __GUI_CORE_DEFINE_H__
#define __GUI_CORE_DEFINE_H__

#define GUI_ALIGN_NONE			0x80

#define GUI_ALIGN_HCENTER		0x01
#define GUI_ALIGN_LEFT			0x02
#define GUI_ALIGN_RIGHT			0x04

#define GUI_ALIGN_VCENTER		0x10
#define GUI_ALIGN_TOP			0x20
#define GUI_ALIGN_BOTTOM		0x40

#define GUI_ALIGN_MERGE(horizontal,vertical)	((horizontal) | (vertical))

#define GUI_ALIGN_IS_NONE(align)		((align) == GUI_ALIGN_NONE)

#define GUI_ALIGN_IS_HCENTER(align)		(((align) & GUI_ALIGN_HCENTER) == GUI_ALIGN_HCENTER)
#define GUI_ALIGN_IS_LEFT(align)		(((align) & GUI_ALIGN_LEFT) == GUI_ALIGN_LEFT)
#define GUI_ALIGN_IS_RIGHT(align)		(((align) & GUI_ALIGN_RIGHT) == GUI_ALIGN_RIGHT)

#define GUI_ALIGN_IS_VCENTER(align)		(((align) & GUI_ALIGN_VCENTER) == GUI_ALIGN_VCENTER)
#define GUI_ALIGN_IS_TOP(align)			(((align) & GUI_ALIGN_TOP) == GUI_ALIGN_TOP)
#define GUI_ALIGN_IS_BOTTOM(align)		(((align) & GUI_ALIGN_BOTTOM) == GUI_ALIGN_BOTTOM)

#define GUI_ALIGN_ADD_HCENTER(align)	align |= GUI_ALIGN_HCENTER
#define GUI_ALIGN_ADD_LEFT(align)		align |= GUI_ALIGN_LEFT
#define GUI_ALIGN_ADD_RIGHT(align)		align |= GUI_ALIGN_RIGHT

#define GUI_ALIGN_ADD_VCENTER(align)	align |= GUI_ALIGN_VCENTER
#define GUI_ALIGN_ADD_TOP(align)		align |= GUI_ALIGN_TOP
#define GUI_ALIGN_ADD_BOTTOM(align)		align |= GUI_ALIGN_BOTTOM

#define GUI_ALIGN_CLEAR(align)			align = GUI_ALIGN_NONE


#endif

