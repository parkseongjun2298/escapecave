#include "pch.h"
#include "Obj.h"
#include "Bomb_Effect.h"

CObj::CObj(GLuint* _shader_program)
{
	shader_program = _shader_program;
	glGenVertexArrays(1, &vao); //--- VAO 를 지정하고 할당하기
	glGenBuffers(2, vbo); //--- 2개의 VBO를 지정하고 할당하기
	glGenBuffers(1, &normalbuffer);

	m_bDead = false;
}

CObj::~CObj()
{
}

void CObj::vector_normalize(glm::vec3& _vec3)
{
	float len;
	len = sqrtf(_vec3.x * _vec3.x + _vec3.y * _vec3.y + _vec3.z * _vec3.z);
	_vec3.x /= len;
	_vec3.y /= len;
	_vec3.z /= len;
}

void CObj::Add_Effect(int num)
{
	for (int i = 0; i < num; ++i) {
		CObj* Effect = new CBomb_Effect(shader_program, object.model_transform.Translate);
		CObjectMgr::Get_Instance()->AddObject(OBJID::EFFECT, Effect);
	}
}

void CObj::get_vec3(glm::vec3 vector) {
	//편의를 위하여 열배 곱했던걸 되돌린다.
	glm::vec3 tmp = vector;
	tmp.x /= 10;
	tmp.y /= 10;
	tmp.z /= 10;
	object.model_transform.Translate = tmp;
}
