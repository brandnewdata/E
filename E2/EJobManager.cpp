#include "EJobManager.h"
#include "Predefines.h"
#include "EGameInstance.h"

DEFINITION_SINGLE(EJobManager)

EJobManager::EJobManager()
{
	m_pJobQueue = new EJobQueue;
	m_NumCore = static_cast<int>(std::thread::hardware_concurrency() / 2);
}

EJobManager::~EJobManager()
{
	SAFE_DEL(m_pJobQueue)
}


bool EJobManager::Init()
{
	m_GI = GET_SINGLE(EGameInstance);
	if (m_GI == nullptr)
		return false;
	else
		return true;
}


void EJobManager::ThreadProc()
{
	LONG lCmp = 0;
	
	while (true)
	{
		// ����ٰ� ������ ���� ���ϸ� ������ WakeByAddress~~()�Լ� ȣ�� �������� ��� ���� ����
		// �׶� ���� ������ sema�� 0�����̸� ���� �ٽ� ���ư�.
		WaitOnAddress(&m_Sema, &lCmp, sizeof(LONG), INFINITE);
		if (m_Sema< 0)	// -1�̸� ����ϱ� �ٷ� ��ȯ
			break;
		InterlockedDecrement(&m_Sema); // ť�� �ϰ� �ϳ� ����
		EJob Job = m_pJobQueue->Pop(); // ť���� �ϰ��� ������
		WakeByAddressSingle(&m_Sema); // ������� ������� �������ϳ� ����

		if(Job.m_OwnerID == 1)
			CRASH(0);

		// ComponentID�� ���� 8�� ��Ʈ�� ������Ʈ �ý��� �ε�����.
		int CompSystemIndex = (Job.m_ComponentID & 0xff00'0000) >> 24;

		// TODO : ��������  ��Ȳ�̸� �����ϴ� ������Ʈ�ý��� ������ JOB�� ����ִ� �ε��� ���� ū ��찡 ����
		// ���� �̰� �� ����� ã�ƾ���
		if (static_cast<int>(m_GI->GetComponentSystems()->size()) < CompSystemIndex || CompSystemIndex < 0)
			CRASH(0);

		// ���� �ν��Ͻ����� > ������Ʈ �ý��� -> ������Ʈ �ý��� operation() ȣ�� 
		// TODO : ������.. ������Ʈ�� ��������.
		m_GI->GetComponentSystemByIndex(CompSystemIndex)->GetSystemOperationByIndex(Job.m_OperationIndex)();
	}
}

void EJobManager::InitThreadPool()
{
	for (int i = 0; i < m_NumCore; i++)
	{
		// �ϴ� emplace �ẽ pushback ���
		// std::thread() ������ ����, ���ο��� �������
		vThread.emplace_back(&EJobManager::ThreadProc, this);
		// vThreads.emplace_back(std::thread(&Render2DSystem::RenderSysProc, this, &Render2DSystem::ThreadTestParamFunc));
		// ������� ������ ���� CreateThread(NULL, 0, Render2DSystem::PoolItemProc, &tp, 0, &dwThreadId);	
	}
}

void EJobManager::DestroyThreadPool()
{
	// TODO : ���⼭ �ð��� �ʹ� ��ü�Ǹ� ũ���� �ϵ��� �߰��� ��. �ݹ� ������ �����̴�.
	// ���� �����尡 �����ϸ� ������� �����Ѵ� ��� ���� ������Ǯ�� ��� �����忡 �����ϵ��� �� ����
	InterlockedExchange(&m_Sema, -1);
	// ��� �����尡 �Ͼ�� �������� ��ȿ���� Ȯ���ϰ� // �������� �������� ���� ó���� ������ // �۾����� ������� ���� ������ �뺸 ����.
	WakeByAddressAll(&m_Sema);
	// ������Ǯ�� ��� ����� ������� join
	for (int32 i = 0; i < m_NumCore; i++)
	{
		if (vThread[i].joinable())
			vThread[i].join();
	}
}

void EJobManager::PushJob(int ownerID, int ComponentID, int OperationIndex, int activeOperation)
{
	//int m_OwnerID = 0;
	//int m_ComponentID = 0;
	//int m_OperationIndex = 0;
	//int m_bActivate = 1; // 1 == ���� ����, 0 == ������
	// ������ ���ο� �����Ҵ��� ��� �׳� ��������� ȣ��...
	// READ
	// m_Sema < 300
	m_pJobQueue->Push(EJob(ownerID, ComponentID, OperationIndex, activeOperation));
	InterlockedIncrement(&m_Sema);	// ���ο� �۾��� �߰��Ǿ����� ����
	WakeByAddressSingle(&m_Sema);	// �۾��� �߰��Ǿ����� �ּҰ��� ���Ͽ� ������� �����带 ������ �����϶�� �˸�
}
