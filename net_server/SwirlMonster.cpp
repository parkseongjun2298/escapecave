#include "pch.h"
#include "SwirlMonster.h"
#include "Player.h"
// #include "MonsterBullet.h"

CSwirlMonster::CSwirlMonster(glm::vec3 pos) : Obj()
{
	info.Translate = pos;
	info.Rotate = glm::vec3(0.f, 0.f, 0.f);
	m_fSpeed = 0.1f;
	// bullet_time = 0.f;
	info.hp = 1;
	//bullet_time = 0.f;
}

int CSwirlMonster::Update()
{
	// ½¯µå?, »ç¸Á Ã³¸®
	/*if (m_bDead) {
		if (CollisionNum < 1) {
			CollisionNum++;
			m_bDead = false;
		}
		else {
			CSoundMgr::GetInstance()->PlaySound((TCHAR*)L"die.mp3", CSoundMgr::EFFECT);
			Add_Effect(20);
			return DEAD_OBJ;

		}
	}*/

	info.Translate.x += m_fSpeed;
	info.Rotate.y += 1.f;
	if (info.Translate.x <= -10.f || info.Translate.x >= 10.f)
		m_fSpeed *= -1;
}

//void CSwirlMonster::Add_Bullet()
//{
//	BulletDir = glm::vec3{ 0.f,0.f,1.f };
//	CMonsterBullet* bullet = new CMonsterBullet(shader_program, object.model_transform.Translate, BulletDir, { 102. / 255.,204. / 255.,102. / 255. });
//	CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER_BULLET, bullet);
//
//	BulletDir = glm::vec3{ 0.f,0.f,-1.f };
//	bullet = new CMonsterBullet(shader_program, object.model_transform.Translate, BulletDir, { 102. / 255.,204. / 255.,102. / 255. });
//	CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER_BULLET, bullet);
//
//
//	BulletDir = glm::vec3{ 1.f,0.f,0.f };
//	bullet = new CMonsterBullet(shader_program, object.model_transform.Translate, BulletDir, { 102. / 255.,204. / 255.,102. / 255. });
//	CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER_BULLET, bullet);
//
//
//	BulletDir = glm::vec3{ -1.f,0.f,0.f };
//	bullet = new CMonsterBullet(shader_program, object.model_transform.Translate, BulletDir,{ 102. / 255.,204. / 255.,102. / 255. });
//	CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER_BULLET, bullet);
//
//}
