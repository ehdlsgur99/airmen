#include "common.h"

void VillageMG::init()
{
	srand(time(NULL));
	for (int i = 0; i < 3; i++) {
		randbox[i] = rand() % 3;
	}
	

	shop = new GameObject;
	shop->loadTexture("Resource/object/inven.png");
	shop->setSrcSize(295, 386);
	shop->setSize(295, 386);
	shop->setPos(300, 320);

	stuff[0] = new GameObject;
	stuff[0]->loadTexture("Resource/object/sword.png");
	stuff[0]->setSrcSize(16, 16);
	stuff[0]->setSize(64, 64);
	stuff[0]->setPos(325, 403);

	stuff[1] = new GameObject;
	stuff[1]->loadTexture("Resource/object/armor.png");
	stuff[1]->setSrcSize(16, 16);
	stuff[1]->setSize(64, 64);
	stuff[1]->setPos(390, 405);

	stuff[2] = new GameObject;
	stuff[2]->loadTexture("Resource/object/ring.png");
	stuff[2]->setSrcSize(16, 16);
	stuff[2]->setSize(64, 64);
	stuff[2]->setPos(460, 405);

	stuff[3] = new GameObject;
	stuff[3]->loadTexture("Resource/object/potion.png");
	stuff[3]->setSrcSize(16, 16);
	stuff[3]->setSize(64, 64);
	stuff[3]->setPos(330, 533);

	stuff[4] = new GameObject;
	stuff[4]->loadTexture("Resource/object/mppotion.png");
	stuff[4]->setSrcSize(16, 16);
	stuff[4]->setSize(64, 64);
	stuff[4]->setPos(395, 533);

	layer[0] = new GameObject;
	layer[0]->loadTexture("Resource/object/bronze.png");
	layer[0]->setSrcSize(64, 64);
	layer[0]->setSize(64, 64);
	layer[0]->setPos(325, 403);
	layer[1] = new GameObject;
	layer[1]->loadTexture("Resource/object/silver.png");
	layer[1]->setSrcSize(64, 64);
	layer[1]->setSize(64, 64);
	layer[1]->setPos(325, 403);
	layer[2] = new GameObject;
	layer[2]->loadTexture("Resource/object/gold.png");
	layer[2]->setSrcSize(64, 64);
	layer[2]->setSize(64, 64);
	layer[2]->setPos(325, 403);

	layer[3] = new GameObject;
	layer[3]->loadTexture("Resource/object/bronze.png");
	layer[3]->setSrcSize(64, 64);
	layer[3]->setSize(64, 64);
	layer[3]->setPos(390, 403);
	layer[4] = new GameObject;
	layer[4]->loadTexture("Resource/object/silver.png");
	layer[4]->setSrcSize(64, 64);
	layer[4]->setSize(64, 64);
	layer[4]->setPos(390, 403);
	layer[5] = new GameObject;
	layer[5]->loadTexture("Resource/object/gold.png");
	layer[5]->setSrcSize(64, 64);
	layer[5]->setSize(64, 64);
	layer[5]-> setPos(390, 403);

	layer[6] = new GameObject;
	layer[6]->loadTexture("Resource/object/bronze.png");
	layer[6]->setSrcSize(64, 64);
	layer[6]->setSize(64, 64);
	layer[6]->setPos(457, 403);
	layer[7] = new GameObject;
	layer[7]->loadTexture("Resource/object/silver.png");
	layer[7]->setSrcSize(64, 64);
	layer[7]->setSize(64, 64);
	layer[7]->setPos(457, 403);
	layer[8] = new GameObject;
	layer[8]->loadTexture("Resource/object/gold.png");
	layer[8]->setSrcSize(64, 64);
	layer[8]->setSize(64, 64);
	layer[8]->setPos(457, 403);


}
void VillageMG::update()
{	
	
	if (InputManager::GetInstance()->isLButtonDonw && InputManager::GetInstance()->LButtonPos.x > 325 && InputManager::GetInstance()->LButtonPos.x < 389 && InputManager::GetInstance()->LButtonPos.y>403 && InputManager::GetInstance()->LButtonPos.y < 467) {
		Player::GetInstance()->playerUI->Buysword = true;
	}
	if (InputManager::GetInstance()->isLButtonDonw && InputManager::GetInstance()->LButtonPos.x > 390 && InputManager::GetInstance()->LButtonPos.x < 454 && InputManager::GetInstance()->LButtonPos.y>403 && InputManager::GetInstance()->LButtonPos.y < 467) {
		Player::GetInstance()->playerUI->Buyarmor = true;
	}
	if (InputManager::GetInstance()->isLButtonDonw && InputManager::GetInstance()->LButtonPos.x > 460 && InputManager::GetInstance()->LButtonPos.x < 524 && InputManager::GetInstance()->LButtonPos.y>403 && InputManager::GetInstance()->LButtonPos.y < 467) {
		Player::GetInstance()->playerUI->Buyring = true;
	}
	if (InputManager::GetInstance()->isLButtonDonw && InputManager::GetInstance()->LButtonPos.x > 330 && InputManager::GetInstance()->LButtonPos.x < 394 && InputManager::GetInstance()->LButtonPos.y>533 && InputManager::GetInstance()->LButtonPos.y < 597) {
		Player::GetInstance()->playerUI->BuyhpPotion = true;
		Player::GetInstance()->playerUI->hpPotionNum++;
	}
	if (InputManager::GetInstance()->isLButtonDonw && InputManager::GetInstance()->LButtonPos.x > 395 && InputManager::GetInstance()->LButtonPos.x < 459 && InputManager::GetInstance()->LButtonPos.y>533 && InputManager::GetInstance()->LButtonPos.y < 597) {
		Player::GetInstance()->playerUI->BuympPotion = true;
		Player::GetInstance()->playerUI->mpPotionNum++;
	}

}

