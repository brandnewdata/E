#pragma once
#include "SystemBase.h"


class ENetworkMnager : public SystemBase
{
//**************************************************************************************************//
//																									//
//						Method Area																	//
//																									//
//**************************************************************************************************//
// �ʱ�ȭ �Լ�
protected:
	virtual void SetSystemOperationSlot() override;

public:
	bool Init();

	DECLARE_SINGLE(ENetworkMnager)
};

