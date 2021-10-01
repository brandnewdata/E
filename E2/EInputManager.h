#pragma once
#include "CoreSystems.h"

// ����Ű�� �����.
// �ٸ� ����� ������ �ִ°� �� ������. ������ �� class������ ���µ� ���� �ִ°� ������ ����.
// Ű ������ ��� 1���� ���� ������ �ϰ� ��Ʈ�����ڸ� �̿��ϴ� ������� ���׷��̵� �����ϴ�.
// 0x 0000 0001 : down 0x 0000 0002 : pressed 0x 0000 0004 : up
// ���� ���� ����ũ�� ���¸� & �����ϸ� ��ư�� ������ �������� �ƴ��� �� �� �ִ�.
// �ƴϸ� ��ư���� �Լ� ������ �迭 �ε����� ����ؼ� looktable���� �ٷ� enventó���Լ��� ȣ�� �Ҽ��� �ִ�.
// Ű�Է� State ����ü
struct _KeyInfo
{
	// TODO : ������ ������ ���� INPUT ������.
	// Ű �̺�Ʈ �̸�, �� ���� �������� map���ִ� Ű�� ��Ʈ���� ����ϴ°� �� ���� ���̴µ�...
	// ���� �̰��� ������ �� ����ü�� KeyState�� ����� �� �ִ�. �Ŀ� ���� ������ �ٽ� Ȯ�� �� ��.
	// Ű �̺�Ʈ : 1�� �̻��� Ű(����Ű, ������ ����Ű) �Է��� �������� �̷��� ������ ����Ű(������ ����Ű�� ����)
	string strName;
	// Ű �̺�Ʈ�� ��������� Ű������ �����Ѵ�. �迭.
	std::vector<DWORD> vKey;
	// Ű�� ������ �̺�Ʈ�� �߻��Ͽ��°�? Ű�� ���� ���� 1�� ���� ��.
	bool bDown;
	// Ű�� ������ ���¸� ������ �ΰ�? Ű�� down�ϰ� up�ϱ� �������� ��� �̻��¸� ������
	bool bPressed;
	// Ű�� up�Ǵ� ���� 1�� �߻��ϴ� �̺�Ʈ (�� �̺�Ʈ�� ���� �����ϱ� ��ٷο� �Ű澵 ��.)
	bool bUp;
	std::vector<function<void()>*> akeyPressedEvent;

	// ����ü�� ������ ��� Ű�� ���¸� false�� �ʱ�ȭ��.
	_KeyInfo() :
		strName(""),
		bDown(false),
		bPressed(false),
		bUp(false)
	{

	}
};
// ����ϰ� ���ϰ� ��������
using KEYINFO = struct _KeyInfo;
using PKEYINFO = KEYINFO * ;


class EInputManager : public SystemBase
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
	HWND m_hWnd;
	// ����� Ű���� �ѹ��� �����ǰ� ��� �˻��Ǿ� �񱳸��ȴ�.
	// ���� ���Ի����� �ӵ��� ��� ����� �ƴϰ� �˻� �ӵ��� ���� ���� ����� ����.
	// �ؽ��ڷᱸ�� ����
	// Ű�̺�Ʈ�̸�, Ű�̺�Ʈ�� �����ϴ� ����Ű���,
	unordered_map<string, PKEYINFO> m_mapKey;
	_KeyInfo * m_pNewCreatedKey;

	// Key Event Dispatchers
	function<void()> akeyPressedEvent[100];
	function<void()> akeyDownEvent[100];
	function<void()> akeyUpEvent[100];

	// funtionbindtest function
	void bindtest();

private:
	bool ExcuteKeyEvent();

public:
	bool Init();
	//
	void Update(float fDeltaTime);
	
public:
	bool IsKeyDown(const string& strKey) const;
	bool IsKeyPressed(const string& strKey) const;
	bool IsKeyUp(const string& strKey) const;

	// todo
	bool SetKeyPresetEvent();
	// @param1 : �Լ�(ComponentOperation)�� bind�� �Է� �̺�Ʈ �̸�
	// @parma2 : manger ������
	void BindKeyEventCallbackByEventName(/*const string & keyName, UserSystemBase* pManager*/)
	{
		// ����� ���� �ʱ�ȭ ���� 
		//unordered_map<string, PKEYINFO>::iterator iter;
		//unordered_map<string, PKEYINFO>::iterator iterEnd = m_mapKey.end();

		// �� Ű�� Pressed �����϶� ȣ��Ǵ� Event Driven �Լ��迭
		//iter->second->akeyPressedEvent[0] = new function<void()>;
		// �ٸ� ��ü(Ŭ����)�� ��� �Լ��� ����Ϸ��� this ���� �˾ƾ���.
		//*(iter->second->akeyPressedEvent[0]) = bind(pManager->GetOperationByIndex(), pManager);
	}

