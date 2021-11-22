#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include "pch.h"
#include "Server.h"
#include "RecvThread.h"
#include "struct.h"
#include "PlayerBullet.h"
#include "enum.h"
#include"CollisionMgr.h"

using namespace std;
#pragma comment(lib, "ws2_32.lib")
#define SERVERPORT 9000
#define BUFSIZE    4096

template <typename T>
void Server::Safe_Delete(T& _obj) {
	delete _obj;
	_obj = nullptr;
}

void Server::err_quit(const char* msg)
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


void Server::err_display(const char* msg)
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

void Server::Send_Initialize() {
	datainfo.infoindex = 'a';
	datainfo.datasize = 'a';

	
	for (int i = 0; i < 3; i++) {
		retval = send(client_sock[i], (char*)&datainfo, sizeof(DataInfo), 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
			return;
		}
	}

	printf("보냄\n");
}

void Server::RunServer() {
	Send_Initialize();

	printf("런서버");
	return;
};

void Server::InitServer() {
	
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		exit(1);

	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	
	retval = listen(sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	
	SOCKADDR_IN clientaddr;
	int addrlen;
	HANDLE hThread;
	int i = 0;

	printf("서버연결");
	
	while (i < 3) {
		addrlen = sizeof(clientaddr);
		client_sock[i] = accept(sock, (SOCKADDR*)&clientaddr, &addrlen);
		if (client_sock[i] == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
		hThread = CreateThread(NULL, 0, Recv_Thread,
			(LPVOID)client_sock[i++], 0, NULL);
		if (hThread == NULL) { closesocket(client_sock[--i]); }
		else { CloseHandle(hThread); }
		printf("%d\n", i);
	}
	
	hSynchro = CreateEvent(NULL, TRUE, TRUE, NULL);
}

void Server::Update()
{
	
	ResetEvent(hSynchro);
	OBJECT_LIST::iterator iter_begin = m_ObjectList[OBJID::PLAYER].begin();
	OBJECT_LIST::iterator iter_end = m_ObjectList[OBJID::PLAYER].end();
	for (int i = 0; i < OBJID::END; ++i)
	{	
		OBJECT_LIST::iterator iter_begin = m_ObjectList[i].begin();
		OBJECT_LIST::iterator iter_end = m_ObjectList[i].end();

		for (; iter_begin != iter_end;)
		{
			//Update() 
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
	CollisionMgr *ColMgr=new CollisionMgr;
	ColMgr->Collision_BulletToMonster(m_ObjectList[OBJID::PLAYER_BULLET], m_ObjectList[OBJID::MONSTER]);
	ColMgr->Collision_BulletToPlayer(m_ObjectList[OBJID::MONSTER_BULLET], m_ObjectList[OBJID::PLAYER]);
	ColMgr->Collision_BulletToBullet(m_ObjectList[OBJID::MONSTER_BULLET], m_ObjectList[OBJID::PLAYER_BULLET]);
	ColMgr->Collision_BossToPlayerBullet(m_ObjectList[OBJID::BOSS], m_ObjectList[OBJID::PLAYER_BULLET]);
	SetEvent(hSynchro);
}

void Server::Send_ObjectInfo() {
	datainfo.infoindex = 'b';
	
	//총알정보를 보내야함

	for (int i = 0; i < 10; i++)
		printf("%d", m_ObjectList[i].size());
	datainfo.datasize = sizeof(m_ObjectList[0].size());

	
	for (int i = 0; i < 3; i++) {
		retval = send(client_sock[i], (char*)&datainfo, sizeof(DataInfo), 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
			return;
		}
	}

	//printf("%d : %d",(int)datainfo.datasize, sizeof(OBJECT_LIST));
	
	for (int i = 0; i < 0; i++) {
		retval = send(client_sock[i], (char*)&datainfo, (int)datainfo.datasize, 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
			return;
		}

	}
	printf("Send_ObjectInfo\n");
}

void Server::Close_Connect() {
	CloseHandle(hSynchro);
	
	closesocket(sock);

	
	WSACleanup();
	exit(1);
}