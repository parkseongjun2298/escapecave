#pragma once
#include <winsock2.h>
#include "struct.h"
DWORD WINAPI Recv_Thread(LPVOID arg);

class Thread
{
	int retval;
public:
	static int thread_num;
	int num;
	HANDLE hCursorEvent;
	DataInfo datainfo;
	SOCKET sock;
	void Recv_Input();
};