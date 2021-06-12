#include "common.h"

void Monster::init(eMonsterType type)
{
	this->monsterType = type;
	this->monsterState = eRun;

	switch (monsterType)
	{
	case eSlime:
		hp = 100;
		power = 1;
		loadTexture("Resource/monster/slime/Run-1.png");
		setSize(96, 75);
		setSrcSize(32, 25);
		setPos(1000, 700);
		speed = 2;
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
	pos.x -= speed;
}

void Monster::update()
{
	// 애니메이션
	ani();

	// 캐릭터 이동
	move();
}

void Monster::render()
{
	GraphicManager::GetInstance()->render(this);
}

void Monster::release()
{

}

void Monster::attack()
{
	if (hp <= 0)
		return;
	if (Player::GetInstance()->state == eAttacked)
		return;

	Player::GetInstance()->hp -= power;
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

	if (hp <= 0 && monsterState != eDie)
	{
		isAttacked = true;
		monsterState = eDie;
	}
	else
	{
		isAttacked = true;
		monsterState = eHurt;
	}
}