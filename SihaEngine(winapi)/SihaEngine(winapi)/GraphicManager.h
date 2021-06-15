#pragma once

#include "common.h"


class Scene;
class GraphicManager : public CSingleton<GraphicManager>
{
public:
	GraphicManager();
	~GraphicManager();
public:
	
	// HWND, HDC
	HWND					hWnd;
	HDC						hdc, memdc;
	WNDCLASSEX				 wc;
	HINSTANCE				hInstance;
	HINSTANCE				hPrevInstance;
	LPSTR					lpszCmdParam;
	int						nCmdShow;
	// PAINT 필요 변수
	PAINTSTRUCT				ps;
	HBITMAP					hBitmap;


	// 윈도우의 초기화 담당
	void init();
	void renderStart();
	void render(GameObject* obj);
	void renderEnd();
	void release();

	void drawText(std::string str, POINT pos, int fontSize, COLORREF fontColor);
	


};

