#include "common.h"

void VillageMG::init()
{
		
	shop = new GameObject;
	shop->loadTexture("Resource/object/inven.png");
	shop->setSrcSize(343, 300);
	shop->setSize(343, 300);
	shop->setPos(300, 320);

	stuff[0] = new GameObject;
	stuff[0]->loadTexture("Resource/object/potion.png");
	stuff[0]->setSrcSize(16, 16);
	stuff[0]->setSize(57, 50);
	stuff[0]->setPos(310, 320);
	stuff[1] = new GameObject;
	stuff[1]->loadTexture("Resource/object/sword.png");
	stuff[1]->setSrcSize(16, 16);
	stuff[1]->setSize(57, 50);
	stuff[1]->setPos(377, 325);
	stuff[2] = new GameObject;
	stuff[2]->loadTexture("Resource/object/arrow.png");
	stuff[2]->setSrcSize(16, 16);
	stuff[2]->setSize(57, 50);
	stuff[2]->setPos(444, 325);



}
void VillageMG::update()
{
	
}

void VillageMG::render()
{
	GraphicManager::GetInstance()->render(shop);
	for (int i = 0; i < 3; i++) {
		GraphicManager::GetInstance()->render(stuff[i]);
	}
}

void VillageMG::release()
{

}