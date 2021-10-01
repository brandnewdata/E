#include "Render2DSystem.h"
#include "EJobManager.h"
#include "ETableManager.h"
#include "EEntityTable.h"
#include "CommonEnums.h"
#include "LockMacro.h"
#include "EMovementSystem.h"

DEFINITION_SINGLE(Render2DSystem)

Render2DSystem::Render2DSystem()
	: SystemBase()
{
	m_pvRender2DComp = new vector<Render2DComponent>;

	m_BaseRenderTarget = new Render2DComponent;
	m_AlphaRenderTarget = new Render2DComponent;
	m_FadeRenderTarget = new Render2DComponent;
}

Render2DSystem::~Render2DSystem()
{
	// https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-deleteobject
	DeleteObject(m_BaseRenderTarget->m_hBmp);
	// ���ҽ�������
	DeleteDC(m_BaseRenderTarget->m_hDC);
}

// TODO : ������ �� �Լ��� �� �� �ʿ����� �������.
void Render2DSystem::SetSystemOperationSlot()
{
	m_vOperation.push_back(bind(&Render2DSystem::Tick, this, placeholders::_1));
	m_vOperation.push_back(bind(&Render2DSystem::Draw2DRenderComp, this, placeholders::_1));
}

void Render2DSystem::LoadRsrcByFilePath()
{
}

void Render2DSystem::Run()
{
}

bool Render2DSystem::Init(HDC hDC)
{ 
	SetSystemOperationSlot();

	m_hDCMain = hDC;
	if (CreateBase() == false)
		return false;
	return true;
}

