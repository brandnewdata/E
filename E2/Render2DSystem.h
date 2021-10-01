#pragma once
#include "Predefines.h"
#include "SystemBase.h"
#pragma comment(lib, "Synchronization.lib") 



// region collider // 최적화를 위해서 필요함/ 
struct Render2DComponent
{
	int64 m_OwnerEntityID;
	HBITMAP m_hBmp;
	HBITMAP m_hOldBmp;
	HDC m_hDC;
	BITMAP m_BitMap; // 실제 비트맵 구조체
	// 알플 블렌딩을 위한 
	BLENDFUNCTION m_BF;
	// 이 스프라이트가 얼마나 앞에있나 수치가 클수록 나중에 찍는다.
	int m_Depth = 0;
	int m_CompDTID; // 
	int m_RenderOperationIndex;
};

class Render2DSystem : public SystemBase
{
private:
	// 컴포넌트 공유시 동기화용
	USE_LOCK;
	// WRITE_LOCK
	// READ_LOCK
	int m_eGameState;
//**************************************************************************************************//
//																									//
//						Method Area																	//
//																									//
//**************************************************************************************************//
// 초기화 함수
protected:
	virtual void SetSystemOperationSlot() override;

private:
	// 오퍼레이션마다 flag있음
	int32 OperationActiveState[20][400];

	// 리소스 로드가 필요한 컴포넌트 인덱스 리스트(아이디 아님 바로 인덱스..)
	vector<int> m_vToDoResrcLoading;
	// ss
	vector<Render2DComponent>* m_pvRender2DComp;
	void LoadRsrcByFilePath();
// 이 시스템만 1개 가지는 특수한 컴포넌트
	HDC m_hDCMain;
	Render2DComponent* m_BaseRenderTarget;
	Render2DComponent* m_AlphaRenderTarget;
	Render2DComponent* m_FadeRenderTarget;
public:
// 렌더타켓 확인 임시
void Run();

// 초기화 함수들
// 윈도우 인스턴스로부터 얻어와야 하는 값들은 이 함수로 얻어오자.
	bool Init(HDC hDC);

// operations
private:

	// void SortingByDepth();

	bool CreateBase();	// 베이스, 알파, 페이드 렌더 타겟 초기화
	// 2DRenderComponent중에서 위의 3개를 제외한 나머지는 아래 방식으로 로드한다.
	bool LoadComponentFromTable();
	
	void Draw2DRenderComp(void* pParams);

	// TODO : 정리하기
	void DrawBGAll();
	void DrawBG();
	void DrawBG2();
	void DrawBG3();
	void DrawHero();
	void DrawHeroAlpha();
	void DrawEnemy();
	void DrawBullet();
	void DrawExplode();
	void DrawTitle();
	void DrawTextTitle();
	void DrawPress();
	void DrawReady();
	void DrawStart();
	void DrawPause();
	void DrawScore();
	void DrawClear();
	void DrawFade();
	void DrawFrame();

// TODO : 실험하려고 퍼블릭함, 실제 사용할때는ㅇprivate로 변경해야함. 
public:
	void Tick(void* pPrams);

	virtual inline function<void(void*)> GetSystemOperationByIndex(int operationIndex) const override
	{
		return m_vOperation[operationIndex];
	}

	DECLARE_SINGLE(Render2DSystem)
};

