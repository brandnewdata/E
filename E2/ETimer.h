#pragma once
#include "Predefines.h"

class ETimer : public SystemBase
{
//**************************************************************************************************//
//																									//
//						Method Area																	//
//																									//
//**************************************************************************************************//
// �ʱ�ȭ �Լ�
protected:
	virtual void SetSystemOperationSlot() override;


public:
	// �ʱ�ȭ
	bool Init();

	float TotalTime()const;  // in seconds �ʴ���
	float DeltaTime()const; // in seconds �ʴ���

	void Reset(); // Call before message loop. �޽��� ���� ������ ȣ�� �ؾ���.
	void Start(); // Call when unpaused. Ÿ�̸� ����, �簳�� ȣ�� �ؾ���
	void Stop();  // Call when paused. �Ͻ������� ȣ�� �ؾ���
	void Tick();  // Call every frame. �� ������ ���� ȣ�� �ؾ� ����� deltatime�� �ǹ���

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
