#include "EMovementSystem.h"

DEFINITION_SINGLE(EMovementSystem)

EMovementSystem::EMovementSystem()
	: SystemBase()
// : super::() // 이구문은 작동하지 않느다. 부모의 오버로딩된 생성자를 호출해서 초기화하려면 이곳에서 하자.
{
	// 별도로 부모 생성자를 호출하지 않으면 기본 생성자로 부모가 초기화 된다.
	pvMovementComponent = new vector<MovementComponent>;
}


EMovementSystem::~EMovementSystem()
{

}

void EMovementSystem::SetSystemOperationSlot()
{
}

bool EMovementSystem::Init()
{
	return true;
}

function<void(void)>& EMovementSystem::GetOperationPtr(int indexOperation)
{
	return m_BindedFuncs[0];
}

bool EMovementSystem::StartManagerProcess()
{
	return false;
}

void EMovementSystem::MovementProc()
{

}

// 임시로 MovementSystemOperation Index : 0
void EMovementSystem::MoveLeft( int componentID)
{
	// 메모리 블럭 vector의 pointer
}