void VillageMG::render()
{
	GraphicManager::GetInstance()->render(shop);
	for (int i = 0; i < 5; i++) {
		GraphicManager::GetInstance()->render(stuff[i]);
	}
	if (randbox[0] == 0) {
		GraphicManager::GetInstance()->render(layer[0]);
		GraphicManager::GetInstance()->drawText("attack", { 325, 473 }, 10, RGB(0, 0, 0));
		GraphicManager::GetInstance()->drawText("+10", { 335, 483 }, 10, RGB(0, 0, 0));
		Player::GetInstance()->playerUI->swordPower=10;
	}
		
	else if (randbox[0] == 1) {
		GraphicManager::GetInstance()->render(layer[1]);
		GraphicManager::GetInstance()->drawText("attack", { 325, 473 }, 10, RGB(0, 0, 0));
		GraphicManager::GetInstance()->drawText("+30", { 335, 483 }, 10, RGB(0, 0, 0));
		Player::GetInstance()->playerUI->swordPower = 30;
	
	}
		
	else if (randbox[0] == 2) {
		GraphicManager::GetInstance()->render(layer[2]);
		GraphicManager::GetInstance()->drawText("attack", { 325, 473 }, 10, RGB(0, 0, 0));
		GraphicManager::GetInstance()->drawText("+50", { 335, 483 }, 10, RGB(0, 0, 0));
		Player::GetInstance()->playerUI->swordPower = 50;
	}
		

	if (randbox[1] == 0) {
		GraphicManager::GetInstance()->render(layer[3]);
		GraphicManager::GetInstance()->drawText("max hp", { 390, 473 }, 10, RGB(0, 0, 0));
		GraphicManager::GetInstance()->drawText("+20", { 400, 483 }, 10, RGB(0, 0, 0));
		Player::GetInstance()->playerUI->armorPower = 20;
	}
		
	else if (randbox[1] == 1) {
		GraphicManager::GetInstance()->render(layer[4]);
		GraphicManager::GetInstance()->drawText("max hp", { 390, 473 }, 10, RGB(0, 0, 0));
		GraphicManager::GetInstance()->drawText("+50", { 400, 483 }, 10, RGB(0, 0, 0));
		Player::GetInstance()->playerUI->armorPower = 50;
	}
		
	else if (randbox[1] == 2) {
		GraphicManager::GetInstance()->render(layer[5]);
		GraphicManager::GetInstance()->drawText("max hp", { 390, 473 }, 10, RGB(0, 0, 0));
		GraphicManager::GetInstance()->drawText("+100", { 400, 483 }, 10, RGB(0, 0, 0));
		Player::GetInstance()->playerUI->armorPower = 100;
	}
		

	if (randbox[2] == 0){
		GraphicManager::GetInstance()->render(layer[6]);
		GraphicManager::GetInstance()->drawText("max mp", { 463, 473 }, 10, RGB(0, 0, 0));
		GraphicManager::GetInstance()->drawText("+20", { 477, 483 }, 10, RGB(0, 0, 0));
		Player::GetInstance()->playerUI->ringPower = 20;
	}
		
	else if (randbox[2] == 1) {
		GraphicManager::GetInstance()->render(layer[7]);
		GraphicManager::GetInstance()->drawText("max mp", { 463, 473 }, 10, RGB(0, 0, 0));
		GraphicManager::GetInstance()->drawText("+50", { 477, 483 }, 10, RGB(0, 0, 0));
		Player::GetInstance()->playerUI->ringPower = 50;
	}
		
	else if (randbox[2] == 2) {
		GraphicManager::GetInstance()->render(layer[8]);
		GraphicManager::GetInstance()->drawText("max mp", { 463, 473 }, 10, RGB(0, 0, 0));
		GraphicManager::GetInstance()->drawText("+100", { 477, 483 }, 10, RGB(0, 0, 0));
		Player::GetInstance()->playerUI->ringPower = 100;

	}
	GraphicManager::GetInstance()->drawText("hp", { 345, 603 }, 10, RGB(0, 0, 0));
	GraphicManager::GetInstance()->drawText("+20", { 335, 613 }, 10, RGB(0, 0, 0));

	GraphicManager::GetInstance()->drawText("mp", { 410, 603 }, 10, RGB(0, 0, 0));
	GraphicManager::GetInstance()->drawText("+20", { 400, 613 }, 10, RGB(0, 0, 0));
	
		
}

void VillageMG::release()
{

}