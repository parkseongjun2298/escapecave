#pragma once
class CFrameMgr
{
public:
	CFrameMgr();
	~CFrameMgr();

public:
	void ReadyFrame(float fFPS);
	bool LockFrame();
	void RenderFrame();

private:
	LARGE_INTEGER	m_CpuTick;
	LARGE_INTEGER	m_BeginTime;
	LARGE_INTEGER	m_EndTime;
	float			m_fDeltaTime;
	float			m_fSecondPerFrame;
	TCHAR			m_szFPS[32];
};

