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

	isDie = false;

	isChange = false;

	Player::GetInstance()->init();


	// bgm 재생
	//SoundManager::GetInstance()->PlayBg("Resource/bg.mp3");
}

void GameScene::update()
{

	if (isDie)
	{
		if (die->alpha <= 255)
		{
			die->alpha += 1;
		}
		else
		{
			if (InputManager::GetInstance()->isKeyDown)
			{
				PostQuitMessage(0);
			}
		}
		render();
		return;
	}

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
	if (isDie)
	{
		GraphicManager::GetInstance()->render(die);
		return;
	}

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
		isDie = true;
		die = new GameObject;
		die->loadTexture("Resource/die.png");
		die->setSize(1600, 900);
		die->setPos(0, 0);
		die->alpha = 0;
	}
	// 2. 포탈 도달
	if (GetTickCount() -  endCount >= 20000 && !isPortal)
	{
		createPortal();
	}
	if (isPortal == true)
	{
		if(Player::GetInstance()->state == eRight || Player::GetInstance()->state == eJump2 || Player::GetInstance()->state == eJump1)
			portal->pos.x -= 4;
		if (CollisionManager::GetInstance()->RectCollisionCheck(portal, Player::GetInstance()->player))
		{
			Player::GetInstance()->nowHp = Player::GetInstance()->hp;
			Player::GetInstance()->nowMp = Player::GetInstance()->mp;
			Player::GetInstance()->level++;
			Player::GetInstance()->isJump = false;
			Player::GetInstance()->isAttack = false;
			Player::GetInstance()->isSmash = false;
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
	if (Player::GetInstance()->level % 2 == 1)
	{
		portal->setPos(1600, 522);
	}
	else
	{
		portal->setPos(1600, 516);
	}

	portal->setSize(200, 200);

}