#define _WINSOCK_DEPRECATED_NO_WARNINGS // 최신 VC++ 컴파일 시 경고 방지
#include "pch.h"
#include "Server.h"
#include "RecvThread.h"

#pragma comment(lib, "ws2_32.lib")
#define SERVERPORT 9000
#define BUFSIZE    4096
void Server::err_quit(const char *msg)
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

// 소켓 함수 오류 출력
void Server::err_display(const char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);

	printf("\n", msg);
}

void Server::Send_Initialize() {
	datainfo.infoindex = 'a';
	datainfo.datasize = 'a';

	// 통신용 구조체 송신
	for (int i = 0;i < 3;i++) {
		retval = send(client_sock[i], (char*)&datainfo, sizeof(DataInfo), 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
			return;
		}
	}

	printf("오브젝트 초기화 요청 송신\n");
}

void Server::RunServer() {
	Send_Initialize();
	printf("게임시작");
	return;
};

void Server::InitServer() {
	// 1. 윈속 초기화
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		exit(1);

	// 2. 소켓 생성
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// 바인딩
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// 3. 클라이언트의 접속 요청을 기다림(listen 함수)
	retval = listen(sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// 통신에 사용할 변수 선언
	SOCKADDR_IN clientaddr;
	int addrlen;
	HANDLE hThread;
	int i = 0;
	// 스레드에서 데이터 수신 비율 출력할 때 다른 스레드가 커서 위치 바꾸지 않도록 제어. 자동 리셋, 신호 상태로 시작
	hCursorEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
	printf("통신 대기 중");
	// 스레드 총 3개 만들면 메인함수로 돌아간다.
	while (i<3) {
		if (hCursorEvent == NULL) break;
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock[i] = accept(sock, (SOCKADDR*)&clientaddr, &addrlen);
		if (client_sock[i] == INVALID_SOCKET) {
			err_display("accept()");
			SetEvent(hCursorEvent);
			break;
		}
		printf("\r[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
		SetEvent(hCursorEvent);
		// 스레드 생성
		hThread = CreateThread(NULL, 0, Recv_Thread,
			(LPVOID)client_sock[i++], 0, NULL);
		if (hThread == NULL) { closesocket(client_sock[--i]); }
		else { CloseHandle(hThread); }
		printf("%d\n", i);
	}
}

void Server::Close_Connect() {
	CloseHandle(hCursorEvent);
	// 4. 소켓 닫음
	closesocket(sock);

	// 5. 윈속 종료
	WSACleanup();
	exit(1);
}