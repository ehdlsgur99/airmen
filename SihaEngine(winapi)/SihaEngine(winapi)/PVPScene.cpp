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

	//��� �� ������Ʈ
	bg = new GameObject;
	bg->loadTexture("Resource/PVPScene/far-buildings.png");
	//bg->loadTexture("Resource/village_bg.png");
	bg->setPos(0, 0);
	//bg->setSrcSize(1280, 1024);
	bg->setSize(1600, 900);

	backbd = new GameObject;
	backbd->loadTexture("Resource/PVPScene/back-buildings.png");
	backbd->setPos(0, 0);
	backbd->setSrcSize(256, 192);
	backbd->setSize(1600, 900);

	backst = new GameObject;
	backst->loadTexture("Resource/PVPScene/foreground.png");
	backst->setPos(0, 0);
	backst->setSrcSize(352, 192);
	backst->setSize(1600, 900);

	for (int i = 0; i < 50; i++) {
		if (i % 2 == 0) {
			ground[i] = new GameObject;
			ground[i]->loadTexture("Resource/object/ground.png");
			ground[i]->setPos(ground[i]->pos.x, 734);
			ground[i]->setSrcSize(16, 48);
			ground[i]->setSize(48, 170);
		}
		else {
			ground[i] = new GameObject;
			ground[i]->loadTexture("Resource/object/ground-b.png");
			ground[i]->setPos(ground[i]->pos.x, 734);
			ground[i]->setSrcSize(16, 48);
			ground[i]->setSize(48, 170);
		}
		if (i == 0) continue;

		ground[i]->pos.x = ground[i - 1]->pos.x + 48;
	}

	for (int i = 0; i < 50; i++) {
		ObjectManager::GetInstance()->addObject(ground[i]);
	}
	//SoundManager::GetInstance()->PlayBg("Resource/bg.mp3");
}

void PVPScene::update()
{
	Player::GetInstance()->update();
	render();
	if (InputManager::GetInstance()->getKey(0x4F)) {
		SceneManager::GetInstance()->SceneChange(SceneManager::GetInstance()->eVillage);
	}
	
}

void PVPScene::render()
{
	GraphicManager::GetInstance()->render(bg);
	GraphicManager::GetInstance()->render(backbd);
	GraphicManager::GetInstance()->render(backst);
	for (int i = 0; i < 50; i++) {
		GraphicManager::GetInstance()->render(ground[i]);
	}
	Player::GetInstance()->render();
}

void PVPScene::release()
{
	//ObjectManager::GetInstance()->release();
}