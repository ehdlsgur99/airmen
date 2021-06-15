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

	coin = new GameObject;
	coin->loadTexture("Resource/GameScene/coin.png");
	coin->setSize(50, 50);
	coin->setPos(1000, 20);

	mpPotion = new GameObject;
	mpPotion->loadTexture("Resource/GameScene/mpPotion.png");
	mpPotion->setSize(50, 50);
	mpPotion->setPos(1200, 20);

	hpPotion = new GameObject;
	hpPotion->loadTexture("Resource/GameScene/hpPotion.png");
	hpPotion->setSize(50, 50);
	hpPotion->setPos(1350, 20);


}

void PlayerBar::update()
{
	int hp = Player::GetInstance()->nowHp;
	int mp = Player::GetInstance()->nowMp;
	if (hp <= 0)
		hp = 0;
	if (mp <= 0)
		mp = 0;
	hpBar->size.cx = 300 * hp / Player::GetInstance()->hp;
	mpBar->size.cx = 300 * mp / Player::GetInstance()->mp;

	
}

void PlayerBar::render(PlayerUI* ui)
{
	GraphicManager::GetInstance()->render(hpIcon);
	GraphicManager::GetInstance()->render(mpIcon);
	GraphicManager::GetInstance()->render(hpBar);
	GraphicManager::GetInstance()->render(mpBar);

	GraphicManager::GetInstance()->render(coin);
	GraphicManager::GetInstance()->render(mpPotion);
	GraphicManager::GetInstance()->render(hpPotion);

	// 가진 돈 그리기
	GraphicManager::GetInstance()->drawText(std::to_string(ui->coinNum), { 1080 , 30 }, 30, RGB(255, 255, 255));
	// 가진 체력 포션 그리기
	GraphicManager::GetInstance()->drawText(std::to_string(ui->hpPotionNum), { 1400 , 30 }, 30, RGB(255, 255, 255));
	// 가진 마나 포션 그리기
	GraphicManager::GetInstance()->drawText(std::to_string(ui->mpPotionNum), { 1250 , 30 }, 30, RGB(255, 255, 255));
}

void PlayerBar::release()
{

}