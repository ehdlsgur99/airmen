#include "common.h"

PVPScene::PVPScene()
{
}

PVPScene::~PVPScene()
{
	
}

void PVPScene::init()
{
	//Player::GetInstance()->mappos = 0;
	//Player::GetInstance()->player->setPos(0, 630);

	//배경 및 오브젝트
	bg2 = new GameObject;
	//bg->loadTexture("Resource/PVPScene/far-buildings.png");
	bg2->loadTexture("Resource/village_bg.png");
	bg2->setPos(0, 0);
	//bg2->setSrcSize(1280, 1024);
	bg2->setSize(1600, 900);

	/*backbd = new GameObject;
	backbd->loadTexture("Resource/PVPScene/back-buildings.png");
	backbd->setPos(0, 0);
	backbd->setSrcSize(384, 288);
	backbd->setSize(1600, 900);

	backst = new GameObject;
	backst->loadTexture("Resource/PVPScene/foreground.png");
	backst->setPos(0, 0);
	backst->setSrcSize(384, 288);
	backst->setSize(1600, 900);*/


	//SoundManager::GetInstance()->PlayBg("Resource/bg.mp3");
}

void PVPScene::update()
{
	Player::GetInstance()->update();
	if (InputManager::GetInstance()->getKey(0x4F)) {
		SceneManager::GetInstance()->SceneChange(SceneManager::GetInstance()->eVillage);
	}
}

void PVPScene::render()
{
	GraphicManager::GetInstance()->render(bg2);
	//Player::GetInstance()->render();
}

void PVPScene::release()
{
	//ObjectManager::GetInstance()->release();
}
