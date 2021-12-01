#include "pch.h"
#include "RecvThread.h"
#include "server.h"
#include "tmp.h"

int Thread::num = 0;
DWORD WINAPI Recv_Thread(LPVOID arg) {
	DataInfo datainfo;
	SOCKET sock = (SOCKET)arg;
	int num = Thread::num++;

	printf("Therad_initialized\n");
	while (true) {
		int retval = recv(sock, (char*)&datainfo, sizeof(DataInfo), 0);
		if (retval == SOCKET_ERROR)
			break;
		//err_display("recv()");
		else if (retval == 0)
			break;
		//retval = WaitForSingleObject(hSynchro, INFINITE);
		//if (retval != WAIT_OBJECT_0)
		//	break;
		switch (datainfo.infoindex) {
			//Recv_Input() 함수 역할
		case 'a':
			printf("받음\n");
			(just_tmp[num]).key = datainfo.datasize;
			break;
		}
		//ResetEvent(hSynchro);	//클라이언트로부터 키 입력이 와도 오브젝트 업데이트까지 적용 대기시킨다.
	}
	return 0;
};


Thread::Thread(SOCKET socket) {
	thread = CreateThread(NULL, 0, Recv_Thread,
		(LPVOID)socket, 0, NULL);
	if (thread == NULL) { closesocket(socket); }
	else { CloseHandle(thread); }
};
