#include "pch.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "tmp.h"
#include"CollisionMgr.h"

IMPLEMENT_SINGLETON(CObjectMgr)

CObjectMgr::CObjectMgr()
{
    Load_All_Obj();

}


CObjectMgr::~CObjectMgr()
{
    Release();
}

CObj* CObjectMgr::GetPlayer()
{
    if (m_ObjectList[OBJID::PLAYER].empty())
        return nullptr;

    return m_ObjectList[OBJID::PLAYER].front();
}
/*
CObj* CObjectMgr::GetMonster()
{
    if (m_ObjectList[OBJID::MONSTER].empty())
        return nullptr;

    return m_ObjectList[OBJID::MONSTER].front();
}

*/
HRESULT CObjectMgr::AddObject(OBJID::OBJ eType, CObj* pObject)
{
    NULL_CHECK_RETURN(pObject, E_FAIL);
    m_ObjectList[eType].push_back(pObject);

    return S_OK;
}

//이 함수에서 모든 오브젝트의 좌표값vec3를 추출하여 전역 리스트에 저장한다.
void CObjectMgr::Update()
{

    for (int i = 0; i < OBJID::END; ++i)
    {
        OBJECT_LIST::iterator iter_begin = m_ObjectList[i].begin();
        OBJECT_LIST::iterator iter_end = m_ObjectList[i].end();

        for (; iter_begin != iter_end;)
        {
            int iEvent = 0;
            iEvent = (*iter_begin)->Update();
            // 각 오브젝트의 좌표값을 리스트에 "구분하여" 정렬 저장한다.
            s_ObjectList[i].push_back((*iter_begin)->return_Trans());


            Shader->Upadate_Shader((*iter_begin)->Get_vao(), (*iter_begin)->Get_vbo(),(*iter_begin)->Get_normalbuffer(), (*iter_begin)->Get_Object());
            (*iter_begin)->Draw();
            if (DEAD_OBJ == iEvent)
            {
                Safe_Delete(*iter_begin);
                iter_begin = m_ObjectList[i].erase(iter_begin);
            }
            else
                ++iter_begin;
        }
    }
    CCollisionMgr::Get_Instance()->Collision_BulletToMonster(m_ObjectList[OBJID::PLAYER_BULLET], m_ObjectList[OBJID::NORMALMONSTER]);
    CCollisionMgr::Get_Instance()->Collision_BulletToMonster(m_ObjectList[OBJID::PLAYER_BULLET], m_ObjectList[OBJID::SHILEDMONSTER]);
    CCollisionMgr::Get_Instance()->Collision_BulletToMonster(m_ObjectList[OBJID::PLAYER_BULLET], m_ObjectList[OBJID::SWIRLMONSTER]);
    CCollisionMgr::Get_Instance()->Collision_BulletToMonster(m_ObjectList[OBJID::PLAYER_BULLET], m_ObjectList[OBJID::TONADOMONSTER]);

    CCollisionMgr::Get_Instance()->Collision_BulletToPlayer(m_ObjectList[OBJID::MONSTER_BULLET], m_ObjectList[OBJID::PLAYER]);
    CCollisionMgr::Get_Instance()->Collision_BulletToBullet(m_ObjectList[OBJID::MONSTER_BULLET], m_ObjectList[OBJID::PLAYER_BULLET]);
    CCollisionMgr::Get_Instance()->Collision_BossToPlayerBullet(m_ObjectList[OBJID::BOSS], m_ObjectList[OBJID::PLAYER_BULLET]);
}

void CObjectMgr::LateUpdate()
{
    for (int i = 0; i < OBJID::END; ++i)
    {
        OBJECT_LIST::iterator iter_begin = m_ObjectList[i].begin();
        OBJECT_LIST::iterator iter_end = m_ObjectList[i].end();

        for (; iter_begin != iter_end; ++iter_begin)
            (*iter_begin)->Late_Update();
    }
    //충돌처리부분

   
}

void CObjectMgr::Load_All_Obj()
{
    loadObj<const char*, OBJECT, glm::vec3>("diamond.obj", m_mapObjFile["diamond"], {0.,0.,0.});
    loadObj<const char*, OBJECT, glm::vec3>("sphere.obj", m_mapObjFile["sphere"], { 0.,0.,0. });
    loadObj<const char*, OBJECT, glm::vec3>("bomb.obj", m_mapObjFile["bomb"], { 0.,0.,0. });
    loadObj<const char*, OBJECT, glm::vec3>("cube.obj", m_mapObjFile["cube"], { 0.,0.,0. });
    loadObj<const char*, OBJECT, glm::vec3>("cylinder.obj", m_mapObjFile["cylinder"], { 0.,0.,0. });
    loadObj<const char*, OBJECT, glm::vec3>("shield.obj", m_mapObjFile["shield"], { 0.,0.,0. });   
    loadObj<const char*, OBJECT, glm::vec3>("player_front.obj", m_mapObjFile["player_front"], { 0.,0.,0. });

}

void CObjectMgr::Release()
{
    for (int i = 0; i < OBJID::END; ++i)
    {
        for_each(m_ObjectList[i].begin(), m_ObjectList[i].end(), Safe_Delete<CObj*>);
        m_ObjectList[i].clear();
    }
}