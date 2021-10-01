#include "SystemBase.h"

SystemBase::SystemBase()
{
	m_pmapCompIndex = new unordered_map<uint64, int>;
}

SystemBase::~SystemBase()
{
	SAFE_DEL(m_pmapCompIndex)
}

int SystemBase::CreateComponent(int ownerID, int AssetID)
{
	return 0;
}