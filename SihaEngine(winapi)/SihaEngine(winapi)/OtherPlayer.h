#pragma once
#include "common.h"
class OtherPlayer : public CSingleton<OtherPlayer>
{
public:
	int power;

	OtherPlayer();
	~OtherPlayer();

	UserInfo getUserInfo2();

	int get2PlayerState();
	void init();
	void update();
	void render();
	void release();

	void gravity(Tail* tail);
public:
	int state;
	int dir;
	int smashDir;
	int nextState;

	int hp;
	int mp;
	int nowHp;
	int nowMp;

	std::string name;
	int JumpTime = 0;
	int JumpCount = 0;
	int JumpPower = 1000;


public:
	GameObject* Oplayer;
	GameObject* Osmash;
	GameObject* Ohpbar;
	PlayerBar* OplayerBar;
	int level;

	bool isSmash;
	bool isUI;
	bool isAttack;
	bool isJump;

	UserInfo userInfo;
};

