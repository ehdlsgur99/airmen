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

// ������ �����͸� �ĺ��Ͽ� �Լ��� �����ϵ��� ������ Ÿ�����¸� enum���� �ʱ�ȭ�Ѵ�.
// eNone    : �����͸� �ְ� �޴� ����
// eRequest : Ŭ���̾�Ʈ�� ������ ������ ������ ���� ��û
enum eDataType
{
	eNone = 0, eRquest, eInviteSend
};
