#include "common.h"

IntroScene::IntroScene()
{

}

IntroScene::~IntroScene()
{

}

void IntroScene::init()
{
	main = new GameObject;
	main->loadTexture("Resource/intro.png");
	main->setSize(1600, 900);
	main->setPos(0, 0);

	pressAnyKey = new GameObject;
	pressAnyKey->loadTexture("Resource/press.png");
	pressAnyKey->setSize(400, 80);
	pressAnyKey->setPos(550, 650);

	alpha = false;
}

void IntroScene::update()
{
	if (alpha)
	{
		pressAnyKey->alpha -= 5;
		if (pressAnyKey->alpha <= 5)
			alpha = false;
	}
	else
	{
		pressAnyKey->alpha += 5;
		if (pressAnyKey->alpha >= 255)
			alpha = true;
	}

	render();

	if (InputManager::GetInstance()->isKeyDown)
		SceneManager::GetInstance()->SceneChange(SceneManager::GetInstance()->eVillage);
}

void IntroScene::render()
{
	GraphicManager::GetInstance()->render(main);
	GraphicManager::GetInstance()->render(pressAnyKey);
}

void IntroScene::release()
{

}
