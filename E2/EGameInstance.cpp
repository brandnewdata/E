#include "EGameInstance.h"
#include "ECore.h"
#include "EMovementSystem.h"
#include "EInputManager.h"
#include "EJobManager.h"
#include "Render2DSystem.h"

DEFINITION_SINGLE(EGameInstance)


EGameInstance::EGameInstance()
{

}

EGameInstance::~EGameInstance()
{

}

void EGameInstance::Tick()
{
}

// 
// Timer,
// Input,
// Movement,
// Collision, End, Max = 3
bool EGameInstance::Init()
{
	// TODO : ManagerIndex::시스템이름 
	m_vSystems[EComponentSystemIndex::Render2D] = static_cast<SystemBase*>(GET_SINGLE(Render2DSystem));

	return true;
}
