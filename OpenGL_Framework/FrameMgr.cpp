#include "pch.h"
#include "FrameMgr.h"


CFrameMgr::CFrameMgr()
{

	ZeroMemory(&m_CpuTick, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_BeginTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_EndTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_szFPS, sizeof(m_szFPS));
	m_fDeltaTime = 0.f;
	m_fSecondPerFrame = 0.f;
}


CFrameMgr::~CFrameMgr()
{
}

void CFrameMgr::ReadyFrame(float fFPS)
{
	m_fSecondPerFrame = 1.f / fFPS;
	QueryPerformanceCounter(&m_EndTime);
	QueryPerformanceFrequency(&m_CpuTick);
	QueryPerformanceCounter(&m_BeginTime);
}

bool CFrameMgr::LockFrame()
{
	QueryPerformanceCounter(&m_EndTime);
	QueryPerformanceFrequency(&m_CpuTick);
	m_fDeltaTime += float(m_EndTime.QuadPart - m_BeginTime.QuadPart) / m_CpuTick.QuadPart;
	m_BeginTime = m_EndTime;
	if (m_fSecondPerFrame <= m_fDeltaTime)
	{
		m_fDeltaTime = 0.f;
		return true;
	}
	return false;
}

void CFrameMgr::RenderFrame()
{
}
