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
	bg->setSize(1280, 1024);
	
	mg = new GameObject;
	mg->loadTexture("Resource/village_mg.png");
	mg->setPos(0,0);
	mg->setSrcSize(384, 288);
	mg->setSize(1280, 1024);

	for(int i=0;i<27;i++){
		if (i % 2 == 0) {
			ground[i] = new GameObject;
			ground[i]->loadTexture("Resource/ground.png");
			ground[i]->setPos(groundx, 854);
			ground[i]->setSrcSize(16, 48);
			ground[i]->setSize(48, 170);
		}
		else {
			ground[i] = new GameObject;
			ground[i]->loadTexture("Resource/ground-b.png");
			ground[i]->setPos(groundx, 854);
			ground[i]->setSrcSize(16, 48);
			ground[i]->setSize(48, 170);
		}
		groundx += 48;
	}
	house1 = new GameObject;
	house1->loadTexture("Resource/house-a.png");
	house1->setPos(0, 337);
	house1->setSrcSize(168, 183);
	house1->setSize(504,549);
	house2 = new GameObject;
	house2->loadTexture("Resource/house-b.png");
	house2->setPos(600,156);
	house2->setSrcSize(210, 244);
	house2->setSize(630, 732);
	
	
	SoundManager::GetInstance()->PlayBg("Resource/bg.mp3");
}

void VillageScene::update()
{
	render();
}

void VillageScene::render()
{
	GraphicManager::GetInstance()->render(bg);
	GraphicManager::GetInstance()->render(mg);
	for (int i = 0; i < 27; i++) {
		GraphicManager::GetInstance()->render(ground[i]);
	}
	GraphicManager::GetInstance()->render(house1);
	GraphicManager::GetInstance()->render(house2);
}

void VillageScene::release()
{

}

