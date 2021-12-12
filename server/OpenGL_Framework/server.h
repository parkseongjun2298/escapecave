#pragma once
#include <winsock2.h>
#ifndef __CLIENT_H__
#define __CLIENT_H__
class CObj;
typedef struct DataInfo {
	char infoindex;	// 패킷 타입
	int datasize;	// 패킷 크기
};

class Server
{
	SOCKET client_sock[3];
	int retval;
	DataInfo datainfo;
	
	SOCKET recv_socket;
	void err_quit(const char *msg);
	void err_display(const char *msg);
	
public:
	void InitServer();
	void Send_GameStart();
	//void Send_GameOver();
	void Send_Object_Info();
	void Close_Connect();


public:
	typedef list<CObj*>   OBJECT_LIST;
	OBJECT_LIST   m_ObjectList[OBJID::END];
};
#endif // !__MAINGAME_H__