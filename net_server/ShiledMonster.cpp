#include "pch.h"
#include "ShiledMonster.h"
#include"NormalMonster.h"

CShiledMonster::CShiledMonster(glm::vec3 pos) : Obj()
{
    info.Translate = pos;
    info.Rotate = glm::vec3(0.f, 0.f, 0.f);
    m_fSpeed = 0.2f;
    info.hp = 1;
}

int CShiledMonster::Update()
{
    // ½¯µå ±úÁü, »ç¸Á
    /*if (m_bDead) {
        if (m_CollisionCount < 2) {
            m_CollisionCount++;
            m_bDead = false;
        }
        else {
            CSoundMgr::GetInstance()->PlaySound((TCHAR*)L"die.mp3", CSoundMgr::EFFECT);
            Add_Effect(20);
            return DEAD_OBJ;

        }

    }*/

    // ÀÌµ¿ ¾÷µ¥ÀÌÆ®
    info.Translate.x += m_fSpeed;

    if (info.Translate.x <= -20.f || info.Translate.x >= 20.f)
        m_fSpeed *= -1;


    return 0;

}