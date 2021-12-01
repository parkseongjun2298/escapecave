#pragma once
#include "Obj.h"

class CPlayer : public CObj
{
	enum STATE {NORMAL_BULLET, DOUBLE_BULLET, STATE_END};
public:
	CPlayer(GLuint* _shader_program, int n);
	~CPlayer();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update( ) override;
	virtual void Late_Update() override;
	virtual void Draw() override;
	virtual void Release() override;
	virtual void Set_ModelTransform() override;

public:
	CAMERA_DESC* Get_Camera() { return &m_Camera; }
	OBJECT* Get_Light() { return &m_light; }
private:
	CAMERA_DESC m_Camera;
	OBJECT m_light;
private:
	OBJECT m_front;
	float bullet_time;
	STATE m_State = NORMAL_BULLET;
public:
	int num;
	static int p_num;
};
