#include "pch.h"
#include "MainGame.h"
#include "Player.h"
#include "tmp.h"

#include "Bomb.h"
#include "Player_Bullet.h"
#include "NormalMonster.h"
#include"ShiledMonster.h"
#include"SwirlMonster.h"
#include "Gate.h"
#include "Map.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "Player_front.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "TonadoMonster.h"
#include "BossMonster.h"
#include "MonsterBullet.h"
#include "Bomb_Effect.h"

void CMainGame::Initialize_MainGame()
{
	Shader.Initialize_Shader();
	CObjectMgr::Get_Instance()->Set_Shader(&Shader);
	//CObjectMgr::Get_Instance()->AddObject(OBJID::MAP, new CMap(Shader.Get_shaderProgram(), glm::vec3{ 50.f, 0.f, -150.f }, glm::vec3{ 10.f, 100.f, 100.f }));

	//CObjectMgr::Get_Instance()->AddObject(OBJID::MAP, new CMap(Shader.Get_shaderProgram(), glm::vec3{ 0.f, 40.f, -150.f }, glm::vec3{ 100.f, 10.f, 100.f }));
	//CObjectMgr::Get_Instance()->AddObject(OBJID::MAP, new CMap(Shader.Get_shaderProgram(), glm::vec3{ 0.f, -40.f, -150.f }, glm::vec3{ 100.f, 10.f,100.f }));
	
	CPlayer* player = new CPlayer(Shader.Get_shaderProgram());
	CObjectMgr::Get_Instance()->AddObject(OBJID::PLAYER, player);
	CObj* pPlayer_front = new CPlayer_front(Shader.Get_shaderProgram());
	CObjectMgr::Get_Instance()->AddObject(OBJID::PLAYER_FRONT, pPlayer_front);

	Camera* camera = dynamic_cast<CPlayer*>(player)->Get_Camera();
	CObjectMgr::Get_Instance()->Set_Camera(camera);
	
	CObjectMgr::Get_Instance()->Set_Light(dynamic_cast<CPlayer*>(player)->Get_Light());

	//Monster
	

	//CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CSwirlMonster(Shader.Get_shaderProgram(), glm::vec3{ 0.9f, 0.f, -1.f }));

	// Map

	// Map
	CObjectMgr::Get_Instance()->AddObject(OBJID::MAP, new CMap(Shader.Get_shaderProgram(), glm::vec3{ 0.f, -2.f, -120.f }, glm::vec3{ 20.f, 0.1f, 80.f }, { 0.7,0.7,0.7 }));
	CObjectMgr::Get_Instance()->AddObject(OBJID::MAP, new CMap(Shader.Get_shaderProgram(), glm::vec3{ 0.f, -2.f, 30.f }, glm::vec3{ 20.f, 0.1f, 70.f }, { 0.4,0.4,0.4 }));
	CObjectMgr::Get_Instance()->AddObject(OBJID::MAP, new CMap(Shader.Get_shaderProgram(), glm::vec3{ 0.f, -2.f, 150.f }, glm::vec3{ 20.f, 0.1f, 50.f }, { 0.1,0.1,0.1 }));
	// Gate
	CObjectMgr::Get_Instance()->AddObject(OBJID::GATE, new CGate(Shader.Get_shaderProgram(), glm::vec3{ 0.f,0.f, -200.f }));
	CObjectMgr::Get_Instance()->AddObject(OBJID::GATE, new CGate(Shader.Get_shaderProgram(), glm::vec3{ 0.f,0.f, -40.f }));
	CObjectMgr::Get_Instance()->AddObject(OBJID::GATE, new CGate(Shader.Get_shaderProgram(), glm::vec3{ 0.f,0.f, 100.f }));

	CSoundMgr::GetInstance()->Initialize();
	CSoundMgr::GetInstance()->PlayBGM((TCHAR*)L"Cave.mp3");

	glEnable(GL_DEPTH_TEST);

}

