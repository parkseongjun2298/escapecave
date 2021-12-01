#pragma once
#include <winsock2.h>
#include "NetObj.h"
#ifndef __CLIENT_H__
#define __CLIENT_H__

//typedef list<Obj*> OBJECT_LIST;

class CObj;

typedef struct DataInfo {
	char infoindex;	// 패킷 타입
	int datasize;	// 패킷 크기
};

class Client
{

	int retval;
	DataInfo datainfo;

	static SOCKET sock;
	void err_quit(const char *msg);
	void err_display(const char *msg);
	//void Recv_ObjectInfo();
	static DWORD WINAPI Recv_Thread(LPVOID arg);

public:
	void set_datainfo(char a, char b);
	void Send_Input(char b);
	void InitClient();
	void Send_GameStart();
	void Recv_Initialize();
	void Close_Connect();

	typedef list<CObj*>   OBJECT_LIST;
	OBJECT_LIST   m_ObjectList[OBJID::END];
	int num;
};
#endif // !__MAINGAME_H__