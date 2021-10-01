#pragma once
#include "Predefines.h"
#include "SystemBase.h"
#pragma comment(lib, "Synchronization.lib") 



// region collider // ����ȭ�� ���ؼ� �ʿ���/ 
struct Render2DComponent
{
	int64 m_OwnerEntityID;
	HBITMAP m_hBmp;
	HBITMAP m_hOldBmp;
	HDC m_hDC;
	BITMAP m_BitMap; // ���� ��Ʈ�� ����ü
	// ���� ������ ���� 
	BLENDFUNCTION m_BF;
	// �� ��������Ʈ�� �󸶳� �տ��ֳ� ��ġ�� Ŭ���� ���߿� ��´�.
	int m_Depth = 0;
	int m_CompDTID; // 
	int m_RenderOperationIndex;
};

class Render2DSystem : public SystemBase
{
private:
	// ������Ʈ ������ ����ȭ��
	USE_LOCK;
	// WRITE_LOCK
	// READ_LOCK
	int m_eGameState;
//**************************************************************************************************//
//																									//
//						Method Area																	//
//																									//
//**************************************************************************************************//
// �ʱ�ȭ �Լ�
protected:
	virtual void SetSystemOperationSlot() override;

private:
	// ���۷��̼Ǹ��� flag����
	int32 OperationActiveState[20][400];

	// ���ҽ� �ε尡 �ʿ��� ������Ʈ �ε��� ����Ʈ(���̵� �ƴ� �ٷ� �ε���..)
	vector<int> m_vToDoResrcLoading;
	// ss
	vector<Render2DComponent>* m_pvRender2DComp;
	void LoadRsrcByFilePath();
// �� �ý��۸� 1�� ������ Ư���� ������Ʈ
	HDC m_hDCMain;
	Render2DComponent* m_BaseRenderTarget;
	Render2DComponent* m_AlphaRenderTarget;
	Render2DComponent* m_FadeRenderTarget;
public:
// ����Ÿ�� Ȯ�� �ӽ�
void Run();

// �ʱ�ȭ �Լ���
// ������ �ν��Ͻ��κ��� ���;� �ϴ� ������ �� �Լ��� ������.
	bool Init(HDC hDC);

// operations
private:

	// void SortingByDepth();

	bool CreateBase();	// ���̽�, ����, ���̵� ���� Ÿ�� �ʱ�ȭ
	// 2DRenderComponent�߿��� ���� 3���� ������ �������� �Ʒ� ������� �ε��Ѵ�.
	bool LoadComponentFromTable();
	
	void Draw2DRenderComp(void* pParams);

	// TODO : �����ϱ�
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

// TODO : �����Ϸ��� �ۺ���, ���� ����Ҷ��¤�private�� �����ؾ���. 
public:
	void Tick(void* pPrams);

	virtual inline function<void(void*)> GetSystemOperationByIndex(int operationIndex) const override
	{
		return m_vOperation[operationIndex];
	}

	DECLARE_SINGLE(Render2DSystem)
};

