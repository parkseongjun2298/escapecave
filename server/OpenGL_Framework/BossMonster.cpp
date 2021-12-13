#include "pch.h"
#include "BossMonster.h"
#include "Boss_head.h"
#include "NormalMonster.h"
#include "ShiledMonster.h"
#include "MonsterBullet.h"
#include "TonadoMonster.h"
#include"SwirlMonster.h"
CBossMonster::CBossMonster(GLuint* _shader_program)
	:CObj(_shader_program)
{
	Initialize();
	m_AttackTime = 500;
}

CBossMonster::~CBossMonster()
{
}

void CBossMonster::Initialize()
{
	loadObj<const char*, OBJECT, glm::vec3>("boss.obj", object, {102./255.,51./255.,0.});
	object.model_transform.Translate = { 0.f,10.f,-150.f };


	//CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER, new CBoss_head(shader_program, this));
}

int CBossMonster::Update()
{
	m_AttackTime++;
	if (m_AttackTime > 1000) {
		m_AttackTime = 0;
		Attack();

	}
	object.model_transform.Rotate.y += 2.f;
	if (m_bDead) {

		if (m_Collision_Time < 50) {
			m_Collision_Time++;
			m_bDead = false;
			Add_Effect(1);
		}
		else {
			CSoundMgr::GetInstance()->PlaySound((TCHAR*)L"die.mp3", CSoundMgr::EFFECT);
			Add_Effect(100);
			return m_bDead;
		}
			
	}
	return 0;
}

void CBossMonster::Late_Update()
{
}

void CBossMonster::Draw()
{
	unsigned int modelLocation = glGetUniformLocation(*shader_program, "model");
	unsigned int viewLocation = glGetUniformLocation(*shader_program, "view");
	unsigned int projLocation = glGetUniformLocation(*shader_program, "projection");
	// ============================= 고정 ============================================


	// ============================= 뷰 변환 ============================================


	glm::mat4 view = glm::mat4(1.f);
	glm::mat4 view_Rotate = glm::mat4(1.f);
	view_Rotate = glm::rotate(view_Rotate, glm::radians(0.f), glm::vec3(0.0, 1.0, 0.0));
	CAMERA_DESC camera = CObjectMgr::Get_Instance()->Get_Camera();
	view = view_Rotate * glm::lookAt(camera.cameraPos, camera.cameraDirection, camera.cameraUp);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	// ============================= 뷰 변환 ============================================

	// ============================= 투영 변환 ============================================
	glm::mat4 projection = glm::mat4(1.f);
	projection = glm::perspective(glm::radians(FOVY), (float)WINCX / (float)WINCY, 1.f, FAR_Z);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);
	// ============================= 투영 변환 ============================================

	glm::mat4 Scale = glm::mat4(1.f);

	glm::mat4 RotateX = glm::mat4(1.f);
	glm::mat4 RotateY = glm::mat4(1.f);
	glm::mat4 RotateZ = glm::mat4(1.f);

	glm::mat4 Translate = glm::mat4(1.f);

	glm::mat4 RevolutionX = glm::mat4(1.f);
	glm::mat4 RevolutionY = glm::mat4(1.f);
	glm::mat4 RevolutionZ = glm::mat4(1.f);

	glm::mat4 Parent = glm::mat4(1.f);

	glm::mat4 Result = glm::mat4(1.f);

	Scale = glm::scale(Scale, object.model_transform.Scale);

	RotateX = glm::rotate(RotateX, glm::radians(object.model_transform.Rotate.x), glm::vec3(1.0, 0.0, 0.0));
	RotateY = glm::rotate(RotateY, glm::radians(object.model_transform.Rotate.y), glm::vec3(0.0, 1.0, 0.0));
	RotateZ = glm::rotate(RotateZ, glm::radians(object.model_transform.Rotate.z), glm::vec3(0.0, 0.0, 1.0));

	Translate = glm::translate(Translate, object.model_transform.Translate);

	RevolutionX = glm::rotate(RevolutionX, glm::radians(object.model_transform.Revolution.x), glm::vec3(1.0, 0.0, 0.0));
	RevolutionY = glm::rotate(RevolutionY, glm::radians(object.model_transform.Revolution.y), glm::vec3(0.0, 1.0, 0.0));
	RevolutionZ = glm::rotate(RevolutionZ, glm::radians(object.model_transform.Revolution.z), glm::vec3(0.0, 0.0, 1.0));
	if (object.model_transform.Parent)
		Parent = glm::translate(Parent, object.model_transform.Parent->Translate);

	// 크 자 이 공 부 거꾸로
	Result = Parent * RevolutionX * RevolutionY * RevolutionZ * Translate * RotateX * RotateY * RotateZ * Scale;
	
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Result));

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, object.vertices.size());
}

