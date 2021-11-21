#pragma once
#include "Obj.h"
class CBoss_head : public CObj
{

public:
	CBoss_head(GLuint* _shader_program, CObj* _parent);
	~CBoss_head();




	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Draw() override;
	virtual void Release() override;
	virtual void Set_ModelTransform() override;



};

