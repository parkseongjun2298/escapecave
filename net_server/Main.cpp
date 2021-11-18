
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include "Server.h"
#include "Function.h"

// ������ ���� �Լ�
int recvn(SOCKET s, char *buf, int len, int flags)
{
	int received;
	char *ptr = buf;
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

// �����峢�� Ŀ�� ��ġ �������� ���ϵ��� ���ڿ� ��� ���� ������ ����ϴ� �Լ�
void set_cursor(COORD pos) {
	//WaitForSingleObject(hCursorEvent, INFINITE);
	// ǥ���ܼ������ �ڵ� ��ȯ -> pos�� ����Ű�� ��ǥ�� ĳ���� �̵���Ų��.
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



/*
// ������. Ŭ���̾�Ʈ�� ������ ���
DWORD WINAPI Recv_Thread(LPVOID arg)
{
	SOCKET client_sock = (SOCKET)arg;
	int retval;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE + 1];

	// cmdâ number��° �ٿ� ���۷� Ǯ��
	int number = num++;
	COORD pos = { 0,number };
	DataInfo datainfo;
	int current_received_size = 0;

	// Ŭ���̾�Ʈ ���� ���
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);

	while (1) {
		// ������ �ޱ�(���� ����)
		retval = recvn(client_sock, (char*)&datainfo, sizeof(DataInfo), 0);
		if (retval == SOCKET_ERROR) {
			set_cursor(pos);
			err_display("recv()");
			break;
		}
		else if (retval == 0) {
			break;
		}
		switch (datainfo.infoindex) {
		case 'a':
			Recv_GameStart();
			break;
		}
		/*
		// ������ �ޱ�(���� ����)
		retval = recvn(client_sock, buf, datainfo.infoindex, 0);
		if (retval == SOCKET_ERROR) {
			set_cursor(pos);
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;
		// ���Ź��� �������� ���� ��� (ĳ���� ���� �� ������ ���� Scroll Up ����)
		current_received_size += retval;
		SetEvent(hCursorEvent);

	}

	// closesocket()
	closesocket(client_sock);
	SetEvent(hCursorEvent);
	return 0;
}
*/
int main(int argc, char *argv[])
{
	Server server;
	//Ŭ���̾�Ʈ 3�� ���� �� ������ ��� -> ������ 3�� �����Ǹ� �Լ� �����
	server.InitServer();
	// Ŭ���̾�Ʈ 3���� ������Ʈ �ʱ�ȭ ��û �۽�
	server.RunServer();
	printf("��");
	while (1) {
		server.Update();
		server.Send_ObjectInfo();
	}
	server.Close_Connect();
	return 0;
}
