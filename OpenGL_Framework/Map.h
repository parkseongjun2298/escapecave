#pragma once
#include "Obj.h"
class CMap :
    public CObj
{
public:
	CMap(GLuint* _shader_program, glm::vec3 pos, glm::vec3 scale, glm::vec3 color);
	~CMap();




	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Draw() override;
	virtual void Release() override;
	virtual void Set_ModelTransform() override;
	
private:
	glm::vec3 m_color;

};

