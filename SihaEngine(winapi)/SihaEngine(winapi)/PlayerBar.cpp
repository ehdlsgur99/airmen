#include "common.h"


void PlayerBar::init()
{
	hpIcon = new GameObject;
	hpIcon->loadTexture("Resource/player/ui/hp.png");
	hpIcon->setSrcSize(182, 159);
	hpIcon->setSize(100, 100);
	hpIcon->setPos(50, 0);

	mpIcon = new GameObject;
	mpIcon->loadTexture("Resource/player/ui/mp.png");
	mpIcon->setSrcSize(182, 159);
	mpIcon->setSize(100, 100);
	mpIcon->setPos(50, 50);

	hpBar = new GameObject;
	hpBar->loadTexture("Resource/player/ui/hpBar.png");
	hpBar->setSrcSize(439, 41);
	hpBar->setSize(300, 20);
	hpBar->setPos(180, 30);

	mpBar = new GameObject;
	mpBar->loadTexture("Resource/player/ui/mpBar.png");
	mpBar->setSrcSize(439, 41);
	mpBar->setSize(300, 20);
	mpBar->setPos(180, 80);
}

void PlayerBar::update()
{
	hpBar->size.cx = 300 * Player::GetInstance()->nowHp/ Player::GetInstance()->hp;
	mpBar->size.cx = 300 * Player::GetInstance()->nowMp / Player::GetInstance()->mp;
}

void PlayerBar::render()
{
	GraphicManager::GetInstance()->render(hpIcon);
	GraphicManager::GetInstance()->render(mpIcon);
	GraphicManager::GetInstance()->render(hpBar);
	GraphicManager::GetInstance()->render(mpBar);
}

void PlayerBar::release()
{

}