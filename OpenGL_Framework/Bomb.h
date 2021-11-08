#pragma once
#include "Obj.h"
class CBomb : public CObj
{
public:

public:
	CBomb(GLuint* _shader_program, glm::vec3 pos);
	~CBomb();




	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Draw() override;
	virtual void Release() override;
	virtual void Set_ModelTransform() override;

public:
	void Add_Bullet();
private:
	bool  m_bScaleBigger = false;
	float m_Create_Time = 0.f;

};

