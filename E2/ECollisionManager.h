#pragma once
#include "SystemBase.h"

class ECollisionManager : public SystemBase
{

//**************************************************************************************************//
//																									//
//						Method Area																	//
//																									//
//**************************************************************************************************//
// �ʱ�ȭ �Լ�
protected:
	virtual void SetSystemOperationSlot() override;

private:
	bool Init();

	// �ݸ��� �̺�Ʈ

	// ������ ���� ���μ����� ����
	// core�� atomic<bool> bReleaseGame�� true�� �ȴ�.
	// �׷��� ��� ������ �Լ��� �� ������ ��ȭ�� �����ϰ� �Լ��� �����Ѵ�.
	// ReleaseManager �Լ��� ���� ���μ����� �����ϸ� ȣ��ǰ�
	// ��� ������ �Լ��� ����Ǿ����� for������ Ȯ���Ѵ�.
	// �Ʒ� ThreadState�� ��� ���̸� �޸� ������ �����Ѵ�.
	//
	void ReleaseManager();
	// �� �Լ� �������� ���� ����Ȯ��(bReleaseGame üũ)
	// ������ ���� ���� ���� ���� atomic<bool>* ThreadState_1�ø�� �ִ�.
	void CalculateCollision();

private:
	// �浹 ó���� �ִ� 3���� �����忡 �л�ó���ȴ�.
	// ���� ������ �ε����� 1��1 ��Ī�̴�.
	// ���� ������� ������ ���� �� ������ ���� true ����� �Լ��� ��ȯ�Ѵ�.
	atomic<bool>* ThreadState[3];
};

