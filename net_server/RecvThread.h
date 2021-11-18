#pragma once
#include <winsock2.h>
#include "struct.h"
#include "NetShare.h"
DWORD WINAPI Recv_Thread(LPVOID arg);

class Thread : public NetShare
{
	void Update_PlayerInfo();
public:
	void Recv_Input();
};