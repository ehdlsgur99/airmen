#pragma once

#include "common.h"

class Player : public CSingleton<Player>
{
public:

	int power;

	Player();
	~Player();

	UserInfo getUserInfo();

	int getPlayerState();
	void init();
	void update();
	void render();
	void release();

	// SERVER - CLIENT 연결함수
	bool enterGame();

	void setDataType(eDataType dataType);

	std::vector<UserInfo> getUserInfos();

	void gravity(Tail* tail);
public:
	int state;
	int dir;
	int nextState;
	
	int hp;
	int mp;
	int nowHp;
	int nowMp;
	int pvpID;

	std::string name;
	int mappos = 0;
	int JumpTime = 0;
	int JumpCount = 0;
	int JumpPower = 1000;

public:
	GameObject* player;
	GameObject* smash;
	PlayerBar* playerBar;
	PlayerUI* playerUI;

	int level;

	bool isSmash;
	bool isUI;
	bool isAttack;
	bool isJump;

public:
	// 서버 관련 변수
	int retval;
	SOCKET sock;
	WSADATA wsa;
	UserInfo userInfo;
	std::vector<UserInfo> userInfos;
	UserInfo enemyInfo;

	HANDLE readOtherUserEvent;
};

