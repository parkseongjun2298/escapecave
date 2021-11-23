#define _WINSOCK_DEPRECATED_NO_WARNINGS // �ֽ� VC++ ������ �� ��� ����
#include "pch.h"
#include "Client.h"
#include "RecvThread.h"
#include "tmp.h"

#pragma comment(lib, "ws2_32.lib")
#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE    5000
#include "ObjMgr.h"
#include "Obj.h"


#define PLAYERN 2
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
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);

	printf("\n",msg);
}


void Client::InitClient() {
	// 1. ���� �ʱ�ȭ
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		exit(1);

	// 2. ���� ����
	recv_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (recv_socket == INVALID_SOCKET) err_quit("socket()");

	// ���ε�
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = ::bind(recv_socket, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// 3. Ŭ���̾�Ʈ�� ���� ��û�� ��ٸ�(listen �Լ�)
	retval = listen(recv_socket, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// ��ſ� ����� ���� ����
	SOCKADDR_IN clientaddr;
	int addrlen;
	HANDLE hThread;
	int i = 0;

	printf("��� ��� ��");
	// ������ �� 3�� ����� �����Լ��� ���ư���.
	while (i < PLAYERN) {
		addrlen = sizeof(clientaddr);
		client_sock[i] = accept(recv_socket, (SOCKADDR*)&clientaddr, &addrlen);
		if (client_sock[i] == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}
		printf("\r[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
		// ������ ����
		Thread hThread(client_sock[i++]);
	}
	// �����忡�� ������ ���� ���� ����� �� �ٸ� �����尡 Ŀ�� ��ġ �ٲ��� �ʵ��� ����. �ڵ� ����, ��ȣ ���·� ����
	//hSynchro = CreateEvent(NULL, TRUE, TRUE, NULL);
}

void Client::Send_GameStart() {
	datainfo.infoindex = 'a';
	datainfo.datasize = 'a';

	// ��ſ� ����ü �۽�
	for (int i=0;i< PLAYERN;i++) {
		retval = send(client_sock[i], (char*)&datainfo, sizeof(DataInfo), 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
			return;
		}
	}
}

CObj* Client::Connect_Player()
{
	m_ObjectList[OBJID::PLAYER] = CObjectMgr::Get_Instance()->m_ObjectList[OBJID::PLAYER];
	if (m_ObjectList[OBJID::PLAYER].empty())
		return nullptr;

	return m_ObjectList[OBJID::PLAYER].front();
}

CObj* Client::Connect_Bullet()
{
	m_ObjectList[OBJID::PLAYER_BULLET] = CObjectMgr::Get_Instance()->m_ObjectList[OBJID::PLAYER_BULLET];
	if (m_ObjectList[OBJID::PLAYER_BULLET].empty())
		return nullptr;

	return m_ObjectList[OBJID::PLAYER_BULLET].front();
}

CObj* Client::Connect_Monster_Bullet()
{
	m_ObjectList[OBJID::MONSTER_BULLET] = CObjectMgr::Get_Instance()->m_ObjectList[OBJID::MONSTER_BULLET];
	if (m_ObjectList[OBJID::MONSTER_BULLET].empty())
		return nullptr;

	return m_ObjectList[OBJID::MONSTER_BULLET].front();
}

void Client::Send_Bullet_Info() {
	datainfo.infoindex = 'b';
	datainfo.datasize = 'b';
	CObj* bullet = Connect_Bullet();
	if (bullet == nullptr)
		return;
	else
	{

		datainfo.m_fx = bullet->Get_Info().x;
		datainfo.m_fy = bullet->Get_Info().y;
		datainfo.m_fz = bullet->Get_Info().z;



		for (int i = 0;i < PLAYERN;i++) {
			retval = send(client_sock[i], (char*)&datainfo, sizeof(DataInfo), 0);
			if (retval == SOCKET_ERROR) {
				err_display("send()");
				return;
			}
		}

	}
}

void Client::Send_Monster_Bullet_Info()
{
	datainfo.infoindex = 'c';
	datainfo.datasize = 'c';
	CObj* bullet = Connect_Monster_Bullet();
	if (bullet == nullptr)
		return;
	else
	{

		datainfo.m_fx = bullet->Get_Info().x;
		datainfo.m_fy = bullet->Get_Info().y;
		datainfo.m_fz = bullet->Get_Info().z;



		// ��ſ� ����ü �۽�
		for (int i = 0;i < PLAYERN;i++) {
			retval = send(client_sock[i], (char*)&datainfo, sizeof(DataInfo), 0);
			if (retval == SOCKET_ERROR) {
				err_display("send()");
				return;
			}
		}

	}


}

void Client::Send_Player_Info()
{
	datainfo.infoindex = 'd';
	datainfo.datasize = 'd';
	CObj* player = Connect_Player();
	if (player == nullptr)
		return;
	else
	{

		datainfo.m_fx = player->Get_Info().x;
		datainfo.m_fy = player->Get_Info().y;
		datainfo.m_fz = player->Get_Info().z;



		// ��ſ� ����ü �۽�
		for (int i = 0;i < PLAYERN;i++) {
			retval = send(client_sock[i], (char*)&datainfo, sizeof(DataInfo), 0);
			if (retval == SOCKET_ERROR) {
				err_display("send()");
				return;
			}
		}

	}


}

void Client::Send_Object_Info()
{
	char buffer[BUFSIZE] = "";
	char tmp[10];
	//0. ��� ������Ʈ���� ��ǥ��vec3�� �����Ͽ� s_ObjectList����Ʈ�� �����ߴ�
	//1. ��µ� �ȴ�.
	//2. ���ۿ� ��ǥ���� �����Ѵ�.(���ڿ��� �ȴ�.)
	//�ϳ��ϳ� ������ buffer���ۿ��ٰ� ���ڿ��� ������ ��
	for (int i = 0; i < OBJID::END; ++i)
	{
		printf("%d\n", i);
		sprintf(tmp, "%d\n", i);
		strcat(buffer, tmp);
		SEND_OBJECT_LIST::iterator iter_begin = s_ObjectList[i].begin();
		SEND_OBJECT_LIST::iterator iter_end = s_ObjectList[i].end();

		for (; iter_begin != iter_end;)
		{
			sprintf(tmp, "%d ", int((*iter_begin).x));
			strcat(buffer, tmp);
			sprintf(tmp, "%d ", int((*iter_begin).y));
			strcat(buffer, tmp);
			sprintf(tmp, "%d\n", int((*iter_begin).z));
			strcat(buffer, tmp);
			printf("%0.f | %0.f | %0.f\n", (*iter_begin).x, (*iter_begin).y, (*iter_begin).z);
			++iter_begin;
		}

		s_ObjectList[i].clear();
	}
	strcat(buffer, "\0");

	//3. ���۸� �������̷� �۽��Ѵ�.
	datainfo.infoindex = 'b';
	datainfo.datasize = sizeof(buffer);
	printf("%d", datainfo.datasize);

	for (int i = 0;i < PLAYERN;i++) {
		// ��ſ� ����ü �۽�
		retval = send(client_sock[i], (char*)&datainfo, sizeof(DataInfo), 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
			return;
		}
		//���� ��ǥ�� �۽�
		retval = send(client_sock[i], buffer, sizeof(buffer), 0);
		printf("��ǥ�����ۼ۽�\n", sizeof(s_ObjectList));
		if (retval == SOCKET_ERROR) {
			err_display("send()");
			return;
		}
	}
}

void Client::Close_Connect() {
	// 4. ���� ����
	closesocket(recv_socket);

	// 5. ���� ����
	WSACleanup();
	exit(1);
}