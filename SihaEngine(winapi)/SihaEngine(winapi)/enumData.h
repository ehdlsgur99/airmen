#pragma once

#include "common.h"

enum ePlayer
{
	eIdle = 0, eLeft, eRight, eJump1,eJump2, eAttack1, eAttack2, eAttacked
};

enum eMonsterType
{
	eSlime, eSkeleton
};

enum eMonsterState
{
	eRun, eHurt, eDie, eAttack
};

enum eMapType
{
	eForest,
};

// 서버가 데이터를 식별하여 함수를 조정하도록 데이터 타입형태를 enum으로 초기화한다.
enum eDataType
{

};
