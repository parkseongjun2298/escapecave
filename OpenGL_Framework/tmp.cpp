#include "pch.h"
#include "tmp.h"
Tmp tmp = {0,0,190.f};

SEND_OBJECT_LIST s_ObjectList[OBJID::END];

// 수동 리셋, 신호 상태로 시작
HANDLE hSynchro = CreateEvent(NULL, FALSE, TRUE, NULL);