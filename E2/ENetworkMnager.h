#pragma once
#include "SystemBase.h"


class ENetworkMnager : public SystemBase
{
//**************************************************************************************************//
//																									//
//						Method Area																	//
//																									//
//**************************************************************************************************//
// 초기화 함수
protected:
	virtual void SetSystemOperationSlot() override;

public:
	bool Init();

	DECLARE_SINGLE(ENetworkMnager)
};

