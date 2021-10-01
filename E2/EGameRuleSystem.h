#pragma once
#include "SystemBase.h"

struct _GameRuleComponent
{
	int64 m_ownerID;
	int32 m_ComponentID;
	int64 m_PlayerEntityDTID;
	int64 m_HUDDTID;
	int64 m_GameStateDTID;
	int64 m_ControllerDTID;
};

// 레벨 서브 엔티티
// 게임모드
	// 플레이어 타입
	// HUD
	// 플레이어 컨트롤러
	// 게임 스테이트
	// 플레이어 스테이트
	// 관찰자 클래스


class EGameRuleSystem :
	public SystemBase
{
//**************************************************************************************************//
//																									//
//						Property Area																	//
//																									//
//**************************************************************************************************//
private:
	vector< _GameRuleComponent> m_vGameRuleComp;
//**************************************************************************************************//
//																									//
//						Method Area																	//
//																									//
//**************************************************************************************************//
// 초기화 함수들
public:
	bool Init();
	virtual void SetSystemOperationSlot() final;

	DECLARE_SINGLE(EGameRuleSystem)
};

