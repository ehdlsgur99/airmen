#include "common.h"

VillageScene::VillageScene()
{

}

VillageScene::~VillageScene()
{

}

void VillageScene::init()
{
	pvpButton = new PVPButton();


	Player::GetInstance()->mappos = 0;
	Player::GetInstance()->player->setPos(0, 630);

	//배경 및 오브젝트
	bg = new GameObject;
	bg->loadTexture("Resource/village_bg.png");
	bg->setPos(0, 0);
	bg->setSrcSize(1280, 1024);
	bg->setSize(1600, 900);
	
	mg = new GameObject;
	mg->loadTexture("Resource/village_mg.png");
	mg->setPos(0,0);
	mg->setSrcSize(384, 288);
	mg->setSize(1600, 900);

	for(int i=0;i<70;i++){
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
		
		ground[i]->pos.x = ground[i-1]->pos.x+48;
	}
	house[0] = new GameObject;
	house[0]->loadTexture("Resource/object/house-a.png");
	house[0]->setPos(-50, 217);
	house[0]->setSrcSize(168, 183);
	house[0]->setSize(504,549);
	house[1] = new GameObject;
	house[1]->loadTexture("Resource/object/house-b.png");
	house[1]->setPos(600 ,35);
	house[1]->setSrcSize(210, 244);
	house[1]->setSize(630, 732);
	house[2] = new GameObject;
	house[2]->loadTexture("Resource/object/house-c.png");
	house[2]->setPos(1250 , 217);
	house[2]->setSrcSize(221, 183);
	house[2]->setSize(663, 549);
	house[3] = new GameObject;
	house[3]->loadTexture("Resource/object/house-d.png");
	house[3]->setPos(2450, 217);
	house[3]->setSrcSize(168, 183);
	house[3]->setSize(504, 549);
	
	box[0] = new GameObject;
	box[0]->loadTexture("Resource/object/crate-stack.png");
	box[0]->setPos(510 , 580);
	box[0]->setSrcSize(73, 68);
	box[0]->setSize(200, 194);

	box[1] = new GameObject;
	box[1]->loadTexture("Resource/object/crate.png");
	box[1]->setPos(2350, 670);
	box[1]->setSrcSize(39, 35);
	box[1]->setSize(117, 105);

	obj[0] = new GameObject;
	obj[0]->loadTexture("Resource/object/sign.png");
	obj[0]->setPos(910 , 573);
	obj[0]->setSrcSize(37, 45);
	obj[0]->setSize(74, 90);
	obj[1] = new GameObject;
	obj[1]->loadTexture("Resource/object/barrel.png");
	obj[1]->setPos(1070 , 688);
	obj[1]->setSrcSize(24, 30);
	obj[1]->setSize(72, 90);
	obj[2] = new GameObject;
	obj[2]->loadTexture("Resource/object/barrel.png");
	obj[2]->setPos(1142 , 688);
	obj[2]->setSrcSize(24, 30);
	obj[2]->setSize(72, 90);
	obj[3] = new GameObject;
	obj[3]->loadTexture("Resource/object/wagon.png");
	obj[3]->setPos(2042, 553);
	obj[3]->setSrcSize(93, 75);
	obj[3]->setSize(279, 225);
	obj[4] = new GameObject;
	obj[4]->loadTexture("Resource/object/well.png");
	obj[4]->setPos(2982, 585);
	obj[4]->setSrcSize(65, 65);
	obj[4]->setSize(195, 195);
	obj[5] = new GameObject;
	obj[5]->loadTexture("Resource/object/bottle.png");
	obj[5]->setPos(2370, 627);
	obj[5]->setSrcSize(16, 16);
	obj[5]->setSize(48, 48);


	textbox[0] = new GameObject;
	textbox[0]->loadTexture("Resource/object/textbox1.png");
	textbox[0]->setSrcSize(183, 113);
	textbox[0]->setSize(183, 113);
	textbox[0]->setPos(330, 520);
	textbox[1] = new GameObject;
	textbox[1]->loadTexture("Resource/object/textbox2.png");
	textbox[1]->setSrcSize(185, 114);
	textbox[1]->setSize(185, 114);
	textbox[1]->setPos(800, 520);
	textbox[2] = new GameObject;
	textbox[2]->loadTexture("Resource/object/textbox3.png");
	textbox[2]->setSrcSize(184, 110);
	textbox[2]->setSize(184, 110);
	textbox[2]->setPos(2000, 520);
	textbox[3] = new GameObject;
	textbox[3]->loadTexture("Resource/object/textbox4.png");
	textbox[3]->setSrcSize(185, 110);
	textbox[3]->setSize(185, 110);
	textbox[3]->setPos(2900, 520);

	
	//add objectmanager 
	ObjectManager::GetInstance()->addObject(house[0]);
	ObjectManager::GetInstance()->addObject(house[1]);
	ObjectManager::GetInstance()->addObject(house[3]);
	ObjectManager::GetInstance()->addObject(box[1]);
	ObjectManager::GetInstance()->addObject(house[2]);
	ObjectManager::GetInstance()->addObject(box[0]);
	ObjectManager::GetInstance()->addObject(textbox[0]);
	ObjectManager::GetInstance()->addObject(textbox[1]);
	ObjectManager::GetInstance()->addObject(textbox[2]);
	ObjectManager::GetInstance()->addObject(textbox[3]);
	for (int i = 0; i < 6; i++) {
		ObjectManager::GetInstance()->addObject(obj[i]);
	}
	for (int i = 0; i < 70; i++) {
		ObjectManager::GetInstance()->addObject(ground[i]);
	}
	//추가 

	Npc::GetInstance()->init();
	shop = new VillageMG;
	shop->init();
	SoundManager::GetInstance()->PlayBg("Resource/bg.mp3");
	
}