public:

	// variadic template : �������� Ÿ���� �Ѳ�����  ���� �����ϴ�.
	// Ÿ���� �迭�� ��� �ΰ� �Ѱ��� ������ �����Ѵ�.
	// �ݵ�� ����Լ��� �̿��ؾ� ���������� ó���� �����ϴ�.

	// ���ø� �Լ��� ����� ������ �־�� ���������� �����ϵ�. 
	// cpp�� �и��ϴ� ������ ��ٷο��� �������� �̷�ٰ� �ᱹ �ȵǴ� ��� ����...
	// TODO : cpp�� ���� �и�
	template <typename T, typename... Types>
	bool AddKey(const T& data, const Types& ...arg)
	{
		// AddKey �Լ� �ѹ� ȣ�⿡ keyinfo��ü�� �� 1���� ȣ��ȴ�. - ���� �ڵ忡 �̾ ������.
		if (m_pNewCreatedKey == nullptr)
		{
			m_pNewCreatedKey = new struct _KeyInfo;
		}

		// �ڷ����� ���ڿ��� �����Ѵ�.
		const char* pTType = typeid(T).name();

		// ���� ���� ���� Ű ���̸� �迭�� Ű ����.����Ű������Ʈ�� �߰��Ѵ�.
		if ((strcmp(pTType, "char") == 0) || (strcmp(pTType, "int") == 0))
		{
			m_pNewCreatedKey->vKey.push_back((DWORD)data);
		}
		else
		{
			// ����(����Ű), ����1��(����Ű)�� �ΰ����� ������ ���� �� �ִ�. �޾Ƶ��� Ű�� �������� �ϳ��� ������ Ű�Է��� ����� ���̴�.
			// AddKey()�Լ� ȣ�⿡ �ٸ� "���ڿ�" ������ ������ �������� Ű �̺�Ʈ�� �ϳ��� ������ Ű�Է� �̺�Ʈ�� �����Ѵ�.	
			// �̸� �̿��ϸ� Ű�ϳ� ������ ���� Ű �帮�� �̺�Ʈ�� ���⵵�� �� �� �ִ�.

			// �� �κ��� ����Ǹ� Ű �̺�Ʈ �̸��� KEYINFO ����ü�� �Ҵ��մϴ�.
			// ���� Ű �̺�Ʈ �̸��� Ű ������ Ű������ �����ͷ��ϴ� ��带 �ʿ� �߰��Ѵ�.
			m_pNewCreatedKey->strName = data;
			m_mapKey.insert(make_pair(m_pNewCreatedKey->strName, m_pNewCreatedKey));
			
			// �Ʒ��� �ߺ�Ű�� �߻��ϴ� ��� ����ó���� ���� ����
			// insert �Լ��� ������ ����� ������ ��ȯ�ϰ� �׸� ���Ͽ� second�� Ȯ���ϸ� �ߺ����� Ȯ���� �����ϴ�.
			// �ߺ��̸� second ���� false�̴�. ������ �����ߴٴ� �ǹ��̴�.
			// ���� �츮�� ���Կ� �õ��� ���� Ű������ ����� ������ �κ��� �ٲٰ� �ʹٸ� 
			// at() �Լ��� �̿��ؼ� �츮�� ���ϴ� ������ �ٲ� �� �ִ�.
			// 
			// if (m.insert(make_pair(3, "w")).second == false) m.at(3) = "w";
		}

		// �Ű����� �迭�� ��Ұ� 2�� �̻��̸� ���� �Լ��� ���ȣ���Ѵ�.
		// ������ ��Ҹ� ���� �Ű����� ó���� �Լ�(�ٷ� �Ʒ� ���ǵǾ� �ִ�)�� ȣ��ȴ�.
		AddKey(arg...);

		//
		if (m_pNewCreatedKey)
			m_pNewCreatedKey = nullptr;

		return true;
	}

	// ���� �������� �Ű������� 1���� ���ø� Ű �߰�
	template <typename T>
	bool AddKey(const T& data)
	{
		// �ڷ����� ���ڿ��� �����Ѵ�.
		const char* pTType = typeid(T).name();

		if (strcmp(pTType, "char") == 0 || strcmp(pTType, "int") == 0)
		{
			m_pNewCreatedKey->vKey.push_back((DWORD)(data));
		}
		else
		{
			m_pNewCreatedKey->strName = data;
			m_mapKey.insert(make_pair(m_pNewCreatedKey->strName, m_pNewCreatedKey));
		}

		return true;
	}

private:
	PKEYINFO FindKey(const string& strKey) const;


	DECLARE_SINGLE(EInputManager)
};



