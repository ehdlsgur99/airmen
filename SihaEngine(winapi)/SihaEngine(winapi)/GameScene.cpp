#include "common.h"


GameScene::GameScene()
{

}

GameScene::~GameScene()
{
}

void GameScene::init()
{
	startTime = GetTickCount();

	endCount = GetTickCount();

	gameBg = new GameBG;
	gameBg->init();

	mc = new MonsterControl;
	mc->init();

	tail = new Tail;
	tail->init();

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
	Player::GetInstance()->gravity(tail);

	// 몬스터 컨트롤러
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

	
	mc->render();

	

	if (isPortal)
	{
		portal->animation("Resource/GameScene/portal", 5, 100);
		GraphicManager::GetInstance()->render(portal);
	}

	if (GetTickCount() - startTime <= 5000)
	{
		std::string str = "STAGE" + std::to_string(Player::GetInstance()->level);
		GraphicManager::GetInstance()->drawText(str, { 450, 400 }, 80, RGB(255, 255, 255));
	}

	Player::GetInstance()->render();
	
}

void GameScene::release()
{
	isChange = true;
	delete gameBg;
}

void GameScene::checkEnd()
{
	// 게임엔딩 조건
	// 1. 사망
	if (Player::GetInstance()->nowHp <= 0)
	{

	}
	// 2. 포탈 도달
	if (GetTickCount() -  endCount >= 10000 && !isPortal)
	{
		createPortal();
	}
	if (isPortal == true)
	{
		if(Player::GetInstance()->state == eRight || Player::GetInstance()->state == eJump2 || Player::GetInstance()->state == eJump1)
		portal->pos.x -= 7;
		if (CollisionManager::GetInstance()->RectCollisionCheck(portal, Player::GetInstance()->player))
		{
			Player::GetInstance()->nowHp = Player::GetInstance()->hp;
			Player::GetInstance()->nowMp = Player::GetInstance()->mp;
			Player::GetInstance()->level++;
			// scene 변경
			SceneManager::GetInstance()->SceneChange(SceneManager::GetInstance()->eVillage);
			isChange = true;
		}
	}
}

void GameScene::createPortal()
{
	isPortal = true;
	portal = new GameObject;
	portal->loadTexture("Resource/GameScene/portal1.png");
	portal->setPos(1600, 525);
	portal->setSize(200, 200);

}