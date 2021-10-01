#pragma once
#include "SystemBase.h"

enum class EPlayerDataTableColumn
{
	SpriteAssetID,	// �޽�, ��������Ʈ, ���
	Level,	// ����
	STR,	// �ٷ�
	AGI,	// ��ø
	INTG,	// ����
	CON,	// ü��
	ATK_Type,	// ��������
	DF_Type,	// �������
	MoveSpeed,	// �̵��ӵ�
	ATK_Range_Min,  // �ּ� ���� ��Ÿ�
	ATK_Range_Max  // �ʴ� ���� ��Ÿ�
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
	// enum�� �����ϰԵ�
	int		nATK_Type = ATK_Type::None;
	int		nDF_Type = DF_Type::None;
};

// �Ŵ��� Ȥ�� ������Ʈ ���� ��������
struct _UnitStatusComponent
{
	// �ʴ� �̵��ӵ�
	float SpeedPerSec = 100;
	// WeaponState
	BOOL bTrigger;
};

// UnitStatusComponent�� ���Ͽ� Manager�� ���� �� �� �ִ� ������ �ε�����
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

