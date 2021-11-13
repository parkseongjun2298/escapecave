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
	static SOCKET sock;
	void err_quit(const char *msg);
	void err_display(const char *msg);
public:
	void set_datainfo(char a, char b);
	void Send_Input(char b);
	void InitClient();
	void Send_GameStart();
	void Recv_Initialize();
	void Close_Connect();
};
#endif // !__MAINGAME_H__