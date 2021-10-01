#pragma once
#include "Predefines.h"
#include "EJobQueue.h"

class EGameInstance;

class EJobManager
{
public:
	bool Init();

	// 모든 스레드에서 이 함수를 호출합니다.
	void ThreadProc();

	//  스레드풀을 생성한다.
	void InitThreadPool();

	// 스레드 풀을 제거한다.
	void DestroyThreadPool();
	
	// 초기화가 완료되고 OnBeginPlay에서 각각 시스템은 Tick마다 실행되는 함수를 큐에 추가합니다.
	// 틱마다 실행되어야 하는 component 시스템 함수는 스스로 자기 자신을 작업큐에 넣습니다.
	// 
	// @param1 : 소유자 Entity의 ID
	// @param2 : 연산대상 ComponentID ComponentSystemIndex와 ComponentIndex로 파싱된다.
	// @param3 : 수행해야하는 연산 OperationIndex (enum)
	// @param4 : 해당 연산을 수행을 원하는 경우 EActiveOperation::True(기본값, 생략가능)
	// 비활성화를 원하는 경우 EActiveOperation::False
	void PushJob(int ownerID, int ComponentID, int OperationIndex, int activeOperation = 0);

public:
	//inline EJobQueue* GetJobQueue() const
	//{
	//	return m_pJobQueue;
	//}

private:
	EGameInstance* m_GI;
	// 조건변수 스레드 대기 처리에 사용한다.
	// condition_variable m_ConVar;

	// 잡큐의 현재 크기를 바탕으로 스레드풀의 활성 비활성을 제어한다.
	// -1 : 종료, 0 : 스레드 대기(일시중지, 작업없음 상황)
	// 1~그이상 : 세마포어 차감 후 작동시작
	LONG m_Sema = 0;
	// 스레드가 현재 게임 상황에 맞춘 특별한 처리를 하도록 만드는 경우에 사용함 현재는 해당사항 없음
	atomic<uint16> m_GameStateFlag;
	// Job 저장되는 큐
	EJobQueue* m_pJobQueue;
	// 현재 컴퓨터의 가용 논리코어의 절반
	int m_NumCore;
	// 생성한 스레드 배열
	vector<std::thread> vThread;
	// 스핀락으로 스레드풀 대기


	DECLARE_SINGLE(EJobManager)
};

