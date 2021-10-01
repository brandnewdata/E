#pragma once
#include "Predefines.h"

struct SystemComponentBase
{
	int m_ComponentOwnerID = 0;
	// 0xff00'0000 ComponentSystemIndex(ComponentCategory)
	// 0x00f0'0000 ComponentMemoryBlockIndex
	// 0x000f'ffff ComponentIndex
	int m_ComponentID = 0;
};

class SystemBase
{
//**************************************************************************************************//
//																									//
//						Property Area																//
//																									//
//**************************************************************************************************//
protected:
	int64 m_CompSysIndex; // ��� ������Ʈ �ý����� �ε����� InitȤ�� �����ڿ��� �ʱ�ȭ �ȴ�.
	vector<function<void(void*)>> m_vOperation; // SystemOperation�迭(vector)
	unordered_map<uint64, int>* m_pmapCompIndex; // Ű�� OwnerID, Data�� �ش� Owner�� ComponentIndex 

//**************************************************************************************************//
//																									//
//						Method Area																	//
//																									//
//**************************************************************************************************//

protected:
	// OwnerID�� ComponentDTID�� �޾Ƽ� ���ο� ������Ʈ�� �����ؼ� �߰���.
	// ������ ������Ʈ�� ��Ÿ�� ������Ʈ ID�� ��ȯ�Ѵ�.
	virtual int CreateComponent(int ownerID, int ComponentDTID);
	// ��ӵǴ� ���� set �Լ���
	virtual void SetSystemOperationSlot() = 0;

//������ �Ҹ���
public:
	SystemBase();
	// ���� ������ ���� 
	SystemBase(const SystemBase& other) = delete;

	// �Ҹ��� ����ȭs
	virtual ~SystemBase();
	
// getter, setter
public:
	// Operation Index�� �ް� Operation�Լ��� �Ѱ��ش�.
	virtual function<void(void*)> GetSystemOperationByIndex(int operationIndex) const
	{
		return m_vOperation[operationIndex];
	}

	void BindKeyEventCallbackByEventName(const string& keyName)
	{
		//GET_SINGLE(EInputManager)->BindKeyEventCallbackByEventName(keyName, this);
	}

	inline const unordered_map<uint64, int>* GetCompIndexMap() const
	{
		return m_pmapCompIndex;
	}
};

