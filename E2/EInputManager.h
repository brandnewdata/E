#pragma once
#include "CoreSystems.h"

// 조합키를 만든다.
// 다른 헤더에 나눠져 있는게 더 귀찮음. 어차피 이 class에서만 쓰는데 여기 있는게 나은거 같음.
// 키 상태의 경우 1개의 정수 변수로 하고 비트연산자를 이용하는 방식으로 업그레이드 가능하다.
// 0x 0000 0001 : down 0x 0000 0002 : pressed 0x 0000 0004 : up
// 위와 같이 마스크와 상태를 & 연산하면 버튼이 가능한 상태인지 아닌지 알 수 있다.
// 아니면 버튼값을 함수 포인터 배열 인덱스로 사용해서 looktable에서 바로 envent처리함수를 호출 할수도 있다.
// 키입력 State 구조체
struct _KeyInfo
{
	// TODO : 개선의 여지가 있음 INPUT 관리자.
	// 키 이벤트 이름, 이 값은 쓰지말고 map에있는 키값 스트링을 사용하는게 더 좋아 보이는데...
	// 만약 이값만 빠지면 이 구조체는 KeyState로 명명할 수 있다. 후에 관련 내용을 다시 확인 할 것.
	// 키 이벤트 : 1개 이상의 키(실제키, 윈도우 가상키) 입력의 조합으로 이뤄진 임의의 가상키(윈도우 가상키와 별개)
	string strName;
	// 키 이벤트의 구성요소인 키조합을 저장한다. 배열.
	std::vector<DWORD> vKey;
	// 키가 눌리는 이벤트가 발생하였는가? 키가 눌린 순간 1번 참이 됨.
	bool bDown;
	// 키가 눌려진 상태를 유지중 인가? 키를 down하고 up하기 전까지는 계속 이상태를 유지함
	bool bPressed;
	// 키가 up되는 순간 1번 발생하는 이벤트 (이 이벤트가 가장 이해하기 까다로움 신경쓸 것.)
	bool bUp;
	std::vector<function<void()>*> akeyPressedEvent;

	// 구조체의 생성자 모든 키의 상태를 false로 초기화함.
	_KeyInfo() :
		strName(""),
		bDown(false),
		bPressed(false),
		bUp(false)
	{

	}
};
// 사용하게 변하게 형재정의
using KEYINFO = struct _KeyInfo;
using PKEYINFO = KEYINFO * ;


class EInputManager : public SystemBase
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
	HWND m_hWnd;
	// 사용할 키값은 한번만 설정되고 계속 검색되어 비교만된다.
	// 따라서 삽입삭제의 속도는 고려 대상이 아니고 검색 속도가 가장 빠른 방식이 좋다.
	// 해쉬자료구조 참조
	// 키이벤트이름, 키이벤트를 구성하는 실제키목록,
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
	// @param1 : 함수(ComponentOperation)을 bind할 입력 이벤트 이름
	// @parma2 : manger 포인터
	void BindKeyEventCallbackByEventName(/*const string & keyName, UserSystemBase* pManager*/)
	{
		// 실험용 변수 초기화 구간 
		//unordered_map<string, PKEYINFO>::iterator iter;
		//unordered_map<string, PKEYINFO>::iterator iterEnd = m_mapKey.end();

		// 이 키가 Pressed 상태일때 호출되는 Event Driven 함수배열
		//iter->second->akeyPressedEvent[0] = new function<void()>;
		// 다른 객체(클래스)의 멤버 함수를 등록하려면 this 값도 알아야함.
		//*(iter->second->akeyPressedEvent[0]) = bind(pManager->GetOperationByIndex(), pManager);
	}

public:

	// variadic template : 여러개의 타입을 한꺼번에  생성 가능하다.
	// 타입을 배열에 담아 두고 한개씩 꺼내서 생성한다.
	// 반드시 재귀함수를 이용해야 정상적으로 처리가 가능하다.

	// 템플릿 함수는 헤더에 내용이 있어야 정상적으로 컴파일됨. 
	// cpp로 분리하는 문법이 까다로워서 나중으로 미루다가 결국 안되는 경우 많음...
	// TODO : cpp로 정의 분리
	template <typename T, typename... Types>
	bool AddKey(const T& data, const Types& ...arg)
	{
		// AddKey 함수 한번 호출에 keyinfo객체는 딱 1개만 호출된다. - 다음 코드에 이어서 설명함.
		if (m_pNewCreatedKey == nullptr)
		{
			m_pNewCreatedKey = new struct _KeyInfo;
		}

		// 자료형을 문자열로 저장한다.
		const char* pTType = typeid(T).name();

		// 받은 값이 실제 키 값이면 배열에 키 정보.실제키값리스트에 추가한다.
		if ((strcmp(pTType, "char") == 0) || (strcmp(pTType, "int") == 0))
		{
			m_pNewCreatedKey->vKey.push_back((DWORD)data);
		}
		else
		{
			// 숫자(가상키), 문자1개(문자키)는 두가지는 여러개 받을 수 있다. 받아들인 키값 묶음으로 하나의 임의의 키입력을 만드는 것이다.
			// AddKey()함수 호출에 다른 "문자열" 여러개 넣으면 여러개의 키 이벤트가 하나의 임임의 키입력 이벤트를 공유한다.	
			// 이름 이용하면 키하나 누르면 여러 키 드리븐 이벤트가 생기도록 할 수 있다.

			// 이 부분이 실행되면 키 이벤트 이름을 KEYINFO 구조체에 할당합니다.
			// 또한 키 이벤트 이름을 키 값으로 키정보를 데이터로하는 노드를 맵에 추가한다.
			m_pNewCreatedKey->strName = data;
			m_mapKey.insert(make_pair(m_pNewCreatedKey->strName, m_pNewCreatedKey));
			
			// 아래는 중복키가 발생하는 경우 예외처리를 위한 예제
			// insert 함수는 삽입한 노드의 참조를 반환하고 그를 통하여 second를 확인하면 중복인지 확인이 가능하다.
			// 중복이면 second 값이 false이다. 삽입이 실패했다는 의미이다.
			// 만약 우리가 삽입에 시도한 노드와 키가같은 노드의 데이터 부분을 바꾸고 싶다면 
			// at() 함수를 이용해서 우리가 원하는 값으로 바꿀 수 있다.
			// 
			// if (m.insert(make_pair(3, "w")).second == false) m.at(3) = "w";
		}

		// 매개변수 배열에 요소가 2개 이상이면 현재 함수를 재귀호출한다.
		// 마지막 요소면 최종 매개변수 처리용 함수(바로 아래 정의되어 있다)가 호출된다.
		AddKey(arg...);

		//
		if (m_pNewCreatedKey)
			m_pNewCreatedKey = nullptr;

		return true;
	}

	// 가장 마지막에 매개변수가 1개인 템플릿 키 추가
	template <typename T>
	bool AddKey(const T& data)
	{
		// 자료형을 문자열로 저장한다.
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



