#pragma once

#ifndef __COLLISIONMGR_H__
class CObj;
class CCollisionMgr
{

	DECLARE_SINGLETON(CCollisionMgr)
private:
	CCollisionMgr();
public:
	virtual ~CCollisionMgr();

public:
	void Collision_BulletToMonster(list<CObj*> pListBullet, list<CObj*> pListMonster);
	void Collision_BulletToPlayer(list<CObj*> pListBullet, list<CObj*> pListPlayer);

	void Collision_GateToMonsterBullet(list<CObj*> pGate, list<CObj*> pListBullet);
	void Collision_GateToPlayerBullet(list<CObj*> pGate, list<CObj*> pListBullet);
	void Collision_BulletToBullet(list<CObj*> pListBullet, list<CObj*> pListBullet2);
	void Collision_BossToPlayerBullet(list<CObj*> pListBoss, list<CObj*> pListPlayerBullet);
	

private:
	bool Check_Sphere(glm::vec3 vPos1, float fRadian1, glm::vec3 vPos2, float fRadian2);



};

#define __COLLISIONMGR_H__
#endif