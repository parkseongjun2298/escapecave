#pragma once
#include <winsock2.h>
#include "struct.h"
DWORD WINAPI Recv_Thread(LPVOID arg);

class Thread
{
	HANDLE thread;
public:
	static int num;
	SOCKET sock;
	Thread(SOCKET recv_socket);
};