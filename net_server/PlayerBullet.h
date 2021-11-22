#pragma once

#include "Obj.h"
class PlayerBullet : public Obj
{
	
	float Create_Time;
public:

	PlayerBullet(glm::vec3 Translate);
	virtual int Update() override;
};