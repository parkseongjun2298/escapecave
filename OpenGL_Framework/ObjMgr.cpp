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


HRESULT CObjectMgr::AddObject(OBJID::OBJ eType, CObj* pObject)
{
    NULL_CHECK_RETURN(pObject, E_FAIL);
    m_ObjectList[eType].push_back(pObject);

    return S_OK;
}

void CObjectMgr::Update()
{
    for (int i = 0; i < OBJID::END; ++i)
    {
        //이하 부분만 필요함
        OBJECT_LIST::iterator iter_begin = m_ObjectList[i].begin();
        OBJECT_LIST::iterator iter_end = m_ObjectList[i].end();

        for (int j = 0; iter_begin != iter_end;j++)
        {
            //모든 객체의 업데이트 함수 최소화할 필요 있다
            (*iter_begin)->Update();

            //수신한 좌표값 동기화하는 부분
            SEND_OBJECT_LIST::iterator send_iter_begin = s_ObjectList[i].begin();
            for (int k = 0; k<j;k++)
                ++send_iter_begin;

            //좌표값 동기화 후 셰이더로 그림
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
 
int* CObjectMgr::return_objlist_sizes() {
    static int list[OBJID::END];

    for (int i = 0; i < OBJID::END; ++i)
    {
        list[i] = m_ObjectList[i].size();
        //printf("%d", list[i]);
    }
    return list;
}

void CObjectMgr::Del_Obj(int id, int num)
{
 // 서버에서 같은 종류의 객체가 제거된 경우
 for (int i = 0;i < num;i++)
 {
      OBJECT_LIST::iterator iter_begin = m_ObjectList[id].begin();
      Safe_Delete(*iter_begin);
     iter_begin = m_ObjectList[id].erase(iter_begin);
 }
}