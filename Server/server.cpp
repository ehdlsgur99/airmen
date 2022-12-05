#include "common.h"
#include <list>

#include "UserInfo.h"
#include "EnumData.h"
// UserInfo ���� List
std::list<UserInfo*> userList;
// Socket ���� List
std::list<SocketInfo> socketList;
// ���� ������ ������ id�ѹ��� ���� id�Ҵ翡 ���̴� ��������
int IDCount;
// �ٸ� Ŭ���̾�Ʈ�� Userlist �� �����ϰ� �ִ��� Ȯ���ϴ� bool ���� 
bool isUsing;

#define SERVERPORT 9000
#define BUFSIZE    512
#define MAX_THREADS	100
int threadCount = 0;

bool isFlag = true;

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// ���� �ʱ�ȭ, ���� ���� �� Bind, Listen, Accept �õ�
int InitServer()
{
	return false;
}

// ������ ���� ��û�� �޾� ������ ������ ������ 1���� �Ҵ��ϰ� �������θ� ��ȯ�Ѵ�.
bool AddUser()
{
	return false;
}

// Ŭ���̾�Ʈ���� ���� ���� ��û�� ���� ��� 
// ���� ������ ����� UserList ���� Ŭ���̾�Ʈ�� �����ϰ� �������θ� ��ȯ�Ѵ�.
bool SendUserInfo(SOCKET client_sock)
{
	return false;
}


// Ŭ���̾�Ʈ���� PvP�� ��û�� ������ ���� UserInfo.id(enemyID) �� ���� ��
// UserList�� socketList ���� �ش� id�� ã�� ����(enum ������ �ĺ� ��) + ����(PvP�� ��û�� ���� ����)�� �����Ѵ�. 
// �������θ� ��ȯ�Ѵ�.
bool SendPvPMessage(SOCKET client_sock, int enemyID)
{
	return false;
}

/*
	PvP�� �³��� Ŭ���̾�Ʈ�� ���� �³� ���ο� ��� ID�� �Ѱ� ���� �� 
	���� id(myID)�� UserList�� �ִ� userInfo.isPvP���� true�� �����Ѵ�. 
	client_sock�� ����(enum ������ �ĺ� ��) + ����(bool �³�) ������ ����
	enemyID�� ������� �ش��ϴ� socket�� ������ ����(enum ������ �ĺ� ��) + ����(bool �³�) ������ ����, 
	enemyID�� UserList�� �ִ� userinfo.isPvP �� true�� ����
*/
bool GotoPVP(SOCKET client_sock, int myID, bool isYes, int enemyID)
{
	return false;
}

/*
	������ UserInfo ���� �޾ƿ� UserList���� �ش� id�� UserInfo ���� �ʱ�ȭ ��Ų��. 
	client_sock���� ProcessClient �������� ���������� enemyID(��� id)�� �޾ƿ� UserList���� �ش� id�� UserInfo ���� �����Ѵ�. 
	���޹��� UserInfo.isPvP���� false�� ��� pvp�� ����� ������ �Ǵ��Ѵ�.
*/
bool ExchangeUserInfo(SOCKET client_sock, UserInfo myInfo, int enemyID)
{
	return false;
}

