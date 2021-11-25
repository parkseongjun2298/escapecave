#pragma once
#include "Obj.h"
class CPlayer_Bullet : public CObj
{
public:
	CPlayer_Bullet(GLuint* _shader_program, glm::vec3 _pos, glm::vec3 _color = { 0.8, 0.8, 1.0 }, glm::vec3 _dir = {0.f,0.f,-1.f});
	~CPlayer_Bullet();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Draw() override;
	virtual void Release() override;
	virtual void Set_ModelTransform() override;

private:
	float Create_Time = 0;
	glm::vec3 m_color{};
	glm::vec3 m_vDir{};

};

