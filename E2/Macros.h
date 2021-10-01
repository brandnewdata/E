#pragma once
// 공용 safe 메모리 해제
#define SAFE_DEL(p) if(p) {delete p; p = nullptr; }
#define SAFE_DEL_ARR(p) if(p) {delete[] p; p = nullptr; }
// Release가 구현된 class에서만 작동하는 그런 코드...
#define SAFE_RELEASE(p) if(p) {p->Release(); p = nullptr; }

// 소멸자 가상화는 이 프로젝트에서만 필요한 구조다.
// 싱글톤 클래스 자동화 매크로
#define DECLARE_SINGLE(Type)	\
	private:\
		static Type*	m_pInst;\
	public:\
		static Type* GetInst()\
		{\
			if(!m_pInst)\
				m_pInst = new Type;\
			return m_pInst;\
		}\
		static void DestroyInst()\
		{\
			SAFE_DEL(m_pInst);\
		}\
	private:\
		Type();\
		virtual ~Type() final;

// 싱글턴의 전역 변수로 cpp에 선언용
#define DEFINITION_SINGLE(Type) Type* Type::m_pInst = nullptr;

// 싱글턴의 getter와 해제함수
#define GET_SINGLE(Type)	Type::GetInst()
#define DESTROY_SINGLE(Type)	Type::DestroyInst()