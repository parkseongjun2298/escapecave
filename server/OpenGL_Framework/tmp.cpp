#include "pch.h"
#include "tmp.h"

Just_tmp just_tmp[3];

MOUSE	Mouse_tmp[3];

// ���� ����, ��ȣ ���·� ����
HANDLE hSynchro = CreateEvent(NULL, FALSE, TRUE, NULL);
SEND_OBJECT_LIST s_ObjectList[OBJID::END];