// Ŭ���̾�Ʈ�� ������ ���
DWORD WINAPI ProcessClient(LPVOID arg)
{
	int retval;
	SOCKET client_sock = (SOCKET)arg;
	struct sockaddr_in clientaddr;
	char addr[INET_ADDRSTRLEN];
	int addrlen;
	char buf[BUFSIZE + 1];


	int threadID = threadCount;
	printf("%d", threadID);

	// Ŭ���̾�Ʈ ���� ���
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (struct sockaddr*)&clientaddr, &addrlen);
	inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));

	int len; 

	// UserList�� ���� ���� UserInfo  �߰�
	UserInfo *userInfo = new UserInfo;
	userInfo->DataType = eDataType::eNone;
	userInfo->ID = threadID;
	userInfo->isPvP = false;
	userInfo->maxhp = 100;
	userInfo->nowhp = 100;
	userInfo->maxmp = 500;
	userInfo->nowmp = 500;
	userInfo->x = 0;
	userInfo->y = 0;
	userInfo->PVPID = -1;
	userInfo->state = 0;
	userInfo->ClientTime = 0;
	userInfo->ServerTime = 0;
	userInfo->OtherRTT = 0;
	userInfo->power = 100;
	userInfo->Frame = 0;


	userList.push_back(userInfo);

	// SocketList�� ���� ���� SocketInfo �߰�
	SocketInfo socketInfo;
	socketInfo.client_sock = client_sock;
	socketInfo.ID = userInfo->ID;

	socketList.push_back(socketInfo);

	// Ŭ���̾�Ʈ�� ������ ���
	// UserInfo ������ ������
	retval = send(client_sock, (const char*)userInfo, sizeof(UserInfo), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
	}
	eDataType dataType;
	while(1) {

		std::list<UserInfo*>::iterator iter;

		// EnumData �ޱ�
		//retval = recv(client_sock, (char*)&dataType, sizeof(dataType), MSG_WAITALL);
		//if (retval == SOCKET_ERROR) {
		//	err_display("recv()");
		//	break;
		//}
		//else if (retval == 0 )
		//	break;
		
		// ��Ŷ �ޱ�
		UserInfo* packet = new UserInfo;
		char buf[BUFSIZE];

		retval = recv(client_sock, buf, sizeof(UserInfo), 0);
		packet = (UserInfo*)buf;

		// DataType �� ���� ���� ����
		
		int userNum = userList.size();
		// �÷��̾� �������� UserInfo�� �߼��Ѵ�.
		if (eDataType::eNone == packet->DataType)
		{
	/*		UserInfo* temp = new UserInfo;
			char buf[BUFSIZE];*/
			//retval = recv(client_sock, buf, sizeof(UserInfo), 0);
			//temp = (UserInfo*)buf;
			for (iter = userList.begin(); iter != userList.end(); iter++)
			{
				if ((*iter)->ID == socketInfo.ID)
				{
					(*iter) = packet;
				}
				
			}
			// PVP ��Ȳ�ΰ�� ���⼭ ���� ������ �����ش�.
		}
		// �÷��̾� �������� �Ѱ��ش�.
		if (eDataType::eRequest == packet->DataType)
		{
			// ���� �ο� ����
			retval = send(client_sock, (char*)&userNum, sizeof(userNum), 0);

			UserInfo *sendTemp = new UserInfo;
			for (iter = userList.begin(); iter != userList.end(); iter++)
			{
				sendTemp = *iter;
				retval = send(client_sock, (char*)sendTemp, sizeof(UserInfo), 0);
			}
		}
		if (eDataType::eInviteSend == packet->DataType)
		{
			// ���������� ���� ���¸� ������ ������
			std::list<UserInfo*>::iterator iter = userList.begin();
			for (iter = userList.begin(); iter != userList.end(); iter++)
			{
				if ((*iter)->ID == packet->PVPID)
				{
					(*iter)->DataType = eInviteRecv;
					(*iter)->PVPID = threadID;
				}
			}
		}
		if (eDataType::eInviteRecv == packet->DataType)
		{
			// ���������� ���� ���¸� ������ ������
			std::list<UserInfo*>::iterator iter = userList.begin();
			for (iter = userList.begin(); iter != userList.end(); iter++)
			{
				if ((*iter)->ID == packet->PVPID)
				{
					(*iter)->DataType = eInviteRecv;
					(*iter)->PVPID = threadID;
				}
			}
		}
		// �����尡 ������ �ִ� ���� �����Ϳ� ��ü userinfo�� �����ش�.
		iter = userList.begin();
		for (iter = userList.begin(); iter != userList.end(); iter++)
		{
			if ((*iter)->ID == threadID)
			{
				userInfo = (*iter);
				break;
			}
		}
		retval = send(client_sock, (const char*)userInfo, sizeof(UserInfo), 0);
	
	}


	// ���� �ݱ�
	closesocket(client_sock);
	printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
		addr, ntohs(clientaddr.sin_port));
	return 0;
}

int main(int argc, char* argv[])
{
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// ���� ����
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) 
		err_quit("socket()");

	// bind()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) 
		err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) 
		err_quit("listen()");

	// ������ ��ſ� ����� ����
	SOCKET client_sock;
	struct sockaddr_in clientaddr;
	int addrlen;
	HANDLE hThread[MAX_THREADS];

	printf("���� �������� ���� ��: %d ", threadCount);
	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (struct sockaddr*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}

		// ������ Ŭ���̾�Ʈ ���� ���
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			addr, ntohs(clientaddr.sin_port));

		// ������ ����
		hThread[threadCount] = CreateThread(NULL, 0, ProcessClient,
			(LPVOID)client_sock, 0, NULL);
		if (hThread[threadCount] == NULL) { closesocket(client_sock); }
		else { CloseHandle(hThread[threadCount]); }
		threadCount++;

		printf("\n���� �������� ���� ��: %d ", threadCount);

	}

	// ���� �ݱ�
	closesocket(listen_sock);

	// ���� ����
	WSACleanup();
	return 0;
}