void VillageScene::update()
{
	pvpButton->update();
	if (InputManager::GetInstance()->getKey(VK_SPACE) && CollisionManager::GetInstance()->RectCollisionCheck(Player::GetInstance()->player, Npc::GetInstance()->npc[0])
		&& InputManager::GetInstance()->delay(500)) {
		
		if (isOpen == true)
			isOpen = false;
		else
			isOpen = true;
	}
	
	
	Player::GetInstance()->update();
	Npc::GetInstance()->update();
	shop->update();

	
	render();
	if(InputManager::GetInstance()->getKey(VK_SPACE) && CollisionManager::GetInstance()->RectCollisionCheck(Player::GetInstance()->player, obj[4])) {
		SceneManager::GetInstance()->SceneChange(SceneManager::GetInstance()->eGame);
	}
	if (InputManager::GetInstance()->getKey(0x4E)) {
		SceneManager::GetInstance()->SceneChange(SceneManager::GetInstance()->ePvp);
	}
}

void VillageScene::render()
{
	GraphicManager::GetInstance()->render(bg);

	GraphicManager::GetInstance()->render(mg);
	for (int i = 0; i < 70; i++) {
		GraphicManager::GetInstance()->render(ground[i]);
	}
	GraphicManager::GetInstance()->render(house[0]);
	GraphicManager::GetInstance()->render(house[1]);
	GraphicManager::GetInstance()->render(house[2]);
	GraphicManager::GetInstance()->render(house[3]);
	GraphicManager::GetInstance()->render(box[0]);
	GraphicManager::GetInstance()->render(box[1]);

	for (int i = 0; i < 6; i++) {
		GraphicManager::GetInstance()->render(obj[i]);
	}

	Npc::GetInstance()->render();


	if (isOpen) {
		shop->render();
		GraphicManager::GetInstance()->render(textbox[2]);
		if (!CollisionManager::GetInstance()->RectCollisionCheck(Player::GetInstance()->player, Npc::GetInstance()->npc[0])) {
			isOpen = false;
		}
	}
	if (InputManager::GetInstance()->getKey(VK_SPACE) && CollisionManager::GetInstance()->RectCollisionCheck(Player::GetInstance()->player, Npc::GetInstance()->npc[1])) {
		GraphicManager::GetInstance()->render(textbox[0]);
	}
	if (InputManager::GetInstance()->getKey(VK_SPACE) && CollisionManager::GetInstance()->RectCollisionCheck(Player::GetInstance()->player, Npc::GetInstance()->npc[3])) {
		GraphicManager::GetInstance()->render(textbox[1]);
	}
	
	if (InputManager::GetInstance()->getKey(VK_SPACE) && CollisionManager::GetInstance()->RectCollisionCheck(Player::GetInstance()->player, Npc::GetInstance()->npc[2])) {
		GraphicManager::GetInstance()->render(textbox[3]);
	}

	Player::GetInstance()->render();
	pvpButton->render();
}

void VillageScene::release()
{
	//delete bg;
	//delete mg;
	//for (int i = 0; i < 70; i++) {
	//	delete ground[i];
	//}
	//for (int i = 0; i < 4; i++) {
	//	delete house[i];
	//	delete textbox[i];
	//}
	//for (int i = 0; i < 10; i++) {
	//	delete box[i];
	//	delete obj[i];
	//}
	
	ObjectManager::GetInstance()->release();

}