void CBossMonster::Release()
{
}

void CBossMonster::Set_ModelTransform()
{
}

void CBossMonster::Attack()
{
	PATTERN random = (PATTERN)(rand() % 3);

	switch (random)
	{
	case CBossMonster::NORMAL:
		Noraml_Attack();
		break;
	case CBossMonster::SKY:
		Sky_Attack();
		break;
	case CBossMonster::BULLET36:
		bullet36_Attack();
		break;
	default:
		break;
	}
}

void CBossMonster::Noraml_Attack()
{

	CObjectMgr::Get_Instance()->AddObject(OBJID::NORMALMONSTER, new CNormalMonster(shader_program, glm::vec3{ -19.f, 0.f, -120.f }));
	CObjectMgr::Get_Instance()->AddObject(OBJID::SHILEDMONSTER, new CShiledMonster(shader_program, glm::vec3{ -19.f, 0.f, -120.f }));

	CObjectMgr::Get_Instance()->AddObject(OBJID::NORMALMONSTER, new CNormalMonster(shader_program, glm::vec3{ 19.f, 0.f, -120.f }));
	CObjectMgr::Get_Instance()->AddObject(OBJID::SHILEDMONSTER, new CShiledMonster(shader_program, glm::vec3{ 19.f, 0.f, -120.f }));
	CObjectMgr::Get_Instance()->AddObject(OBJID::NORMALMONSTER, new CNormalMonster(shader_program, glm::vec3{ -19.f, 0.f, -180.f }));
	CObjectMgr::Get_Instance()->AddObject(OBJID::SHILEDMONSTER, new CShiledMonster(shader_program, glm::vec3{ -19.f, 0.f, -180.f }));

	CObjectMgr::Get_Instance()->AddObject(OBJID::NORMALMONSTER, new CNormalMonster(shader_program, glm::vec3{ 19.f, 0.f, -180.f }));
	CObjectMgr::Get_Instance()->AddObject(OBJID::SHILEDMONSTER, new CShiledMonster(shader_program, glm::vec3{ 19.f, 0.f, -180.f }));
	m_AttackTime = 600;
}

void CBossMonster::Sky_Attack()
{

	CObjectMgr::Get_Instance()->AddObject(OBJID::SWIRLMONSTER, new CSwirlMonster(shader_program, glm::vec3{ -19.f, 0.f, -120.f }));

	CObjectMgr::Get_Instance()->AddObject(OBJID::SWIRLMONSTER, new CSwirlMonster(shader_program, glm::vec3{ 19.f, 0.f, -120.f }));

	CObjectMgr::Get_Instance()->AddObject(OBJID::TONADOMONSTER, new CTonadoMonster(shader_program, glm::vec3{ -19.f, 0.f, -180.f }));

	CObjectMgr::Get_Instance()->AddObject(OBJID::TONADOMONSTER, new CTonadoMonster(shader_program, glm::vec3{ 19.f, 0.f, -180.f }));
	m_AttackTime = 300;
}

void CBossMonster::bullet36_Attack()
{
	glm::vec3 pos = object.model_transform.Translate;
	pos.y = 0.f;
	CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER_BULLET, new CTonadoMonster(shader_program,pos));
	pos.z += 20.f;

	CObjectMgr::Get_Instance()->AddObject(OBJID::MONSTER_BULLET, new CTonadoMonster(shader_program, pos));
	m_AttackTime = 900;

}
