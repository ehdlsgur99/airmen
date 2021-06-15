#include "common.h"

void PlayerUI::init()
{
	// �⺻ HP, MP 100 ����
	swordPower = 10;
	armorPower = 10;
	ringPower = 10;

	hpPotionNum = 1;
	mpPotionNum = 1;
	coinNum = 0;
}

void PlayerUI::update()
{

}

void PlayerUI::render()
{
	GraphicManager::GetInstance()->render(bg);
	GraphicManager::GetInstance()->render(sword);
	GraphicManager::GetInstance()->render(armor);
	GraphicManager::GetInstance()->render(ring);
	GraphicManager::GetInstance()->render(hpPotion);
	GraphicManager::GetInstance()->render(mpPotion);
	GraphicManager::GetInstance()->render(coin);

	// ���� ��� 
	// std::string �� ���ڳ� ���ڿ� ��ȯ �����ؼ� ���
	//GraphicManager::GetInstance()->drawText();
}

void PlayerUI::release()
{

}