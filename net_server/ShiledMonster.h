#pragma once
#include "Obj.h"
class CShiledMonster : public Obj
{

public:
    CShiledMonster(glm::vec3 pos);

    // CObj을(를) 통해 상속됨

    virtual int Update() override;


private:
    int m_CollisionCount = 0;
};

