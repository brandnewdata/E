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

// ���� �����Ʈ ������Ʈ�� transform ���ұ��� �ϰ� �ִ�.
struct  _MovementComponent
{
	// ���溤��
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
	// �� ���� false == 1 , true == 0 ���� �����ؾ� �Ѵ�.
	int m_bActivate;
};

// �� Ŭ������ movement manager�� �Բ� ����Ǿ����.
#pragma pack(push, 1) 
struct MovementComponent
{
	POINT Location;
	Vec2 ForwardVector;
	float Rotator;
	// �ʴ� ��� ȸ�� ��������
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
	// ������Ʈ ������ ����ȭ��
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

// �ʱ�ȭ �Լ�
protected:
	virtual void SetSystemOperationSlot() override;

	// ������ �ʱ�ȭ �Լ�
public:
	bool Init();
// getter, setter
public:
	// ������ �Լ��� �ּҸ� ��ȯ�մϴ�.
	// TODO : enum��ÿ� enum class ���°� �� Ȯ���� ���δ�...
	function<void(void)>& GetOperationPtr(int indexOperation);

public:
	// ��ǲó���� �Ϸ�Ǹ� �� �Լ��� ȣ���ؼ� �ٸ� ������Ǯ�� ť�� �����Ѵ�.
	bool StartManagerProcess();

	// �����忡 ���ڷ� ���޵� �Լ�.
	// param 1 : ������Ʈ ID ����Ʈ
	// param 2 : ������Ʈ�� ������ �ʿ����� �ƴ��� ����Ʈ
	// �Ʒ� �ڵ忡�� �Ű����� ���� ����� ���� ����.(����) // ��ġ�⵵��.
	// �ϴ� ���Լ��� �Ŵ����� ������ coponent Block 1���� ���Ͽ� ���ÿ� 1���� ȣ��ȴ�. ������ ������ ����Ǵ� ť�� �������� ����Ѵ�.
	void MovementProc(/* vector<int>* vID, vector<bool>* vValidity */);

	// Coponent Operations, MovementProc �Լ� ���ο��� �Լ��迭[Index]()���·� ȣ��Ǵ� �Լ���.
private:
	// Index : 0 // job queue�� OperationIndex�� �̰Ŵ�.
	void MoveLeft(int componentID);

	// functional �迭. 
private:
	// ���� ��ȿ�� �ִ� �ε��� �Լ��� 2���� 1�� 10���� 9�̴�.
	int m_SizeBindFuncs = 0;
	function<void(void)> m_BindedFuncs[11] = {
		bind(&EMovementSystem::MovementProc, this),
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

	// ����� �ٸ� ��ġ�� �̵��� ���ɼ� ����
private:
	// ���忡 ��ġ ������ movementcomponent memory block�� �ִ밳��                           
	static constexpr int iMaxMovementComponentBlock = 4;
	// movementcomponent memory block �ϳ��� ���� movementcomponent�ǰ���
	// �� movementcomponent�� ���� == iMaxMovementComponentBlock * iMaxMovementComponent
	static constexpr int iMaxMovementComponent = 100;

	// components
private:
	vector<MovementComponent> aMovementInfo[iMaxMovementComponentBlock];

	// other thread - game logic �������� flag (��� ���ϴ� ��ĵ� ���� �Ű���.)
	// �ٸ� �����忡�� ������Ʈ �۾��� ��ġ�� �� ���� ���� true����
	// bMultiWorkDone.load() == true?
	// ť�� �̹�ƽ�� ������Ʈ �۾� �Է��� ��� ������ �������� ���Ḧ Ȯ���ϰ�
	// �������� �۾�����ť�� �۾����� ť�� ���� �ٲ۴�. 
	// bMultiWorkDone�� int 1�� xor�ϸ� 0,1��� ������.
	// [�߿�] ���� ������ �� �۾��� ���� ������ ������Ǯ�� ������� �÷��� 
	atomic<BOOL>* InputQueueIndex = new atomic<BOOL>;
	atomic<BOOL>* OutputQueueIndex = new atomic<BOOL>;

	// �� ���� true�� ��쿡�� �۾�ť�� swap�ϰ� movementó���� �ٸ� �����忡 �����.
	bool bReadyMovementProc = true;

	DECLARE_SINGLE(EMovementSystem)
}; 


