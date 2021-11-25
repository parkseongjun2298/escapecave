#include "pch.h"
#include "tmp.h"

Just_tmp just_tmp;
// 수동 리셋, 신호 상태로 시작
HANDLE hSynchro = CreateEvent(NULL, FALSE, TRUE, NULL);
SEND_OBJECT_LIST s_ObjectList[OBJID::END];