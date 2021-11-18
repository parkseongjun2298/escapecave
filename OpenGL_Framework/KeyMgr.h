#pragma once

#ifndef __KEYMGR_H__
#define __KEYMGR_H__

const DWORD KEY_UP = VK_UP; // 0000 0000 0000 0000 0000 0000 0000 0001
const DWORD KEY_DOWN = VK_DOWN; // 0000 0000 0000 0000 0000 0000 0000 0010	
const DWORD KEY_LEFT = VK_LEFT; // 0000 0000 0000 0000 0000 0000 0000 0100
const DWORD KEY_RIGHT = VK_RIGHT; // 0000 0000 0000 0000 0000 0000 0000 1000
const DWORD KEY_A = 'A'; // 0000 0000 0000 0000 0000 0000 0000 1000
const DWORD KEY_S = 'S'; // 0000 0000 0000 0000 0000 0000 0000 1000

const DWORD KEY_SPACE = VK_SPACE; // 0000 0000 0000 0000 0000 0000 0001 0000
const DWORD KEY_RETURN = 0x00000020; // 0000 0000 0000 0000 0000 0000 0010 0000
const DWORD KEY_LBUTTON = 0x00000040; // 0000 0000 0000 0000 0000 0000 0100 0000
const DWORD KEY_RBUTTON = 0x00000080; // 0000 0000 0000 0000 0000 0000 1000 0000


class CKeyMgr
{
private:
	CKeyMgr();
	~CKeyMgr();

public:
	bool Key_Down(int _key);
	bool Key_Up(int _key);
	bool Key_Pressing(int _key);
	void Key_Update();

public:
	static CKeyMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CKeyMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CKeyMgr*	m_pInstance;
	bool			m_bKeyState[VK_MAX];
};

#endif // !__KEYMGR_H__
