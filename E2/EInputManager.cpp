#include "EInputManager.h"

DEFINITION_SINGLE(EInputManager)

EInputManager::EInputManager()
	: SystemBase(), m_pNewCreatedKey(nullptr) // 할필요 없는데 사건 있어서 그냥 체크차원에서 해둠
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

// 매틱마다 키보드 상태를 체크해서 입력 상태를 업데이트한다.
void EInputManager::Update(float fDeltaTime)
{
	unordered_map<string, PKEYINFO>::iterator iter;
	unordered_map<string, PKEYINFO>::iterator iterEnd = m_mapKey.end();

	for (iter = m_mapKey.begin(); iter != iterEnd; ++iter)
	{
		// 현재 눌린상태인 윈도우 키의 숫자
		int nDownedKeyCount = 0;
		for (size_t i = 0; i < iter->second->vKey.size(); ++i)
		{
			// GetAsyncKeyState()함수의 반환값이 1000 0000 0000 0000과 &연산후(마스킹처리)에 참이려면
			// 반환값에서 해당 비트가 1이이어야한다. (1000 0000 0000 0000가 참이면 버튼이 눌렸음을 의미한다.)
			if (GetAsyncKeyState(iter->second->vKey[i]) & 0x8000)
				++nDownedKeyCount; // 눌린 상태인 버튼의 수를 누적한다.
		}
		
		// 눌린 상태인 버튼의 개수가 키를 이벤트 활성화 조건수와 같다면
		// 키의 상태를 set한다.
		if (nDownedKeyCount == iter->second->vKey.size())
		{
			// down과 pressed가 둘다 false이면 해당 버튼이 처음 눌렸다는 것을 의미한다.
			if (iter->second->bDown == false && iter->second->bPressed == false)
			{
				// 다운 이벤트 발생 // pressed도 같이 유효화
				iter->second->bDown = true;
				iter->second->bPressed = true;
				// up이 발생하고 빛의 속도로 다시 키를 입력해서 up이 여전히 true인 경우를 방지하기 위해서
				// 만약 빛의속도로 down이 눌렸는데 이구문이 없으면ㅇ up과 down이 동시에 참인 괴현상이 가능해짐.
				iter->second->bUp = false;
				// TODO
				// 키입력 이벤트에 바인드된 이벤트 드리븐 함수들 실행
				// 다른 매니저 객체의 큐에 큐잉하는 함수.
			}
			// 이전 tick에서 게임앱의key의 state가 down = true였고
			// 현재 윈도우 키상태에서 해당 key가 여전히 눌려있는 상태라면 이는 pressed = true이다.
			// down이벤트는 눌린 시점에 1회만 발생해야 하므로 false로 처리해준다.
			// 핵심은 이 이벤트는 keydown 발생한 후에 무조건 발생한다는 것, keydown이 무조건 앞에 1번 있다는 것!
			else if (iter->second->bDown == true)
			{
				iter->second->bDown = false;
				// TODO
				// 키입력 이벤트에 바인드된 이벤트 드리븐 함수들 실행
				// 다른 매니저 객체의 큐에 큐잉하는 함수.
			}
				
		}
		else
		{
			// 키가 활성화를 하기에는 눌린 키가 부족하다면 
			// 이전에 키가 눌렸던 적이 있는지 확인하고 만약 눌렸던 적이 있다면
			// 키가 up되었다는 이벤트를 발생시킨다.
			if (iter->second->bPressed)
			{
				iter->second->bUp = true;
				iter->second->bDown = false;
				iter->second->bPressed = false;

				// TODO
				// 키입력 이벤트에 바인드된 이벤트 드리븐 함수들 실행
				// 다른 매니저 객체의 큐에 큐잉하는 함수.
			}
			// 현재 키는 안 눌린 상태이고 
			// 이전 tick에 up이 true였다면 up 이벤트가 두번 발생하지 않도록 up을 false로 바꾼다.
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

	// 다 뒤져도 해당 문자열로 등록된 키가 없다는 말이다.!
	if (iter == m_mapKey.end())
		return nullptr;

	return iter->second;
}
