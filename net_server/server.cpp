#define _WINSOCK_DEPRECATED_NO_WARNINGS // 최신 VC++ 컴파일 시 경고 방지
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#define SERVERPORT 9000
#define BUFSIZE    4096

void err_quit(char* msg);
void err_display(const char* msg);

typedef struct DataInfo {
	char infoindex;	// 패킷 타입
	char datasize;	// 패킷 크기
};

//  cmd창 num번째 줄에 문자열 출력
int num = 0;
int startnum = 0;
// 문자열 출력할 때 다른 스레드가 커서 위치 바꾸지 않도록 제어
HANDLE hCursorEvent;

// 소켓 함수 오류 출력 후 종료
void err_quit(char* msg)
{
	LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, WSAGetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf, 0, NULL);
   // MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
    LocalFree(lpMsgBuf);
    exit(1);
}

// 소켓 함수 오류 출력
void err_display(const char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

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
	WaitForSingleObject(hCursorEvent, INFINITE);
	// 표준콘솔출력의 핸들 반환 -> pos가 가리키는 좌표로 캐럿을 이동시킨다.
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void RunServer() {
	printf("게임시작");
	return;
};

void Recv_GameStart() {
	startnum++;
	printf("게임시작요청 %d인", startnum);
	if (startnum == 3)
		RunServer();
}

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
			*/
		// 수신받은 데이터의 비율 출력 (캐럿을 줄의 맨 앞으로 보내 Scroll Up 방지)
		current_received_size += retval;
		SetEvent(hCursorEvent);

	}

	// closesocket()
	closesocket(client_sock);
	SetEvent(hCursorEvent);
	return 0;
}

void InitServer() {

}
int main(int argc, char *argv[])
{
	int retval;

	// 1. 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 2. 소켓 생성
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit((char*)"socket()");

	// 바인딩
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit((char*)"bind()");

	// 3. 클라이언트의 접속 요청을 기다림(listen 함수)
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit((char*)"listen()");

	// 통신에 사용할 변수 선언
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	HANDLE hThread;

	// 스레드에서 데이터 수신 비율 출력할 때 다른 스레드가 커서 위치 바꾸지 않도록 제어. 자동 리셋, 신호 상태로 시작
	hCursorEvent = CreateEvent(NULL, FALSE, TRUE, NULL);

	printf("통신 대기 중");
	while (1) {
		if (hCursorEvent == NULL) break;
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
		COORD pos = { 0,num++ };
		if (client_sock == INVALID_SOCKET) {
			set_cursor(pos);
			err_display("accept()");
			SetEvent(hCursorEvent);
			break;
		}

		// 접속한 클라이언트 정보 출력
		set_cursor(pos);
		printf("\r[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
		SetEvent(hCursorEvent);

		// 스레드 생성
		hThread = CreateThread(NULL, 0, Recv_Thread,
			(LPVOID)client_sock, 0, NULL);
		if (hThread == NULL) { closesocket(client_sock); }
		else { CloseHandle(hThread); }

	}
	CloseHandle(hCursorEvent);
	// 4. 소켓 닫음
	closesocket(listen_sock);

	// 5. 윈속 종료
	WSACleanup();
	return 0;
}
