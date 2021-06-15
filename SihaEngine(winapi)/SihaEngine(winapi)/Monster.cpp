#include "common.h"

void Monster::init(eMonsterType type)
{
	this->monsterType = type;
	this->monsterState = eRun;

	hpbar = new GameObject;
	hpbar->loadTexture("Resource/monster/hpbar.png");
	hpbar->setSrcSize(200, 20);
	hpbar->setSize(100, 5);

	switch (monsterType)
	{
	case eSlime:
		hp = 100;
		power = 10;
		loadTexture("Resource/monster/slime/Run-1.png");
		setSize(96, 75);
		setSrcSize(32, 25);
		setPos(1600, 650);
		speed = 2;
		break;
	case eSkeleton:
		hp = 100;
		power = 10;
		loadTexture("Resource/monster/skeleton/Run-1.png");
		setSize(srcSize.cx * 4, srcSize.cy * 4);
		setPos(1600, 580);
		speed = 3;
		break;
	default:
		break;
	}
	isAttacked = false;
	isAttack = false;
	isDie = false;
}


void Monster::ani()
{
	// 애니메이션
	// 규칙 몬스터-모션-숫자
	// EX)SLIME-ATTACK-0
	std::string path;
	// 몬스터 타입
	switch (monsterType)
	{
	case eSlime:
		path = "Resource/monster/slime/";
		break;
	default:
		path = "Resource/monster/skeleton/";
		break;
	}
	// 몬스터 모션
	switch (monsterState)
	{
	case eRun:
		path += "Run-";
		break;
	case eHurt:
		path += "Hurt-";
		break;
	case eAttack:
		path += "Attack-";
		break;
	case eDie:
		path += "Die-";
		break;
	default:
		break;
	}
	if (animation(path, 4, 100) )
	{
		if (monsterState == eDie)
			isDie = true;
		monsterState = eRun;
	}
}

void Monster::move()
{
	if(Player::GetInstance()->state == eRight || Player::GetInstance()->state == eJump1 || Player::GetInstance()->state == eJump2)
		pos.x -= speed * 2;
	else
		pos.x -= speed;
}

void Monster::update()
{
	// 애니메이션
	ani();

	// 캐릭터 이동
	move();

	// hpbar 설정
	hpbar->setPos(pos.x, pos.y - 40);

	if (hp <= 0)
	{
		hpbar->size.cx = 1;
		hpbar->size.cy = 1;
	}
	else
		hpbar->size.cx = 100 * hp / 100;
}

void Monster::render()
{
	GraphicManager::GetInstance()->render(this);
	if(!isDie)
		GraphicManager::GetInstance()->render(hpbar);

}

void Monster::release()
{
	delete hpbar;
}

void Monster::attack()
{
	if (hp <= 0)
		return;
	if (Player::GetInstance()->state == eAttacked)
		return;

	Player::GetInstance()->nowHp -= power;
	Player::GetInstance()->state = eAttacked;

	monsterState = eAttack;
}

void Monster::attacked()
{

	if (hp <= 0)
		return;
	if (Player::GetInstance()->state == eAttack1)
		hp -= Player::GetInstance()->power;
	else if (Player::GetInstance()->state == eAttack2)
		hp -= Player::GetInstance()->power * 2;

	pos.x += 50;

	if (hp <= 0 && monsterState != eDie)
	{
		Player::GetInstance()->playerUI->coinNum += 25;
		hp = 0;
		isAttacked = true;
		monsterState = eDie;
	}
	else
	{
		isAttacked = true;
		monsterState = eHurt;
	}
}

void Monster::smashAttacked()
{
	if (hp <= 0)
		return;

		hp -= Player::GetInstance()->power * 5;

	pos.x += 50;

	if (hp <= 0 && monsterState != eDie)
	{
		Player::GetInstance()->playerUI->coinNum += 25;
		hp = 0;
		isAttacked = true;
		monsterState = eDie;
	}
	else
	{
		isAttacked = true;
		monsterState = eHurt;
	}
}