#define _WINSOCK_DEPRECATED_NO_WARNINGS // �ֽ� VC++ ������ �� ��� ����
#include "pch.h"
#include "Server.h"
#include "RecvThread.h"
#include "struct.h"
#include "player.h"
#include "enum.h"
#include "StaticList.h"
#include "Function.h"

using namespace std;
#pragma comment(lib, "ws2_32.lib")
#define SERVERPORT 9000
#define BUFSIZE    4096

template <typename T>
void Server::Safe_Delete(T& _obj) {
	delete _obj;
	_obj = nullptr;
}

void Server::err_quit(const char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// ���� �Լ� ���� ���
void Server::err_display(const char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);

	printf("\n", msg);
}

void Server::Send_Initialize() {
	datainfo.infoindex = 'a';
	datainfo.datasize = 'a';

	// ��ſ� ����ü �۽�
	for (int i = 0;i < 3;i++) {
		retval = send(client_sock[i], (char*)&datainfo, sizeof(DataInfo), 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
			return;
		}
	}

	printf("������Ʈ �ʱ�ȭ ��û �۽�\n");
}

void Server::RunServer() {
	Send_Initialize();

	printf("���ӽ���");
	return;
};

void Server::InitServer() {
	// 1. ���� �ʱ�ȭ
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		exit(1);

	// 2. ���� ����
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// ���ε�
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// 3. Ŭ���̾�Ʈ�� ���� ��û�� ��ٸ�(listen �Լ�)
	retval = listen(sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// ��ſ� ����� ���� ����
	SOCKADDR_IN clientaddr;
	int addrlen;
	HANDLE hThread;
	int i = 0;
	// �����忡�� ������ ���� ���� ����� �� �ٸ� �����尡 Ŀ�� ��ġ �ٲ��� �ʵ��� ����. �ڵ� ����, ��ȣ ���·� ����
	hCursorEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
	printf("��� ��� ��");
	// ������ �� 3�� ����� �����Լ��� ���ư���.
	while (i<3) {
		if (hCursorEvent == NULL) break;
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock[i] = accept(sock, (SOCKADDR*)&clientaddr, &addrlen);
		if (client_sock[i] == INVALID_SOCKET) {
			err_display("accept()");
			SetEvent(hCursorEvent);
			break;
		}
		printf("\r[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
		SetEvent(hCursorEvent);
		// ������ ����
		hThread = CreateThread(NULL, 0, Recv_Thread,
			(LPVOID)client_sock[i++], 0, NULL);
		if (hThread == NULL) { closesocket(client_sock[--i]); }
		else { CloseHandle(hThread); }
		printf("%d\n", i);
	}
}

void Server::Update()
{
	OBJECT_LIST::iterator iter_begin = m_ObjectList[OBJID::PLAYER].begin();
	OBJECT_LIST::iterator iter_end = m_ObjectList[OBJID::PLAYER].end();
	for (int i = 0; i < OBJID::END; ++i)
	{	// �޶���ϴµ� �� ���̰���
		OBJECT_LIST::iterator iter_begin = m_ObjectList[i].begin();
		OBJECT_LIST::iterator iter_end = m_ObjectList[i].end();

		for (; iter_begin != iter_end;)
		{
			//Update() �Լ��� hp�� ��ȯ�ϰ� 0�̸� ����
			int iEvent = 0;
			iEvent = (*iter_begin)->Update();
			if (!iEvent)
			{
				Safe_Delete(*iter_begin);
				iter_begin = m_ObjectList[i].erase(iter_begin);
			}
			else
				++iter_begin;
		}
	}
}

void Server::Close_Connect() {
	CloseHandle(hCursorEvent);
	// 4. ���� ����
	closesocket(sock);

	// 5. ���� ����
	WSACleanup();
	exit(1);
}