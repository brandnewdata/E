#include "EEntityManager.h"
#include "ETableManager.h"

DEFINITION_SINGLE(EEntityManager)

EEntityManager::EEntityManager()
{
	m_pvObject = new vector<_EEntityComponent>;
}

EEntityManager::~EEntityManager()
{
	// �����͸� �����Ѱ� �ƴ϶� ���� ��ҵ� �Բ� ��������.
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
		// ��
	}
}
