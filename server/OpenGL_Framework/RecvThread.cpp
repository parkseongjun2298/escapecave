#include "pch.h"
#include "RecvThread.h"
#include "server.h"
#include "tmp.h"

int recvn(SOCKET s, char* buf, int len, int flags)
{
	int received;
	char* ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);
}

int Thread::num = 0;
#define BUFSIZE    5000
DWORD WINAPI Recv_Thread(LPVOID arg) {
	DataInfo datainfo;
	SOCKET sock = (SOCKET)arg;
	char buf[10];
	int num = Thread::num++;

	printf("Therad_initialized\n");
	while (true) {
		int retval = recv(sock, (char*)&datainfo, sizeof(DataInfo), 0);
		if (retval == SOCKET_ERROR)
			break;
		//err_display("recv()");
		//else if (retval == 0)
			//break;
		EnterCriticalSection(&cs);
		switch (datainfo.infoindex) {
			//Recv_Input() �Լ� ����
		case 'a':
			//printf("����\n");
			if (datainfo.datasize == 'p')//���콺 Ŭ��(����)
				(Mouse_tmp[num]).key = datainfo.datasize;
			else {//Ű���� �Է�(�̵�)
				retval = recvn(sock, buf, sizeof(buf), 0);
				for (int i = 0; i < 6; i++)
				{
					just_tmp[num].key[i] = buf[i];
				}
				just_tmp[num].key[6] = '\0';
				//printf("%s", just_tmp[num].key);
			}
			break;
		}
		LeaveCriticalSection(&cs);	//Ŭ���̾�Ʈ�κ��� Ű �Է��� �͵� ������Ʈ ������Ʈ���� ���� ����Ų��.
	}
	return 0;
};


Thread::Thread(SOCKET socket) {
	thread = CreateThread(NULL, 0, Recv_Thread,
		(LPVOID)socket, 0, NULL);
	if (thread == NULL) { closesocket(socket); }
	else { CloseHandle(thread); }
}
