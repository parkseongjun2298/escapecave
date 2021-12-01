#pragma once
#include "Obj.h"
class CPlayer_front3 : public CObj
{
public:
	CPlayer_front3(GLuint* _shader_program);
	~CPlayer_front3();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Draw() override;
	virtual void Release() override;
	virtual void Set_ModelTransform() override;
};

