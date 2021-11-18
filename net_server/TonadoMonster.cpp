#include "pch.h"
#include "TonadoMonster.h"

//#include "MonsterBullet.h"
//#include "ObjMgr.h"
CTonadoMonster::CTonadoMonster(glm::vec3 pos) : Obj()
{
	info.Translate = pos;
	info.Rotate.y = 0.f;
	m_fSpeed = 0.05f;
	//bullet_time = 0.f;
	//BulletDir = glm::vec3{ 0.f,0.f,1.f };
	angle = 0.f;
}

int CTonadoMonster::Update()
{
	info.Rotate.y += 10.f;
	// »ç¸Á Ã³¸®
	/*if (m_bDead) {
		if (Collision_Time < 2.f)
		{
			m_bDead = false;
			Collision_Time++;
		}
		else {
			CSoundMgr::GetInstance()->PlaySound((TCHAR*)L"die.mp3", CSoundMgr::EFFECT);
			Add_Effect(20);
			return DEAD_OBJ;

		}

	}*/

	info.Translate.x += m_fSpeed;
	angle += 0.09f;
	//BulletDir.x = sin(angle);
	//BulletDir.z = -cos(angle);
	

	if (info.Translate.x <= -20.f || info.Translate.x >= 20.f)
		m_fSpeed *= -1;

	/*bullet_time += 0.1f;
	if (bullet_time > 1.f)
	{
		bullet_time = 0;
		Add_Bullet();

	}

	cout << angle << endl;*/
	return 0;
}

//void CTonadoMonster::Add_Bullet()
//{
//	
//	CMonsterBullet* bullet = new CMonsterBullet(shader_program, object.model_transform.Translate, glm::normalize(BulletDir), { 204. / 255.,153. / 255.,204. / 255. });
//	CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER_BULLET, bullet);
//
//	
//}