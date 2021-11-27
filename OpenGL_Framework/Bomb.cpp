#include "pch.h"
#include "Bomb.h"
#include "Bomb_Effect.h"
#include "Player_Bullet.h"
CBomb::CBomb(GLuint* _shader_program, glm::vec3 pos)
	:CObj(_shader_program)
{
	object.model_transform.Translate = pos;
	Initialize();
}

CBomb::~CBomb()
{
}

void CBomb::Initialize()
{
	loadObj<const char*, OBJECT, glm::vec3>("bomb.obj", object, glm::vec3(0.0, 51.0/255.0, 204.0/225.));

}

int CBomb::Update( )
{
	m_Create_Time += 0.1f;

	if(m_bScaleBigger)
		object.model_transform.Scale *= 1.1f;
	else
		object.model_transform.Scale *= 0.9f;

	if (object.model_transform.Scale.x < 0.5f) {
		m_bScaleBigger = true;
		object.model_transform.Scale = {0.5f,0.5f,0.5f};
	}
	else if (object.model_transform.Scale.x > 1.f){
		object.model_transform.Scale = { 1.f, 1.f, 1.f };
		m_bScaleBigger = false;
	}

    return 0;
}

void CBomb::Late_Update()
{
}

void CBomb::Draw()
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

	RotateX = glm::rotate(RotateX, glm::radians(object.model_transform.Rotate.x = { 0.f }), glm::vec3(1.0, 0.0, 0.0));
	RotateY = glm::rotate(RotateY, glm::radians(object.model_transform.Rotate.y = { 0.f }), glm::vec3(0.0, 1.0, 0.0));
	RotateZ = glm::rotate(RotateZ, glm::radians(object.model_transform.Rotate.z = { 0.f }), glm::vec3(0.0, 0.0, 1.0));

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

void CBomb::Release()
{
}

void CBomb::Set_ModelTransform()
{
}



void CBomb::Add_Bullet()
{
	// 위
	glm::vec3 dir = { 0.f,0.f,-1.f };
	CObj* bullet = new CPlayer_Bullet(shader_program, object.model_transform.Translate, { 0.0, 51.0 / 255.0, 204.0 / 225. }, dir);
	CObjectMgr::Get_Instance()->AddObject(OBJID::PLAYER_BULLET, bullet);
	// 오 대각선 위
	dir = { 1.f,0.f,-1.f };
	vector_normalize(dir);
	bullet = new CPlayer_Bullet(shader_program, object.model_transform.Translate, { 0.0, 51.0 / 255.0, 204.0 / 225. }, dir);
	CObjectMgr::Get_Instance()->AddObject(OBJID::PLAYER_BULLET, bullet);
	// 오
	dir = { 1.f,0.f,0.f };
	vector_normalize(dir);
	bullet = new CPlayer_Bullet(shader_program, object.model_transform.Translate, { 0.0, 51.0 / 255.0, 204.0 / 225. }, dir);
	CObjectMgr::Get_Instance()->AddObject(OBJID::PLAYER_BULLET, bullet);
	// 오 대각선 아래
	dir = { 1.f,0.f,1.f };
	vector_normalize(dir);
	bullet = new CPlayer_Bullet(shader_program, object.model_transform.Translate, { 0.0, 51.0 / 255.0, 204.0 / 225. }, dir);
	CObjectMgr::Get_Instance()->AddObject(OBJID::PLAYER_BULLET, bullet);

	// 아래
	dir = { 0.f,0.f,1.f };
	vector_normalize(dir);
	bullet = new CPlayer_Bullet(shader_program, object.model_transform.Translate, { 0.0, 51.0 / 255.0, 204.0 / 225. }, dir);
	CObjectMgr::Get_Instance()->AddObject(OBJID::PLAYER_BULLET, bullet);

	// 왼 아래
	dir = { -1.f,0.f,1.f };
	vector_normalize(dir);
	bullet = new CPlayer_Bullet(shader_program, object.model_transform.Translate, { 0.0, 51.0 / 255.0, 204.0 / 225. }, dir);
	CObjectMgr::Get_Instance()->AddObject(OBJID::PLAYER_BULLET, bullet);

	// 왼
	dir = { -1.f,0.f,0.f };
	vector_normalize(dir);
	bullet = new CPlayer_Bullet(shader_program, object.model_transform.Translate, { 0.0, 51.0 / 255.0, 204.0 / 225. }, dir);
	CObjectMgr::Get_Instance()->AddObject(OBJID::PLAYER_BULLET, bullet);

	// 왼 위
	dir = { -1.f,0.f,-1.f };
	vector_normalize(dir);
	bullet = new CPlayer_Bullet(shader_program, object.model_transform.Translate, { 0.0, 51.0 / 255.0, 204.0 / 225. }, dir);
	CObjectMgr::Get_Instance()->AddObject(OBJID::PLAYER_BULLET, bullet);
}

