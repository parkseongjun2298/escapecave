#pragma once
#include <winsock2.h>
#include "struct.h"
#include "enum.h"
#include "Obj.h"
typedef list<Obj*> OBJECT_LIST;
using namespace std;

class NetShare
{
protected:
	int retval;
public:

	static OBJECT_LIST m_ObjectList[OBJID::END];
	static int thread_num;
	int num;
	HANDLE hCursorEvent;
	DataInfo datainfo;
	SOCKET sock;
};