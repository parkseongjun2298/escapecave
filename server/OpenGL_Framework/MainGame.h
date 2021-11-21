#pragma once
#ifndef __MAINGAME_H__
#define __MAINGAME_H__
#include "Obj.h"
#include "Shader.h"

class CMainGame
{
public:
	enum STAGE{STAGE1, STAGE2, STAGE3, STAGE_END};
public:
	CMainGame() {}
	~CMainGame() {}

public:
	void Initialize_MainGame();
	void Update_MainGame();
	void Late_Update();
	void Draw_MainGame();
	void Release_MainGame();

public:
	STAGE Get_NowStage() { return m_eNowStage; }
private:
	void Monster_Stage1();
	void Monster_Stage2();
	void Monster_Stage3();
private:
	list<CObj*> list_objects[OBJID::END];
	CShader Shader;

private:
	int Stage_Monster_Wave = 0;
	STAGE m_eNowStage = STAGE1;
};

#endif // !__MAINGAME_H__
