#include "pch.h"
#include "BossMonster.h"
#include "Boss_head.h"
#include "NormalMonster.h"
#include "ShiledMonster.h"
//#include "MonsterBullet.h"
#include "TonadoMonster.h"
CBossMonster::CBossMonster() : Obj()
{
	info.Translate = { 0.f,10.f,-150.f };
	m_AttackTime = 500;
	info.Rotate = glm::vec3(0.f, 0.f, 0.f);
	info.hp = 1;
}

int CBossMonster::Update()
{
	m_AttackTime++;
	if (m_AttackTime > 1000) {
		m_AttackTime = 0;
		Attack();

	}
	info.Rotate.y += 2.f;

	// ∏ÛΩ∫≈Õ ªÁ∏¡
	/*if (m_bDead) {

		if (m_Collision_Time < 200) {
			m_Collision_Time++;
			m_bDead = false;
			Add_Effect(1);
		}
		else {
			CSoundMgr::GetInstance()->PlaySound((TCHAR*)L"die.mp3", CSoundMgr::EFFECT);
			Add_Effect(100);
			return m_bDead;
		}
			
	}*/
	return 0;
}

void CBossMonster::Attack()
{
	PATTERN random = (PATTERN)(rand() % 3);

	switch (random)
	{
	case CBossMonster::NORMAL:
		Noraml_Attack();
		break;
	case CBossMonster::SKY:
		Sky_Attack();
		break;
	case CBossMonster::BULLET36:
		bullet36_Attack();
		break;
	default:
		break;
	}
}

//void CBossMonster::Noraml_Attack()
//{
//
//	CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CNormalMonster(shader_program, glm::vec3{ -19.f, 0.f, -120.f }));
//	CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CShiledMonster(shader_program, glm::vec3{ -19.f, 0.f, -120.f }));
//
//	CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CNormalMonster(shader_program, glm::vec3{ 19.f, 0.f, -120.f }));
//	CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CShiledMonster(shader_program, glm::vec3{ 19.f, 0.f, -120.f }));
//	CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CNormalMonster(shader_program, glm::vec3{ -19.f, 0.f, -180.f }));
//	CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CShiledMonster(shader_program, glm::vec3{ -19.f, 0.f, -180.f }));
//
//	CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CNormalMonster(shader_program, glm::vec3{ 19.f, 0.f, -180.f }));
//	CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CShiledMonster(shader_program, glm::vec3{ 19.f, 0.f, -180.f }));
//}
//
//void CBossMonster::Sky_Attack()
//{
//	for (int i = 0; i < 100; ++i) {
//		int randomX = rand() % 40 - 20;
//		int randomY = rand() % 20 + 30;
//		int randomZ = rand() % 100 - 180;
//		glm::vec3 pos = { (float)randomX,(float)randomY, (float)randomZ };
//		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER_BULLET, new CMonsterBullet(shader_program, pos, { 0.f,-2.f,0.f }, { 102. / 255.,51. / 255.,0. }));
//	}
//	m_AttackTime = 500;
//}
//
//void CBossMonster::bullet36_Attack()
//{
//	glm::vec3 pos = object.model_transform.Translate;
//	pos.y = 0.f;
//	CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER_BULLET, new CTonadoMonster(shader_program,pos));
//	pos.z += 20.f;
//
//	CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER_BULLET, new CTonadoMonster(shader_program, pos));
//	m_AttackTime = 500;
//
//}
