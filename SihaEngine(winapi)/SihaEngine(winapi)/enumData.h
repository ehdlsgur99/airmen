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