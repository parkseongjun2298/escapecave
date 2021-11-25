#pragma once
#include "Obj.h"
class CBossMonster : public CObj
{
	enum PATTERN {NORMAL, SKY, BULLET36, PATTERN_END};
public:
	CBossMonster(GLuint* _shader_program);
	~CBossMonster();




	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Draw() override;
	virtual void Release() override;
	virtual void Set_ModelTransform() override;
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

