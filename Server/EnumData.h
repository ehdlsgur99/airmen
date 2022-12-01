#pragma once

// 서버가 데이터를 식별하여 함수를 조정하도록 데이터 타입형태를 enum으로 초기화한다.
// eNone    : 데이터만 주고 받는 상태
// eRequest : 클라이언트가 서버에 접속한 유저들 정보 요청
enum eDataType
{
	eNone = 0, eRequest, eInviteSend, eInviteRecv
};