#include "EInputManager.h"

DEFINITION_SINGLE(EInputManager)

EInputManager::EInputManager()
	: SystemBase(), m_pNewCreatedKey(nullptr) // ���ʿ� ���µ� ��� �־ �׳� üũ�������� �ص�
{
}

EInputManager::~EInputManager()
{
	Safe_Del_Map(m_mapKey);
}

void EInputManager::SetSystemOperationSlot()
{
}

void EInputManager::bindtest()
{
}

bool EInputManager::ExcuteKeyEvent()
{

	return false;
}

bool EInputManager::Init()
{
	AddKey("MoveForward", VK_UP);
	AddKey("MoveBackward", VK_DOWN);
	AddKey("MoveRight", VK_RIGHT);
	AddKey("MoveLeft", VK_LEFT);
	AddKey("ShootBoom", '1');

	return true;
}

// ��ƽ���� Ű���� ���¸� üũ�ؼ� �Է� ���¸� ������Ʈ�Ѵ�.
void EInputManager::Update(float fDeltaTime)
{
	unordered_map<string, PKEYINFO>::iterator iter;
	unordered_map<string, PKEYINFO>::iterator iterEnd = m_mapKey.end();

	for (iter = m_mapKey.begin(); iter != iterEnd; ++iter)
	{
		// ���� ���������� ������ Ű�� ����
		int nDownedKeyCount = 0;
		for (size_t i = 0; i < iter->second->vKey.size(); ++i)
		{
			// GetAsyncKeyState()�Լ��� ��ȯ���� 1000 0000 0000 0000�� &������(����ŷó��)�� ���̷���
			// ��ȯ������ �ش� ��Ʈ�� 1���̾���Ѵ�. (1000 0000 0000 0000�� ���̸� ��ư�� �������� �ǹ��Ѵ�.)
			if (GetAsyncKeyState(iter->second->vKey[i]) & 0x8000)
				++nDownedKeyCount; // ���� ������ ��ư�� ���� �����Ѵ�.
		}
		
		// ���� ������ ��ư�� ������ Ű�� �̺�Ʈ Ȱ��ȭ ���Ǽ��� ���ٸ�
		// Ű�� ���¸� set�Ѵ�.
		if (nDownedKeyCount == iter->second->vKey.size())
		{
			// down�� pressed�� �Ѵ� false�̸� �ش� ��ư�� ó�� ���ȴٴ� ���� �ǹ��Ѵ�.
			if (iter->second->bDown == false && iter->second->bPressed == false)
			{
				// �ٿ� �̺�Ʈ �߻� // pressed�� ���� ��ȿȭ
				iter->second->bDown = true;
				iter->second->bPressed = true;
				// up�� �߻��ϰ� ���� �ӵ��� �ٽ� Ű�� �Է��ؼ� up�� ������ true�� ��츦 �����ϱ� ���ؼ�
				// ���� ���Ǽӵ��� down�� ���ȴµ� �̱����� �����餷 up�� down�� ���ÿ� ���� �������� ��������.
				iter->second->bUp = false;
				// TODO
				// Ű�Է� �̺�Ʈ�� ���ε�� �̺�Ʈ �帮�� �Լ��� ����
				// �ٸ� �Ŵ��� ��ü�� ť�� ť���ϴ� �Լ�.
			}
			// ���� tick���� ���Ӿ���key�� state�� down = true����
			// ���� ������ Ű���¿��� �ش� key�� ������ �����ִ� ���¶�� �̴� pressed = true�̴�.
			// down�̺�Ʈ�� ���� ������ 1ȸ�� �߻��ؾ� �ϹǷ� false�� ó�����ش�.
			// �ٽ��� �� �̺�Ʈ�� keydown �߻��� �Ŀ� ������ �߻��Ѵٴ� ��, keydown�� ������ �տ� 1�� �ִٴ� ��!
			else if (iter->second->bDown == true)
			{
				iter->second->bDown = false;
				// TODO
				// Ű�Է� �̺�Ʈ�� ���ε�� �̺�Ʈ �帮�� �Լ��� ����
				// �ٸ� �Ŵ��� ��ü�� ť�� ť���ϴ� �Լ�.
			}
				
		}
		else
		{
			// Ű�� Ȱ��ȭ�� �ϱ⿡�� ���� Ű�� �����ϴٸ� 
			// ������ Ű�� ���ȴ� ���� �ִ��� Ȯ���ϰ� ���� ���ȴ� ���� �ִٸ�
			// Ű�� up�Ǿ��ٴ� �̺�Ʈ�� �߻���Ų��.
			if (iter->second->bPressed)
			{
				iter->second->bUp = true;
				iter->second->bDown = false;
				iter->second->bPressed = false;

				// TODO
				// Ű�Է� �̺�Ʈ�� ���ε�� �̺�Ʈ �帮�� �Լ��� ����
				// �ٸ� �Ŵ��� ��ü�� ť�� ť���ϴ� �Լ�.
			}
			// ���� Ű�� �� ���� �����̰� 
			// ���� tick�� up�� true���ٸ� up �̺�Ʈ�� �ι� �߻����� �ʵ��� up�� false�� �ٲ۴�.
			else if (iter->second->bUp)	
				iter->second->bUp = false;
		}
	}

}

bool EInputManager::IsKeyDown(const string & strKey) const
{
	PKEYINFO pKeyInfo = FindKey(strKey);

	if (pKeyInfo == nullptr)
		return false;

	return pKeyInfo->bDown;
}

bool EInputManager::IsKeyPressed(const string & strKey) const
{
	PKEYINFO pKeyInfo = FindKey(strKey);

	if (pKeyInfo == nullptr)
		return false;

	return pKeyInfo->bPressed;
}

bool EInputManager::IsKeyUp(const string & strKey) const
{
	PKEYINFO pKeyInfo = FindKey(strKey);

	if (pKeyInfo == nullptr)
		return false;

	return pKeyInfo->bUp;
}


PKEYINFO EInputManager::FindKey(const string & strKey) const
{
	unordered_map<string, PKEYINFO>::const_iterator iter = m_mapKey.find(strKey);

	// �� ������ �ش� ���ڿ��� ��ϵ� Ű�� ���ٴ� ���̴�.!
	if (iter == m_mapKey.end())
		return nullptr;

	return iter->second;
}
