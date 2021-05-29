
#include "common.h"


GraphicManager::GraphicManager()
{}

GraphicManager::~GraphicManager()
{}

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// 메인 프로시저
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		InputManager::GetInstance()->isLButtonDonw = true;
		InputManager::GetInstance()->isLButtonUp = false;
		InputManager::GetInstance()->LButtonPos = { LOWORD(lParam), HIWORD(lParam) };
		break;
	case WM_LBUTTONUP:
		InputManager::GetInstance()->isLButtonDonw = false;
		InputManager::GetInstance()->isLButtonUp = true;
		break;
	case WM_RBUTTONDOWN:
		InputManager::GetInstance()->isRButtonDonw = true;
		InputManager::GetInstance()->isRButtonUp = false;
		break;
	case WM_RBUTTONUP:
		InputManager::GetInstance()->isRButtonDonw = false;
		InputManager::GetInstance()->isRButtonUp = true;
		break;
	case WM_KEYDOWN:
		// 키보드가 눌렸을때
		InputManager::GetInstance()->isKeyDown = true;
		InputManager::GetInstance()->isKeyUp = false;
		break;
	case WM_KEYUP:
		InputManager::GetInstance()->isKeyDown = false;
		InputManager::GetInstance()->isKeyUp = true;
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void GraphicManager::init()
{
	this->hInstance = hInstance;
	this->hPrevInstance = hPrevInstance;
	this->lpszCmdParam = lpszCmdParam;
	this->nCmdShow = nCmdShow;

	//// 윈도우 클래스를 생성후 적용
	wc = {
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, NULL, NULL,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"SihaEngine", NULL
	};
	RegisterClassEx(&wc);



	hWnd = CreateWindow(L"SihaEngine", L"SihaEngine", WS_OVERLAPPEDWINDOW, 0, 0, 1280, 1024, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, true);
	UpdateWindow(hWnd);

}


void GraphicManager::renderStart()
{
	hdc = GetDC(hWnd);
	hBitmap = CreateCompatibleBitmap(hdc, 1280, 1024);
	memdc = CreateCompatibleDC(hdc);
	SelectObject(memdc, hBitmap);
}




void GraphicManager::render(GameObject* obj)
{
	// 오브젝트의 Visible 이 true 일 경우에만 렌더 한다.
	if (obj->isVisible == true)
	{
		// 오브젝트의 사이즈 설정
		//RECT size;
		//size.left = 0;
		//size.top = 0;
		//size.bottom = obj->getSize().cy;
		//size.right = obj->getSize().cx;

		// 편의에 따라 blt 류 함수 사용해도됨
		obj->texture.Draw(memdc, obj->getPos().x, obj->getPos().y, obj->getSize().cx ,obj->getSize().cy,
			0, 0, obj->getSrcSize().cx, obj->getSrcSize().cy);
	}
}



void GraphicManager::renderEnd()
{
	BitBlt(hdc, 0, 0, 1280, 1024, memdc, 0, 0, SRCCOPY); //--- 메모리 DC의 그림을 화면 DC에 복사하기
	DeleteObject(hBitmap);
	DeleteDC(memdc);
	ReleaseDC(hWnd, hdc);
}

void GraphicManager::release()
{
	// release 뭐 이건 나중에 함
}

