#include "pch.h"
#include "Bomb_Effect.h"

CBomb_Effect::CBomb_Effect(GLuint* _shader_program, glm::vec3 pos)
    :CObj(_shader_program)
{
	int random = rand() % 20 - 10;
	/*pos.x += random;
	pos.z += rand() % 20 - 10;*/
	object.model_transform.Translate = pos;
	object.model_transform.Scale *= 0.4f;
	object.model_transform.Rotate.x = rand() % 180;
	object.model_transform.Rotate.y = rand() % 180;
	object.model_transform.Rotate.z = rand() % 180;

	int color_rand = rand() % 3;
	if (color_rand == 0) {
		m_color = { 0.4,0.0,0.0 };
	}
	else if (color_rand == 1) {
		m_color = { 0.5,0.5,0.0 };
	}
	else
		m_color = { 0.4,0.4,0.4 };
	Initialize();
}

CBomb_Effect::~CBomb_Effect()
{
}

void CBomb_Effect::Initialize()
{
	// triangle
	object.vertices.push_back({ 0.0,1.0,0.0 });
	object.vertices.push_back({ -1.0,-1.0,0.0 });
	object.vertices.push_back({ 1.0,-1.0,0.0 });
	object.color.push_back(m_color);
	object.color.push_back(m_color);
	object.color.push_back(m_color);
	object.normals.push_back({ 0.0,1.0,0.0 });
	object.normals.push_back({ -1.0,-1.0,0.0 });
	object.normals.push_back({ 1.0,-1.0,0.0 });
	int randomX = rand() % 40 - 20;
	int randomY = rand() % 20 - 10;
	int randomZ = rand() % 40 - 20;

	m_vDir = { randomX * 0.01f,randomY * 0.01f, randomZ * 0.01f };
}

int CBomb_Effect::Update()
{
	m_fCreatetime += 0.1f;
	if (m_fCreatetime > 5.f)
		return DEAD_OBJ;
	object.model_transform.Translate += m_vDir;

    return 0;
}

void CBomb_Effect::Late_Update()
{
}

void CBomb_Effect::Draw()
{
	unsigned int modelLocation = glGetUniformLocation(*shader_program, "model");
	unsigned int viewLocation = glGetUniformLocation(*shader_program, "view");
	unsigned int projLocation = glGetUniformLocation(*shader_program, "projection");
	// ============================= 고정 ============================================


	// ============================= 뷰 변환 ============================================
	// 카메라 좌표 설정
	glLineWidth(0.2f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


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

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void CBomb_Effect::Release()
{
}

void CBomb_Effect::Set_ModelTransform()
{
}
