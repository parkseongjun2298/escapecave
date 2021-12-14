#include "pch.h"
#include "Player.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Player_Bullet.h"
#include "Bomb.h"
#include "tmp.h"

CPlayer::CPlayer(GLuint* _shader_program, int n)
	:CObj(_shader_program)
{
	//플레이어에 번호 지정0, 1, 2
	m_CollisionCount = 0;
	num = n;
	Initialize();
	m_light.model_transform.Translate = { 0.f,20.f, -250.f };
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initialize()
{
	loadObj<const char*, OBJECT, glm::vec3>("sphere.obj", object, glm::vec3(0.0, 0.0, 0.2));

	m_Camera.cameraPos = { 0.f,20.f,30.f };
	m_Camera.cameraDirection = { 0.f,0.f,0.f };
	m_Camera.cameraUp = { 0.f,1.f,0.f };

	object.model_transform.Scale *= 1.5f;
	m_fSpeed = 0.3f;
	bullet_time = 0.f;
	m_State = NORMAL_BULLET;
	object.model_transform.Translate.x = num * 10.0;
	object.model_transform.Translate.z = 190.f;

}

int CPlayer::Update()
{
	if (m_bDead) {
		if (m_CollisionCount < 15) {
			m_CollisionCount++;
			m_bDead = false;
		}
		else {
			CSoundMgr::GetInstance()->PlaySound((TCHAR*)L"die.mp3", CSoundMgr::EFFECT);
			Add_Effect(20);
			return DEAD_OBJ;
		}
	}

	/*object.model_transform.Translate.x -= m_fSpeed;
	float delta_time = CTimeMgr::Get_Instance()->Get_DeltaTime();*/
	m_Camera.cameraPos = object.model_transform.Translate;
	m_Camera.cameraDirection = object.model_transform.Translate;
	//m_Camera.cameraDirection.z = min(object.model_transform.Translate.z, -10.f);
	m_Camera.cameraDirection.y += 10.f;
	m_Camera.cameraPos.y = 40.f;
	m_Camera.cameraPos.z += 30.f;
	glm::vec3 MoveSize{};

	switch (Mouse_tmp[num].key)
	{
	case 'p':
		if (m_State == NORMAL_BULLET)
			Add_Bullet();
		if (m_State == DOUBLE_BULLET)
			Double_Bullet();
		break;

	}
	Mouse_tmp[num].key = 0;

	if (just_tmp[num].key[0] == 'a') // case 'a':
		object.model_transform.Translate.x -= m_fSpeed;

	if (just_tmp[num].key[1] == 'd') // case 'd':
		object.model_transform.Translate.x += m_fSpeed;

	if (just_tmp[num].key[2] == 'w') // case 'w':
		object.model_transform.Translate.z -= m_fSpeed;

	if (just_tmp[num].key[3] == 's') // case 's':
		object.model_transform.Translate.z += m_fSpeed;

	bullet_time += 0.1f;

	if (just_tmp[num].key[4] == 'z') {
		if (bullet_time > 30.f)
		{
			Add_Bomb();
			bullet_time = 0;
		}
	}


	if (just_tmp[num].key[5] == 'x') {
		if (m_State == NORMAL_BULLET)
			m_State = DOUBLE_BULLET;
		else
			m_State = NORMAL_BULLET;
	}

	for (int i = 0; i < 6; i++)
		just_tmp[num].key[i] = ' ';

	if (object.model_transform.Translate.x <= -20.f)
		object.model_transform.Translate.x = -20.f;
	else if (object.model_transform.Translate.x >= 20.f)
		object.model_transform.Translate.x = 20.f;

	return 0;
}

void CPlayer::Late_Update()
{
	
}

void CPlayer::Draw()
{
	unsigned int modelLocation = glGetUniformLocation(*shader_program, "model");
	unsigned int viewLocation = glGetUniformLocation(*shader_program, "view");
	unsigned int projLocation = glGetUniformLocation(*shader_program, "projection");
	// ============================= 고정 ============================================


	// ============================= 뷰 변환 ============================================
	// 카메라 좌표 설정
	
	
	glm::mat4 view = glm::mat4(1.f);
	glm::mat4 view_Rotate = glm::mat4(1.f);
	view_Rotate = glm::rotate(view_Rotate, glm::radians(0.f), glm::vec3(0.0, 1.0, 0.0));

	view = view_Rotate * glm::lookAt(m_Camera.cameraPos, m_Camera.cameraDirection, m_Camera.cameraUp);
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


	// 조명
	int lightPosLocation = glGetUniformLocation(*shader_program, "lightPos"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
	glUniform3f(lightPosLocation, m_light.model_transform.Translate.x, m_light.model_transform.Translate.y, m_light.model_transform.Translate.z);
	unsigned int LightColorLocation = glGetUniformLocation(*shader_program, "lightColor");
	glUniform3f(LightColorLocation, 0.8f, 0.8f, 0.8f);
	unsigned int viewPosLocation = glGetUniformLocation(*shader_program, "viewPos");
	glUniform3f(viewPosLocation, m_Camera.cameraPos.x, m_Camera.cameraPos.y, m_Camera.cameraPos.z);
	//////


	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Result));

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, object.vertices.size());



}

void CPlayer::Release()
{
}

void CPlayer::Set_ModelTransform()
{
}

void CPlayer::Add_Bullet(glm::vec3 _location)
{

	CObj* bullet = new CPlayer_Bullet(shader_program, object.model_transform.Translate + _location);
	CObjectMgr::Get_Instance()->AddObject(OBJID::PLAYER_BULLET, bullet);

}

void CPlayer::Double_Bullet()
{
	Add_Bullet({ -0.8f,0.f,0.f });
	Add_Bullet({ 0.8f,0.f,0.f });

}

void CPlayer::Add_Bomb()
{
	CObj* bomb = new CBomb(shader_program, object.model_transform.Translate);
	CObjectMgr::Get_Instance()->AddObject(OBJID::BOMB, bomb);
}

void CPlayer::Move_Camera(glm::vec3 _MoveSize)
{
	m_Camera.cameraPos += _MoveSize;
	m_Camera.cameraDirection += _MoveSize;
}
