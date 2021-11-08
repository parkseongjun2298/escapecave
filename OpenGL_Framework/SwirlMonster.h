#pragma once
#include "Obj.h"
class CSwirlMonster :
    public CObj
{
public:
    CSwirlMonster(GLuint* _shader_program, glm::vec3 pos);
    ~CSwirlMonster();
    // CObj을(를) 통해 상속됨
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Draw() override;
    virtual void Release() override;
    virtual void Set_ModelTransform() override;

private:
    void Add_Bullet();
    float bullet_time;
    glm::vec3 BulletDir;

    int CollisionNum = 0;

};

