#pragma once
#include "common.h"
class OtherPlayer : public CSingleton<Player>
{
public:
	int power;

	OtherPlayer();
	~OtherPlayer();

	UserInfo getUserInfo();

	int get2PlayerState();
	void init();
	void update();
	void render();
	void release();

	void gravity(Tail* tail);
public:
	ePlayer state;
	ePlayer nextState;
	int hp;
	int mp;
	int nowHp;
	int nowMp;

	std::string name;
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

	UserInfo userInfo;
};

