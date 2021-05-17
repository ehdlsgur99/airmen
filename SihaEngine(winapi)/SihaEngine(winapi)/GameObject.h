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
	POINT pos;

	// isVisible = true �϶��� ���
	bool	isVisible;

	// �ִϸ��̼��� ���� ��
	int		aniNow;			// ���� ������
	float	aniTime;

	// ũ�� ����
	float Scale;

	// �ؽ��� �ҷ�����
	void loadTexture(std::string filename);

	// ������� ��ġ ����
	void setSize(int x, int y);
	void setPos(int x, int y);

	// ������� ��ġ ��������
	SIZE getSize();
	POINT getPos();

	// �ִϸ��̼�
	bool animation(std::string filename, int frame, int delay);


private:

};

