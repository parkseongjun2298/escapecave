#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(glm::vec3 Translate)
{
	info.Translate = Translate;
	info.hp = 1;
	m_fSpeed = 0.3f;
	Create_Time = 0.f;
}

int PlayerBullet::Update()
{
	if (!info.hp)
		return 0;

	//cout << "총알업데이트" << endl;


	Create_Time += 0.1f;
	if (Create_Time > 10)
		return 0;

	info.Translate.z -= m_fSpeed;


	return 1;
}