void CMainGame::Update_MainGame()
{
	int sent_list_size[OBJID::END];
	int* list = (CObjectMgr::Get_Instance()->return_objlist_sizes());

	//서버로부터 데이터 못 받은 경우는 업데이트 안 한다.
	if (s_ObjectList[0].size() == 0)
		return;
	//매니저에게서 어떻게든 m_obj_list 사이즈값 받아와서 생성할거있으면 생성 한 뒤에 업뎃으로 들어가야함
	for (int i = 0; i < OBJID::END; ++i)
	{
		sent_list_size[i] = s_ObjectList[i].size();
		printf("%d:%d", sent_list_size[i], list[i]);
		if (sent_list_size[i] > list[i])
		{
			printf("오브젝트추가하는함수(메인게임쪽함수)동작\n");
			New_Obj(i, sent_list_size[i] - list[i]);

		}
		else if (sent_list_size[i] < list[i])
		{
			printf("오브젝트제거하는함수(매니저쪽함수)동작\n");
			CObjectMgr::Get_Instance()->Del_Obj(i, list[i] - sent_list_size[i]);

		}
		else
		{
			printf("변화없음\n");
		}
	}
	printf("끝\n");
	CObjectMgr::Get_Instance()->Update();

}
void CMainGame::Late_Update()
{
	CKeyMgr::Get_Instance()->Key_Update();
	
}

void CMainGame::Draw_MainGame()
{

}

void CMainGame::Release_MainGame()
{
	CObjectMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CCollisionMgr::Destroy_Instance();
}

void CMainGame::Monster_Stage1()
{
	
}

void CMainGame::Monster_Stage2()
{
	
}

void CMainGame::Monster_Stage3()
{
	if (Stage_Monster_Wave == 0) {
		CObjectMgr::Get_Instance()->AddObject(OBJID::BOSS, new CBossMonster(Shader.Get_shaderProgram()));
		Stage_Monster_Wave++;
	}
	else if (Stage_Monster_Wave == 1) {
		Stage_Monster_Wave++;
		dynamic_cast<CGate*>(CObjectMgr::Get_Instance()->Get_Gate_Back())->Set_Open();
	}
	else if (Stage_Monster_Wave == 2) {
		if (CObjectMgr::Get_Instance()->Get_Size(OBJID::GATE) == 0) {
			// 클리어
			CSoundMgr::GetInstance()->StopAll();
			CSoundMgr::GetInstance()->PlayBGM((TCHAR*)L"clear.wav");

			m_eNowStage = STAGE_END;
			Stage_Monster_Wave = 4;
		}
	}

}

