#pragma once

#include <winsock2.h> // ����2 ���� ���
#include <ws2tcpip.h> // ����2 Ȯ�� ���

#pragma comment(lib, "ws2_32") // ws2_32.lib ��ũ

struct UserInfo {
	int DataType;
	int Frame;
	int ID;
	int PVPID;
	int maxhp;
	int maxmp;
	int power;
	int nowhp;
	int nowmp;
	int x;
	int y;
	int state;
	bool isPvP;
	bool isSmash;
	int ClientTime;
	int ServerTime;
	int OtherRTT;
	int dir;
};

struct SocketInfo {
	SOCKET client_sock;
	int ID;
	HANDLE writeEvent;
	HANDLE sendEvent;
	
};