#pragma once
#include "Obj.h"
class CGate : public CObj
{
	
public:
	CGate(GLuint* _shader_program, glm::vec3 pos);
	~CGate();




	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Draw() override;
	virtual void Release() override;
	virtual void Set_ModelTransform() override;

public:
	void Set_Open() { m_bOpen = true; }
private:
	bool m_bOpen = false;
	bool m_bSound = false;
};

