#include "pch.h"
#include "Player.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Player_Bullet.h"
#include "Bomb.h"
#include "Client.h"
#include "tmp.h"

CPlayer::CPlayer(GLuint* _shader_program, int n)
	:CObj(_shader_program)
{
	//플레이어에 번호 지정0, 1, 2
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

int CPlayer::Update( )
{
	//카메라의 소실점
	m_Camera.cameraPos = object.model_transform.Translate;
	//카메라 좌표
	m_Camera.cameraDirection = object.model_transform.Translate;
	//m_Camera.cameraDirection.z = min(object.model_transform.Translate.z, -10.f);
	m_Camera.cameraDirection.y += 10.f;
	m_Camera.cameraPos.y = 40.f;
	m_Camera.cameraPos.z += 30.f;

	Client client;
	int cnt = 0;
	if (CKeyMgr::Get_Instance()->Key_Pressing(KEY_LEFT))
	{
		printf("LEFT\n");
		//client.Send_Input('a');
		Keyin[0] = 'a';
	}
	else
		Keyin[0] = ' ';

	if (CKeyMgr::Get_Instance()->Key_Pressing(KEY_RIGHT))
	{
		printf("RIGHT\n");
		//client.Send_Input('d');
		Keyin[1] = 'd';
	}
	else
		Keyin[1] = ' ';

	if (CKeyMgr::Get_Instance()->Key_Pressing(KEY_UP))
	{
		printf("UP\n");
		//client.Send_Input('w');
		Keyin[2] = 'w';
	}
	else
		Keyin[2] = ' ';

	if (CKeyMgr::Get_Instance()->Key_Pressing(KEY_DOWN))
	{
		printf("DOWN\n");
		//client.Send_Input('s');
		Keyin[3] = 's';
	}
	else
		Keyin[3] = ' ';

	if (CKeyMgr::Get_Instance()->Key_Pressing(KEY_A))
	{
		printf("A\n");
		//client.Send_Input('z');
		Keyin[4] = 'z';
	}
	else
		Keyin[4] = ' ';

	if (CKeyMgr::Get_Instance()->Key_Pressing(KEY_S))
	{
		printf("S\n");
		//client.Send_Input('x');
		Keyin[5] = 'x';
	}
	else
		Keyin[5] = ' ';

	Keyin[6] = '\0';

	for (int i = 0; i < 6; i++)
	{
		if (Keyin[i] != ' ')
			cnt++;
	}
	if (cnt != 0)
		client.Send_Keyin(Keyin);
	else
		cnt = 0;

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


	// 조명. 여기 고쳐야 카메라 고쳐질 듯
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