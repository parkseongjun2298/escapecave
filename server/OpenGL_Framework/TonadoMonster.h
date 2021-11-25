#pragma once
#include "Obj.h"
class CTonadoMonster :
    public CObj
{
public:
        CTonadoMonster(GLuint* _shader_program, glm::vec3 pos);
        ~CTonadoMonster();
        // CObj을(를) 통해 상속됨
        virtual void Initialize() override;
        virtual int Update() override;
        virtual void Late_Update() override;
        virtual void Draw() override;
        virtual void Release() override;
        virtual void Set_ModelTransform() override;


private:
    void Add_Bullet();
    //void Create_Particle();
    float bullet_time;
    glm::vec3 BulletDir;
    float angle;
    glm::vec3 ParticleDir[100];
    float ParticleDirX[100] = { 0.f, };
    float ParticleDirY[100] = { 0.f, };
    float ParticleDirZ[100] = { 0.f, };

private:
    float Collision_Time = 0.f;




};

