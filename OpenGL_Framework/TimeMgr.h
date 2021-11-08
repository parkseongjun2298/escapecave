#pragma once
class CTimeMgr
{
	DECLARE_SINGLETON(CTimeMgr)

private:
	CTimeMgr();
	~CTimeMgr();


public:
	float Get_DeltaTime() { return m_fDeltaTime; }

public:
	void Ready_Time();
	void Update_Time();
private:
	LARGE_INTEGER		m_CpuTick;
	LARGE_INTEGER		m_BeginTime;
	LARGE_INTEGER		m_EndTime;

	float				m_fDeltaTime;

};

