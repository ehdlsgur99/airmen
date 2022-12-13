#include "common.h"

PVPScene::PVPScene()
{
	
}

PVPScene::~PVPScene()
{
	
}

void PVPScene::init()
{
	winX = -1000;
	winY = -1000;

	//tail = new Tail;
	//tail->init();

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
	portal->setPos(700, 630);
	portal->setSize(100, 161);

	crown = new GameObject;
	crown->loadTexture("Resource/GameScene/crown.png");
	crown->setSize(30, 30);
	
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
	//SoundManager::GetInstance()->PlayBg("stop ", "Resource/bg.mp3");
	//SoundManager::GetInstance()->PlayBg("play ","Resource/PVPScene/cyberpunk-street.mp3");
}

void PVPScene::update()
{
	
	// ==================================================== 
	// 상대방 강제 종료 확인 코드
	// ====================================================
	// 수정 필요 ############################################

	Player::GetInstance()->getUserInfo();
	if (Player::GetInstance()->enemyInfo.DataType == eDataType::eExit)
	{
		Player::GetInstance()->userInfo.DataType = eDataType::eNone;
		Player::GetInstance()->getUserInfo();
		Player::GetInstance()->enemyInfo = UserInfo();
		Player::GetInstance()->userInfo.isPvP = false;
		Player::GetInstance()->userInfo.PVPID = -1;
		SceneManager::GetInstance()->SceneChange(SceneManager::eVillage);
		// 상대방이 강제 종료한 경우입니다.
	}
	
	
	//CHECK WINNER
	if (Player::GetInstance()->nowHp < 0)
	{
		GameSet = true;
		winX = OtherPlayer::GetInstance()->Oplayer->pos.x;
		winY = OtherPlayer::GetInstance()->Oplayer->pos.y;
	}
	else if (OtherPlayer::GetInstance()->nowHp < 0)
	{
		GameSet = true;
		winX = Player::GetInstance()->player->pos.x;
		winY = Player::GetInstance()->player->pos.y;
	}
	if (GameSet)
	{
		crown->setPos(winX, winY);
		portal->animation("Resource/GameScene/portal", 5, 100);
		if (CollisionManager::GetInstance()->RectCollisionCheck(portal, Player::GetInstance()->player))
		{
			Player::GetInstance()->userInfo.DataType = eDataType::eNone;
			Player::GetInstance()->userInfo.isPvP = false;
			Player::GetInstance()->nowHp = Player::GetInstance()->userInfo.maxhp;
			Player::GetInstance()->nowMp = Player::GetInstance()->userInfo.maxmp;
			SceneManager::GetInstance()->SceneChange(SceneManager::GetInstance()->eVillage);
			GameSet = false;
		}
	}
	
	//pvp INFO
	Player::GetInstance()->userInfo.x = Player::GetInstance()->player->pos.x;
	Player::GetInstance()->userInfo.y = Player::GetInstance()->player->pos.y;
	Player::GetInstance()->userInfo.dir = Player::GetInstance()->dir;
	Player::GetInstance()->userInfo.state = Player::GetInstance()->state;
	Player::GetInstance()->userInfo.nowhp = Player::GetInstance()->nowHp;
	Player::GetInstance()->userInfo.nowmp = Player::GetInstance()->nowMp;
	Player::GetInstance()->userInfo.power = Player::GetInstance()->power;
	Player::GetInstance()->userInfo.isSmash = Player::GetInstance()->isSmash;

	int range = 0;
	if (Player::GetInstance()->state == eAttack1 || Player::GetInstance()->state == eAttack2)
	{
		if (CollisionManager::GetInstance()->RectCollisionCheck(Player::GetInstance()->player- range, OtherPlayer::GetInstance()->Oplayer))
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
		if (CollisionManager::GetInstance()->RectCollisionCheck(OtherPlayer::GetInstance()->Oplayer- range, Player::GetInstance()->player))
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
		Player::GetInstance()->nowHp -= OtherPlayer::GetInstance()->power+30;
		OtherPlayer::GetInstance()->isSmash = false;
		OtherPlayer::GetInstance()->Osmash->pos.x = -1000;

	}
	if (CollisionManager::GetInstance()->RectCollisionCheck(Player::GetInstance()->smash, OtherPlayer::GetInstance()->Oplayer))
	{
		OtherPlayer::GetInstance()->state = eAttacked;
		OtherPlayer::GetInstance()->nowHp -= Player::GetInstance()->power+30;
		Player::GetInstance()->isSmash = false;
		Player::GetInstance()->smash->pos.x = -1000;
		
	}
	

	Player::GetInstance()->update();
	OtherPlayer::GetInstance()->update();

	//Player::GetInstance()->gravity(tail);
	//tail->update();

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
		GraphicManager::GetInstance()->render(portal);
		GraphicManager::GetInstance()->render(crown);
	}

	
	Player::GetInstance()->render();
	OtherPlayer::GetInstance()->render();
	//tail->render();
}

void PVPScene::release()
{
	ObjectManager::GetInstance()->release();
}
