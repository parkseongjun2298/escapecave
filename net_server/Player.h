#pragma once

#include "Obj.h"
#include"NetShare.h"
class Player : public Obj,NetShare
{
	enum STATE { NORMAL_BULLET, DOUBLE_BULLET, STATE_END };
	STATE m_State = NORMAL_BULLET;
	float bullet_time;
public:

	Player();
	virtual int Update() override;


private:
	void Add_Bullet(glm::vec3 _location = {});
};