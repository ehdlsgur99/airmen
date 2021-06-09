#include "common.h"

VillageScene::VillageScene()
{

}

VillageScene::~VillageScene()
{

}

void VillageScene::init()
{
	bg = new GameObject;
	bg->loadTexture("Resource/village_bg.png");
	bg->setPos(0, 0);
	bg->setSrcSize(1280, 1024);
	bg->setSize(1600, 900);
	
	mg = new GameObject;
	mg->loadTexture("Resource/village_mg.png");
	mg->setPos(0,0);
	mg->setSrcSize(384, 288);
	mg->setSize(1600, 900);

	for(int i=0;i<40;i++){
		if (i % 2 == 0) {
			ground[i] = new GameObject;
			ground[i]->loadTexture("Resource/obj/ground.png");
			ground[i]->setPos(groundx, 734);
			ground[i]->setSrcSize(16, 48);
			ground[i]->setSize(48, 170);
		}
		else {
			ground[i] = new GameObject;
			ground[i]->loadTexture("Resource/obj/ground-b.png");
			ground[i]->setPos(groundx, 734);
			ground[i]->setSrcSize(16, 48);
			ground[i]->setSize(48, 170);
		}
		groundx += 48;
	}
	house[0] = new GameObject;
	house[0]->loadTexture("Resource/obj/house-a.png");
	house[0]->setPos(-50, 217);
	house[0]->setSrcSize(168, 183);
	house[0]->setSize(504,549);
	house[1] = new GameObject;
	house[1]->loadTexture("Resource/obj/house-b.png");
	house[1]->setPos(600,35);
	house[1]->setSrcSize(210, 244);
	house[1]->setSize(630, 732);
	house[2] = new GameObject;
	house[2]->loadTexture("Resource/obj/house-c.png");
	house[2]->setPos(1250, 217);
	house[2]->setSrcSize(221, 183);
	house[2]->setSize(663, 549);
	
	box[0] = new GameObject;
	box[0]->loadTexture("Resource/obj/crate-stack.png");
	box[0]->setPos(510, 573);
	box[0]->setSrcSize(73, 68);
	box[0]->setSize(200, 194);

	obj[0] = new GameObject;
	obj[0]->loadTexture("Resource/obj/sign.png");
	obj[0]->setPos(910, 573);
	obj[0]->setSrcSize(37, 45);
	obj[0]->setSize(74, 90);
	obj[1] = new GameObject;
	obj[1]->loadTexture("Resource/obj/barrel.png");
	obj[1]->setPos(1070, 688);
	obj[1]->setSrcSize(24, 30);
	obj[1]->setSize(72, 90);
	obj[2] = new GameObject;
	obj[2]->loadTexture("Resource/obj/barrel.png");
	obj[2]->setPos(1142, 688);
	obj[2]->setSrcSize(24, 30);
	obj[2]->setSize(72, 90);
	Player::GetInstance()->init();
	
	SoundManager::GetInstance()->PlayBg("Resource/bg.mp3");
}

void VillageScene::update()
{
	Player::GetInstance()->update();
	render();
}

void VillageScene::render()
{
	GraphicManager::GetInstance()->render(bg);

	GraphicManager::GetInstance()->render(mg);
	for (int i = 0; i < 40; i++) {
		GraphicManager::GetInstance()->render(ground[i]);
	}
	GraphicManager::GetInstance()->render(house[0]);
	GraphicManager::GetInstance()->render(house[1]);
	GraphicManager::GetInstance()->render(house[2]);

	GraphicManager::GetInstance()->render(box[0]);
	for (int i = 0; i < 3; i++) {
		GraphicManager::GetInstance()->render(obj[i]);
	}
	Player::GetInstance()->render();

}

void VillageScene::release()
{
	Player::GetInstance()->release();

}

