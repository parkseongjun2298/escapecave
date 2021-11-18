#pragma once
#include "Obj.h"
class CBoss_head : public Obj
{

public:
	CBoss_head();

	// CObj을(를) 통해 상속됨
	virtual int Update() override;
};

