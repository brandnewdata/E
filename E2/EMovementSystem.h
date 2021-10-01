#pragma once
#include "Predefines.h"


struct _ERotator
{
	float m_Pitch = 0.f;
	float m_Roll = 0.f;
	float m_Yaw = 0.f;
};
struct _CameraComponent
{
	uint64 m_OwnerID = 0;
	int32 m_ComponentID = 0;
	int32 m_RelatedXpos = 0;
	int32 m_RelatedYpos = 0;
	int32 m_Xpos = 0;
	int32 m_Ypos = 0;
};

// 현재 무브먼트 컴포넌트가 transform 역할까지 하고 있다.
struct  _MovementComponent
{
	// 전방벡터
	Vec2 m_ForwardVector;
	// 2D location
	POINT m_Point;
	// Rotation
	int Rotation;
	// Scale
	Vec2 m_Scale;
};

struct _MovementComponentRecord
{
	int m_OwnerID;
	int m_ComponentAssetID;
	int m_X;
	int m_Y;
	float m_SpeedPerSecond;
	// 이 값은 false == 1 , true == 0 으로 설정해야 한다.
	int m_bActivate;
};

// 이 클래스는 movement manager오 함께 선언되어야함.
#pragma pack(push, 1) 
struct MovementComponent
{
	POINT Location;
	Vec2 ForwardVector;
	float Rotator;
	// 초당 몇도나 회전 가능한지
	float RotationSpeed;
};
#pragma pack(pop)

class EMovementSystem : public SystemBase
{
//**************************************************************************************************//
//																									//
//						Property Area																//
//																									//
//**************************************************************************************************//
private:
	// 컴포넌트 공유시 동기화용
	USE_LOCK;
	vector<MovementComponent>* pvMovementComponent;

//**************************************************************************************************//
//																									//
//						Method Area																	//
//																									//
//**************************************************************************************************//

// Getter, Setter
public:
	inline const vector<MovementComponent>* GetMovementCompBlock() const
	{
		return pvMovementComponent;
	}

// 초기화 함수
protected:
	virtual void SetSystemOperationSlot() override;

	// 생성자 초기화 함수
public:
	bool Init();
// getter, setter
public:
	// 연산자 함수의 주소를 반환합니다.
	// TODO : enum대시엔 enum class 쓰는게 더 확실해 보인다...
	function<void(void)>& GetOperationPtr(int indexOperation);

public:
	// 인풋처리가 완료되면 이 함수를 호출해서 다른 스레드풀에 큐를 전달한다.
	bool StartManagerProcess();

	// 스레드에 인자로 전달될 함수.
	// param 1 : 컴포넌트 ID 리스트
	// param 2 : 컴포넌트가 연산이 필요한지 아닌지 리스트
	// 아래 코드에서 매개변수 순서 뒤집어서 집어 넣음.(주의) // 고치기도함.
	// 일단 이함수는 매니저가 소유한 coponent Block 1개에 대하여 동시에 1개만 호출된다. 스레드 세이프 보장되는 큐는 공통으로 사용한다.
	void MovementProc(/* vector<int>* vID, vector<bool>* vValidity */);

	// Coponent Operations, MovementProc 함수 내부에서 함수배열[Index]()형태로 호출되는 함수다.
private:
	// Index : 0 // job queue에 OperationIndex가 이거다.
	void MoveLeft(int componentID);

	// functional 배열. 
private:
	// 값이 유효한 최대 인덱스 함수가 2개면 1고 10개면 9이다.
	int m_SizeBindFuncs = 0;
	function<void(void)> m_BindedFuncs[11] = {
		bind(&EMovementSystem::MovementProc, this),
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

	// 상수들 다른 위치로 이동할 가능서 있음
private:
	// 월드에 배치 가능한 movementcomponent memory block위 최대개수                           
	static constexpr int iMaxMovementComponentBlock = 4;
	// movementcomponent memory block 하나에 들어가는 movementcomponent의개수
	// 총 movementcomponent의 개수 == iMaxMovementComponentBlock * iMaxMovementComponent
	static constexpr int iMaxMovementComponent = 100;

	// components
private:
	vector<MovementComponent> aMovementInfo[iMaxMovementComponentBlock];

	// other thread - game logic 교통정리 flag (사용 안하는 방식도 있을 거같음.)
	// 다른 스레드에서 컴포넌트 작업을 마치면 이 변수 값이 true가됨
	// bMultiWorkDone.load() == true?
	// 큐에 이번틱에 오브젝트 작업 입력이 모두 끝나면 스레드의 종료를 확인하고
	// 스레드의 작업진행큐와 작업수주 큐를 서로 바꾼다. 
	// bMultiWorkDone와 int 1을 xor하면 0,1토글 가능함.
	// [중요] 메인 스레드 쪽 작업이 먼저 끝나면 스레드풀의 세마포어를 올려서 
	atomic<BOOL>* InputQueueIndex = new atomic<BOOL>;
	atomic<BOOL>* OutputQueueIndex = new atomic<BOOL>;

	// 이 값이 true인 경우에만 작업큐를 swap하고 movement처리를 다른 스레드에 맏긴다.
	bool bReadyMovementProc = true;

	DECLARE_SINGLE(EMovementSystem)
}; 


