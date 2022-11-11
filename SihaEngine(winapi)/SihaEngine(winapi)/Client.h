#pragma once

#include "common.h"
#define SERVERPORT 9000

class Client {
public:
	WSADATA wsa;
	SOCKET sock;
	struct sockaddr_in serveraddr;

	UserInfo csPlayerInfo;

	char* SERVERIP = (char*)"127.0.0.1";

	int ConnectedPlayerNum = 0;
	int ClinetId = 0;

public:
	Client();
	~Client();

	void CSConnect();
	void CSSend();
	void err_quit(const char* msg);
	void err_display(const char* msg);
	void err_display(int errcode);
};

DWORD WINAPI RecvThread(LPVOID arg);