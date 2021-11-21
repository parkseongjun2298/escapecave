#include "pch.h"
#include "RecvThread.h"



DWORD WINAPI Recv_Thread(LPVOID arg) {
	SOCKET client_sock = (SOCKET)arg;
	printf("Therad_initialized\n");
	/*
	while 1:
		recv();
	*/
	return 0;
};