#pragma once


//int m_OwnerID = 0;
//int m_ComponentID = 0;
//int m_OperationIndex = 0;
//void* m_pOperationParams = nullptr;
//int m_bActivate = 1; // 1 == ���� ����, 0 == ������
class EJob
{
public:
	int m_OwnerID = 0;
	int m_ComponentID = 0;
	int m_OperationIndex = 0;
	int m_bActivate = 1; // 1 == ���� ����, 0 == ������

public:
	EJob()
	{
	}

	EJob(const EJob& other)
	{
		m_OwnerID = other.m_OwnerID;
		m_ComponentID = other.m_ComponentID;
		m_OperationIndex = other.m_OperationIndex;
		m_bActivate = other.m_bActivate;
	}

	EJob& operator=(const EJob& other)
	{
		m_OwnerID = other.m_OwnerID;
		m_ComponentID = other.m_ComponentID;
		m_OperationIndex = other.m_OperationIndex;
		m_bActivate = other.m_bActivate;

		return *this;
	}

	EJob(int ownerID, int componentID, int operationIndex, int bActivate)
		:m_OwnerID(ownerID), m_ComponentID(componentID),
		m_OperationIndex(operationIndex),
		m_bActivate(bActivate)
	{
	}

	// �⺻ ���� �����ڿ� ���� ����... ���߿� �����Ͱ� ó���� �޸��� ���� �־ �̵������� �����.
	EJob(EJob&& other)
	{
		m_OwnerID = other.m_OwnerID;
		m_ComponentID = other.m_ComponentID;
		m_OperationIndex = other.m_OperationIndex;
		m_bActivate = other.m_bActivate;
	}

	EJob& operator= (EJob&& other)
	{
		m_OwnerID = other.m_OwnerID;
		m_ComponentID = other.m_ComponentID;
		m_OperationIndex = other.m_OperationIndex;
		m_bActivate = other.m_bActivate;

		return *this;
	}
};

