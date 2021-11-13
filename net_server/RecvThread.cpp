#include "pch.h"
#include "RecvThread.h"
#include "Server.h"
int Thread::thread_num = 0;

void Thread::Recv_Input() {
	switch (datainfo.datasize) {
	case 'a':
		printf("a");
		break;
	case 's':
		printf("s");
		break;
	case 'd':
		printf("d");
		break;
	case 'w':
		printf("w");
		break;
	}


}

DWORD WINAPI Recv_Thread(LPVOID arg) {
	Thread thread;
	thread.sock = (SOCKET)arg;
	thread.num = Thread::thread_num++;

	printf("Therad_initialized\n");
	while (true) {
		int retval = recv(thread.sock, (char*)&thread.datainfo, sizeof(DataInfo), 0);
		if (retval == SOCKET_ERROR)
			break;
			//err_display("recv()");
		else if (retval == 0)
			break;
		switch (thread.datainfo.infoindex) {
		case 'a':
			thread.Recv_Input();
			break;
		}
	}
	return 0;
};