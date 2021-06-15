#include "common.h"

void GameBG::init()
{
	level = Player::GetInstance()->level;

	if (level % 2 == 1)
	{
		std::string path = "Resource/GameScene/BG/Layer_000";
		int count = 9;
		for (int i = 0; i < 10; i++)
		{
			layer1[i] = new GameObject;
			layer1[i]->loadTexture(path + std::to_string(count) + ".png");
			layer1[i]->setPos(0, -100);
			layer1[i]->setSize(1600, 900);
			layer1[i]->setSrcSize(1600, 900);

			layer2[i] = new GameObject;
			layer2[i]->loadTexture(path + std::to_string(count) + ".png");
			layer2[i]->setPos(1600, -100);
			layer2[i]->setSize(1600, 900);
			layer2[i]->setSrcSize(1600, 900);
			count--;
		}
	}
	else
	{
		std::string path = "Resource/GameScene/BG3/layer";
		for (int i = 0; i < 4; i++)
		{
			layer1[i] = new GameObject;
			layer1[i]->loadTexture(path + std::to_string(i + 1) + ".png");
			layer1[i]->setPos(0, -100);
			layer1[i]->setSize(1600, 900);


			layer2[i] = new GameObject;
			layer2[i]->loadTexture(path + std::to_string(i + 1) + ".png");
			layer2[i]->setPos(1600, -100);
			layer2[i]->setSize(1600, 900);

		}
	}

	
	moveTime = GetTickCount();
}

void GameBG::update()
{
	if (Player::GetInstance()->state == eRight || Player::GetInstance()->state == eJump1 ||
		Player::GetInstance()->state == eJump2)
	{
		if (GetTickCount() - moveTime >= 10)
		{
			moveTime = GetTickCount();
			int count;
			if (level % 2 == 1)
				count = 10;
			else
				count = 4;
			for (int i = 0; i < count; i++)
			{
				layer1[i]->pos.x -= i + 3;
				layer2[i]->pos.x -= i + 3;
				if (layer1[i]->pos.x <= -1600)
					layer1[i]->pos.x = 1600;
				if (layer2[i]->pos.x <= -1600)
					layer2[i]->pos.x = 1600;
			}
		}
	}


	
}

void GameBG::render()
{
	int count;
	if (level % 2 == 1)
		count = 10;
	else
		count = 4;
	for (int i = 0; i < count; i++)
	{
		GraphicManager::GetInstance()->render(layer1[i]);
		GraphicManager::GetInstance()->render(layer2[i]);
	}
}

void GameBG::release()
{

}