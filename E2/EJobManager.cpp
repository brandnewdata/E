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
		// 깨어났다가 조건을 만족 못하면 다음에 WakeByAddress~~()함수 호출 시점까지 계속 잠들어 있음
		// 그때 깨어났어도 여전히 sema가 0이하이면 대기로 다시 돌아감.
		WaitOnAddress(&m_Sema, &lCmp, sizeof(LONG), INFINITE);
		if (m_Sema< 0)	// -1이면 종료니까 바로 반환
			break;
		InterlockedDecrement(&m_Sema); // 큐에 일감 하나 감소
		EJob Job = m_pJobQueue->Pop(); // 큐에서 일감을 꺼내옴
		WakeByAddressSingle(&m_Sema); // 세마포어에 대기중인 스레드하나 깨움

		if(Job.m_OwnerID == 1)
			CRASH(0);

		// ComponentID의 상위 8개 비트가 컴포넌트 시스템 인덱스다.
		int CompSystemIndex = (Job.m_ComponentID & 0xff00'0000) >> 24;

		// TODO : 정상적인  상황이면 존재하는 컴포넌트시스템 수보다 JOB에 들어있는 인덱스 값이 큰 경우가 없음
		// 따라서 이건 뺄 방법을 찾아야함
		if (static_cast<int>(m_GI->GetComponentSystems()->size()) < CompSystemIndex || CompSystemIndex < 0)
			CRASH(0);

		// 게임 인스턴스에서 > 컴포넌트 시스템 -> 컴포넌트 시스템 operation() 호출 
		// TODO : 지금은.. 컴포넌트가 아직없음.
		m_GI->GetComponentSystemByIndex(CompSystemIndex)->GetSystemOperationByIndex(Job.m_OperationIndex)();
	}
}

void EJobManager::InitThreadPool()
{
	for (int i = 0; i < m_NumCore; i++)
	{
		// 일단 emplace 써봄 pushback 대신
		// std::thread() 생성자 생략, 내부에서 만들어짐
		vThread.emplace_back(&EJobManager::ThreadProc, this);
		// vThreads.emplace_back(std::thread(&Render2DSystem::RenderSysProc, this, &Render2DSystem::ThreadTestParamFunc));
		// 윈도우식 스레드 생성 CreateThread(NULL, 0, Render2DSystem::PoolItemProc, &tp, 0, &dwThreadId);	
	}
}

void EJobManager::DestroyThreadPool()
{
	// TODO : 여기서 시간이 너무 지체되면 크래쉬 하도록 추가할 것. 금방 끝나야 정상이다.
	// 메인 스레드가 종료하면 세마포어를 공유한는 모든 같은 스레드풀의 모든 스레드에 종료하도록 값 설정
	InterlockedExchange(&m_Sema, -1);
	// 모든 스레드가 일어나서 세마포어 유효성을 확인하고 // 로직까직 가기전에 종료 처리를 시작함 // 작업중인 스레드는 다음 루프때 통보 받음.
	WakeByAddressAll(&m_Sema);
	// 스레드풀에 모든 멤버를 대상으로 join
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
	//int m_bActivate = 1; // 1 == 실행 안함, 0 == 실행함
	// 어차피 내부에 동적할당이 없어서 그냥 복사생성자 호출...
	// READ
	// m_Sema < 300
	m_pJobQueue->Push(EJob(ownerID, ComponentID, OperationIndex, activeOperation));
	InterlockedIncrement(&m_Sema);	// 새로운 작업이 추가되었으니 증가
	WakeByAddressSingle(&m_Sema);	// 작업이 추가되었으니 주소값에 대하여 대기중인 스레드를 깨워서 실행하라고 알림
}
