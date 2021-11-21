#include "pch.h"
#include "MainGame.h"
#include "Player.h"

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

void CMainGame::Initialize_MainGame()
{
	Shader.Initialize_Shader();
	CObjectMgr::Get_Instance()->Set_Shader(&Shader);
	//CObjectMgr::Get_Instance()->AddObject(OBJID::MAP, new CMap(Shader.Get_shaderProgram(), glm::vec3{ 50.f, 0.f, -150.f }, glm::vec3{ 10.f, 100.f, 100.f }));

	//CObjectMgr::Get_Instance()->AddObject(OBJID::MAP, new CMap(Shader.Get_shaderProgram(), glm::vec3{ 0.f, 40.f, -150.f }, glm::vec3{ 100.f, 10.f, 100.f }));
	//CObjectMgr::Get_Instance()->AddObject(OBJID::MAP, new CMap(Shader.Get_shaderProgram(), glm::vec3{ 0.f, -40.f, -150.f }, glm::vec3{ 100.f, 10.f,100.f }));
	
	CPlayer* player = new CPlayer(Shader.Get_shaderProgram(),0);
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

	//for (int i = 0; i < OBJID::END; ++i) {
	//	for (auto& object : list_objects[i]) {
	//		object->Update();
	//		Shader.Upadate_Shader(object->Get_vao(), object->Get_vbo(), object->Get_Object());
	//		object->Draw();

	//	}
	//

	// 현재 몬스터가 0개면 몬스터 추가하는 방식임
	if (CObjectMgr::Get_Instance()->Get_Size(OBJID::MONSTER) == 0 && CObjectMgr::Get_Instance()->Get_Size(OBJID::BOSS) == 0) {
		switch (m_eNowStage)
		{
		case CMainGame::STAGE1:
			Monster_Stage1();
			break;
		case CMainGame::STAGE2:
			Monster_Stage2();
			break;
		case CMainGame::STAGE3:
			Monster_Stage3();
			break;
		case CMainGame::STAGE_END:
			Release_MainGame();
			break;
		default:
			break;
		}
	}
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
	if (Stage_Monster_Wave == 0) {
		if (CObjectMgr::Get_Instance()->GetPlayer()->Get_Info().z <= 185.f) {
			Stage_Monster_Wave++;

			CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CNormalMonster(Shader.Get_shaderProgram(), glm::vec3{ -19.f, 0.f, 160.f }));
			CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CNormalMonster(Shader.Get_shaderProgram(), glm::vec3{ 19.f, 0.f, 160.f }));
			CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CShiledMonster(Shader.Get_shaderProgram(), glm::vec3{ -19.f, 0.f, 160.f }));
			CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CShiledMonster(Shader.Get_shaderProgram(), glm::vec3{ 19.f, 0.f, 160.f }));
		}

	}
	else if (Stage_Monster_Wave == 1) {
		Stage_Monster_Wave++;

		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CNormalMonster(Shader.Get_shaderProgram(), glm::vec3{ -19.f, 0.f, 110.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CNormalMonster(Shader.Get_shaderProgram(), glm::vec3{ 19.f, 0.f, 110.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CShiledMonster(Shader.Get_shaderProgram(), glm::vec3{ -19.f, 0.f, 110.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CShiledMonster(Shader.Get_shaderProgram(), glm::vec3{ 19.f, 0.f, 110.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CNormalMonster(Shader.Get_shaderProgram(), glm::vec3{ -10.f, 0.f, 110.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CNormalMonster(Shader.Get_shaderProgram(), glm::vec3{ 10.f, 0.f, 110.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CShiledMonster(Shader.Get_shaderProgram(), glm::vec3{ -10.f, 0.f, 110.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CShiledMonster(Shader.Get_shaderProgram(), glm::vec3{ 10.f, 0.f, 110.f }));
	}
	else if (Stage_Monster_Wave == 2) {
		// 첫번째 게이트 열림
		// 리스트의 맨마지막 게이트 연다.
		Stage_Monster_Wave++;
		dynamic_cast<CGate*>(CObjectMgr::Get_Instance()->Get_Gate_Back())->Set_Open();
	}
	else if (Stage_Monster_Wave == 3) {
		if (CObjectMgr::Get_Instance()->Get_Size(OBJID::GATE) == 2) {
			// 문이 다열림
			// 다음 스테이지로 이동
			m_eNowStage = STAGE2;
			Stage_Monster_Wave = 0;
		}
	}
}

void CMainGame::Monster_Stage2()
{
	if (Stage_Monster_Wave == 0) {
		Stage_Monster_Wave++;
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CSwirlMonster(Shader.Get_shaderProgram(), glm::vec3{ 9.f, 0.f, 60.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CSwirlMonster(Shader.Get_shaderProgram(), glm::vec3{ 9.f, 0.f, 75.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CSwirlMonster(Shader.Get_shaderProgram(), glm::vec3{ 9.f, 0.f, 90.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CSwirlMonster(Shader.Get_shaderProgram(), glm::vec3{ -9.f, 0.f, 60.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CSwirlMonster(Shader.Get_shaderProgram(), glm::vec3{ -9.f, 0.f, 75.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CSwirlMonster(Shader.Get_shaderProgram(), glm::vec3{ -9.f, 0.f, 90.f }));
	}
	else if (Stage_Monster_Wave == 1) {
		Stage_Monster_Wave++;
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CNormalMonster(Shader.Get_shaderProgram(), glm::vec3{ -19.f, 0.f, 0.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CNormalMonster(Shader.Get_shaderProgram(), glm::vec3{ 19.f, 0.f, 0.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CShiledMonster(Shader.Get_shaderProgram(), glm::vec3{ -19.f, 0.f, 0.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CShiledMonster(Shader.Get_shaderProgram(), glm::vec3{ 19.f, 0.f, 0.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CNormalMonster(Shader.Get_shaderProgram(), glm::vec3{ -10.f, 0.f, 0.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CNormalMonster(Shader.Get_shaderProgram(), glm::vec3{ 10.f, 0.f, 0.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CShiledMonster(Shader.Get_shaderProgram(), glm::vec3{ -10.f, 0.f, 0.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CShiledMonster(Shader.Get_shaderProgram(), glm::vec3{ 10.f, 0.f, 0.f }));

		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CNormalMonster(Shader.Get_shaderProgram(), glm::vec3{ -19.f, 0.f, 40.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CNormalMonster(Shader.Get_shaderProgram(), glm::vec3{ 19.f, 0.f, 40.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CShiledMonster(Shader.Get_shaderProgram(), glm::vec3{ -19.f, 0.f, 40.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CShiledMonster(Shader.Get_shaderProgram(), glm::vec3{ 19.f, 0.f, 40.f }));

		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CTonadoMonster(Shader.Get_shaderProgram(), glm::vec3{ 19.f, 0.f, -30.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CTonadoMonster(Shader.Get_shaderProgram(), glm::vec3{ 10.f, 0.f, -30.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CTonadoMonster(Shader.Get_shaderProgram(), glm::vec3{ -10.f, 0.f, -20.f }));
		CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CTonadoMonster(Shader.Get_shaderProgram(), glm::vec3{ -19.f, 0.f, -20.f }));

	}
	else if (Stage_Monster_Wave == 2) {
		// 번째 게이트 열림
		// 리스트의 맨마지막 게이트 연다.
		Stage_Monster_Wave++;
		dynamic_cast<CGate*>(CObjectMgr::Get_Instance()->Get_Gate_Back())->Set_Open();
	}
	else if (Stage_Monster_Wave == 3) {
		if (CObjectMgr::Get_Instance()->Get_Size(OBJID::GATE) == 1) {
			// 문이 다열림
			// 다음 스테이지로 이동
			m_eNowStage = STAGE3;
			Stage_Monster_Wave = 0;
		}
	}
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
