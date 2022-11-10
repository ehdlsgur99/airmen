#include "common.h"
#include <list>
#include "UserInfo.h"

// UserInfo 관리 List
std::list<UserInfo> userList;
// Socket 관리 List
std::list<SocketInfo> socketList;
// 현재 생성된 스레드 id넘버와 유저 id할당에 쓰이는 전역변수
int IDCount;
// 다른 클라이언트가 Userlist 에 접근하고 있는지 확인하는 bool 변수 
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

// 윈속 초기화, 소켓 생성 및 Bind, Listen, Accept 시도
int InitServer()
{

}

// 유저의 입장 요청을 받아 각각의 유저에 스레드 1개씩 할당하고 성공여부를 반환한다.
bool AddUser()
{

}

// 클라이언트에게 유저 정보 요청을 받은 경우 
// 실행 서버에 저장된 UserList 값을 클라이언트에 전송하고 성공여부를 반환한다.
bool SendUserInfo(SOCKET client_sock)
{

}


// 클라이언트에게 PvP를 신청할 유저에 대한 UserInfo.id(enemyID) 를 받은 후
// UserList와 socketList 에서 해당 id를 찾아 고정(enum 데이터 식별 값) + 가변(PvP를 신청한 유저 정보)를 전송한다. 
// 성공여부를 반환한다.
bool SendPvPMessage(SOCKET client_sock, int enemyID)
{

}

/*
	PvP를 승낙한 클라이언트로 부터 승낙 여부와 상대 ID를 넘겨 받은 후 
	현재 id(myID)의 UserList에 있는 userInfo.isPvP값을 true로 변경한다. 
	client_sock에 고정(enum 데이터 식별 값) + 가변(bool 승낙) 데이터 전송
	enemyID를 기반으로 해당하는 socket을 가져와 고정(enum 데이터 식별 값) + 가변(bool 승낙) 데이터 전송, 
	enemyID의 UserList에 있는 userinfo.isPvP 값 true로 변경
*/
bool GotoPVP(SOCKET client_sock, int myID, bool isYes, int enemyID)
{

}

/*
	본인의 UserInfo 값을 받아와 UserList에서 해당 id의 UserInfo 값을 초기화 시킨다. 
	client_sock에게 ProcessClient 스레드의 지역변수인 enemyID(상대 id)를 받아와 UserList에서 해당 id의 UserInfo 값을 전송한다. 
	전달받은 UserInfo.isPvP값이 false인 경우 pvp가 종료된 것으로 판단한다.
*/
bool ExchangeUserInfo(SOCKET client_sock, UserInfo myInfo, int enemyID)
{

}

// 클라이언트와 데이터 통신
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

	// 클라이언트 정보 얻기
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (struct sockaddr*)&clientaddr, &addrlen);
	inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));

	int len; 

	// 클라이언트와 데이터 통신
	while (1) {
		// 파일 이름 크기 받기
		retval = recv(client_sock, (char*)&len, sizeof(len), MSG_WAITALL);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;

		// 파일 이름 내용 받기
		// 데이터 받기(가변 길이)
		retval = recv(client_sock, buf, len, MSG_WAITALL);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;

		// 받은 데이터 출력
		// 파일 이름
		buf[retval] = '\0';
		printf("[TCP/%s:%d] %s", addr, ntohs(clientaddr.sin_port), buf);

		// File 생성하기
		FILE* fp = fopen(buf, "ab");
		if (fp == NULL)
		{
			printf("파일 입출력 오류");
			break;
		}

		// 파일 전체 크기
		int totalfileSize;
		retval = recv(client_sock, (char*)&totalfileSize, sizeof(int), MSG_WAITALL);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;
		printf("\t 파일 사이즈 : %d \n", totalfileSize);

		int nowFileSize = 0;
		int size = 512;
		// 파일 데이터 받기
		while (1)
		{
			// 데이터 내용
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
				printf("포트번호 : %d 진행도 : %.2f %% \t\t\t\t\t", ntohs(clientaddr.sin_port),
					((float)nowFileSize / (float)totalfileSize) * 100.f);
				gotoxy(0, (threadCount + 1) * 2);
				isFlag = true;
			}

		}
		gotoxy(0, 15 + threadID);
		printf("포트번호 : %d 진행도 : %.2f %% \t\t\t\t\t", ntohs(clientaddr.sin_port),
			((float)nowFileSize / (float)totalfileSize) * 100.f);
		gotoxy(0, (threadCount + 1) * 2);
		fclose(fp);
	}

	// 소켓 닫기
	closesocket(client_sock);
	printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
		addr, ntohs(clientaddr.sin_port));
	return 0;
}

int main(int argc, char* argv[])
{
	int retval;

	printf("서버 포트 입력 : ");
	scanf("%d", &serverport);

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 소켓 생성
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

	// 데이터 통신에 사용할 변수
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

		// 접속한 클라이언트 정보 출력
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			addr, ntohs(clientaddr.sin_port));

		// 스레드 생성
		hThread[threadCount] = CreateThread(NULL, 0, ProcessClient,
			(LPVOID)client_sock, 0, NULL);
		threadCount++;
		if (hThread[threadCount] == NULL) { closesocket(client_sock); }
		else { CloseHandle(hThread[threadCount]); }


	}

	// 소켓 닫기
	closesocket(listen_sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}