void Render2DSystem::Draw2DRenderComp(void* pParams)
{
	// WRITE_LOCK
	const unordered_map<uint64, int>* pMoveCompIndexMap(nullptr);
	pMoveCompIndexMap = GET_SINGLE(EMovementSystem)->GetCompIndexMap();
	if (pMoveCompIndexMap == nullptr)
		return;

	const vector<MovementComponent>* pMoveCompBlock(nullptr);
	pMoveCompBlock = GET_SINGLE(EMovementSystem)->GetMovementCompBlock();
	if (pMoveCompBlock == nullptr)
		return;

	vector<Render2DComponent>::iterator Iter = m_pvRender2DComp->begin();
	vector<Render2DComponent>::iterator EndIter = m_pvRender2DComp->end();
	int i = 0;

	// TODO : if�� ��� vs 32kb activeTable���� �߿� ��� ���� ������ �� ������?
	READ_LOCK
	for (Iter; Iter != EndIter; ++Iter)
	{
		int64 ownerID = m_vRender2DComp[CompIndex].m_OwnerEntityID;
		unordered_map<uint64, int>::const_iterator iter = pMoveCompIndexMap->find(ownerID);
	}
}
bool Render2DSystem::LoadComponentFromTable()
{
	LPCWCHAR NewPath;
	Render2DComponent NewComponent;

	const unordered_map<uint32, Render2DComponentDTRecord>* pAssetTable = GET_SINGLE(ETableManager)->GetRender2DComponentAssetTable();
	unordered_map<uint32, Render2DComponentDTRecord>::const_iterator iter = pAssetTable->begin();
	unordered_map<uint32, Render2DComponentDTRecord>::const_iterator iterEnd = pAssetTable->end();
	
	for (iter; iter != iterEnd; ++iter)
	{
		NewPath = iter->second.m_2DTextrueFilePath;

		NewComponent.m_hBmp = (HBITMAP)LoadImage(NULL, NewPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//��Ʈ�� �ڵ� ������ ���� 
		if (NewComponent.m_hBmp == NULL)
		{
			MessageBox(NULL, NewPath, L"��Ʈ�� �ε� ����", MB_OK);
			return false;
		}
		NewComponent.m_hDC = CreateCompatibleDC(NULL); // ��ü�� ��Ȯ�� �𸣰ھ� �̰�
		NewComponent.m_hOldBmp = (HBITMAP)SelectObject(NewComponent.m_hDC, NewComponent.m_hBmp);//dc �� ��Ʈ���̶� ����
		GetObject(NewComponent.m_hBmp, sizeof(BITMAP), &NewComponent.m_BitMap);

		m_vRender2DComp.push_back(NewComponent);
	}
	return false;
}



bool Render2DSystem::CreateBase()
{
	LPCWCHAR BasePath = GET_SINGLE(ETableManager)->GetFilePathByComponentDTID(RenderBase_2DRenderCompDTID);
	LPCWCHAR AlphaPath = GET_SINGLE(ETableManager)->GetFilePathByComponentDTID(AlphaBase_2DRenderCompDTID);
	LPCWCHAR FadePath = GET_SINGLE(ETableManager)->GetFilePathByComponentDTID(FadeBase_2DRenderCompDTID);

	// Base 
	m_BaseRenderTarget->m_hBmp = (HBITMAP)LoadImage(NULL, BasePath, IMAGE_BITMAP,0 , 0, LR_LOADFROMFILE);//��Ʈ�� �ڵ� ������ ���� 
	if (m_BaseRenderTarget->m_hBmp == NULL)
	{
		MessageBox(NULL, BasePath, L"��Ʈ�� �ε� ����", MB_OK);
		return false;
	}
	m_BaseRenderTarget->m_hDC = CreateCompatibleDC(NULL); // ��ü�� ��Ȯ�� �𸣰ھ� �̰�
	m_BaseRenderTarget->m_hOldBmp = (HBITMAP)SelectObject(m_BaseRenderTarget->m_hDC, m_BaseRenderTarget->m_hBmp);//dc �� ��Ʈ���̶� ����
	GetObject(m_BaseRenderTarget->m_hBmp, sizeof(BITMAP), &m_BaseRenderTarget->m_BitMap);
	
	// Alpha
	m_AlphaRenderTarget->m_hBmp = (HBITMAP)LoadImage(NULL, AlphaPath, IMAGE_BITMAP,0 , 0, LR_LOADFROMFILE);//��Ʈ�� �ڵ� ������ ���� 
	if (m_AlphaRenderTarget->m_hBmp == NULL)
	{
		MessageBox(NULL, AlphaPath, L"��Ʈ�� �ε� ����", MB_OK);
		return false;
	}
	m_AlphaRenderTarget->m_hDC = CreateCompatibleDC(NULL); // ��ü�� ��Ȯ�� �𸣰ھ� �̰�
	m_AlphaRenderTarget->m_hOldBmp = (HBITMAP)SelectObject(m_AlphaRenderTarget->m_hDC, m_AlphaRenderTarget->m_hBmp);//dc �� ��Ʈ���̶� ����
	GetObject(m_AlphaRenderTarget->m_hBmp, sizeof(BITMAP), &m_AlphaRenderTarget->m_BitMap);
	
	m_AlphaRenderTarget->m_BF.AlphaFormat = 0;
	m_AlphaRenderTarget->m_BF.BlendFlags = 0;
	m_AlphaRenderTarget->m_BF.BlendOp = 0;
	m_AlphaRenderTarget->m_BF.SourceConstantAlpha = 255; // ���� 0~255 // 127~128 ������

	// Fade 
	m_FadeRenderTarget->m_hBmp = (HBITMAP)LoadImage(NULL, FadePath, IMAGE_BITMAP,0 , 0, LR_LOADFROMFILE);//��Ʈ�� �ڵ� ������ ���� 

	if (m_FadeRenderTarget->m_hBmp == NULL)
	{
		MessageBox(NULL, FadePath, L"��Ʈ�� �ε� ����", MB_OK);
		return false;
	}
	m_FadeRenderTarget->m_hDC = CreateCompatibleDC(NULL); // ��ü�� ��Ȯ�� �𸣰ھ� �̰�
	m_FadeRenderTarget->m_hOldBmp = (HBITMAP)SelectObject(m_FadeRenderTarget->m_hDC, m_FadeRenderTarget->m_hBmp);//dc �� ��Ʈ���̶� ����
	GetObject(m_FadeRenderTarget->m_hBmp, sizeof(BITMAP), &m_FadeRenderTarget->m_BitMap);

	m_FadeRenderTarget->m_BF.AlphaFormat = 0;
	m_FadeRenderTarget->m_BF.BlendFlags = 0;
	m_FadeRenderTarget->m_BF.BlendOp = 0;
	m_FadeRenderTarget->m_BF.SourceConstantAlpha = 255;//������...0�������� ������ 127

	return true;
}

void Render2DSystem::DrawBGAll()
{
	switch (m_nStageNum)
	{
	case 0:
		DrawBG();
		break;
	case 1:
		DrawBG2();
		break;
	case 2:
		DrawBG3();
		break;
	default:
		break;
	}
}

void Render2DSystem::DrawBG()
{
	//base dc�� bg dc ����������
	BitBlt(m_Base.dc,//dest dc
		0, 0, //��𿡴ٰ� �������� ��ǥ
		m_BG.bit.bmWidth,//���� ���� ����
		m_BG.bit.bmHeight,
		m_BG.dc,//src dc
		0, 0, //�ҽ� ��𼭺��� �������� ��ǥ
		SRCCOPY //���� ������� �ɼ� 
	);

}

void Render2DSystem::DrawBG2()
{
	StretchBlt(m_Base.dc,//����Ʈ
		0, 0, XRES, YRES,//����̶� 1024 768 ���� 
		m_BG2.dc,//�ҽ�
		0,//����ũ���̶� x��ǥ�� 0���� ���� 
		m_BG2.pt.y,
		XRES, YRES,//
		SRCCOPY);

}

void Render2DSystem::DrawBG3()
{
	//BitBlt(m_Base.dc, 0, 0,
	//	XRES, YRES,
	//	m_BG3[m_uBG3.Frame].dc,	0, 0, SRCCOPY);
	StretchBlt(m_Base.dc,
		0, 0, XRES, YRES,
		m_BG3[m_uBG3.Frame].dc,
		0, 0, 640, 480,
		SRCCOPY);
}

void Render2DSystem::DrawHero()
{
	//base  <- hero
	TransparentBlt(m_Base.dc,//dest
		m_Hero.pt.x,
		m_Hero.pt.y,
		m_Hero.bit.bmWidth,
		m_Hero.bit.bmHeight,
		m_Hero.dc,//src
		0, 0,
		m_Hero.bit.bmWidth,
		m_Hero.bit.bmHeight,
		RGB(255, 0, 255)
	);
}

void Render2DSystem::DrawHeroAlpha()
{
	//1.�ϴ� ���ݱ��� ���̽��� ���Ŀ��ٰ� ������ (bitblt)
	BitBlt(m_Alpha.dc, 0, 0, XRES, YRES, m_Base.dc, 0, 0, SRCCOPY);

	//2. �� ���Ŀ��ٰ� ����� ��� (trans)
	TransparentBlt(m_Alpha.dc,//dest
		m_Hero.pt.x,
		m_Hero.pt.y,
		m_Hero.bit.bmWidth,
		m_Hero.bit.bmHeight,
		m_Hero.dc,//src
		0, 0,
		m_Hero.bit.bmWidth,
		m_Hero.bit.bmHeight,
		RGB(255, 0, 255)
	);

	// �ٽ��� ���� ���̽��� ������޵Ǽ� �������� ���� �ȼ��� ȭ�鿡 �����°�! []=--------
	//3.���ĺ귻�� �Լ��� ���̽����ٰ� ���ĸ� ��� (alphablend)
	AlphaBlend(m_Base.dc,
		m_Hero.pt.x,
		m_Hero.pt.y,
		m_Hero.bit.bmWidth,
		m_Hero.bit.bmHeight,
		m_Alpha.dc,
		m_Hero.pt.x,
		m_Hero.pt.y,
		m_Hero.bit.bmWidth,
		m_Hero.bit.bmHeight,
		m_Hero.bf);
}

void Render2DSystem::DrawEnemy()
{
	TransparentBlt(m_Base.dc,//dest
		m_Enemy.pt.x,
		m_Enemy.pt.y,
		m_Enemy.bit.bmWidth,
		m_Enemy.bit.bmHeight,
		m_Enemy.dc,//src
		0, 0,
		m_Enemy.bit.bmWidth,
		m_Enemy.bit.bmHeight,
		RGB(255, 0, 255)
	);
}

void Render2DSystem::DrawBullet()
{
	if (m_uHero.bTrigger == FALSE)  return;

	TransparentBlt(m_Base.dc,
		m_Bullet.pt.x,
		m_Bullet.pt.y,
		m_Bullet.bit.bmWidth,
		m_Bullet.bit.bmHeight,
		m_Bullet.dc,
		0, 0,
		m_Bullet.bit.bmWidth,
		m_Bullet.bit.bmHeight,
		RGB(255, 0, 255)
	);
}

void Render2DSystem::DrawExplode()
{
	if (m_uExplode.bTrigger == FALSE) return; //���� ���� �ƴ� ������

	TransparentBlt(m_Base.dc,
		m_Explde.pt.x,
		m_Explde.pt.y,//���� ������ ��ġ xy
		m_uExplode.size, //m_u
		m_Explde.bit.bmHeight, //m_
		m_Explde.dc,//�ҽ��� dc
		m_uExplode.Frame * m_uExplode.size,//�ҽ��� x ��ǥ�� ó����0�̴�
		0,///y ��ǥ�� ó�� ó������ �������Ŵ� 
		m_uExplode.size,//���� �ҽ��� �ʺ�
		m_Explde.bit.bmHeight,//�ҽ��� ����
		RGB(0, 0, 255)//������ ��ȫ������ٰ� ���� �׸����� .. 
	);


}
void Render2DSystem::DrawTitle()
{	//base dc�� bg dc ����������
	BitBlt(m_Base.dc,//dest dc
		0, 0, //��𿡴ٰ� �������� ��ǥ
		m_Title.bit.bmWidth,//���� ���� ����
		m_Title.bit.bmHeight,
		m_Title.dc,//src dc
		0, 0, //�ҽ� ��𼭺��� �������� ��ǥ
		SRCCOPY //���� ������� �ɼ� 
	);
}

void Render2DSystem::DrawTextTitle()
{
	int x = m_rtClient.right / 2 - 280;
	int y = 150;
	WCHAR title[] = L"PENGSU's ADV";

	SetBkMode(m_Base.dc, TRANSPARENT); //���� ����� �����ϰ� 

	SetTextColor(m_Base.dc, RGB(195, 195, 195));
	TextOut(m_Base.dc, x, y, title, 12);

	SetTextColor(m_Base.dc, RGB(255, 201, 14));
	TextOut(m_Base.dc, x - 2, y - 2, title, 12);

}
void Render2DSystem::DrawPress()
{
	if (m_uPress.bTrigger == FALSE) return;

	int x = m_rtClient.right / 2 - m_Press.bit.bmWidth / 2;
	int y = 500;
	TransparentBlt(m_Base.dc,//dest
		x,
		y,
		m_Press.bit.bmWidth,
		m_Press.bit.bmHeight,
		m_Press.dc,//src
		0, 0,
		m_Press.bit.bmWidth,
		m_Press.bit.bmHeight,
		RGB(255, 0, 255)
	);

}

void Render2DSystem::DrawReady()
{
	int x = m_rtClient.right / 2 - m_Ready.bit.bmWidth / 2;
	int y = m_rtClient.bottom / 2 - m_Ready.bit.bmHeight / 2;
	TransparentBlt(m_Base.dc,//dest
		x,
		y,
		m_Ready.bit.bmWidth,
		m_Ready.bit.bmHeight,
		m_Ready.dc,//src
		0, 0,
		m_Ready.bit.bmWidth,
		m_Ready.bit.bmHeight,
		RGB(255, 0, 255)
	);
}
void Render2DSystem::DrawStart()
{
	int x = m_rtClient.right / 2 - m_Start.bit.bmWidth / 2;
	int y = m_rtClient.bottom / 2 - m_Start.bit.bmHeight / 2;
	TransparentBlt(m_Base.dc,//dest
		x,
		y,
		m_Start.bit.bmWidth,
		m_Start.bit.bmHeight,
		m_Start.dc,//src
		0, 0,
		m_Start.bit.bmWidth,
		m_Start.bit.bmHeight,
		RGB(255, 0, 255)
	);
}

void Render2DSystem::DrawPause()
{
	if (m_uPause.bTrigger == FALSE) return;
	int x = m_rtClient.right / 2 - m_Pause.bit.bmWidth / 2;
	int y = m_rtClient.bottom / 2 - m_Pause.bit.bmHeight / 2;
	TransparentBlt(m_Base.dc,//dest
		x,
		y,
		m_Pause.bit.bmWidth,
		m_Pause.bit.bmHeight,
		m_Pause.dc,//src
		0, 0,
		m_Pause.bit.bmWidth,
		m_Pause.bit.bmHeight,
		RGB(255, 0, 255)
	);
}

void Render2DSystem::DrawScore()
{
	size_t size = 0;
	wsprintf(m_chScore, L"SCORE : %d", m_nScore * 100);
	StringCchLength(m_chScore, STRINGSIZE, &size);

	//�ι��� ��ü���ְ� 

	SetBkMode(m_Base.dc, TRANSPARENT);

	SetTextColor(m_Base.dc, RGB(0, 0, 0));
	TextOut(m_Base.dc, 10, 10, m_chScore, (int)size);

	SetTextColor(m_Base.dc, RGB(255, 255, 255));
	TextOut(m_Base.dc, 8, 8, m_chScore, (int)size);
	//
}

void Render2DSystem::DrawClear()
{
	int x = m_rtClient.right / 2 - m_Clear.bit.bmWidth / 2;
	int y = m_rtClient.bottom / 2 - m_Clear.bit.bmHeight / 2;


	TransparentBlt(m_Base.dc,
		x,
		y,
		m_Clear.bit.bmWidth,
		m_Clear.bit.bmHeight,
		m_Clear.dc,
		0, 0,
		m_Clear.bit.bmWidth,
		m_Clear.bit.bmHeight,
		RGB(255, 0, 255));//���
}
void Render2DSystem::DrawFade()
{
	//1. ����dc ���ٰ� ���������
	BitBlt(m_Alpha.dc, 0, 0, XRES, YRES, m_Fade.dc, 0, 0, SRCCOPY);
	//2. ���� �귻�� �Լ��� ���̽����ٰ� ���ĸ���� 
	AlphaBlend(m_Base.dc, 0, 0, XRES, YRES, m_Alpha.dc, 0, 0, XRES, YRES, m_Fade.bf);

}

void Render2DSystem::DrawFrame()
{
	if (m_Frame.bTrigger == FALSE) return;

	WCHAR fps[50];
	wsprintf(fps, L"FPS = %d", m_Frame.FrameRate);
	size_t size;
	StringCchLength(fps, 50, &size);

	TextOut(m_Base.dc, 10, 530, fps, (int)size);

}

void Render2DSystem::Tick(void* pPrams)
{
	switch (m_eGameState)
	{
	case TITLE:
		DrawTitle();
		DrawTextTitle();
		DrawPress();
		break;
	case GAME_READY:
		DrawBGAll();//bg ->base
		DrawHero();
		DrawEnemy();
		DrawReady();
		DrawScore();
		DrawFade();
		break;
	case GAME_START:
		DrawBGAll();//bg ->base
		DrawScore();
		DrawHero();
		DrawEnemy();
		DrawStart();
		break;
	case GAME_MAIN:
		DrawBGAll();//bg ->base
		DrawScore();
		//DrawHero();
		DrawHeroAlpha();
		DrawEnemy();
		DrawBullet();
		DrawExplode();
		DrawPause();
		break;
	case STAGE_CLEAR:
		DrawBGAll();//bg ->base
		DrawScore();
		DrawHero();
		DrawEnemy();
		DrawBullet();
		DrawExplode();
		DrawClear();

		break;
	default:
		break;
	}

	//base dc�� bg dc ����������
	BitBlt(m_hDCMain,//dest dc
		0, 0, //��𿡴ٰ� �������� ��ǥ
		m_BaseRenderTarget->m_BitMap.bmWidth,//���� ���� ����
		m_BaseRenderTarget->m_BitMap.bmHeight,
		m_BaseRenderTarget->m_hDC,//src dc
		0, 0, //�ҽ� ��𼭺��� �������� ��ǥ
		SRCCOPY //���� ������� �ɼ� 
	);
}

void Render2DSystem::DrawHeroAlpha()
{
	//1.�ϴ� ���ݱ��� ���̽��� ���Ŀ��ٰ� ������ (bitblt)
	BitBlt(m_Alpha.dc, 0, 0, XRES, YRES, m_Base.dc, 0, 0, SRCCOPY);

	//2. �� ���Ŀ��ٰ� ����� ��� (trans)
	TransparentBlt(m_Alpha.dc,//dest
		m_Hero.pt.x,
		m_Hero.pt.y,
		m_Hero.bit.bmWidth,
		m_Hero.bit.bmHeight,
		m_Hero.dc,//src
		0, 0,
		m_Hero.bit.bmWidth,
		m_Hero.bit.bmHeight,
		RGB(255, 0, 255)
	);
//int Render2DSystem::CreateComponent(int ownerID, int AssetID)
//{
//	return 0;
//}
