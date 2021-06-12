#pragma once

#include "common.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
public:
	CImage texture;

	// ������� ��ġ
	SIZE size;
	SIZE srcSize;
	POINT pos;

	// isVisible = true �϶��� ���
	bool	isVisible;

	// �ִϸ��̼��� ���� ��
	int		aniNow;			// ���� ������
	std::string		oldFineName;		// �ٸ� �ִϸ��̼��� ���
	float	aniTime;

	// ũ�� ����
	float Scale;

	// �ؽ��� �ҷ�����
	void loadTexture(std::string filename);

	// ������� ��ġ ����
	void setSize(int x, int y);
	void setPos(int x, int y);
	void setSrcSize(int x, int y);

	// ������� ��ġ ��������
	SIZE getSize();
	SIZE getSrcSize();
	POINT getPos();

	// ���������϶� �ִϸ��̼�
	bool animation(std::string filename, int frame, int delay);

private:

};

