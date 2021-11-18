#include "pch.h"
#include "NormalMonster.h"
#include "Player.h"
//#include "MonsterBullet.h"

CNormalMonster::CNormalMonster(glm::vec3 pos) : Obj()
{
	info.Translate = pos;
	info.Rotate = glm::vec3(0.f, 0.f, 0.f);
	info.hp = 1;
	m_fSpeed = 0.2f;
	// bullet_time = 0.f;
}

int CNormalMonster::Update()
{
	// 사망 업데이트
	/*if (m_bDead) {
		CSoundMgr::GetInstance()->PlaySound((TCHAR*)L"die.mp3", CSoundMgr::EFFECT);
		Add_Effect(20);
		return DEAD_OBJ;

	}*/

	// 이동 업데이트
	info.Translate.x += m_fSpeed;
	if (info.Translate.x <= -20.f || info.Translate.x >= 20.f)
		m_fSpeed *= -1;

	// 총알 생성 부분
	/*CPlayer* pPlayer = dynamic_cast<CPlayer*>(CObjectMgr::Get_Instance()->GetPlayer());
	BulletDir = pPlayer->Get_Info() - model_transform.Translate;
	vector_normalize(BulletDir);
	bullet_time += 0.1f;
	if (bullet_time > 3.f)
	{
		bullet_time = 0;
		Add_Bullet();

	}*/
	
	
	return 0;
	


	
}

// 총알 생성
//void CNormalMonster::Add_Bullet()
//{
//	CMonsterBullet* bullet = new CMonsterBullet(shader_program, object.model_transform.Translate, BulletDir, {1.f,102./255.,102./255.});
//	CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER_BULLET, bullet);
//}
