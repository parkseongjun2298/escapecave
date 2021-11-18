
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include "Server.h"
#include "Function.h"

// 데이터 수신 함수
int recvn(SOCKET s, char *buf, int len, int flags)
{
	int received;
	char *ptr = buf;
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

// 스레드끼리 커서 위치 간섭하지 못하도록 문자열 출력 끝날 때까지 대기하는 함수
void set_cursor(COORD pos) {
	//WaitForSingleObject(hCursorEvent, INFINITE);
	// 표준콘솔출력의 핸들 반환 -> pos가 가리키는 좌표로 캐럿을 이동시킨다.
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



/*
// 스레드. 클라이언트와 데이터 통신
DWORD WINAPI Recv_Thread(LPVOID arg)
{
	SOCKET client_sock = (SOCKET)arg;
	int retval;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE + 1];

	// cmd창 number번째 줄에 전송률 풀력
	int number = num++;
	COORD pos = { 0,number };
	DataInfo datainfo;
	int current_received_size = 0;

	// 클라이언트 정보 얻기
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);

	while (1) {
		// 데이터 받기(고정 길이)
		retval = recvn(client_sock, (char*)&datainfo, sizeof(DataInfo), 0);
		if (retval == SOCKET_ERROR) {
			set_cursor(pos);
			err_display("recv()");
			break;
		}
		else if (retval == 0) {
			break;
		}
		switch (datainfo.infoindex) {
		case 'a':
			Recv_GameStart();
			break;
		}
		/*
		// 데이터 받기(가변 길이)
		retval = recvn(client_sock, buf, datainfo.infoindex, 0);
		if (retval == SOCKET_ERROR) {
			set_cursor(pos);
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;
		// 수신받은 데이터의 비율 출력 (캐럿을 줄의 맨 앞으로 보내 Scroll Up 방지)
		current_received_size += retval;
		SetEvent(hCursorEvent);

	}

	// closesocket()
	closesocket(client_sock);
	SetEvent(hCursorEvent);
	return 0;
}
*/
int main(int argc, char *argv[])
{
	Server server;
	//클라이언트 3명 연결 될 때까지 대기 -> 스레드 3개 생성되면 함수 종료됨
	server.InitServer();
	// 클라이언트 3명에게 오브젝트 초기화 요청 송신
	server.RunServer();
	printf("끝");
	while (1) {
		server.Update();
		server.Send_ObjectInfo();
	}
	server.Close_Connect();
	return 0;
}
