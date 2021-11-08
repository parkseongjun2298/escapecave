#pragma once
#include "Obj.h"
class CShiledMonster :
    public CObj
{

public:
    CShiledMonster(GLuint* _shader_program, glm::vec3 pos);
    ~CShiledMonster();




    // CObj을(를) 통해 상속됨
    virtual void Initialize() override;

    virtual int Update() override;

    virtual void Late_Update() override;

    virtual void Draw() override;

    virtual void Release() override;

    virtual void Set_ModelTransform() override;


private:
    int m_CollisionCount = 0;



};

