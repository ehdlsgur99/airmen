#include "common.h"

void PlayerUI::init()
{
	// 기본 HP, MP 100 설정
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

	// 개수 출력 
	// std::string 라서 숫자나 문자열 변환 응용해서 출력
	//GraphicManager::GetInstance()->drawText();
}

void PlayerUI::release()
{

}