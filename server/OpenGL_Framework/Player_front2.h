#pragma once
#include "Obj.h"
class CPlayer_front2 : public CObj
{
public:
	CPlayer_front2(GLuint* _shader_program);
	~CPlayer_front2();

public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Draw() override;
	virtual void Release() override;
	virtual void Set_ModelTransform() override;
};

