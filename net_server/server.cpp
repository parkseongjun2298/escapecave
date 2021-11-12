#define _WINSOCK_DEPRECATED_NO_WARNINGS // �ֽ� VC++ ������ �� ��� ����
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#define SERVERPORT 9000
#define BUFSIZE    4096

void err_quit(char* msg);
void err_display(const char* msg);

typedef struct DataInfo {
	char infoindex;	// ��Ŷ Ÿ��
	char datasize;	// ��Ŷ ũ��
};

//  cmdâ num��° �ٿ� ���ڿ� ���
int num = 0;
int startnum = 0;
// ���ڿ� ����� �� �ٸ� �����尡 Ŀ�� ��ġ �ٲ��� �ʵ��� ����
HANDLE hCursorEvent;

// ���� �Լ� ���� ��� �� ����
void err_quit(char* msg)
{
	LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, WSAGetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf, 0, NULL);
   // MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
    LocalFree(lpMsgBuf);
    exit(1);
}

// ���� �Լ� ���� ���
void err_display(const char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

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
	WaitForSingleObject(hCursorEvent, INFINITE);
	// ǥ���ܼ������ �ڵ� ��ȯ -> pos�� ����Ű�� ��ǥ�� ĳ���� �̵���Ų��.
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void RunServer() {
	printf("���ӽ���");
	return;
};

void Recv_GameStart() {
	startnum++;
	printf("���ӽ��ۿ�û %d��", startnum);
	if (startnum == 3)
		RunServer();
}

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
			*/
		// ���Ź��� �������� ���� ��� (ĳ���� ���� �� ������ ���� Scroll Up ����)
		current_received_size += retval;
		SetEvent(hCursorEvent);

	}

	// closesocket()
	closesocket(client_sock);
	SetEvent(hCursorEvent);
	return 0;
}

void InitServer() {

}
int main(int argc, char *argv[])
{
	int retval;

	// 1. ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 2. ���� ����
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit((char*)"socket()");

	// ���ε�
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit((char*)"bind()");

	// 3. Ŭ���̾�Ʈ�� ���� ��û�� ��ٸ�(listen �Լ�)
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit((char*)"listen()");

	// ��ſ� ����� ���� ����
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	HANDLE hThread;

	// �����忡�� ������ ���� ���� ����� �� �ٸ� �����尡 Ŀ�� ��ġ �ٲ��� �ʵ��� ����. �ڵ� ����, ��ȣ ���·� ����
	hCursorEvent = CreateEvent(NULL, FALSE, TRUE, NULL);

	printf("��� ��� ��");
	while (1) {
		if (hCursorEvent == NULL) break;
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
		COORD pos = { 0,num++ };
		if (client_sock == INVALID_SOCKET) {
			set_cursor(pos);
			err_display("accept()");
			SetEvent(hCursorEvent);
			break;
		}

		// ������ Ŭ���̾�Ʈ ���� ���
		set_cursor(pos);
		printf("\r[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
		SetEvent(hCursorEvent);

		// ������ ����
		hThread = CreateThread(NULL, 0, Recv_Thread,
			(LPVOID)client_sock, 0, NULL);
		if (hThread == NULL) { closesocket(client_sock); }
		else { CloseHandle(hThread); }

	}
	CloseHandle(hCursorEvent);
	// 4. ���� ����
	closesocket(listen_sock);

	// 5. ���� ����
	WSACleanup();
	return 0;
}
