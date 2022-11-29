#pragma once

#include <winsock2.h> // 윈속2 메인 헤더
#include <ws2tcpip.h> // 윈속2 확장 헤더

#pragma comment(lib, "ws2_32") // ws2_32.lib 링크

struct UserInfo {
	int DataType;
	int Frame;
	int ID;
	int maxhp;
	int maxmp;
	int power;
	int nowhp;
	int nowmp;
	int x;
	int y;
	int state;
	bool isPvP;
	int ClientTime;
	int ServerTime;
	int OtherRTT;
};

struct SocketInfo {
	SOCKET client_sock;
	int ID;
};