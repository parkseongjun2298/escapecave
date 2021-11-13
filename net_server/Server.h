#pragma once
#include <winsock2.h>
#include "struct.h"
#ifndef __SERVER_H__
#define __SERVER_H__



class Server
{	
	SOCKET client_sock[3];
	int retval;
	void err_quit(const char *msg);
	void err_display(const char *msg);
public:
	DataInfo datainfo;
	SOCKET sock;
	void RunServer();
	void InitServer();
	void Send_Initialize();
	void Close_Connect();
};
#endif // !__MAINGAME_H__