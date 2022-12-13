#pragma once

typedef struct UserInfo {
	int DataType = -1;
	int Frame=-1;
	int ID = -1;
	int PVPID = -1;
	int maxhp=-1;
	int maxmp=-1;
	int power=-1;
	int nowhp=-1;
	int nowmp=-1;
	int x=-1;
	int y=-1;
	int state = -1;
	bool isPvP = false;
	bool isSmash = false;
	int dir = -1;
};