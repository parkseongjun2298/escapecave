#pragma once
#include "Obj.h"
class CTonadoMonster : public Obj
{
public:
        CTonadoMonster(glm::vec3 pos);
        // CObj��(��) ���� ��ӵ�
        virtual int Update() override;
private:
    //void Add_Bullet();
    //float bullet_time;
    //glm::vec3 BulletDir;
    float angle;

private:
    float Collision_Time = 0.f;
};

