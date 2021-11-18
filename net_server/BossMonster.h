#pragma once
#include "Obj.h"
class CBossMonster : public Obj
{
	enum PATTERN {NORMAL, SKY, BULLET36, PATTERN_END};
public:
	CBossMonster();

	// CObj을(를) 통해 상속됨
	virtual int Update() override;

private:
	void Attack();
	void Noraml_Attack();
	void Sky_Attack();
	void bullet36_Attack();
private:
	glm::vec3 m_color;
	int m_AttackTime = 0;
	int m_Collision_Time = 0;
};

