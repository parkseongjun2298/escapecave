#pragma once
#include "Obj.h"
#include "MainGame.h"
class CNormalMonster :
	public CObj
{
public:
	CNormalMonster(GLuint* _shader_program, glm::vec3 pos);
	~CNormalMonster();




	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;

	virtual int Update() override;

	virtual void Late_Update() override;

	virtual void Draw() override;

	virtual void Release() override;

	virtual void Set_ModelTransform() override;
private:
	void Add_Bullet();
	float bullet_time;
	glm::vec3 BulletDir;


};

