#include "pch.h"
#include "RecvThread.h"
#include "Server.h"
#include "StaticList.h"
#include "Function.h"
#include "Player.h"

int Thread::thread_num = 0;


void Thread::Update_PlayerInfo() {



}


void Thread::Recv_Input() {
	OBJECT_LIST::iterator iter_begin = m_ObjectList[OBJID::PLAYER].begin();
	OBJECT_LIST::iterator iter_end = m_ObjectList[OBJID::PLAYER].end();
	for (int i = 0; i < num;i++)
		++iter_begin;;
	(*iter_begin)->key = datainfo.datasize;
	printf("%c", (*iter_begin)->key);
}

DWORD WINAPI Recv_Thread(LPVOID arg) {
	Player* pObject = new Player();
	Thread::m_ObjectList[OBJID::PLAYER].push_back(pObject);

	Thread thread;
	thread.sock = (SOCKET)arg;
	thread.num = Thread::thread_num++;

	printf("Therad_initialized\n");
	while (true) {
		int retval = recv(thread.sock, (char*)&thread.datainfo, sizeof(DataInfo), 0);
		if (retval == SOCKET_ERROR)
			break;
			//err_display("recv()");
		else if (retval == 0)
			break;
		switch (thread.datainfo.infoindex) {
		case 'a':
			thread.Recv_Input();
			break;
		}
	}
	return 0;
};