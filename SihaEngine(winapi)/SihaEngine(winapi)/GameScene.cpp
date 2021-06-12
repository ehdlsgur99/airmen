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

	// bgm 재생
	//SoundManager::GetInstance()->PlayBg("Resource/bg.mp3");
}

void GameScene::update()
{

	gameBg->update();

	// 캐릭터 애니메이션
	Player::GetInstance()->update();

	// 몬스터 컨트롤러
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
