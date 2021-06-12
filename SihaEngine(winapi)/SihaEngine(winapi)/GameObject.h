#pragma once

#include "common.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
public:
	CImage texture;

	// 사이즈와 위치
	SIZE size;
	SIZE srcSize;
	POINT pos;

	// isVisible = true 일때만 출력
	bool	isVisible;

	// 애니매이션을 위한 값
	int		aniNow;			// 현재 프레임
	std::string		oldFineName;		// 다른 애니메이션일 경우
	float	aniTime;

	// 크기 관련
	float Scale;

	// 텍스쳐 불러오기
	void loadTexture(std::string filename);

	// 사이즈와 위치 적용
	void setSize(int x, int y);
	void setPos(int x, int y);
	void setSrcSize(int x, int y);

	// 사이즈와 위치 가져오기
	SIZE getSize();
	SIZE getSrcSize();
	POINT getPos();

	// 낱개파일일때 애니메이션
	bool animation(std::string filename, int frame, int delay);

private:

};

