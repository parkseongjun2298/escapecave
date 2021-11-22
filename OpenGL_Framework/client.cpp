#include "pch.h"
#include "Client.h"
#include "RecvThread.h"

#pragma comment(lib, "ws2_32.lib")
#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE    50
#include "ObjMgr.h"
#include "Obj.h"

SOCKET Client::sock = NULL;
void Client::Recv_ObjectInfo() {
	retval = recv(Client::sock, (char*)&datainfo, sizeof(DataInfo), 0);

	if (retval == SOCKET_ERROR)
		err_display("recv()");
	else if (retval == 0)
		return;
	printf("%c", datainfo.datasize);

}

DWORD WINAPI Client::Recv_Thread(LPVOID arg) {
	SOCKET client_sock = (SOCKET)arg;
	printf("Therad_initialized\n");
	DataInfo datainfo;
	while (1) {
		// �����ϰ�
		int retval = recv(Client::sock, (char*)&datainfo, sizeof(DataInfo), 0);
		if (retval == SOCKET_ERROR);
		//err_display("recv()");
		else if (retval == 0)
			return 0;
		switch (datainfo.infoindex) {
		case 'b':
			printf("%c", datainfo.datasize);
		}
		// �̺�Ʈ true���� ����ϰ�
		//int retval = WaitForSingleObject(hSynchro, INFINITE);
		//if (retval != WAIT_OBJECT_0) exit(1);
		// ������Ʈ ���� �� �ڿ�
		//update();
		//������Ʈ ȭ�鿡 �׸���.
		//SetEvent(client.hSynchro);
	}
	return 0;
};

void Client::err_quit(const char *msg)
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
void Client::err_display(const char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);

	printf("\n", msg);
}

void Client::set_datainfo(char a, char b) {
	datainfo.infoindex = a;
	datainfo.datasize = b;
}

void Client::Send_Input(char b) {
	set_datainfo('a', b);
	// ��ſ� ����ü �۽�
	retval = send(Client::sock, (char*)&datainfo, sizeof(DataInfo), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
		return;
	}
}

void Client::InitClient() {
	// 1. ���� �ʱ�ȭ
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		exit(1);

	// 2. ���� ����
	Client::sock = socket(AF_INET, SOCK_STREAM, 0);
	if (Client::sock == INVALID_SOCKET) err_quit("socket()");

	// 3. ������ ����
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(Client::sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");
	// 4. ������ ����
	HANDLE thread = CreateThread(NULL, 0, Recv_Thread,
		(LPVOID)Client::sock, 0, NULL);
	if (thread == NULL) { closesocket(Client::sock); }
	else { CloseHandle(thread); }
	hSynchro = CreateEvent(NULL, FALSE, TRUE, NULL);

}
void Client::Send_GameStart() {

	set_datainfo('a', 'a');
	// ��ſ� ����ü �۽�
	retval = send(Client::sock, (char*)&datainfo, sizeof(DataInfo), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
		return;
	}
	Recv_Initialize();
}
void Client::Recv_Initialize() {
	retval = recv(Client::sock, (char*)&datainfo, sizeof(DataInfo), 0);
	printf("a");
	if (retval == SOCKET_ERROR)
		err_display("recv()");
	else if (retval == 0)
		return;
	printf("������Ʈ �ʱ�ȭ ��û ����\n");
}

//CObj* Client::Connect_Bullet()
//{
//	m_ObjectList[OBJID::PLAYER_BULLET] = CObjectMgr::Get_Instance()->m_ObjectList[OBJID::PLAYER_BULLET];
//	if (m_ObjectList[OBJID::PLAYER_BULLET].empty())
//		return nullptr;
//
//	return m_ObjectList[OBJID::PLAYER_BULLET].front();
//}
//
//CObj* Client::Connect_Monster_Bullet()
//{
//	m_ObjectList[OBJID::MONSTER_BULLET] = CObjectMgr::Get_Instance()->m_ObjectList[OBJID::MONSTER_BULLET];
//	if (m_ObjectList[OBJID::MONSTER_BULLET].empty())
//		return nullptr;
//
//	return m_ObjectList[OBJID::MONSTER_BULLET].front();
//}
//
//void Client::Send_Bullet_Info() {
//	datainfo.infoindex = 'b';
//	datainfo.datasize = 'b';
//	CObj* bullet = Connect_Bullet();
//	if (bullet == nullptr)
//		return;
//	else
//	{
//
//		datainfo.m_fx = bullet->Get_Info().x;
//		datainfo.m_fy = bullet->Get_Info().y;
//		datainfo.m_fz = bullet->Get_Info().z;
//
//
//
//		// ��ſ� ����ü �۽�
//		retval = send(recv_socket, (char*)&datainfo, sizeof(DataInfo), 0);
//		if (retval == SOCKET_ERROR) {
//			err_display("send()");
//			return;
//		}
//
//	}
//}
//
//void Client::Send_Monster_Bullet_Info()
//{
//	datainfo.infoindex = 'c';
//	datainfo.datasize = 'c';
//	CObj* bullet = Connect_Monster_Bullet();
//	if (bullet == nullptr)
//		return;
//	else
//	{
//
//		datainfo.m_fx = bullet->Get_Info().x;
//		datainfo.m_fy = bullet->Get_Info().y;
//		datainfo.m_fz = bullet->Get_Info().z;
//
//
//
//		// ��ſ� ����ü �۽�
//		retval = send(recv_socket, (char*)&datainfo, sizeof(DataInfo), 0);
//		if (retval == SOCKET_ERROR) {
//			err_display("send()");
//			return;
//		}
//
//	}
//
//
//}



void Client::Close_Connect() {
	// 4. ���� ����
	closesocket(Client::sock);

	// 5. ���� ����
	WSACleanup();
	exit(1);
}