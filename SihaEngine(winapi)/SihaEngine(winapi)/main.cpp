#include "common.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	System cs;

	cs.init();

	cs.msgLoop();

	cs.release();
}
