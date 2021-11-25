#include "pch.h"
#include "TimeMgr.h"

IMPLEMENT_SINGLETON(CTimeMgr)


CTimeMgr::CTimeMgr()
{
	Ready_Time();
}


CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::Ready_Time()
{
	ZeroMemory(&m_CpuTick, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_BeginTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_EndTime, sizeof(LARGE_INTEGER));

	QueryPerformanceFrequency(&m_CpuTick);
	QueryPerformanceCounter(&m_BeginTime);
	QueryPerformanceCounter(&m_EndTime);
}

void CTimeMgr::Update_Time()
{

	// 시간 = 거리/속력
	QueryPerformanceFrequency(&m_CpuTick);
	QueryPerformanceCounter(&m_EndTime);
	m_fDeltaTime = float(m_EndTime.QuadPart - m_BeginTime.QuadPart) / m_CpuTick.QuadPart;

	m_BeginTime = m_EndTime;
}
