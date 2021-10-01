#include "EEntityManager.h"
#include "ETableManager.h"

DEFINITION_SINGLE(EEntityManager)

EEntityManager::EEntityManager()
{
	m_pvObject = new vector<_EEntityComponent>;
}

EEntityManager::~EEntityManager()
{
	// 포인터를 저장한게 아니라 개별 요소도 함께 해제가능.
	SAFE_DEL(m_pvObject);
}

void EEntityManager::SetSystemOperationSlot()
{
}

bool EEntityManager::Init()
{
	
	return true;
}

void EEntityManager::LoadEntityFromTable()
{
	// 
	m_CompSysIndex = 0x0001'0000'0000'0000;

	vector<_EEntityComponent>::iterator iter;
	vector<_EEntityComponent>::iterator iterEnd = m_pvObject->end();

	for (iter = m_pvObject->begin(); iter != iterEnd; ++iter)
	{
		// ㄹ
	}
}
