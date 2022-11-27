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

	// 그래픽 클래스를 초기화 한다.
	GraphicManager::GetInstance()->init();

	// 시작 씬을 정한다.
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
	// 씬과 그래픽을 해제한다.
// 씬 해제에는 텍스쳐, 오브젝트 해제도 포함되어있다.
	SceneManager::GetInstance()->scene->release();
	GraphicManager::GetInstance()->release();
}
void System::mainLoop()
{
	// Render을 시작한다.
	GraphicManager::GetInstance()->renderStart();

	// 해당 씬을 업데이트를 해주고	
	SceneManager::GetInstance()->scene->update();

	// Render을 끝낸다.
	GraphicManager::GetInstance()->renderEnd();
}