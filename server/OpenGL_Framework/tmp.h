#pragma once
#include "enum.h"
struct Just_tmp {
	char key;
};
extern HANDLE hSynchro;

extern Just_tmp just_tmp[3];

typedef list<glm::vec3>   SEND_OBJECT_LIST;
extern SEND_OBJECT_LIST s_ObjectList[OBJID::END];