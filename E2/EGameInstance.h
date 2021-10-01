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
	//int m_bActivate = 1; // 1 == ���� ����, 0 == ������
	vector<SystemBase*> m_vSystems{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
	// Ÿ�̸� ��ü ������
	//ETimer* m_pTimer;
	//EInputManager* m_pInputManager;

	// 0~255���� ������ ��ũ ���� Manager Index
	// 256~512 ����� ���� Manager Index
	// SystemOperation�� ��������
	// 0~255 ������ ��ũ ���� System Operation Index
	// 256~512 ����� ���� System Operation Index
	// GET_SINGLE
	// �ε����� �Ű������� �޾Ƽ� �Ŵ��� �ּҸ� ��ȯ�ϱ� ���� Table
	//void* m_aManagerTable[ManagerIndex::Max];
	// Tick �Լ�
private:
	virtual void Tick();

	// ���� �Լ���
public:
	// �Է¹��� �������� Component System�� Event 

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

	// �ʱ�ȭ �Լ�
public:
	virtual bool Init();

	DECLARE_SINGLE(EGameInstance)
};

