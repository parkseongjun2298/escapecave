#pragma once
#include "Obj.h"
class CShiledMonster : public Obj
{

public:
    CShiledMonster(glm::vec3 pos);

    // CObj��(��) ���� ��ӵ�

    virtual int Update() override;


private:
    int m_CollisionCount = 0;
};

