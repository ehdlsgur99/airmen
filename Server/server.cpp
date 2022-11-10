#include "common.h"
#include <list>
#include "UserInfo.h"

// UserInfo ���� List
std::list<UserInfo> userList;
// Socket ���� List
std::list<SocketInfo> socketList;
// ���� ������ ������ id�ѹ��� ���� id�Ҵ翡 ���̴� ��������
int IDCount;
// �ٸ� Ŭ���̾�Ʈ�� Userlist �� �����ϰ� �ִ��� Ȯ���ϴ� bool ���� 
bool isUsing;




int serverport;
//#define SERVERPORT 9000
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

}

// ������ ���� ��û�� �޾� ������ ������ ������ 1���� �Ҵ��ϰ� �������θ� ��ȯ�Ѵ�.
bool AddUser()
{

}

// Ŭ���̾�Ʈ���� ���� ���� ��û�� ���� ��� 
// ���� ������ ����� UserList ���� Ŭ���̾�Ʈ�� �����ϰ� �������θ� ��ȯ�Ѵ�.
bool SendUserInfo(SOCKET client_sock)
{

}


// Ŭ���̾�Ʈ���� PvP�� ��û�� ������ ���� UserInfo.id(enemyID) �� ���� ��
// UserList�� socketList ���� �ش� id�� ã�� ����(enum ������ �ĺ� ��) + ����(PvP�� ��û�� ���� ����)�� �����Ѵ�. 
// �������θ� ��ȯ�Ѵ�.
bool SendPvPMessage(SOCKET client_sock, int enemyID)
{

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

}

/*
	������ UserInfo ���� �޾ƿ� UserList���� �ش� id�� UserInfo ���� �ʱ�ȭ ��Ų��. 
	client_sock���� ProcessClient �������� ���������� enemyID(��� id)�� �޾ƿ� UserList���� �ش� id�� UserInfo ���� �����Ѵ�. 
	���޹��� UserInfo.isPvP���� false�� ��� pvp�� ����� ������ �Ǵ��Ѵ�.
*/
bool ExchangeUserInfo(SOCKET client_sock, UserInfo myInfo, int enemyID)
{

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

	// Ŭ���̾�Ʈ�� ������ ���
	while (1) {
		// ���� �̸� ũ�� �ޱ�
		retval = recv(client_sock, (char*)&len, sizeof(len), MSG_WAITALL);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;

		// ���� �̸� ���� �ޱ�
		// ������ �ޱ�(���� ����)
		retval = recv(client_sock, buf, len, MSG_WAITALL);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;

		// ���� ������ ���
		// ���� �̸�
		buf[retval] = '\0';
		printf("[TCP/%s:%d] %s", addr, ntohs(clientaddr.sin_port), buf);

		// File �����ϱ�
		FILE* fp = fopen(buf, "ab");
		if (fp == NULL)
		{
			printf("���� ����� ����");
			break;
		}

		// ���� ��ü ũ��
		int totalfileSize;
		retval = recv(client_sock, (char*)&totalfileSize, sizeof(int), MSG_WAITALL);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;
		printf("\t ���� ������ : %d \n", totalfileSize);

		int nowFileSize = 0;
		int size = 512;
		// ���� ������ �ޱ�
		while (1)
		{
			// ������ ����
			retval = recv(client_sock, buf, size, MSG_WAITALL);
			if (retval == SOCKET_ERROR) {
				err_display("recv()");
				break;
			}
			else if (retval == 0)
				break;
			fwrite(buf, 1, retval, fp);
			nowFileSize += retval;

			if (isFlag)
			{
				isFlag = false;
				gotoxy(0, 15 + threadID);
				printf("��Ʈ��ȣ : %d ���൵ : %.2f %% \t\t\t\t\t", ntohs(clientaddr.sin_port),
					((float)nowFileSize / (float)totalfileSize) * 100.f);
				gotoxy(0, (threadCount + 1) * 2);
				isFlag = true;
			}

		}
		gotoxy(0, 15 + threadID);
		printf("��Ʈ��ȣ : %d ���൵ : %.2f %% \t\t\t\t\t", ntohs(clientaddr.sin_port),
			((float)nowFileSize / (float)totalfileSize) * 100.f);
		gotoxy(0, (threadCount + 1) * 2);
		fclose(fp);
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

	printf("���� ��Ʈ �Է� : ");
	scanf("%d", &serverport);

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// ���� ����
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(serverport);
	retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// ������ ��ſ� ����� ����
	SOCKET client_sock;
	struct sockaddr_in clientaddr;
	int addrlen;
	HANDLE hThread[MAX_THREADS];


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
		threadCount++;
		if (hThread[threadCount] == NULL) { closesocket(client_sock); }
		else { CloseHandle(hThread[threadCount]); }


	}

	// ���� �ݱ�
	closesocket(listen_sock);

	// ���� ����
	WSACleanup();
	return 0;
}
