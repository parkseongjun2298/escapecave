#include "pch.h"
#include "RecvThread.h"

DWORD WINAPI Recv_Thread(LPVOID arg) {
	printf("Therad_initialized\n");
	return 0;
};

Thread::Thread(SOCKET recv_socket) {
	thread = CreateThread(NULL, 0, Recv_Thread,
		(LPVOID)recv_socket, 0, NULL);
	if (thread == NULL) { closesocket(recv_socket); }
	else { CloseHandle(thread); }

};
