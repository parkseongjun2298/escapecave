#include "pch.h"
#include "tmp.h"
Tmp tmp = {0,0,190.f};

SEND_OBJECT_LIST s_ObjectList[OBJID::END];

// ���� ����, ��ȣ ���·� ����
HANDLE hSynchro = CreateEvent(NULL, FALSE, TRUE, NULL);