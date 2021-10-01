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
// 초기화 함수
protected:
	virtual void SetSystemOperationSlot() override;

private:
	// 인덱스

	// 포인터가 아니라 실제 배열로 매니저 안에 가지고 있다.
	// 스택은 다른 스레드에서 접근 불가능 하다. 따라서 heap에 잡는다.
	vector<_EEntityComponent>* m_pvObject;

	// 키는 object의 임시 아이디, 데이터는 object의 컴포넌트ID List
	unordered_map<int, vector<int>> m_mapWaitCreatEntity;

public:
	bool Init();

	// Load Entity From Table
	void LoadEntityFromTable();





	// 게임이 시작하면 1회 불리는 초기화용 함수, objectInfoList를 파싱해서 오브젝트들을 생성 대기 리스트에 추가함
	bool LoadObjectFromDefault(const _EEntityComponent* obj);
	// 서버에 로그인하여 전달받은 objectInfoList를 파싱해서 오브젝트들을 생성 대기 리스트에 추가함
	bool LoadObjectFromServer();
	// 세이브 파일을 로드하여 전달받은 objectInfoList를 파싱해서 생성대기 리스트에 추가함
	bool LoadObjectFromSaveFile ();

	DECLARE_SINGLE(EEntityManager)

};

