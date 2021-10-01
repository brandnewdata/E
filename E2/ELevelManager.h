#pragma once
#include "SystemBase.h"

class ELevelManager : public SystemBase
{
	DECLARE_SINGLE(ELevelManager)

public:
	virtual void SetSystemOperationSlot() override;

};

