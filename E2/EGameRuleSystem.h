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

// ���� ���� ��ƼƼ
// ���Ӹ��
	// �÷��̾� Ÿ��
	// HUD
	// �÷��̾� ��Ʈ�ѷ�
	// ���� ������Ʈ
	// �÷��̾� ������Ʈ
	// ������ Ŭ����


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
// �ʱ�ȭ �Լ���
public:
	bool Init();
	virtual void SetSystemOperationSlot() final;

	DECLARE_SINGLE(EGameRuleSystem)
};

