#include "EMovementSystem.h"

DEFINITION_SINGLE(EMovementSystem)

EMovementSystem::EMovementSystem()
	: SystemBase()
// : super::() // �̱����� �۵����� �ʴ���. �θ��� �����ε��� �����ڸ� ȣ���ؼ� �ʱ�ȭ�Ϸ��� �̰����� ����.
{
	// ������ �θ� �����ڸ� ȣ������ ������ �⺻ �����ڷ� �θ� �ʱ�ȭ �ȴ�.
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

// �ӽ÷� MovementSystemOperation Index : 0
void EMovementSystem::MoveLeft( int componentID)
{
	// �޸� �� vector�� pointer
}
