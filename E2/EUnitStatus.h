#pragma once
#include "SystemBase.h"

enum class EPlayerDataTableColumn
{
	SpriteAssetID,	// 메쉬, 스프라이트, 경로
	Level,	// 레벨
	STR,	// 근력
	AGI,	// 민첩
	INTG,	// 지능
	CON,	// 체질
	ATK_Type,	// 공격유형
	DF_Type,	// 방어유형
	MoveSpeed,	// 이동속도
	ATK_Range_Min,  // 최소 공격 사거리
	ATK_Range_Max  // 초대 공격 사거리
};

struct _PlayerAttributes
{
	int		Level,
		STR,
		AGI,
		INT,
		CON = 0;

	float	MoveSpeed,
		PhysicalAttackPoint,
		MagicalAttackPpoint,
		AttackPerSec,
		Critical_Rate,
		Critical_Power,
		HP,
		MP,
		ATK_Range_Min,
		ATK_Range_Max = 0.f;
	// enum과 연산하게됨
	int		nATK_Type = ATK_Type::None;
	int		nDF_Type = DF_Type::None;
};

// 매니저 혹은 컴포넌트 간의 의존관계
struct _UnitStatusComponent
{
	// 초당 이동속도
	float SpeedPerSec = 100;
	// WeaponState
	BOOL bTrigger;
};

// UnitStatusComponent에 대하여 Manager가 수행 할 수 있는 연산의 인덱스들
namespace UnitStatusOperation
{
	// 
	enum
	{

	};
}

class EUnitStatus :
	public SystemBase
{
};

