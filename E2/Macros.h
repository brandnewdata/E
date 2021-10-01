#pragma once
// ���� safe �޸� ����
#define SAFE_DEL(p) if(p) {delete p; p = nullptr; }
#define SAFE_DEL_ARR(p) if(p) {delete[] p; p = nullptr; }
// Release�� ������ class������ �۵��ϴ� �׷� �ڵ�...
#define SAFE_RELEASE(p) if(p) {p->Release(); p = nullptr; }

// �Ҹ��� ����ȭ�� �� ������Ʈ������ �ʿ��� ������.
// �̱��� Ŭ���� �ڵ�ȭ ��ũ��
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

// �̱����� ���� ������ cpp�� �����
#define DEFINITION_SINGLE(Type) Type* Type::m_pInst = nullptr;

// �̱����� getter�� �����Լ�
#define GET_SINGLE(Type)	Type::GetInst()
#define DESTROY_SINGLE(Type)	Type::DestroyInst()