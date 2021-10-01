#pragma once
#include "Predefines.h"

struct _EEntityComponent
{
	uint64 m_EntityID;
	int m_SizeComponentList;
	vector<int> m_vComponentID;
};

class EEntityManager : public SystemBase
{
//**************************************************************************************************//
//																									//
//						Property Area																//
//																									//
//**************************************************************************************************//
private:

//**************************************************************************************************//
//																									//
//						Method Area																	//
//																									//
//**************************************************************************************************//
// �ʱ�ȭ �Լ�
protected:
	virtual void SetSystemOperationSlot() override;

private:
	// �ε���

	// �����Ͱ� �ƴ϶� ���� �迭�� �Ŵ��� �ȿ� ������ �ִ�.
	// ������ �ٸ� �����忡�� ���� �Ұ��� �ϴ�. ���� heap�� ��´�.
	vector<_EEntityComponent>* m_pvObject;

	// Ű�� object�� �ӽ� ���̵�, �����ʹ� object�� ������ƮID List
	unordered_map<int, vector<int>> m_mapWaitCreatEntity;

public:
	bool Init();

	// Load Entity From Table
	void LoadEntityFromTable();





	// ������ �����ϸ� 1ȸ �Ҹ��� �ʱ�ȭ�� �Լ�, objectInfoList�� �Ľ��ؼ� ������Ʈ���� ���� ��� ����Ʈ�� �߰���
	bool LoadObjectFromDefault(const _EEntityComponent* obj);
	// ������ �α����Ͽ� ���޹��� objectInfoList�� �Ľ��ؼ� ������Ʈ���� ���� ��� ����Ʈ�� �߰���
	bool LoadObjectFromServer();
	// ���̺� ������ �ε��Ͽ� ���޹��� objectInfoList�� �Ľ��ؼ� ������� ����Ʈ�� �߰���
	bool LoadObjectFromSaveFile ();

	DECLARE_SINGLE(EEntityManager)

};

