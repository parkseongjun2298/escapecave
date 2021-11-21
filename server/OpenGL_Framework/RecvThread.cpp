#include "pch.h"
#include "RecvThread.h"
#include "Client.h"
#include "tmp.h"


DWORD WINAPI Recv_Thread(LPVOID arg) {
	DataInfo datainfo;
	SOCKET sock = (SOCKET)arg;
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
			//Recv_Input() �Լ� ����
		case 'a':
			just_tmp.key = datainfo.datasize;
			break;
		}
		//ResetEvent(hSynchro);	//Ŭ���̾�Ʈ�κ��� Ű �Է��� �͵� ������Ʈ ������Ʈ���� ���� ����Ų��.
	}
	return 0;
};


Thread::Thread(SOCKET socket) {
	thread = CreateThread(NULL, 0, Recv_Thread,
		(LPVOID)socket, 0, NULL);
	if (thread == NULL) { closesocket(socket); }
	else { CloseHandle(thread); }
};
