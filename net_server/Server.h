#pragma once
#include <winsock2.h>
#ifndef __SERVER_H__
#define __SERVER_H__

typedef struct DataInfo {
	char infoindex;	// ��Ŷ Ÿ��
	char datasize;	// ��Ŷ ũ��
};


class Server
{	

	int startnum = 0;
	SOCKET client_sock[3];
	HANDLE hCursorEvent;
	int retval;
	DataInfo datainfo;
	SOCKET listen_sock;
	void Recv_GameStart();
	void err_quit(const char *msg);
	void err_display(const char *msg);
public:
	void RunServer();
	void InitServer();
	void Send_GameStart();
	void Send_Initialize();
	void Close_Connect();
};
#endif // !__MAINGAME_H__