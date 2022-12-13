#include "common.h"
#include <list>
#include <time.h>
#include <vector>
#include "UserInfo.h"
#include "EnumData.h"

// UserInfo 관리 List
std::list<UserInfo*> userList;
// Socket 관리 List
std::vector<SocketInfo> socketList;

#define SERVERPORT 9000
#define BUFSIZE    512
#define MAX_THREADS	100

int threadCount = 0;

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

	// UserList에 현재 유저 UserInfo  추가
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
	userInfo->power = 100;
	userInfo->Frame = 0;
	userInfo->dir = 0;

	userList.push_back(userInfo);

	// SocketList에 현재 유저 SocketInfo 추가
	SocketInfo socketInfo;
	socketInfo.client_sock = client_sock;
	socketInfo.writeEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	socketInfo.sendEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	socketInfo.ID = userInfo->ID;

	socketList.push_back(socketInfo);

	// 클라이언트와 데이터 통신
	// UserInfo 데이터 보내기
	retval = send(client_sock, (const char*)userInfo, sizeof(UserInfo), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
	}
	while(1) {
		std::list<UserInfo*>::iterator iter;
		
		// 패킷 받기
		UserInfo* packet = new UserInfo;
		char buf[BUFSIZE];

		retval = recv(client_sock, buf, sizeof(UserInfo), 0);
		packet = (UserInfo*)buf;

		// DataType 에 따른 다음 동작
		
		int userNum = userList.size();
		// 플레이어 데이터인 UserInfo를 발송한다.
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
			// PVP 상황인경우 여기서 상대방 정보를 보내준다.
		}
		// 플레이어 정보들을 넘겨준다.
		if (eDataType::eRequest == packet->DataType)
		{
			// 접속 인원 전송
			retval = send(client_sock, (char*)&userNum, sizeof(userNum), 0);

			UserInfo *sendTemp = new UserInfo;
			for (iter = userList.begin(); iter != userList.end(); iter++)
			{
				sendTemp = *iter;
				retval = send(client_sock, (char*)sendTemp, sizeof(UserInfo), 0);
				// 나는 none으로 대기
				if ((*iter)->ID == socketInfo.ID)
				{
					packet->DataType = eDataType::eNone;
					(*iter) = packet;
				}
			}
		}
		// 플레이어가 상대에게 초대 메세지 발송
		if (eDataType::eInviteSend == packet->DataType)
		{
			// 서버에서의 유저 상태를 보내는 데이터
			std::list<UserInfo*>::iterator iter = userList.begin();
			for (iter = userList.begin(); iter != userList.end(); iter++)
			{
				if ((*iter)->ID == packet->PVPID)
				{
					(*iter)->DataType = eInviteRecv;
					(*iter)->PVPID = threadID;
				}
				// 나는 none으로 대기
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
		}
		if (eDataType::eGoToPVP == packet->DataType)
		{
			for (iter = userList.begin(); iter != userList.end(); iter++)
			{
				if ((*iter)->ID == packet->PVPID)
				{
					(*iter)->DataType = eGoToPVP;	
					// 이때 이벤트 열어주자			
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

		// 현재 두 플레이어 모두 PVP 씬인지 확인한다.
		iter = userList.begin();
		int pvpCount = 0;
		for (iter = userList.begin(); iter != userList.end(); iter++)
		{
			if ((*iter)->ID == threadID)
			{
				if ((*iter)->DataType == eDataType::eInPVP)
					pvpCount += 1;
			}
			if ((*iter)->ID == packet->PVPID)
			{
				if ((*iter)->DataType == eDataType::eInPVP)
					pvpCount += 1;
			}

		}
		if (eDataType::eInPVP == packet->DataType && pvpCount < 2)
		{
			for (iter = userList.begin(); iter != userList.end(); iter++)
			{
				if ((*iter)->ID == socketInfo.ID)
				{
					(*iter) = packet;
					break;
				}

			}
		}
		else if (eDataType::eInPVP == packet->DataType && pvpCount >= 2)
		{
			if (packet->ID > packet->PVPID)
			{
				WaitForSingleObject(socketList[packet->PVPID - 1].sendEvent, INFINITE);	// b 보내기 완료 대기
			}
			else
				WaitForSingleObject(socketList[packet->PVPID - 1].writeEvent, INFINITE); // a 쓰기 완료 대기

			for (iter = userList.begin(); iter != userList.end(); iter++)
			{
				if ((*iter)->ID == socketInfo.ID)
				{
					(*iter) = packet;
					if (packet->ID > packet->PVPID)
					{
						ResetEvent(socketList[packet->PVPID - 1].sendEvent);
						SetEvent(socketList[packet->ID - 1].writeEvent);	// a 쓰기 완료 set
					}
					else
					{
						ResetEvent(socketList[packet->PVPID - 1].writeEvent);
						SetEvent(socketList[packet->ID - 1].writeEvent);    // b 쓰기 완료 set
					}

					break;
				}

			}
		}

		// 강제 종료 했을 때
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

		// 스레드가 가지고 있는 유저 데이터와 전체 userinfo를 합쳐준다.
		iter = userList.begin();
		for (iter = userList.begin(); iter != userList.end(); iter++)
		{
			if ((*iter)->ID == threadID)
			{
				userInfo = (*iter);
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
					retval = send(client_sock, (const char*)(*iter), sizeof(UserInfo), 0);
					break;
				}
			}
		}
		else
		{
			// 상대방 정보 전송
			if (packet->ID > packet->PVPID)
				WaitForSingleObject(socketList[packet->PVPID - 1].writeEvent, INFINITE); // b 쓰기 대기
			else
				WaitForSingleObject(socketList[packet->PVPID - 1].sendEvent, INFINITE); // a 보내기 대기

			for (iter = userList.begin(); iter != userList.end(); iter++)
			{
					if (packet->PVPID == (*iter)->ID )
					{
						retval = send(client_sock, (const char*)(*iter), sizeof(UserInfo), 0);
						if (packet->ID > packet->PVPID)
						{
							ResetEvent(socketList[packet->PVPID - 1].writeEvent);
							SetEvent(socketList[packet->ID - 1].sendEvent); // a 보내기 완료 set
						}
						else
						{
							ResetEvent(socketList[packet->PVPID - 1].sendEvent);
							SetEvent(socketList[packet->ID - 1].sendEvent); // b 보내기 완료 set
						}	
						break;
					}
			}
	
		}

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

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 소켓 생성
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

	// 데이터 통신에 사용할 변수
	SOCKET client_sock;
	struct sockaddr_in clientaddr;
	int addrlen;
	HANDLE hThread[MAX_THREADS];

	printf("현재 접속중인 유저 수: %d ", threadCount);
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
		if (hThread[threadCount] == NULL) { closesocket(client_sock); }
		else { CloseHandle(hThread[threadCount]); }
		threadCount++;

		printf("\n현재 접속중인 유저 수: %d ", threadCount);

	}

	// 소켓 닫기
	closesocket(listen_sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}
