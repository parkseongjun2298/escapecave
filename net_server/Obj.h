#pragma once

#include "struct.h"
using namespace std;
class Obj
{
protected:
	ObjectInfo info;
	float m_fSpeed;
public:
	void print();
	char key = '0';
	virtual int Update() = 0;
};