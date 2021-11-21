#include "pch.h"
#include "Boss_head.h"

CBoss_head::CBoss_head(GLuint* _shader_program, CObj* _parent)
	:CObj(_shader_program)
{
	Initialize();
	object.model_transform.Parent = &_parent->Get_Object().model_transform;
}

CBoss_head::~CBoss_head()
{
}

void CBoss_head::Initialize()
{
	loadObj<const char*, OBJECT, glm::vec3>("diamond.obj", object, { 128. / 255., 0., 0. });
	object.model_transform.Translate = { 0.f,8.f,0.f };
	object.model_transform.Scale *= 1.5f;
}

int CBoss_head::Update()
{
	object.model_transform.Rotate.y += 5.f;
	return 0;
}

void CBoss_head::Late_Update()
{
}

void CBoss_head::Draw()
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

void CBoss_head::Release()
{
}

void CBoss_head::Set_ModelTransform()
{
}
