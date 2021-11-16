#pragma once
#include <winsock2.h>
#ifndef __CLIENT_H__
#define __CLIENT_H__
class CObj;
typedef struct DataInfo {
	char infoindex;	// ��Ŷ Ÿ��
	char datasize;	// ��Ŷ ũ��

	float m_fx;
	float m_fy;
	float m_fz;

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
	CObj* Connect_Bullet();
	CObj* Connect_Monster_Bullet();

	void Send_Bullet_Info();
	void Send_Monster_Bullet_Info();
	void Close_Connect();


public:
	typedef list<CObj*>   OBJECT_LIST;
	OBJECT_LIST   m_ObjectList[OBJID::END];
};
#endif // !__MAINGAME_H__