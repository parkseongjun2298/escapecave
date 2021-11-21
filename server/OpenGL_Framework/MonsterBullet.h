#pragma once
#include "Obj.h"
class CMonsterBullet :
    public CObj
{

public:
	CMonsterBullet(GLuint* _shader_program, glm::vec3 pos, glm::vec3 dir, glm::vec3 _color = { 0.8, 0.8, 0.8 });
	~CMonsterBullet();




	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Draw() override;
	virtual void Release() override;
	virtual void Set_ModelTransform() override;

private:
	float Create_Time = 0;
	glm::vec3 f_dir;
	glm::vec3 m_vColor;
	int m_EffectNum = 0;
};

