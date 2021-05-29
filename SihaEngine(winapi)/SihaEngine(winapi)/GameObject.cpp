#include "common.h"

GameObject::GameObject()
{
	aniNow = 0;
	aniTime = 0;
	isVisible = true;
	Scale = 1.0f;
}

GameObject::~GameObject()
{

}

void GameObject::loadTexture(std::string fileName)
{

	// 자료형 변환 해줘야함 ;;;
	// string to tchar 로..
	int slength = (int)fileName.length() + 1;
	int len = MultiByteToWideChar(CP_ACP, 0, fileName.c_str(), slength, 0, 0);
	TCHAR* buf = new TCHAR[len];
	MultiByteToWideChar(CP_ACP, 0, fileName.c_str(), slength, buf, len);
	TCHAR *r(buf);

	// 예전에 있던 이미지 파괴
	texture.Destroy();

	texture.Load(r);
}

void GameObject::setPos(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

void GameObject::setSize(int x, int y)
{
	size.cx = x;
	size.cy = y;
}

void GameObject::setSrcSize(int x, int y)
{

}

POINT GameObject::getPos()
{
	return pos;
}


SIZE GameObject::getSize()
{
	return size;
}

SIZE GameObject::getSrcSize()
{
	return srcSize;
}

bool GameObject::animation(std::string filename, int frame, int delay)
{
	if (GetTickCount() - aniTime >= delay)
	{
		aniTime = GetTickCount();
		
		// 현재 프레임과 지정 프레임수가 같은 경우
		if (aniNow == frame)
		{
			aniTime = 0;
			aniNow = 0;

			// 
			return true;
		}

		// 프레임 증가
		aniNow++;
		filename += to_string(aniNow);
		filename += ".png";


		// 이미지 다시 로드
		loadTexture(filename);

	}
}