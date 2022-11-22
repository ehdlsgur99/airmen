#pragma once

#include "common.h"

class Player : public CSingleton<Player>
{
public:
	ePlayer state;
	ePlayer nextState;
	int hp;
	int mp;
	int nowHp;
	int nowMp;

	// =====================================
	// playerInfo 초기화 추가 해줘합니다!
	// =====================================
	UserInfo playerInfo;

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
	UserInfo* userInfo;
public:
	
	int power;

	Player();
	~Player();
	
	int getPlayerState();
	void init();
	void update();
	void render();
	void release();

	// SERVER - CLIENT 연결함수
	bool enterGame();

	void gravity(Tail* tail);
};

