#pragma once
#include <winsock2.h>
#ifndef __CLIENT_H__
#define __CLIENT_H__

typedef struct DataInfo {
	char infoindex;	// ��Ŷ Ÿ��
	char datasize;	// ��Ŷ ũ��
};


class Client
{
	int retval;
	DataInfo datainfo;
	SOCKET recv_socket;
	void err_quit(const char *msg);
	void err_display(const char *msg);
public:
	void InitClient();
	void Send_GameStart();
	void Close_Connect();
};
#endif // !__MAINGAME_H__