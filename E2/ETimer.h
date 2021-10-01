#pragma once
#include "Predefines.h"

class ETimer : public SystemBase
{
//**************************************************************************************************//
//																									//
//						Method Area																	//
//																									//
//**************************************************************************************************//
// 초기화 함수
protected:
	virtual void SetSystemOperationSlot() override;


public:
	// 초기화
	bool Init();

	float TotalTime()const;  // in seconds 초단위
	float DeltaTime()const; // in seconds 초단위

	void Reset(); // Call before message loop. 메시지 루프 이전에 호출 해야함.
	void Start(); // Call when unpaused. 타이머 시작, 재개시 호출 해야함
	void Stop();  // Call when paused. 일시정지시 호출 해야함
	void Tick();  // Call every frame. 매 프리임 마다 호출 해야 사용함 deltatime을 의미함

private:
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime;
	__int64 mPausedTime;
	__int64 mStopTime;
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool mStopped;

	DECLARE_SINGLE(ETimer)
};
