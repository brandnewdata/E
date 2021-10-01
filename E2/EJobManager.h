#pragma once
#include "Predefines.h"
#include "EJobQueue.h"

class EGameInstance;

class EJobManager
{
public:
	bool Init();

	// ��� �����忡�� �� �Լ��� ȣ���մϴ�.
	void ThreadProc();

	//  ������Ǯ�� �����Ѵ�.
	void InitThreadPool();

	// ������ Ǯ�� �����Ѵ�.
	void DestroyThreadPool();
	
	// �ʱ�ȭ�� �Ϸ�ǰ� OnBeginPlay���� ���� �ý����� Tick���� ����Ǵ� �Լ��� ť�� �߰��մϴ�.
	// ƽ���� ����Ǿ�� �ϴ� component �ý��� �Լ��� ������ �ڱ� �ڽ��� �۾�ť�� �ֽ��ϴ�.
	// 
	// @param1 : ������ Entity�� ID
	// @param2 : ������ ComponentID ComponentSystemIndex�� ComponentIndex�� �Ľ̵ȴ�.
	// @param3 : �����ؾ��ϴ� ���� OperationIndex (enum)
	// @param4 : �ش� ������ ������ ���ϴ� ��� EActiveOperation::True(�⺻��, ��������)
	// ��Ȱ��ȭ�� ���ϴ� ��� EActiveOperation::False
	void PushJob(int ownerID, int ComponentID, int OperationIndex, int activeOperation = 0);

public:
	//inline EJobQueue* GetJobQueue() const
	//{
	//	return m_pJobQueue;
	//}

private:
	EGameInstance* m_GI;
	// ���Ǻ��� ������ ��� ó���� ����Ѵ�.
	// condition_variable m_ConVar;

	// ��ť�� ���� ũ�⸦ �������� ������Ǯ�� Ȱ�� ��Ȱ���� �����Ѵ�.
	// -1 : ����, 0 : ������ ���(�Ͻ�����, �۾����� ��Ȳ)
	// 1~���̻� : �������� ���� �� �۵�����
	LONG m_Sema = 0;
	// �����尡 ���� ���� ��Ȳ�� ���� Ư���� ó���� �ϵ��� ����� ��쿡 ����� ����� �ش���� ����
	atomic<uint16> m_GameStateFlag;
	// Job ����Ǵ� ť
	EJobQueue* m_pJobQueue;
	// ���� ��ǻ���� ���� ���ھ��� ����
	int m_NumCore;
	// ������ ������ �迭
	vector<std::thread> vThread;
	// ���ɶ����� ������Ǯ ���


	DECLARE_SINGLE(EJobManager)
};

