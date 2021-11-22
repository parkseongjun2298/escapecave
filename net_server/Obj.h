#pragma once

#include "struct.h"
using namespace std;
class Obj
{
protected:
	ObjectInfo info;
	float m_fSpeed;
	bool  m_bDead;
public:
	void print();
	char key = '0';
	virtual int Update() = 0;
	glm::vec3& Get_Info() { return info.model_transform.Translate; }
	glm::vec3& Get_size() { return info.model_transform.Scale; }
	void  Set_Dead() { m_bDead = true; }
};