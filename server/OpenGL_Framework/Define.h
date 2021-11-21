#pragma once
#define WINCX 1400
#define WINCY 800


// ≈∏¿Ã∏”
#define TIMER_MAIN	0
#define TIMER_ADD	1
#define ADD_TIME	500
#define SAFE_DELETE(p) { delete p, p = nullptr;}

#define VK_MAX		0xFF

#define FOVY		45.f
#define FAR_Z		1000.f

#define NULL_CHECK_RETURN(ptr, val) if(nullptr == (ptr)) return val;

#define NO_EVENT 0
#define DEAD_OBJ 1
#define NO_COPY(ClassName)						\
private:										\
	ClassName(const ClassName&);				\
	ClassName operator=(const ClassName&);		\

#define DECLARE_SINGLETON(ClassName)			\
		NO_COPY(ClassName)						\
public:											\
	static ClassName* GetInstance();			\
	void DestroyInstance();						\
private:										\
	static ClassName* m_pInstance;

#define DECLARE_SINGLETON(Class)						\
public:													\
	static Class* Get_Instance()						\
	{													\
		if (nullptr == m_pInstance)						\
			m_pInstance = new Class;					\
		return m_pInstance;								\
	}													\
	static void Destroy_Instance()						\
	{													\
		if (m_pInstance)								\
		{												\
			delete m_pInstance;							\
			m_pInstance = nullptr;						\
		}												\
	}													\
private:												\
	static Class* m_pInstance;				


#define IMPLEMENT_SINGLETON(Class)					\
Class* Class::m_pInstance = nullptr;
