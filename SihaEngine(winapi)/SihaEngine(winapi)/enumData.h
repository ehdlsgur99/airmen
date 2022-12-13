#pragma once

#include "common.h"

enum ePlayer
{
	eIdle = 0, eLeft,eRight,eJump, eAttack1, eAttack2, eAttacked, eWalk
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
	eNone = 0, eRequest, eInviteSend, eInviteRecv, eGoToPVP, eInPVP, eExit
};

//enum ePlayerDir
//{
//	eLeft =0, eRight 
//};