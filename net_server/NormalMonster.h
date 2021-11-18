#pragma once
#include "Obj.h"
class CNormalMonster : public Obj
{
public:
	CNormalMonster(glm::vec3 pos);

	// CObj을(를) 통해 상속됨
	virtual int Update() override;

private:
	// void Add_Bullet();
	// float bullet_time;
	// glm::vec3 BulletDir;
};