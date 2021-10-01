#pragma once
#include "Predefines.h"
#include "CoreSystems.h"



class EGameInstance
{
private:
	int32 m_nGameState;
	//int m_OwnerID = 0;
	//int m_ComponentID = 0; // ComponentSystem		`	Index + Target ComponentIndex
	//int m_OperationIndex = 0;
	//int m_bActivate = 1; // 1 == 실행 안함, 0 == 실행함
	vector<SystemBase*> m_vSystems{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
	// 타이머 객체 포인터
	//ETimer* m_pTimer;
	//EInputManager* m_pInputManager;

	// 0~255까지 프레임 워크 제공 Manager Index
	// 256~512 사용자 정의 Manager Index
	// SystemOperation도 마찬가지
	// 0~255 프레임 워크 제공 System Operation Index
	// 256~512 사용자 정의 System Operation Index
	// GET_SINGLE
	// 인덱스를 매개변수로 받아서 매니저 주소를 반환하기 위한 Table
	//void* m_aManagerTable[ManagerIndex::Max];
	// Tick 함수
private:
	virtual void Tick();

	// 역할 함수들
public:
	// 입력받은 내용으로 Component System에 Event 

	// getters, setters
public:
	inline const vector<SystemBase*>* GetComponentSystems() const
	{
		return &m_vSystems;
	}

	inline SystemBase* GetComponentSystemByIndex(int componentSystemIndex) const
	{
		return m_vSystems[componentSystemIndex];
	}
	/*inline void* GetManagerByIndex(int managerIndex) const
	{
		return m_aManagerTable[managerIndex];
	}*/

	/*ETimer* GetTimer() const
	{
		return m_pTimer;
	}

	EInputManager* GetInputManager() const
	{
		return m_pInputManager;
	}*/

	// 초기화 함수
public:
	virtual bool Init();

	DECLARE_SINGLE(EGameInstance)
};

