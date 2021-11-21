#pragma once
class CSoundMgr
{
public:
	static CSoundMgr* GetInstance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSoundMgr;

		return m_pInstance;
	}
	static void DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
public:
	enum CHANNELID { BGM, PLAYER, PLAYEREFFECT, MONSTER, BOSSEFFECT, BOSS, EFFECT, MAXCHANNEL };
private:
	CSoundMgr();
	~CSoundMgr();

public:
	void Initialize();

	void Release();
public:
	void PlaySound(TCHAR* pSoundKey, CHANNELID eID);
	void PlaySoundVolume(TCHAR* pSoundKey, CHANNELID eID, float vol);
	void PlayBGM(TCHAR* pSoundKey);
	void StopSound(CHANNELID eID);
	void StopAll();
	void SetVolume(CHANNELID eID, float vol);
	void Update() { FMOD_System_Update(m_pSystem); }//사운드가 재생되는 씬의 레이트업데이트 맨 마지막에 저거 호출해주면


private:
	void LoadSoundFile();

private:
	static CSoundMgr* m_pInstance;
	// 사운드 리소스 정보를 갖는 객체 
	map<TCHAR*, FMOD_SOUND*> m_mapSound;
	// FMOD_CHANNEL : 재생하고 있는 사운드를 관리할 객체 
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL];
	// 사운드 ,채널 객체 및 장치를 관리하는 객체 
	FMOD_SYSTEM* m_pSystem;

};

