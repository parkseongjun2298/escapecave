#pragma once

#include "Obj.h"
class Player : public Obj
{
	enum STATE { NORMAL_BULLET, DOUBLE_BULLET, STATE_END };
	STATE m_State = NORMAL_BULLET;
	float bullet_time;
public:

	Player();
	virtual int Update() override;
};