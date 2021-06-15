#include "common.h"


GameScene::GameScene()
{

}

GameScene::~GameScene()
{
}

void GameScene::init()
{

	endCount = GetTickCount();

	gameBg = new GameBG;
	gameBg->init();

	mc = new MonsterControl;
	mc->init();

	tail = new Tail;
	tail->init();

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

	tail->update();

	if(!isChange)
		render();
	checkEnd();

}

void GameScene::render()
{
	gameBg->render();
	tail->render();

	Player::GetInstance()->render();
	mc->render();

	GraphicManager::GetInstance()->drawText("test", {100, 100}, 20, RGB(255, 255, 255));

	if (isPortal)
		GraphicManager::GetInstance()->render(portal);
}

void GameScene::release()
{
	isChange = true;
	delete gameBg;
}

void GameScene::checkEnd()
{
	// ���ӿ��� ����
	// 1. ���
	// 2. ��Ż ����
	if (GetTickCount() -  endCount >= 10000 && !isPortal)
	{
		createPortal();
	}
	if (isPortal == true)
	{
		portal->pos.x -= 5;
		if (CollisionManager::GetInstance()->RectCollisionCheck(portal, Player::GetInstance()->player))
		{
			// scene ����
			SceneManager::GetInstance()->SceneChange(SceneManager::GetInstance()->eVillage);
			isChange = true;
		}
	}
}

void GameScene::createPortal()
{
	isPortal = true;
	portal = new GameObject;
	portal->loadTexture("Resource/GameScene/portal.png");
	portal->setPos(1600, 550);
	portal->setSize(100, 200);

}