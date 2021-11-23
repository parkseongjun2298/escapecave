#include "pch.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "tmp.h"
#include "enum.h"
#include"CollisionMgr.h"

#include "NormalMonster.h"
#include"ShiledMonster.h"
#include"SwirlMonster.h"
#include "Gate.h"
#include "Map.h"
#include "Player_front.h"
#include "TonadoMonster.h" 
#include "Player_Bullet.h"
#include "BossMonster.h"
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
CObj* CObjectMgr::GetMonster()
{
    if (m_ObjectList[OBJID::MONSTER].empty())
        return nullptr;

    return m_ObjectList[OBJID::MONSTER].front();
}


HRESULT CObjectMgr::AddObject(OBJID::OBJ eType, CObj* pObject)
{
    NULL_CHECK_RETURN(pObject, E_FAIL);
    m_ObjectList[eType].push_back(pObject);

    return S_OK;
}

void CObjectMgr::Update()
{
    int send, m;
    //s_ObjectList[i] 와 m_ObjectList[i] 오브젝트 개수 비교해서 s가 많으면 객체생성, s가 적으면 객체 삭제 해야됨.
    for (int i = 0; i < OBJID::END; ++i)
    {
        send = s_ObjectList[i].size();
        m = m_ObjectList[i].size();
        //서버에서 같은 종류의 새로운 객체가 생성된 경우
        if (send > m)
        {
            switch (i) {
            case OBJID::MAP:
                for (;m != send;m++) {
                }
                break;
            case OBJID::GATE:
                for (;m != send;m++) {
                }
                break;
            case OBJID::PLAYER_FRONT:
                for (;m != send;m++) {
                }
                break;
            case OBJID::PLAYER:
                for (;m != send;m++) {
                }
                break;
            case OBJID::PLAYER_BULLET:
                for (;m != send;m++) {
                    GLuint* shader_program;
                    CObj* bullet = new CPlayer_Bullet(shader_program, {0,0,0});
                    CObjectMgr::Get_Instance()->AddObject(OBJID::PLAYER_BULLET, bullet);
                }
                break;
            case OBJID::MONSTER:
                for (;m != send;m++) {
                   CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CNormalMonster((*Shader).Get_shaderProgram(), glm::vec3{ -19.f, 0.f, 160.f }));
                }
                break;
            case OBJID::BOSS:
                for (;m != send;m++) {
                }
                break;
            case OBJID::MONSTER_BULLET:
                for (;m != send;m++) {
                }
                break;
            case OBJID::EFFECT:
                for (;m != send;m++) {
                }
                break;
            case OBJID::UI:
                for (;m != send;m++) {
                }
                break;
            case OBJID::END:
                for (;m != send;m++) {
                }
                break;
            }
            //i값이 뭐냐에 따라 생성해야할 객체가 달라질 것
        }
        // 서버에서 같은 종류의 객체가 제거된 경우
        else if (send < m)
            for (;m != send;m--) {
                OBJECT_LIST::iterator iter_begin = m_ObjectList[i].begin();
                Safe_Delete(*iter_begin);
                iter_begin = m_ObjectList[i].erase(iter_begin);
            }

        OBJECT_LIST::iterator iter_begin = m_ObjectList[i].begin();
        OBJECT_LIST::iterator iter_end = m_ObjectList[i].end();

        for (int j = 0; iter_begin != iter_end;j++)
        {
            int iEvent = 0;
            iEvent = (*iter_begin)->Update();

            //좌표값 대신 동기화하는함수
            SEND_OBJECT_LIST::iterator send_iter_begin = s_ObjectList[i].begin();
            for (int k = 0; k<j;k++)
                ++send_iter_begin;
            (*iter_begin)->get_vec3((*send_iter_begin));


            Shader->Upadate_Shader((*iter_begin)->Get_vao(), (*iter_begin)->Get_vbo(),(*iter_begin)->Get_normalbuffer(), (*iter_begin)->Get_Object());
            (*iter_begin)->Draw();
            ++iter_begin;
        }
    }
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