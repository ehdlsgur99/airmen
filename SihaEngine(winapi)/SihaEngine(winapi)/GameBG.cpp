#include "common.h"

void GameBG::init()
{
	std::string path = "Resource/GameScene/BG/Layer_000";
	int count = 9;
	for (int i = 0; i < 10; i++)
	{
		layer1[i] = new GameObject;
		layer1[i]->loadTexture(path + std::to_string(count) +".png");
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

void GameBG::update()
{
	for (int i = 0; i < 10; i++)
	{
		layer1[i]->pos.x -= i;
		layer2[i]->pos.x -= i;
		if (layer1[i]->pos.x <= -1600)
			layer1[i]->pos.x = 1600;
		if (layer2[i]->pos.x <= -1600)
			layer2[i]->pos.x = 1600;
	}
}

void GameBG::render()
{
	for (int i = 0; i < 10; i++)
	{
		GraphicManager::GetInstance()->render(layer1[i]);
		GraphicManager::GetInstance()->render(layer2[i]);
	}
}

void GameBG::release()
{

}