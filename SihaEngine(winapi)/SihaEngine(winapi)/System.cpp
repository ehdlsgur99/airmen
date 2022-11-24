#include "common.h"

System::System()
{

}
System::~System()
{

}


void System::init()
{
	Player::GetInstance();

	// �׷��� Ŭ������ �ʱ�ȭ �Ѵ�.
	GraphicManager::GetInstance()->init();

	// ���� ���� ���Ѵ�.
	SceneManager::GetInstance()->SceneChange(SceneManager::eIntro);
}
void System::msgLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			mainLoop();
		}
	}
}
void System::release()
{
	// ���� �׷����� �����Ѵ�.
// �� �������� �ؽ���, ������Ʈ ������ ���ԵǾ��ִ�.
	SceneManager::GetInstance()->scene->release();
	GraphicManager::GetInstance()->release();
}
void System::mainLoop()
{
	// Render�� �����Ѵ�.
	GraphicManager::GetInstance()->renderStart();

	// �ش� ���� ������Ʈ�� ���ְ�	
	SceneManager::GetInstance()->scene->update();

	// Render�� ������.
	GraphicManager::GetInstance()->renderEnd();
}