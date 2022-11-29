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

	void gravity(Tail* tail);
public:
	ePlayer state;
	ePlayer dir;
	ePlayer nextState;
	int hp;
	int mp;
	int nowHp;
	int nowMp;

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

};

