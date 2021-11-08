#pragma once

class CShader
{
public:
	CShader();
	~CShader();

public:
	void Initialize_Shader();
	void Upadate_Shader(GLuint _vao, GLuint _vbo[2], GLuint _normalbuffer, const OBJECT& _object);

private:
	void make_vertexShader();
	void make_fragmentShader();
	void Update_buffer(GLuint _vao, GLuint _vbo[2], GLuint _normalbuffer, const OBJECT& _object);
	void Upadte_Shader_Program();

public:
	GLuint* Get_shaderProgram() { return &shader_program; }

private:
	GLchar* vertexsource, *fragmentsource;	// 소스코드 저장 변수
	GLuint vertexshader, fragmentshader;	// 쉐이더 객체
	GLuint shader_program;

};

