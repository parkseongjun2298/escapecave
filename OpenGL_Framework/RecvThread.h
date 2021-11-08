#pragma once
#include <winsock2.h>
class Thread
{
	HANDLE thread;
public:
	Thread(SOCKET recv_socket);
};
