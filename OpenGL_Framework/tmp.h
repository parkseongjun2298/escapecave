#pragma once

struct Tmp {
	float x, y, z;
};

extern Tmp tmp;

typedef list<glm::vec3>   SEND_OBJECT_LIST;
extern SEND_OBJECT_LIST s_ObjectList[OBJID::END];
extern HANDLE hSynchro;