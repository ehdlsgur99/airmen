#include "common.h"

void PlayerUI::init()
{
	// 기본 HP, MP 100 설정
	swordPower = 10;
	armorPower = 10;
	ringPower = 10;

	hpPotionNum = 1;
	mpPotionNum = 1;
	coinNum = 1000;

	 Buysword=false;
	 Buyarmor = false;
	 Buyring = false;
	 BuyhpPotion = false;
	 BuympPotion = false;

	bg = new GameObject;
	bg->loadTexture("Resource/object/inventory.png");
	bg->setSrcSize(314, 370);
	bg->setSize(414, 570);
	bg->setPos(800, 135);

	sword = new GameObject;
	sword->loadTexture("Resource/object/sword.png");
	sword->setSrcSize(16, 16);
	sword->setSize(64, 64);
	sword->setPos(835, 350);

	armor = new GameObject;
	armor->loadTexture("Resource/object/armor.png");
	armor->setSrcSize(16, 16);
	armor->setSize(64, 64);
	armor->setPos(835, 450);

	ring = new GameObject;
	ring->loadTexture("Resource/object/ring.png");
	ring->setSrcSize(16, 16);
	ring->setSize(64, 64);
	ring->setPos(835, 550);

	hpPotion = new GameObject;
	hpPotion->loadTexture("Resource/object/potion.png");
	hpPotion->setSrcSize(16, 16);
	hpPotion->setSize(64, 64);
	hpPotion->setPos(835, 235);

	mpPotion = new GameObject;
	mpPotion->loadTexture("Resource/object/mppotion.png");
	mpPotion->setSrcSize(16, 16);
	mpPotion->setSize(64, 64);
	mpPotion->setPos(900, 235);

	/// <summary>
	/// //////////////////////////////////////////////////////////////////////////////////////////////////////
	/// </summary>
	layer[0] = new GameObject;
	layer[0]->loadTexture("Resource/object/bronze.png");
	layer[0]->setSrcSize(64, 64);
	layer[0]->setSize(64, 64);
	layer[0]->setPos(835, 350);
	layer[1] = new GameObject;
	layer[1]->loadTexture("Resource/object/silver.png");
	layer[1]->setSrcSize(64, 64);
	layer[1]->setSize(64, 64);
	layer[1]->setPos(835, 350);
	layer[2] = new GameObject;
	layer[2]->loadTexture("Resource/object/gold.png");
	layer[2]->setSrcSize(64, 64);
	layer[2]->setSize(64, 64);
	layer[2]->setPos(835, 350);

	layer[3] = new GameObject;
	layer[3]->loadTexture("Resource/object/bronze.png");
	layer[3]->setSrcSize(64, 64);
	layer[3]->setSize(64, 64);
	layer[3]->setPos(835, 450);
	layer[4] = new GameObject;
	layer[4]->loadTexture("Resource/object/silver.png");
	layer[4]->setSrcSize(64, 64);
	layer[4]->setSize(64, 64);
	layer[4]->setPos(835, 450);
	layer[5] = new GameObject;
	layer[5]->loadTexture("Resource/object/gold.png");
	layer[5]->setSrcSize(64, 64);
	layer[5]->setSize(64, 64);
	layer[5]->setPos(835, 450);

	layer[6] = new GameObject;
	layer[6]->loadTexture("Resource/object/bronze.png");
	layer[6]->setSrcSize(64, 64);
	layer[6]->setSize(64, 64);
	layer[6]->setPos(835, 550);
	layer[7] = new GameObject;
	layer[7]->loadTexture("Resource/object/silver.png");
	layer[7]->setSrcSize(64, 64);
	layer[7]->setSize(64, 64);
	layer[7]->setPos(835, 550);
	layer[8] = new GameObject;
	layer[8]->loadTexture("Resource/object/gold.png");
	layer[8]->setSrcSize(64, 64);
	layer[8]->setSize(64, 64);
	layer[8]->setPos(835, 550);
	
	
}

void PlayerUI::update()
{
	
}

void PlayerUI::render()
{
	
	GraphicManager::GetInstance()->render(bg);
	if (Buysword) {
		GraphicManager::GetInstance()->render(sword);
		GraphicManager::GetInstance()->drawText("공격력+", { 940, 380 }, 10, RGB(0, 0, 0));
		GraphicManager::GetInstance()->drawText(std::to_string(swordPower), { 1020, 380 }, 10, RGB(0, 0, 0));
		//stat
		GraphicManager::GetInstance()->drawText("공격력:", { 1090, 380 }, 10, RGB(0, 0, 0));
		GraphicManager::GetInstance()->drawText(std::to_string(swordPower+10), { 1155, 380 }, 10, RGB(0, 0, 0));
		if(swordPower==10){
			GraphicManager::GetInstance()->render(layer[0]);
		}
		else if(swordPower == 30) {
			GraphicManager::GetInstance()->render(layer[1]);
		}
		else if (swordPower == 50) {
			GraphicManager::GetInstance()->render(layer[2]);
		}
	}
	
	if (Buyarmor) {
		GraphicManager::GetInstance()->render(armor);
		GraphicManager::GetInstance()->drawText("체력+", { 940, 480 }, 10, RGB(0, 0, 0));
		GraphicManager::GetInstance()->drawText(std::to_string(armorPower), { 1020, 480 }, 10, RGB(0, 0, 0));
		//stat
		GraphicManager::GetInstance()->drawText("체력:", { 1090, 450 }, 10, RGB(0, 0, 0));
		GraphicManager::GetInstance()->drawText(std::to_string(armorPower+100), { 1140, 450 }, 10, RGB(0, 0, 0));
		if (armorPower == 20) {
			GraphicManager::GetInstance()->render(layer[3]);
		}
		else if (armorPower == 50) {
			GraphicManager::GetInstance()->render(layer[4]);
		}
		else if (armorPower == 100) {
			GraphicManager::GetInstance()->render(layer[5]);
		}
	}
	if (Buyring) {
		GraphicManager::GetInstance()->render(ring);
		GraphicManager::GetInstance()->drawText("마나+", { 940, 580 }, 10, RGB(0, 0, 0));
		GraphicManager::GetInstance()->drawText(std::to_string(ringPower), { 1020, 580 }, 10, RGB(0, 0, 0));
		//stat
		GraphicManager::GetInstance()->drawText("마나:", { 1090, 510 }, 10, RGB(0, 0, 0));
		GraphicManager::GetInstance()->drawText(std::to_string(ringPower+100), { 1140, 510 }, 10, RGB(0, 0, 0));
		if (ringPower == 20) {
			GraphicManager::GetInstance()->render(layer[6]);
		}
		else if (ringPower == 50) {
			GraphicManager::GetInstance()->render(layer[7]);
		}
		else if (ringPower == 100) {
			GraphicManager::GetInstance()->render(layer[8]);
		}
	}
	
	
		GraphicManager::GetInstance()->render(hpPotion);
		GraphicManager::GetInstance()->drawText(std::to_string(hpPotionNum), { 870, 290 }, 10, RGB(0, 0, 0));
	

	
		GraphicManager::GetInstance()->render(mpPotion);
		GraphicManager::GetInstance()->drawText(std::to_string(mpPotionNum), { 934, 290 }, 10, RGB(0, 0, 0));
	
	GraphicManager::GetInstance()->drawText(std::to_string(coinNum), { 1145, 245 }, 10, RGB(0, 0, 0));
	
	
	// 개수 출력 
	// std::string 라서 숫자나 문자열 변환 응용해서 출력
	//GraphicManager::GetInstance()->drawText();
}

void PlayerUI::release()
{

}