#include "pch.h"
#include "CollisionMgr.h"
#include"Obj.h"
#include"Player.h"
#include"Player_Bullet.h"
#include"NormalMonster.h"
#include"MonsterBullet.h"
IMPLEMENT_SINGLETON(CCollisionMgr)


CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_BulletToMonster(list<CObj*> pListBullet, list<CObj*> pListMonster)
{
	for (auto& Bullet : pListBullet)
	{
		for (auto& Monster : pListMonster)
		{
			glm::vec3 vPos = Bullet->Get_Info();
			glm::vec3 vPos2 = Monster->Get_Info();
			glm::vec3 vSize = Bullet->Get_size();
			glm::vec3 vSize2 = Monster->Get_size();

			if (Check_Sphere(vPos, vSize.x,
				vPos2, vSize2.x
			))
			{
				Monster->Set_Dead();
				Bullet->Set_Dead();
				//cout << "面倒:" << endl;
			}


		}
	}

}
void CCollisionMgr::Collision_BulletToPlayer(list<CObj*> pListBullet, list<CObj*> pListPlayer)
{
	for (auto& Bullet : pListBullet)
	{
		for (auto& Player : pListPlayer)
		{
			glm::vec3 vPos = Bullet->Get_Info();
			glm::vec3 vPos2 = Player->Get_Info();
			glm::vec3 vSize = Bullet->Get_size();
			glm::vec3 vSize2 = Player->Get_size();

			if (Check_Sphere(vPos, vSize.x,
				vPos2, vSize2.x
			))
			{
				
				Bullet->Set_Dead();
				//cout << "面倒:" << endl;
			}


		}
	}
}

void CCollisionMgr::Collision_GateToMonsterBullet(list<CObj*> pGate, list<CObj*> pListBullet)
{
	for (auto& Gate : pGate)
	{
		for (auto& Bullet : pListBullet)
		{
			glm::vec3 vPos = Gate->Get_Info();
			glm::vec3 vPos2 = Bullet->Get_Info();
			glm::vec3 vSize = Gate->Get_size();
			glm::vec3 vSize2 = Bullet->Get_size();

			if (Check_Sphere(vPos, vSize.x,
				vPos2, vSize2.x
			))
			{
				
				Bullet->Set_Dead();
				cout << "面倒:" << endl;
			}


		}
	}
}

void CCollisionMgr::Collision_GateToPlayerBullet(list<CObj*> pGate, list<CObj*> pListBullet)
{
	for (auto& Gate : pGate)
	{
		for (auto& Bullet : pListBullet)
		{
			glm::vec3 vPos = Gate->Get_Info();
			glm::vec3 vPos2 = Bullet->Get_Info();
			glm::vec3 vSize = Gate->Get_size();
			glm::vec3 vSize2 = Bullet->Get_size();

			if (Check_Sphere(vPos, vSize.x,
				vPos2, vSize2.x
			))
			{

				Bullet->Set_Dead();
				cout << "面倒:" << endl;
			}


		}
	}
}

void CCollisionMgr::Collision_BulletToBullet(list<CObj*> pListBullet, list<CObj*> pListBullet2)
{
	for (auto& Bullet : pListBullet)
	{
		for (auto& Bullet2 : pListBullet2)
		{
			glm::vec3 vPos = Bullet->Get_Info();
			glm::vec3 vPos2 = Bullet2->Get_Info();
			glm::vec3 vSize = Bullet->Get_size();
			glm::vec3 vSize2 = Bullet2->Get_size();

			if (Check_Sphere(vPos, vSize.x,
				vPos2, vSize2.x
			))
			{

				Bullet->Set_Dead();
				Bullet2->Set_Dead();
				//cout << "面倒:" << endl;
			}


		}
	}

}

void CCollisionMgr::Collision_BossToPlayerBullet(list<CObj*> pListBoss, list<CObj*> pListPlayerBullet)
{
	for (auto& Boss : pListBoss)
	{
		for (auto& Bullet : pListPlayerBullet)
		{
			glm::vec3 vPos = Boss->Get_Info();
			vPos.y = 0.f;
			vPos.z = -155.f;
			glm::vec3 vPos2 = Bullet->Get_Info();
			glm::vec3 vSize = { 4.f,4.f,4.f };
			glm::vec3 vSize2 = Bullet->Get_size();

			if (Check_Sphere(vPos, vSize.x,
				vPos2, vSize2.x
			))
			{
				Bullet->Set_Dead();
				Boss->Set_Dead();
				cout << "面倒:" << endl;
			}


		}
	}
}

bool CCollisionMgr::Check_Sphere(glm::vec3 vPos1, float fRadian1, glm::vec3 vPos2, float fRadian2)
{
	float fDist;
	fDist = glm::length(vPos1 - vPos2);
	if (fDist <= fRadian1/2  + fRadian2/2 )
		return true;
	return false;
}
