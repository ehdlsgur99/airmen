#include "common.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	System cs;

	cs.init();
	SetTimer(GraphicManager::GetInstance()->hWnd, 0, 1000/60, NULL);

	cs.msgLoop();

	cs.release();
	KillTimer(GraphicManager::GetInstance()->hWnd, 0);
}
