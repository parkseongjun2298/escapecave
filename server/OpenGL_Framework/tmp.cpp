#include "pch.h"
#include "tmp.h"

Just_tmp just_tmp[3];
MOUSE	Mouse_tmp[3];
CRITICAL_SECTION cs;	//임계영역
SEND_OBJECT_LIST s_ObjectList[OBJID::END];