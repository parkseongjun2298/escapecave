#pragma once
#ifndef __OBJ_H__
#define __OBJ_H__


class CObj
{
public:
	CObj(GLuint* _shader_program);
	~CObj();
public:
	virtual void Initialize()=0;
	virtual int Update()=0;
	virtual void Late_Update() = 0;
	virtual void Draw()=0;
	virtual void Release()=0;

public:
	GLuint& Get_vao() { return vao; }
	GLuint* Get_vbo() { return vbo; }
	GLuint& Get_normalbuffer() { return normalbuffer; }
	OBJECT& Get_Object() { return object; }
	glm::vec3& Get_Info() { return object.model_transform.Translate; }
	glm::vec3& Get_size() { return object.model_transform.Scale; }
	void  Set_Dead() { m_bDead = true; }
public:
	void Set_Translate(glm::vec3 _moveSize) { object.model_transform.Translate += _moveSize; }
public:
	void Set_ShaderProgram(GLuint* _shader_program) { shader_program = _shader_program; }
	void vector_normalize(glm::vec3& _vec3);

protected:
	void Add_Effect(int num);

protected:
	virtual void Set_ModelTransform() = 0;
	GLuint vao, vbo[2];
	GLuint normalbuffer;
	GLuint* shader_program;
	OBJECT object;


	float m_fSpeed = 0;
	glm::vec3 Look;
	bool  m_bDead;
};


#endif // !__OBJ_H__

