#include "pch.h"
#include "CollisionMgr.h"
#include"Obj.h"
#include"PlayerBullet.h"



void CollisionMgr::Collision_BulletToMonster(list<Obj*> pListBullet, list<Obj*> pListMonster)
{
	//cout << "몬스터와총알충돌" << endl;
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
				//cout << "충돌:" << endl;
			}


		}
	}
}

void CollisionMgr::Collision_BulletToPlayer(list<Obj*> pListBullet, list<Obj*> pListPlayer)
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
				//cout << "충돌:" << endl;
			}


		}
	}
}

void CollisionMgr::Collision_GateToMonsterBullet(list<Obj*> pGate, list<Obj*> pListBullet)
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
				cout << "충돌:" << endl;
			}


		}
	}
}

void CollisionMgr::Collision_GateToPlayerBullet(list<Obj*> pGate, list<Obj*> pListBullet)
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
				cout << "충돌:" << endl;
			}


		}
	}
}

void CollisionMgr::Collision_BulletToBullet(list<Obj*> pListBullet, list<Obj*> pListBullet2)
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
				//cout << "충돌:" << endl;
			}


		}
	}
}

void CollisionMgr::Collision_BossToPlayerBullet(list<Obj*> pListBoss, list<Obj*> pListPlayerBullet)
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
				cout << "충돌:" << endl;
			}


		}
	}
}

bool CollisionMgr::Check_Sphere(glm::vec3 vPos1, float fRadian1, glm::vec3 vPos2, float fRadian2)
{
	float fDist;
	fDist = glm::length(vPos1 - vPos2);
	if (fDist <= fRadian1 / 2 + fRadian2 / 2)
		return true;
	return false;
}
