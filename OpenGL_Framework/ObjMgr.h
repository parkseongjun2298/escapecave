#pragma once
#include "Shader.h"

class CObj;
class CObjectMgr
{
	DECLARE_SINGLETON(CObjectMgr)
private:
	CObjectMgr();
	~CObjectMgr();
public:

	CObj* GetPlayer();
	CObj* GetMonster();

public:
	HRESULT AddObject(OBJID::OBJ eType, CObj* pObject);
	void Update();
	void LateUpdate();
	void Set_Shader(CShader* _Shader) { Shader = _Shader; }
	void Set_Camera(Camera* _Camera) { m_Camera = _Camera; }
	void Set_Light(OBJECT* _light) { m_light = _light; }
	const Camera& Get_Camera() { return *m_Camera; }
	const OBJECT& Get_light() { return *m_light; }
	const int& Get_Size(OBJID::OBJ _ObjID) { return m_ObjectList[_ObjID].size(); }
	CObj* Get_Gate_Back() { return m_ObjectList[OBJID::GATE].back(); }
	OBJECT Get_Obj_File(string _name) { return m_mapObjFile[_name]; }
public:
	void Load_All_Obj();
private:
	void Release();

public:
	typedef list<CObj*>   OBJECT_LIST;
	OBJECT_LIST   m_ObjectList[OBJID::END];
	CShader* Shader;
	Camera* m_Camera;
	OBJECT* m_light;
	map<string, OBJECT> m_mapObjFile;
};