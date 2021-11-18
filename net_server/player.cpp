#include "Player.h"

Player::Player()
{
	info.Translate = glm::vec3(0.0, 0.0, 0.2);
	info.hp = 1;
	m_fSpeed = 0.3f;
}

int Player::Update()
{
	if (!info.hp)
		return 0;

	// 醚藕 磊悼 积己 何盒
	bullet_time += 0.1f;
	if (bullet_time > 2.f)
	{
		bullet_time = 0;
		if (m_State == NORMAL_BULLET)
			printf("醚藕积己\n");
			//Add_Bullet();
		else
			printf("醚藕3惯积己\n");
			//Double_Bullet();
	}
	switch (key) {
		case 'a':
			info.Translate.x -= m_fSpeed;
			printf("a");
			break;
		case 's':
			info.Translate.z += m_fSpeed;
			printf("s");
			break;
		case 'd':
			info.Translate.x += m_fSpeed;
			printf("d");
			break;
		case 'w':
			info.Translate.z -= m_fSpeed;
			printf("w");
			break;
		case 'z':
			printf("z");
			//Add_Bomb();
			break;
		case 'x':
			if (m_State == NORMAL_BULLET)
				m_State = DOUBLE_BULLET;
			else
				m_State = NORMAL_BULLET;
			break;
	}
	key = '0';
	if (info.Translate.x <= -20.f)
		info.Translate.x = -20.f;
	else if (info.Translate.x >= 20.f)
		info.Translate.x = 20.f;

	return 1;
}