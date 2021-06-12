#pragma once

#include "common.h"

enum ePlayer
{
	eIdle = 0, eLeft, eRight, eJump, eAttack1, eAttack2, eAttacked
};

enum eMonsterType
{
	eSlime
};

enum eMonsterState
{
	eRun, eHurt, eDie, eAttack
};
