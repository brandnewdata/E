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
	int64 m_CompSysIndex; // 모든 컴포넌트 시스템의 인덱스는 Init혹은 생성자에서 초기화 된다.
	vector<function<void(void*)>> m_vOperation; // SystemOperation배열(vector)
	unordered_map<uint64, int>* m_pmapCompIndex; // 키는 OwnerID, Data는 해당 Owner의 ComponentIndex 

//**************************************************************************************************//
//																									//
//						Method Area																	//
//																									//
//**************************************************************************************************//

protected:
	// OwnerID와 ComponentDTID를 받아서 새로운 컴포넌트를 생성해서 추가함.
	// 생성된 컴포넌트의 런타임 컴포넌트 ID를 반환한다.
	virtual int CreateComponent(int ownerID, int ComponentDTID);
	// 상속되는 내부 set 함수들
	virtual void SetSystemOperationSlot() = 0;

//생성자 소멸자
public:
	SystemBase();
	// 복사 생성자 막음 
	SystemBase(const SystemBase& other) = delete;

	// 소멸자 가상화s
	virtual ~SystemBase();
	
// getter, setter
public:
	// Operation Index를 받고 Operation함수를 넘겨준다.
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

