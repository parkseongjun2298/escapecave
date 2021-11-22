#include "Player.h"
#include"PlayerBullet.h"


Player::Player()
{
	info.Translate = glm::vec3(0.0, 0.0, 0.2);
	info.hp = 1;
	m_fSpeed = 0.3f;
	bullet_time = 0.f;
}

int Player::Update()
{
	if (!info.hp)
		return 0;
	//cout << "�����÷��̾������Ʈ" << endl;
	//��ź �ڵ� ���� �κ�
	bullet_time += 0.1f;
	if (bullet_time > 2.f)
	{
		//m_State�� �˾ƾߵ�
		Add_Bullet(info.Translate);
		bullet_time = 0;
		
		if (m_State == NORMAL_BULLET)
		{
			printf("��ź����\n");
			Add_Bullet(info.Translate);
		}
		else
			printf("��ź3�߻���\n");
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

void Player::Add_Bullet(glm::vec3 _location)
{
	PlayerBullet* bullet = new PlayerBullet(_location);
	NetShare::m_ObjectList[OBJID::PLAYER_BULLET].push_back(bullet);
	

}