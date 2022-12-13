#include "common.h"
#include <list>
#include <time.h>
#include <vector>

#include "UserInfo.h"
#include "EnumData.h"
// UserInfo ���� List
std::list<UserInfo*> userList;
// Socket ���� List
std::vector<SocketInfo> socketList;
// ���� ������ ������ id�ѹ��� ���� id�Ҵ翡 ���̴� ��������
int IDCount;
// �ٸ� Ŭ���̾�Ʈ�� Userlist �� �����ϰ� �ִ��� Ȯ���ϴ� bool ���� 
bool isUsing;

#define SERVERPORT 9000
#define BUFSIZE    512
#define MAX_THREADS	100
int threadCount = 0;

bool isFlag = true;

// ���� �ð�
clock_t serverTime;

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

// �ð� ������
DWORD WINAPI Timer(LPVOID arg)
{
	while (1)
	{
		serverTime = clock();
	}

	return 0;
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
	//printf("%d", threadID);

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
	userInfo->isSmash = false;
	userInfo->maxhp = 100;
	userInfo->nowhp = 100;
	userInfo->maxmp = 500;
	userInfo->nowmp = 500;
	userInfo->x = 0;
	userInfo->y = 0;
	userInfo->PVPID = -1;
	userInfo->state = 0;
	userInfo->ClientTime = (int)serverTime;
	userInfo->ServerTime = (int)serverTime;
	userInfo->OtherRTT = 0;
	userInfo->power = 100;
	userInfo->Frame = 0;
	userInfo->dir = 0;


	userList.push_back(userInfo);

	// SocketList�� ���� ���� SocketInfo �߰�
	SocketInfo socketInfo;
	socketInfo.client_sock = client_sock;
	socketInfo.writeEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	socketInfo.sendEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
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
			for (iter = userList.begin(); iter != userList.end(); iter++)
			{
				if ((*iter)->ID == socketInfo.ID)
				{
					if ((*iter)->DataType == eInviteRecv)
						packet->DataType = eInviteRecv;
					if ((*iter)->DataType == eGoToPVP)
						packet->DataType = eGoToPVP;
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
				// ���� none���� ���
				if ((*iter)->ID == socketInfo.ID)
				{
					packet->DataType = eDataType::eNone;
					(*iter) = packet;
				}
			}
		}
		// �÷��̾ ��뿡�� �ʴ� �޼��� �߼�
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
				// ���� none���� ���
				if ((*iter)->ID == socketInfo.ID)
				{
					packet->DataType = eDataType::eNone;
					(*iter) = packet;
				}
			}
		}
		if (eDataType::eInviteRecv == packet->DataType)
		{
			if (packet->isPvP)
				packet->DataType = eDataType::eGoToPVP;
			// ���������� ���� ���¸� ������ ������
			std::list<UserInfo*>::iterator iter = userList.begin();
			for (iter = userList.begin(); iter != userList.end(); iter++)
			{
				//for (iter = userList.begin(); iter != userList.end(); iter++)
				//{
				//	if ((*iter)->ID == socketInfo.ID)
				//	{
				//		(*iter) = packet;
				//	}
				//}
				// ���� recv�� ��ȯ
				//if ((*iter)->ID == packet->PVPID)
				//{
				//	(*iter)->DataType = eInviteRecv;
				//	(*iter)->PVPID = threadID;
				//}
				// ���� none���� ���
				//if ((*iter)->ID == socketInfo.ID)
				//{
				//	packet->DataType = eDataType::eNone;
				//	(*iter) = packet;
				//}
			}
		}
		if (eDataType::eGoToPVP == packet->DataType)
		{
			for (iter = userList.begin(); iter != userList.end(); iter++)
			{
				if ((*iter)->ID == packet->PVPID)
				{
					(*iter)->DataType = eGoToPVP;	
					// �̶� �̺�Ʈ ��������			
					if (packet->ID > packet->PVPID)
					{
						SetEvent(socketList[packet->PVPID - 1].sendEvent);	
					}
					else
						SetEvent(socketList[packet->ID - 1].sendEvent); 
				}
				if ((*iter)->ID == packet->ID)
				{
					(*iter) = packet;
					(*iter)->isPvP = true;
				}

			}
		}
		if (eDataType::eInPVP == packet->DataType)
		{
			//if (packet->ID > packet->PVPID)
			//{
			//	WaitForSingleObject(socketList[packet->PVPID - 1].sendEvent, INFINITE);	// b ������ �Ϸ� ���
			//}
			//else
			//	WaitForSingleObject(socketList[packet->PVPID - 1].writeEvent, INFINITE); // a ���� �Ϸ� ���

			for (iter = userList.begin(); iter != userList.end(); iter++)
			{
				if ((*iter)->ID == socketInfo.ID)
				{
					(*iter) = packet;
					if (packet->ID > packet->PVPID)
					{
						ResetEvent(socketList[packet->PVPID - 1].sendEvent);	
						SetEvent(socketList[packet->ID - 1].writeEvent);	// a ���� �Ϸ� set
					}				
					else
					{
						ResetEvent(socketList[packet->PVPID - 1].writeEvent);
						SetEvent(socketList[packet->ID - 1].writeEvent);    // b ���� �Ϸ� set
					}
						
					break;
				}

			}
		}
		// ���� ���� ������
		if(eDataType::eExit == packet->DataType)
		{
			for (iter = userList.begin(); iter != userList.end(); iter++)
			{
				if ((*iter)->ID == socketInfo.ID)
				{
					(*iter) = packet;
				}
			}
		}

		// �����尡 ������ �ִ� ���� �����Ϳ� ��ü userinfo�� �����ش�.
		iter = userList.begin();
		int pvpCount = 0;
		for (iter = userList.begin(); iter != userList.end(); iter++)
		{
			if ((*iter)->ID == threadID)
			{
				if ((*iter)->DataType == eDataType::eInPVP)
					pvpCount += 1;
				// ���� �ð�
				(*iter)->ServerTime = (int)serverTime;
				userInfo = (*iter);
			}
			if ((*iter)->ID == packet->PVPID)
			{
				if ((*iter)->DataType == eDataType::eInPVP)
					pvpCount += 1;
			}

		}
		if (eDataType::eInPVP != packet->DataType)
		{
			retval = send(client_sock, (const char*)userInfo, sizeof(UserInfo), 0);
		}	
		else if(eDataType::eInPVP == packet->DataType && pvpCount < 2)
		{
			for (iter = userList.begin(); iter != userList.end(); iter++)
			{
				if (packet->PVPID == (*iter)->ID)
				{
					// ���� �ð�
					(*iter)->ServerTime = (int)serverTime;
					retval = send(client_sock, (const char*)(*iter), sizeof(UserInfo), 0);
					break;
				}
			}
		}
		else
		{
			// ���� ���� ����
			if (packet->ID > packet->PVPID)
				WaitForSingleObject(socketList[packet->PVPID - 1].writeEvent, INFINITE); // b ���� ���
			else
				WaitForSingleObject(socketList[packet->PVPID - 1].sendEvent, INFINITE); // a ������ ���

			for (iter = userList.begin(); iter != userList.end(); iter++)
			{
					if (packet->PVPID == (*iter)->ID )
					{
						// ���� �ð�
						(*iter)->ServerTime = (int)serverTime;
						retval = send(client_sock, (const char*)(*iter), sizeof(UserInfo), 0);
						if (packet->ID > packet->PVPID)
						{
							ResetEvent(socketList[packet->PVPID - 1].writeEvent);
							SetEvent(socketList[packet->ID - 1].sendEvent); // a ������ �Ϸ� set
						}
						else
						{
							ResetEvent(socketList[packet->PVPID - 1].sendEvent);
							SetEvent(socketList[packet->ID - 1].sendEvent); // b ������ �Ϸ� set
						}
							
						break;
					}
			}
	
		}
		//if (userInfo->DataType == eDataType::eExit)
		//{
		//	iter = userList.begin();
		//	for (iter = userList.begin(); iter != userList.end(); iter++)
		//	{
		//		if ((*iter)->ID == threadID)
		//		{
		//			break;
		//		}
		//	}
		//	userList.erase(iter);
		//	break;
		//}
	}


	// ���� �ݱ�
	closesocket(client_sock);
	printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
		addr, ntohs(clientaddr.sin_port));
	return 0;
}

int main(int argc, char* argv[])
{
	// �ð� ������ ����
	CreateThread(NULL, 0, Timer,0, 0, NULL);


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
