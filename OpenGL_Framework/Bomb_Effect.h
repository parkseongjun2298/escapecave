#pragma once
#include "Obj.h"
class CBomb_Effect : public CObj
{
public:
	CBomb_Effect(GLuint* _shader_program, glm::vec3 pos);
	~CBomb_Effect();




	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Draw() override;
	virtual void Release() override;
	virtual void Set_ModelTransform() override;

private:
	float m_fCreatetime = 0.f;
	glm::vec3 m_vDir{};
	glm::vec3 m_color{};

};

