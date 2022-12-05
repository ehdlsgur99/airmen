#include "common.h"

UserInfo info;

// 소켓 함수 오류 출력 후 종료
void err_quit(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	MessageBoxA(NULL, (const char*)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// 소켓 함수 오류 출력
void err_display(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	printf("[%s] %s\n", msg, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// 소켓 함수 오류 출력
void err_display(int errcode)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	printf("[오류] %s\n", (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}


// Player 클래스가 싱글톤이고 보기 쉽게 여기에 쓰레드를 생성합니다.
DWORD WINAPI ClientThread(LPVOID arg)
{
	int retval;
	Player::GetInstance()->getUserInfo();
	while (1)
	{
		//retval = send(Player::GetInstance()->sock, (char*)&type, sizeof(type), 0);
	/*	if (retval == SOCKET_ERROR) {
			err_display("send()");
		}*/
		switch (Player::GetInstance()->getUserInfo().DataType)
		{
		case eDataType::eNone:
			// 플레이어 데이터인 UserInfo를 발송한다.
			retval = send(Player::GetInstance()->sock, (char*)&Player::GetInstance()->userInfo, sizeof(UserInfo), 0);
			// PVP 초대 메세지 받기
			break;
		case eDataType::eRequest:
			retval = send(Player::GetInstance()->sock, (char*)&Player::GetInstance()->userInfo, sizeof(UserInfo), 0);

			// 다른 플레이어가 몇명인지 받아온다.
			int otherNum;
			retval = recv(Player::GetInstance()->sock, (char*)&otherNum, sizeof(otherNum), MSG_WAITALL);

			Player::GetInstance()->userInfos.clear();
			Player::GetInstance()->userInfos.reserve(otherNum);
			// UserInfo 구조체  받기
			//char buf[BUFSIZE];

			// 다른 유저들의 데이터를 받아온다.
			for (int i = 0; i < otherNum; ++i)
			{
				UserInfo temp;
				retval = recv(Player::GetInstance()->sock, (char*)&temp, sizeof(UserInfo), 0);
				Player::GetInstance()->userInfos.push_back(temp);
			}
			Player::GetInstance()->getUserInfos();
			// dataType 다시 eNone으로 변경
			SetEvent(Player::GetInstance()->readOtherUserEvent);
			Player::GetInstance()->userInfo.DataType = eNone;
			break;
		case eDataType::eInviteSend:
			// 선택한 상대방 아이디와 내 유저 정보를 보낸다
			retval = send(Player::GetInstance()->sock, (char*)&Player::GetInstance()->userInfo, sizeof(UserInfo), 0);
			// dataType 다시 eNone으로 변경
			//Player::GetInstance()->userInfo.DataType = eNone;
			break;
		}
		
		//if (eDataType::eInviteRecv == Player::GetInstance()->getUserInfo().DataType)
		//{
		//	retval = send(Player::GetInstance()->sock, (char*)&Player::GetInstance()->userInfo, sizeof(UserInfo), 0);
		//}

		// 끝날때 서버로부터 패킷을 받아온다. 내 데이터 or 상대 데이터(pvp)
		UserInfo temp;
		//retval = recv(Player::GetInstance()->sock, (char*)&Player::GetInstance()->userInfo, sizeof(UserInfo), 0);
		retval = recv(Player::GetInstance()->sock, (char*)&temp, sizeof(UserInfo), 0);
		// 만약 초대 받은 상황이라면?
		// 현재 상태 변경
		if (temp.DataType == eDataType::eInviteRecv)
		{
			Player::GetInstance()->userInfo.DataType = eDataType::eInviteRecv;
		}

	
		
		//Player::GetInstance()->userInfo = temp;


	}
	return 0;
}


bool Player::enterGame()
{
	//"127.0.0.1";
	char* SERVERIP = (char*)"127.0.0.1";

	// 윈속 초기화
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 소켓 생성
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	// UserInfo 구조체  받기
	char buf[BUFSIZE];
	//retval = recv(sock, buf, sizeof(UserInfo), 0);
	retval = recv(sock, (char*)&userInfo, sizeof(UserInfo), 0);
	buf[retval] = '\0';

	//info.ID = userInfo->ID;
	//info.power = userInfo->power;
 	return true;
}

void Player::setDataType(eDataType dataType)
{
	userInfo.DataType = dataType;
}

std::vector<UserInfo> Player::getUserInfos()
{
	return userInfos;
}

Player::Player()
{

	readOtherUserEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	pvpID = -1;

	level = 1;

	//userInfo = new UserInfo;

	player = new GameObject;
	player->loadTexture("Resource/player/idle/player1.png");
	player->setSrcSize(50, 37);
	player->setSize(200, 161);
	player->setPos(0, 620);


	playerUI = new PlayerUI;
	playerUI->init();
	playerBar = new PlayerBar;
	playerBar->init();

	smash = new GameObject;
	smash->setSize(150, 120);
	smash->setPos(player->pos.x, player->pos.y);


	nowHp = hp = 100;
	nowMp = mp = 100;
	player->setPos(50, 560);
	power = 10;
	state = eRight;

	// 생성자에서 쓰레드 생성
	// =====================================
	// playerInfo 초기화 확인필수!
	// =====================================

	// =====================================
	// 서버 연결
	// =====================================
	enterGame();
	
	getUserInfo();
	HANDLE hThread = CreateThread(NULL, 0, ClientThread, &userInfo, 0, NULL);
	if (hThread == NULL) return;
	CloseHandle(hThread);

}

Player::~Player()
{

}

int Player::getPlayerState()
{
	return state;
}

UserInfo Player::getUserInfo()
{
	return userInfo;
}

void Player::init()
{
	smash = new GameObject;
	smash->setSize(150, 120);
	smash->setPos(-1000, player->pos.y);

	if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eGame)
	{
		nowHp = hp = playerUI->armorPower + 100;
		nowMp = mp = playerUI->ringPower + 100;
		player->setPos(50, 560);
		power = playerUI->swordPower + 10;
		state = eRight;
	}

}

// getKey 사용할때
// https://m.blog.naver.com/power2845/50143021565 참고

void Player::update()
{
	if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eVillage)
	{
		if (player->pos.y <= 500)
		{
			player->pos.y += 10;
		}

	}
	if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->ePvp)
	{
		if (player->pos.y <= 500)
		{
			player->pos.y += 10;
		}

	}
	// 캐릭터 애니메이션

	// 캐릭터 이동 예시
	if (InputManager::GetInstance()->getKey(VK_LEFT))
	{
		if(!isJump)
			state = eLeft;
		if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eVillage)
		{
			if (mappos >= 800 && mappos <= 1000)
				player->pos.x += 10;
			if (mappos >= 0) {
				player->pos.x -= 10;
				ObjectManager::GetInstance()->cameraMove(-10, 0);
				mappos -= 10;
			}
			
		}
		if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->ePvp)
		{
			if (player->pos.x <= -20)
				player->pos.x += 10;
			else
				player->pos.x -= 10;
		}
	}
	else if (InputManager::GetInstance()->getKey(VK_RIGHT))
	{
		if (!isJump)
			state = eRight;
		if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eVillage)
		{

			if(mappos>=800&&mappos<=1000)
				player->pos.x -= 10;
			if (mappos <= 1600) {
				player->pos.x += 10;
				ObjectManager::GetInstance()->cameraMove(10, 0);
				mappos += 10;
			}
		}
		if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->ePvp)
		{
			if (player->pos.x >= 1400)
				player->pos.x -= 10;
			else
				player->pos.x += 10;
		}
			
	}
	else if (InputManager::GetInstance()->getKey(0x41))
	{
		if (!isAttack || state != eAttack2 && state != eAttack1)
		{
			state = eAttack1;
			isAttack = true;
		}
		else if (isAttack && state == eAttack1 && player->aniNow >= 5 && nextState != eAttack2)
		{
			if (nowMp >= 10)
			{
				nextState = eAttack2;
				nowMp -= 10;
			}
		}
	
	}
	// JUMP
	if (InputManager::GetInstance()->getKey(VK_UP))
	{
		
		if (!isJump && state != eJump1)
		{
			state = eJump1;
			isJump = true;
			JumpCount = 0;
		}
		// 점프1중 일때
		if (isJump && state == eJump1 && state != eJump2 && JumpCount > 2)
		{
			if (nowMp >= 10)
			{
				state = eJump2;
				JumpCount = 0;
				nowMp -= 10;
			}
		}
	}

	if (isJump  && GetTickCount64() - JumpTime >= 50 && state == eJump1)
	{
		JumpTime = GetTickCount64();
		if (JumpCount < 16)
		{
			if (JumpCount < 8)
				player->pos.y -= 15;
			else
				player->pos.y += 15;
			JumpCount++;
		}
		else
		{
			state = eIdle;
			if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eGame)
				state = eRight;
			JumpCount = 0;
			isJump = false;
		}
	}
	if (isJump && GetTickCount64() - JumpTime >= 50 && state == eJump2)
	{
		JumpTime = GetTickCount64();
		if (JumpCount < 8)
		{
			player->pos.y -= 15;
			JumpCount++;
		}
		else
		{
			state = eIdle;
			if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eGame)
				state = eRight;
			JumpCount = 0;
			isJump = false;
		}
	}

	// 포션 먹기
	// 체력 포션 1번키
	if (InputManager::GetInstance()->getKey(0x31))
	{
		if (playerUI->hpPotionNum > 0)
		{
			if (nowHp < 100)
			{
				playerUI->hpPotionNum -= 1;
				nowHp += 20;
				if (nowHp > 100)
					nowHp = 100;
			}
			
		}
	}
	// 마나 포션
	// 2번키
	if (InputManager::GetInstance()->getKey(0x32))
	{
		if (playerUI->mpPotionNum > 0)
		{
			if (nowMp < 100)
			{
				playerUI->mpPotionNum -= 1;
				nowMp += 50;
				if (nowMp > 100)
					nowMp = 100;
			}
		}
	}
	if (InputManager::GetInstance()->getKey(0x4D))
	{
		playerUI->coinNum = 9999;
	}
	// 스매쉬
	if (InputManager::GetInstance()->getKey(0x53))
	{
		if (state == eAttack2 && !isSmash)
		{
			if (nowMp >= 30)
			{
				isSmash = true;
				nowMp -= 30;
				smash->setPos(player->pos.x + 20, player->pos.y + 50);
			}
		}
	}

	// 캐릭터 애니메이션
	switch (state)
	{
	case eIdle:
		player->animation("Resource/player/idle/player", 6, 200);
		break;
	case eLeft:
		if (player->animation("Resource/player/left/left", 6, 30))
			state = eIdle;

		break;
	case eRight:
		if (player->animation("Resource/player/right/right", 6, 30))
		{
			state = eIdle;
			if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eGame)
				state = eRight;
		}
		break;
	case eJump1:

		if (player->animation("Resource/player/jump/jump", 4, 200)) {
			//if (nextState == eJump2)
			//	state = eJump2;
			//else
			//{
			//	state = eIdle;
			//	isJump = false;
			//}
		}
			
		break;
	case eJump2:

		if (player->animation("Resource/player/doublejump/doublejump", 4, 100)) {

		}
			
		break;
	case eAttack1:
		if (player->animation("Resource/player/attack/attack1-", 6, 100))
		{
			if (nextState == eAttack2)
				state = eAttack2;
			else
			{
				nextState = eRight;
				state = eRight;
				isAttack = false;
			}		
		}
		break;
	case eAttack2:
		if (player->animation("Resource/player/attack/attack2-", 6, 100))
		{
			isAttack = false;
			nextState = eRight;
			state = eRight;
		}
			
		break;
	case eAttacked:
		if (player->animation("Resource/player/hurt/hurt-", 6, 200))
		{
			nextState = eRight;
			state = eRight;

		}
	default:
		break;
	}

	// 스매쉬 이동
	if (isSmash)
	{
		smash->animation("Resource/GameScene/smash",4, 100 );
		smash->pos.x += 10;
		if (smash->pos.x >= 2000)
		{
			isSmash = false;
			smash->pos.x = -100;
		}
	}

	if(SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eGame)
		playerBar->update();
	if (InputManager::GetInstance()->getKey(0x49) && InputManager::GetInstance()-> delay(500))
	{
		playerUI->update();
		if (isUI) 
			isUI = false;
		
		else
			isUI = true;
	}
}

void Player::render()
{
	GraphicManager::GetInstance()->render(player);

	if (isSmash)
		GraphicManager::GetInstance()->render(smash);

	//if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eGame)
	playerBar->render(playerUI);


	if (isUI)
	{
		playerUI->render();
	}

}

void Player::release()
{
	GraphicManager::GetInstance()->release();
}


void Player::gravity(Tail *tail)
{
	// 플레이어는 바닥에 붙어 있는게 아니면 중력에 영향 받아야함 ㅇㅇ
	if (state != eJump1 && state != eJump2)
	{
		if (player->pos.y <= 560)
		{
			bool isCrush = false;
			GameObject* tempObject = new GameObject;
			tempObject->size = player->size;
			tempObject->pos = player->pos;
			tempObject->size.cy = 20;
			tempObject->pos.y += 130;
			for (int i = 0; i < tail->tails.size(); i++)
			{
				if (CollisionManager::GetInstance()->RectCollisionCheck(tempObject, tail->tails[i]))
				{
					isCrush = true;
				}
			}
			if (!isCrush)
				player->pos.y += 10;
		}
	}

}