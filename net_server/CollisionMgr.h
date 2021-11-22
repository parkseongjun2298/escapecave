#pragma once
#include "struct.h"
#include "pch.h"
#include "NetShare.h"
#include "Obj.h"
class Obj;

#ifndef __COLLISIONMGR_H__
class CollisionMgr : public NetShare
{

public:
	void Collision_BulletToMonster(list<Obj*> pListBullet, list<Obj*> pListMonster);
	void Collision_BulletToPlayer(list<Obj*> pListBullet, list<Obj*> pListPlayer);

	void Collision_GateToMonsterBullet(list<Obj*> pGate, list<Obj*> pListBullet);
	void Collision_GateToPlayerBullet(list<Obj*> pGate, list<Obj*> pListBullet);
	void Collision_BulletToBullet(list<Obj*> pListBullet, list<Obj*> pListBullet2);
	void Collision_BossToPlayerBullet(list<Obj*> pListBoss, list<Obj*> pListPlayerBullet);


private:
	bool Check_Sphere(glm::vec3 vPos1, float fRadian1, glm::vec3 vPos2, float fRadian2);

};

#define __COLLISIONMGR_H__
#endif