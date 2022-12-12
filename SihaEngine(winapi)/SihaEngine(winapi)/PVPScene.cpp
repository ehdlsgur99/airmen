#include "common.h"

PVPScene::PVPScene()
{
	
}

PVPScene::~PVPScene()
{
	
}

void PVPScene::init()
{
	GameSet = false;
	winX = -1;
	winY = -1;

	// 아이디가 높은 플레이어가 오른쪽으로 간다.
	if (Player::GetInstance()->userInfo.ID > Player::GetInstance()->enemyInfo.ID)
	{
		Player::GetInstance()->player->setPos(1400, 630);
		Player::GetInstance()->userInfo.x = 1400;
		Player::GetInstance()->dir = eLeft;

		OtherPlayer::GetInstance()->Oplayer->setPos(0, 630);
		OtherPlayer::GetInstance()->dir = eRight;

	}
	else
	{
		Player::GetInstance()->player->setPos(0, 630);
		Player::GetInstance()->userInfo.x = 0;
		Player::GetInstance()->dir = eRight;
		OtherPlayer::GetInstance()->Oplayer->setPos(1400, 630);
		OtherPlayer::GetInstance()->dir = eLeft;

	}



	Player::GetInstance()->userInfo.maxhp = Player::GetInstance()->hp;
	Player::GetInstance()->userInfo.maxmp = Player::GetInstance()->mp;
	Player::GetInstance()->userInfo.power = Player::GetInstance()->power;
	
	//배경 및 오브젝트
	bg = new GameObject;
	bg->loadTexture("Resource/PVPScene/far-buildings.png");
	
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

	portal = new GameObject;
	portal->loadTexture("Resource/GameScene/portal1.png");
	portal->setPos(700, 522);
	portal->setSize(200, 630);
	crown = new GameObject;
	crown->loadTexture("Resource/GameScene/crown.png");
	crown->setSrcSize(130, 104);
	crown->setSize(130, 104);
	
	for (int i = 0; i < GROUNDINDEX; i++) {
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

	for (int i = 0; i < GROUNDINDEX; i++) {
		ObjectManager::GetInstance()->addObject(ground[i]);
	}
	SoundManager::GetInstance()->PlayBg("stop ", "Resource/bg.mp3");
	SoundManager::GetInstance()->PlayBg("play ","Resource/PVPScene/cyberpunk-street.mp3");
}

void PVPScene::update()
{
	if (Player::GetInstance()->nowHp <= 0)
	{
		GameSet = true;
		winX = OtherPlayer::GetInstance()->Oplayer->pos.x;
		winY = OtherPlayer::GetInstance()->Oplayer->pos.y;
	}
	else if (OtherPlayer::GetInstance()->nowHp <= 0)
	{
		GameSet = true;
		winX = Player::GetInstance()->player->pos.x;
		winY = Player::GetInstance()->player->pos.y;
	}
	if (GameSet)
	{
		Player::GetInstance()->userInfo.isPvP = false;
		if (CollisionManager::GetInstance()->RectCollisionCheck(portal, Player::GetInstance()->player))
		{
			Player::GetInstance()->nowHp = Player::GetInstance()->hp;
			Player::GetInstance()->nowMp = Player::GetInstance()->mp;
			SceneManager::GetInstance()->SceneChange(SceneManager::GetInstance()->eVillage);
			GameSet = false;
		}
	}
	
	PVPinfoRS();
	
	Player::GetInstance()->update();
	OtherPlayer::GetInstance()->update();
	render();
	
	if (InputManager::GetInstance()->getKey(0x4F)) {
		SceneManager::GetInstance()->SceneChange(SceneManager::GetInstance()->eVillage);
		SoundManager::GetInstance()->PlayBg("stop ", "Resource/PVPScene/cyberpunk-street.mp3");
	}
	
}

void PVPScene::render()
{
	GraphicManager::GetInstance()->render(bg);
	GraphicManager::GetInstance()->render(backbd);
	GraphicManager::GetInstance()->render(backst);
	for (int i = 0; i < GROUNDINDEX; i++) {
		GraphicManager::GetInstance()->render(ground[i]);
	}
	if (GameSet)
	{
		portal->animation("Resource/GameScene/portal", 5, 100);
		GraphicManager::GetInstance()->render(portal);
		crown->setPos(winX, winY);
		GraphicManager::GetInstance()->render(crown);
	}
	Player::GetInstance()->render();
	OtherPlayer::GetInstance()->render();
}

void PVPScene::release()
{
	ObjectManager::GetInstance()->release();
}
void PVPinfoRS() 
{
	int crushPower = 50;
	Player::GetInstance()->userInfo.x = Player::GetInstance()->player->pos.x;
	Player::GetInstance()->userInfo.y = Player::GetInstance()->player->pos.y;
	Player::GetInstance()->userInfo.dir = Player::GetInstance()->dir;
	Player::GetInstance()->userInfo.state = Player::GetInstance()->state;
	Player::GetInstance()->userInfo.nowhp = Player::GetInstance()->nowHp;
	Player::GetInstance()->userInfo.nowmp = Player::GetInstance()->nowMp;
	Player::GetInstance()->userInfo.power = Player::GetInstance()->power;
	Player::GetInstance()->userInfo.isSmash = Player::GetInstance()->isSmash;

	if (Player::GetInstance()->state == eAttack1 || Player::GetInstance()->state == eAttack2)
	{
		if (CollisionManager::GetInstance()->RectCollisionCheck(Player::GetInstance()->player, OtherPlayer::GetInstance()->Oplayer))
		{
			OtherPlayer::GetInstance()->state = eAttacked;
			OtherPlayer::GetInstance()->nowHp -= Player::GetInstance()->power;
			if (Player::GetInstance()->dir == eLeft)
			{
				OtherPlayer::GetInstance()->Oplayer->pos.x -= crushPower;
			}
			else if (Player::GetInstance()->dir == eRight)
			{
				OtherPlayer::GetInstance()->Oplayer->pos.x += crushPower;
			}





		}
	}

	if (OtherPlayer::GetInstance()->state == eAttack1 || OtherPlayer::GetInstance()->state == eAttack2)
	{
		if (CollisionManager::GetInstance()->RectCollisionCheck(OtherPlayer::GetInstance()->Oplayer, Player::GetInstance()->player))
		{
			Player::GetInstance()->state = eAttacked;
			Player::GetInstance()->nowHp -= OtherPlayer::GetInstance()->power;
			if (OtherPlayer::GetInstance()->dir == eLeft)
			{
				Player::GetInstance()->player->pos.x -= crushPower;
			}
			else if (OtherPlayer::GetInstance()->dir == eRight)
			{
				Player::GetInstance()->player->pos.x += crushPower;
			}

		}
	}
	if (CollisionManager::GetInstance()->RectCollisionCheck(OtherPlayer::GetInstance()->Osmash, Player::GetInstance()->player))
	{
		Player::GetInstance()->state = eAttacked;
		Player::GetInstance()->nowHp -= OtherPlayer::GetInstance()->power;
	}
	if (CollisionManager::GetInstance()->RectCollisionCheck(Player::GetInstance()->smash, OtherPlayer::GetInstance()->Oplayer))
	{
		OtherPlayer::GetInstance()->state = eAttacked;
		OtherPlayer::GetInstance()->nowHp -= Player::GetInstance()->power;
	}
}
