#include "pch.h"
#include "Client.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "tmp.h"
#include "MainGame.h"

#pragma comment(lib, "ws2_32.lib")
#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE    5000

SOCKET Client::sock = NULL;

/*void Client::Recv_ObjectInfo() {
	retval = recv(Client::sock, (char*)&datainfo, sizeof(DataInfo), 0);

	if (retval == SOCKET_ERROR)
		err_display("recv()");
	else if (retval == 0)
		return;
	printf("%c", datainfo.datasize);

}*/

glm::vec3 strtovec3(char* sentense) {
	glm::vec3 vector{};
	bool isitx = true;
	char tmp[2] = "";
	char xyz[10] = "";

	for (int i = 0; sentense[i] != '\0'; i++) {
		if (sentense[i] == ' ') {
			//printf("%s || ", xyz);
			if (isitx)
				vector.x = atoi(xyz);
			else
				vector.y = atoi(xyz);
			isitx = !isitx;
			xyz[0] = '\0';
		}
		else {
			tmp[0] = sentense[i];
			strcat(xyz, tmp);
		}
	}
	//printf("%s", xyz);
	vector.z = atoi(xyz);
	return vector;
}
void BuffertoList(char* buffer) {
	for (int i = 0; i < OBJID::END; ++i)
	{
		s_ObjectList[i].clear();
	}
	//printf("%s\n\n\n", buffer);
	char tmp[2] = "";
	char sentense[20] = "";
	int enummm;
	for (int i = 0; buffer[i] != '\0'; i++)
	{
		if (buffer[i] == '\n') {
			if (sentense[2] == '\0') {
				enummm = atoi(sentense);
				//printf("���Ⱑ enum�� �κ�%d",enummm);
			}
			else {
				glm::vec3 vector = strtovec3(sentense);
				s_ObjectList[enummm].push_back(vector);
				//printf("%0.f,%0.f,%0.f", vector.x, vector.y, vector.z);
			}
			//printf("\n");
			sentense[0] = '\0';
			sentense[2] = '\0';
		}
		else
		{
			tmp[0] = buffer[i];
			strcat(sentense, tmp);
		}
	}

	// ������Ʈ ����Ʈ�� ��ǥ�� ����ϴ� ����
	for (int i = OBJID::END; i < OBJID::END; ++i)
	{
		SEND_OBJECT_LIST::iterator iter_begin = s_ObjectList[i].begin();
		SEND_OBJECT_LIST::iterator iter_end = s_ObjectList[i].end();
		//printf("enum:%d\n",i);
		for (; iter_begin != iter_end;)
		{
			//printf("%0.f,%0.f,%0.f\n", (*iter_begin).x, (*iter_begin).y, (*iter_begin).z);
			++iter_begin;
		}
	}
}

// ������ ���� �Լ�
int recvn(SOCKET s, char* buf, int len, int flags)
{
	int received;
	char* ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);
}

DWORD WINAPI Client::Recv_Thread(LPVOID arg) {

	char buffer[BUFSIZE] = "";
	SOCKET client_sock = (SOCKET)arg;
	printf("Therad_initialized\n");
	DataInfo datainfo;
	while (1) {
		datainfo.infoindex = ' ';
		datainfo.datasize = 0;
		// �����ϰ�
		int retval = recv(Client::sock, (char*)&datainfo, sizeof(DataInfo), 0);
		if (retval == SOCKET_ERROR)
			;
			//err_display("recv()");
		else if (retval == 0)
			return 0;
		SEND_OBJECT_LIST::iterator iter_begin;
		switch (datainfo.infoindex) {
		case 'b':
			//Recv_obj_Info();
			retval = recvn(Client::sock, buffer, sizeof(buffer), 0);
			if (retval == SOCKET_ERROR)
				printf("���Ͽ���\n");
			EnterCriticalSection(&cs);
			BuffertoList(buffer);
			LeaveCriticalSection(&cs);
			break;

		case 'd':
			printf("?\n");
			break;

		case 'z':
			/*glColor3f(1.0, 0.0, 0.0);
			glRasterPos2f(0, 0);
			char* string = "ABCDEFGHI";

			while (*string) {
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *string++);
			}*/
			break;
		}
		// �̺�Ʈ true���� ����ϰ�
		//int retval = WaitForSingleObject(hSynchro, INFINITE);
		//if (retval != WAIT_OBJECT_0) exit(1);
		// ������Ʈ ���� �� �ڿ�
		//update();
		//������Ʈ ȭ�鿡 �׸���.
		//SetEvent(client.hSynchro);
	}
	return 0;
};

void Client::err_quit(const char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// ���� �Լ� ���� ���
void Client::err_display(const char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);

	printf("%s\n",msg);
}

void Client::set_datainfo(char a, char b) {
	datainfo.infoindex = a;
	datainfo.datasize = b;
}

void Client::Send_Input(char b) {
	set_datainfo('a', b);
	// ��ſ� ����ü �۽�
	retval = send(Client::sock, (char*)&datainfo, sizeof(DataInfo), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
		return;
	}
}

void Client::InitClient() {
	// 1. ���� �ʱ�ȭ
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		exit(1);

	// 2. ���� ����
	Client::sock = socket(AF_INET, SOCK_STREAM, 0);
	if (Client::sock == INVALID_SOCKET) err_quit("socket()");

	// 3. ������ ����
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(Client::sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");
	// 4. ������ ����
	HANDLE thread = CreateThread(NULL, 0, Recv_Thread,
		(LPVOID)Client::sock, 0, NULL);
	if (thread == NULL) { closesocket(Client::sock); }
	else { CloseHandle(thread); }
}

void Client::Recv_Initialize() {
	// �÷��̾� ��ȣ �Ҵ�޴´�.
	retval = recv(Client::sock, (char*)&datainfo, sizeof(DataInfo), 0);

	if (retval == SOCKET_ERROR)
		err_display("recv()");
	else if (retval == 0)
		return;
	num = datainfo.datasize;
	printf("������Ʈ �ʱ�ȭ ��û ����\n");
}

void Client::Send_GameStart() {
	set_datainfo('a', 'a');
	// ��ſ� ����ü �۽�
	retval = send(Client::sock, (char*)&datainfo, sizeof(DataInfo), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
		return;
	}
	//Recv_Initialize();
}

void Client::Close_Connect() {
	// 4. ���� ����
	closesocket(Client::sock);

	// 5. ���� ����
	WSACleanup();
	exit(1);
}

void Client::Send_Keyin(char* key)
{
	char buffer[10] = "";

	strcpy(buffer, key);
	strcat(buffer, "\0");

	datainfo.infoindex = 'a';
	datainfo.datasize = sizeof(buffer);
	
	// ��ſ� ����ü �۽�
	retval = send(Client::sock, (char*)&datainfo, sizeof(DataInfo), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
		return;
	}
	//Ű �Է� �۽�
	retval = send(Client::sock, buffer, sizeof(buffer), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
		return;
	}

}
