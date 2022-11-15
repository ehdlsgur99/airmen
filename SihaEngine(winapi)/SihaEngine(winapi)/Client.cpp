//#include "common.h"
//
//Client::CSClient()
//{
//	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) err_quit("WSA()");
//
//	sock = socket(AF_INET, SOCK_STREAM, 0);
//	if (sock == INVALID_SOCKET) err_quit("socket()");
//
//
//	/*csPlayerInfo.Frame = 0;
//	csPlayerInfo.ID = 0;
//	csPlayerInfo.maxhp = 0;
//	csPlayerInfo.maxmp = 0;
//	csPlayerInfo.power = 0;
//	csPlayerInfo.nowhp = 0;
//	csPlayerInfo.nowmp = 0;
//	csPlayerInfo.x = 0;
//	csPlayerInfo.y = 0;
//	csPlayerInfo.state = 0;
//	csPlayerInfo.isPvP = 0;
//	csPlayerInfo.ClientTime = 0;*/
//
//}
//
//Client::~CSClient()
//{
//	closesocket(sock);
//
//	WSACleanup();
//}
//
//void Client::CSConnect()
//{
//	int retval;
//	memset(&serveraddr, 0, sizeof(serveraddr));
//	serveraddr.sin_family = AF_INET;
//	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
//	serveraddr.sin_port = htons(SERVERPORT);
//	retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
//	if (retval == SOCKET_ERROR) err_quit("connect()");
//
//	//connect성공시 고유의 id값을 받는다.
//	retval = recv(sock, (char*)&ClinetId, sizeof(int), MSG_WAITALL);
//	if (retval == SOCKET_ERROR) err_display("send()");
//	csPlayerInfo.ID = ClinetId;
//
//	HANDLE hThread = CreateThread(NULL, 0, RecvThread, (LPVOID)this, 0, NULL);
//	CloseHandle(hThread);
//}
//
//void Client::CSSend()
//{
//	int retval;
//	retval = send(sock, (char*)&csPlayerInfo, sizeof(csPlayerInfo), 0);
//	if (retval == SOCKET_ERROR) err_display("send()");
//}
//
//void Client::err_quit(const char* msg)
//{
//	LPVOID lpMsgBuf;
//	FormatMessageA(
//		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
//		NULL, WSAGetLastError(),
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//		(char*)&lpMsgBuf, 0, NULL);
//	MessageBoxA(NULL, (const char*)lpMsgBuf, msg, MB_ICONERROR);
//	LocalFree(lpMsgBuf);
//	exit(1);
//}
//
//void Client::err_display(const char* msg)
//{
//	LPVOID lpMsgBuf;
//	FormatMessageA(
//		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
//		NULL, WSAGetLastError(),
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//		(char*)&lpMsgBuf, 0, NULL);
//	printf("[%s] %s\n", msg, (char*)lpMsgBuf);
//	LocalFree(lpMsgBuf);
//}
//
//void Client::err_display(int errcode)
//{
//	LPVOID lpMsgBuf;
//	FormatMessageA(
//		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
//		NULL, errcode,
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//		(char*)&lpMsgBuf, 0, NULL);
//	printf("[오류] %s\n", (char*)lpMsgBuf);
//	LocalFree(lpMsgBuf);
//}
//
//void gotoxy(int x, int y)
//{
//	COORD Cur;
//	Cur.X = x;
//	Cur.Y = y;
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
//}
//
//DWORD WINAPI RecvThread(LPVOID arg)
//{
//	UserInfo info[5];
//	
//	Client* pClient = (Client*)arg;
//	SOCKET sock = pClient->sock;
//	int retval, ConnectedNum;
//	char buf[512];
//
//	while (1) {
//	}
//	return 0;
//}