void CMainGame::New_Obj(int id, int num) {
	//서버에서 같은 종류의 새로운 객체가 생성된 경우
	//id에 해당하는 오브젝트를 num개 생성
	switch (id) {
	case OBJID::MAP:
		for (int i = 0;i < num;i++) {
			printf("id:%d객체 생성 부분 없음!", id);
		}
		break;
	case OBJID::GATE:
		for (int i = 0;i < num;i++) {
			printf("id:%d객체 생성 부분 없음!", id);
		}
		break;
	case OBJID::PLAYER_FRONT:
		for (int i = 0;i < num;i++) {
			printf("id:%d객체 생성 부분 없음!", id);
		}
		break;
	case OBJID::PLAYER:
		for (int i = 0;i < num;i++) {
			printf("id:%d객체 생성 부분 없음!", id);
		}
		break;
	case OBJID::PLAYER_BULLET:
		for (int i = 0;i < num;i++) {
			CObj* bullet = new CPlayer_Bullet(Shader.Get_shaderProgram(), { 0,0,0 });
			CObjectMgr::Get_Instance()->AddObject(OBJID::PLAYER_BULLET, bullet);
		}
		break;
	case OBJID::BOMB:
		for (int i = 0;i < num;i++) {
			CObj* bomb = new CBomb(Shader.Get_shaderProgram(), {});
			CObjectMgr::Get_Instance()->AddObject(OBJID::BOMB, bomb);
		}
		break;
	case OBJID::NORMALMONSTER:
		for (int i = 0;i < num;i++) {
			CObjectMgr::Get_Instance()->AddObject(OBJID::NORMALMONSTER, new CNormalMonster(Shader.Get_shaderProgram(), glm::vec3{ -19.f, 0.f, 160.f }));
		}
		break;
	case OBJID::SHILEDMONSTER:
		for (int i = 0;i < num;i++) {
			CObjectMgr::Get_Instance()->AddObject(OBJID::SHILEDMONSTER, new CShiledMonster(Shader.Get_shaderProgram(), glm::vec3{ -19.f, 0.f, 0.f }));
		}
		break;
	case OBJID::SWIRLMONSTER:
		for (int i = 0;i < num;i++) {
			CObjectMgr::Get_Instance()->AddObject(OBJID::SWIRLMONSTER, new CSwirlMonster(Shader.Get_shaderProgram(), glm::vec3{ -9.f, 0.f, 90.f }));
		}
		break;
	case OBJID::TONADOMONSTER:
		for (int i = 0;i < num;i++) {

			CObjectMgr::Get_Instance()->AddObject(OBJID::TONADOMONSTER, new CTonadoMonster(Shader.Get_shaderProgram(), glm::vec3{ 19.f, 0.f, -30.f }));
		}
		break;
	case OBJID::BOSS:
		for (int i = 0;i < num;i++) {
			CObjectMgr::Get_Instance()->AddObject(OBJID::BOSS, new CBossMonster(Shader.Get_shaderProgram()));
		}
		break;
	case OBJID::MONSTER_BULLET:
		for (int i = 0;i < num;i++) {
			CMonsterBullet* bullet = new CMonsterBullet(Shader.Get_shaderProgram(), { 0,0,0 }, { 0,0,0 }, { 1.f,102. / 255.,102. / 255. });
			CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER_BULLET, bullet);
		}
		break;
	case OBJID::EFFECT:
		for (int i = 0;i < num;i++) {
			CObj* Effect = new CBomb_Effect(Shader.Get_shaderProgram(), {});
			CObjectMgr::Get_Instance()->AddObject(OBJID::EFFECT, Effect);
		}
		break;
	case OBJID::UI:
		for (int i = 0;i < num;i++) {
			printf("id:%d객체 생성 부분 없음!", id);
		}
		break;
	case OBJID::END:
		for (int i = 0;i < num;i++) {
			printf("id:%d객체 생성 부분 없음!", id);
		}
		break;
	}
};
//void CMainGame::Add_Object(OBJID::OBJ _objID)
//{
//	CObj* pObj = nullptr;
//	if (_objID == OBJID::PLAYER) {
//		pObj = new CPlayer(Shader.Get_shaderProgram());
//	}
//	if (_objID == OBJID::MONSTER)
//	{
//		pObj = new CNormalMonster(Shader.Get_shaderProgram(), glm::vec3{ -10.f, 0.f, -10.f });
//		list_objects[_objID].emplace_back(pObj);
//	}
//
//	if (_objID == OBJID::MAP)
//	{
//		pObj = new CMap(Shader.Get_shaderProgram(), glm::vec3{ -2.f, 0.f, 0.f }, glm::vec3{ 0.1f, 2.f, 1.f });
//		list_objects[_objID].emplace_back(pObj);
//		
//		pObj=new CMap(Shader.Get_shaderProgram(), glm::vec3{ 2.f, 0.f, 0.f }, glm::vec3{ 0.1f, 2.f, 1.f });
//		list_objects[_objID].emplace_back(pObj);
//
//		pObj = new CMap(Shader.Get_shaderProgram(), glm::vec3{ 0.f, 2.f, 0.f }, glm::vec3{ 2.f, 0.1f, 1.f });
//		list_objects[_objID].emplace_back(pObj);
//
//		pObj = new CMap(Shader.Get_shaderProgram(), glm::vec3{ 0.f, -2.f, 0.f }, glm::vec3{ 2.f, 0.1f,1.f });
//		list_objects[_objID].emplace_back(pObj);
//	}
//
//
//	list_objects[_objID].emplace_back(pObj);
//}
