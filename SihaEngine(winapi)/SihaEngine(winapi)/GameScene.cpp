#include "common.h"


GameScene::GameScene()
{

}

GameScene::~GameScene()
{
}

void GameScene::init()
{
	gameBg = new GameBG;
	gameBg->init();

	mc = new MonsterControl;
	mc->init();

	isChange = false;

	Player::GetInstance()->init();

	// bgm ���
	//SoundManager::GetInstance()->PlayBg("Resource/bg.mp3");
}

void GameScene::update()
{

	gameBg->update();

	// ĳ���� �ִϸ��̼�
	Player::GetInstance()->update();

	// ���� ��Ʈ�ѷ�
	mc->update();

	if(!isChange)
		render();
}

void GameScene::render()
{
	gameBg->render();
	Player::GetInstance()->render();
	mc->render();
}

void GameScene::release()
{
	isChange = true;
	delete gameBg;
}
