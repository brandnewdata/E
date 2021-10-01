#pragma once
#include "SystemBase.h"

class ECollisionManager : public SystemBase
{

//**************************************************************************************************//
//																									//
//						Method Area																	//
//																									//
//**************************************************************************************************//
// 초기화 함수
protected:
	virtual void SetSystemOperationSlot() override;

private:
	bool Init();

	// 콜리젼 이벤트

	// 게임이 종료 프로세스에 들어가면
	// core에 atomic<bool> bReleaseGame이 true가 된다.
	// 그러면 모든 스레드 함수는 그 변수의 변화를 감지하고 함수를 종료한다.
	// ReleaseManager 함수는 종료 프로세스가 시작하면 호출되고
	// 모든 스레드 함수가 종료되었는지 for문으로 확인한다.
	// 아래 ThreadState가 모두 참이면 메모리 정리를 시작한다.
	//
	void ReleaseManager();
	// 이 함수 구현에는 게임 종료확인(bReleaseGame 체크)
	// 스레드 종료 보고 종료 보고 atomic<bool>* ThreadState_1시리즈가 있다.
	void CalculateCollision();

private:
	// 충돌 처리는 최대 3개의 스레드에 분산처리된다.
	// 각각 스레드 인덱스와 1대1 매칭이다.
	// 각각 스레드는 종료할 때에 이 변수의 값을 true 만들고 함수를 반환한다.
	atomic<bool>* ThreadState[3];
};

