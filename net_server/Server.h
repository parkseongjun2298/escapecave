#pragma once
#include <winsock2.h>
#include "struct.h"
#include "pch.h"
#include "NetShare.h"
#include "Obj.h"


#ifndef __SERVER_H__
#define __SERVER_H__

class Server : public NetShare
{	
	SOCKET client_sock[3];
	void err_quit(const char *msg);
	void err_display(const char *msg);
public:
	template <typename T>
	void Safe_Delete(T& _obj);
	void Update();
	void RunServer();
	void InitServer();
	void Send_Initialize();
	void Close_Connect();
	void Send_ObjectInfo();
};
#endif // !__MAINGAME_H__