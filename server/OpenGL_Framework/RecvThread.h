#pragma once
#include <winsock2.h>
#include "struct.h"
DWORD WINAPI Recv_Thread(LPVOID arg);

class Thread
{
	HANDLE thread;
public:
	SOCKET sock;
	Thread(SOCKET recv_socket);
};