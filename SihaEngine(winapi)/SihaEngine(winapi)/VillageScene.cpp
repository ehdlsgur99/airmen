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
	bg->loadTexture("Resource/village.png");
	bg->setPos(0, 0);
	bg->setSize(1280,1024);	
	
	SoundManager::GetInstance()->PlayBg("Resource/bg.mp3");
}

void VillageScene::update()
{
	
}

void VillageScene::render()
{
	GraphicManager::GetInstance()->render(bg);
}

void VillageScene::release()
{

}

