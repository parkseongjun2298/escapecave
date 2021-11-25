#include "pch.h"
#include "BossMonster.h"
#include "Boss_head.h"
#include "NormalMonster.h"
#include "ShiledMonster.h"
#include "MonsterBullet.h"
#include "TonadoMonster.h"
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

int CBossMonster::Update( )
{
	object.model_transform.Rotate.y += 2.f;
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
	// ============================= ���� ============================================


	// ============================= �� ��ȯ ============================================


	glm::mat4 view = glm::mat4(1.f);
	glm::mat4 view_Rotate = glm::mat4(1.f);
	view_Rotate = glm::rotate(view_Rotate, glm::radians(0.f), glm::vec3(0.0, 1.0, 0.0));
	CAMERA_DESC camera = CObjectMgr::Get_Instance()->Get_Camera();
	view = view_Rotate * glm::lookAt(camera.cameraPos, camera.cameraDirection, camera.cameraUp);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	// ============================= �� ��ȯ ============================================

	// ============================= ���� ��ȯ ============================================
	glm::mat4 projection = glm::mat4(1.f);
	projection = glm::perspective(glm::radians(FOVY), (float)WINCX / (float)WINCY, 1.f, FAR_Z);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);
	// ============================= ���� ��ȯ ============================================

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

	// ũ �� �� �� �� �Ųٷ�
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
}

void CBossMonster::Noraml_Attack()
{
}

void CBossMonster::Sky_Attack()
{
}

void CBossMonster::bullet36_Attack()
{

}
