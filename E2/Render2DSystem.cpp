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
	// 리소스해제들
	DeleteDC(m_BaseRenderTarget->m_hDC);
}

// TODO : 문서에 이 함수가 왜 꼭 필요한지 적어두자.
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

	// TODO : if문 방식 vs 32kb activeTable접근 중에 어느 쪽이 성능이 더 좋은가?
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

		NewComponent.m_hBmp = (HBITMAP)LoadImage(NULL, NewPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//비트맵 핸들 얻어오는 과정 
		if (NewComponent.m_hBmp == NULL)
		{
			MessageBox(NULL, NewPath, L"비트맵 로딩 에러", MB_OK);
			return false;
		}
		NewComponent.m_hDC = CreateCompatibleDC(NULL); // 정체를 정확히 모르겠어 이건
		NewComponent.m_hOldBmp = (HBITMAP)SelectObject(NewComponent.m_hDC, NewComponent.m_hBmp);//dc 랑 비트맵이랑 연결
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
	m_BaseRenderTarget->m_hBmp = (HBITMAP)LoadImage(NULL, BasePath, IMAGE_BITMAP,0 , 0, LR_LOADFROMFILE);//비트맵 핸들 얻어오는 과정 
	if (m_BaseRenderTarget->m_hBmp == NULL)
	{
		MessageBox(NULL, BasePath, L"비트맵 로딩 에러", MB_OK);
		return false;
	}
	m_BaseRenderTarget->m_hDC = CreateCompatibleDC(NULL); // 정체를 정확히 모르겠어 이건
	m_BaseRenderTarget->m_hOldBmp = (HBITMAP)SelectObject(m_BaseRenderTarget->m_hDC, m_BaseRenderTarget->m_hBmp);//dc 랑 비트맵이랑 연결
	GetObject(m_BaseRenderTarget->m_hBmp, sizeof(BITMAP), &m_BaseRenderTarget->m_BitMap);
	
	// Alpha
	m_AlphaRenderTarget->m_hBmp = (HBITMAP)LoadImage(NULL, AlphaPath, IMAGE_BITMAP,0 , 0, LR_LOADFROMFILE);//비트맵 핸들 얻어오는 과정 
	if (m_AlphaRenderTarget->m_hBmp == NULL)
	{
		MessageBox(NULL, AlphaPath, L"비트맵 로딩 에러", MB_OK);
		return false;
	}
	m_AlphaRenderTarget->m_hDC = CreateCompatibleDC(NULL); // 정체를 정확히 모르겠어 이건
	m_AlphaRenderTarget->m_hOldBmp = (HBITMAP)SelectObject(m_AlphaRenderTarget->m_hDC, m_AlphaRenderTarget->m_hBmp);//dc 랑 비트맵이랑 연결
	GetObject(m_AlphaRenderTarget->m_hBmp, sizeof(BITMAP), &m_AlphaRenderTarget->m_BitMap);
	
	m_AlphaRenderTarget->m_BF.AlphaFormat = 0;
	m_AlphaRenderTarget->m_BF.BlendFlags = 0;
	m_AlphaRenderTarget->m_BF.BlendOp = 0;
	m_AlphaRenderTarget->m_BF.SourceConstantAlpha = 255; // 투명도 0~255 // 127~128 반투명

	// Fade 
	m_FadeRenderTarget->m_hBmp = (HBITMAP)LoadImage(NULL, FadePath, IMAGE_BITMAP,0 , 0, LR_LOADFROMFILE);//비트맵 핸들 얻어오는 과정 

	if (m_FadeRenderTarget->m_hBmp == NULL)
	{
		MessageBox(NULL, FadePath, L"비트맵 로딩 에러", MB_OK);
		return false;
	}
	m_FadeRenderTarget->m_hDC = CreateCompatibleDC(NULL); // 정체를 정확히 모르겠어 이건
	m_FadeRenderTarget->m_hOldBmp = (HBITMAP)SelectObject(m_FadeRenderTarget->m_hDC, m_FadeRenderTarget->m_hBmp);//dc 랑 비트맵이랑 연결
	GetObject(m_FadeRenderTarget->m_hBmp, sizeof(BITMAP), &m_FadeRenderTarget->m_BitMap);

	m_FadeRenderTarget->m_BF.AlphaFormat = 0;
	m_FadeRenderTarget->m_BF.BlendFlags = 0;
	m_FadeRenderTarget->m_BF.BlendOp = 0;
	m_FadeRenderTarget->m_BF.SourceConstantAlpha = 255;//불투명...0완전투명 반투명 127

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
	//base dc에 bg dc 를찍을거임
	BitBlt(m_Base.dc,//dest dc
		0, 0, //어디에다가 찍을건지 좌표
		m_BG.bit.bmWidth,//찍을 가로 길이
		m_BG.bit.bmHeight,
		m_BG.dc,//src dc
		0, 0, //소스 어디서부터 찍을건지 좌표
		SRCCOPY //고대로 찍으라는 옵션 
	);

}

void Render2DSystem::DrawBG2()
{
	StretchBlt(m_Base.dc,//데스트
		0, 0, XRES, YRES,//배경이라 1024 768 고정 
		m_BG2.dc,//소스
		0,//종스크롤이라 x좌표는 0으로 고정 
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
	//1.일단 지금까지 베이스를 알파에다가 다찍음 (bitblt)
	BitBlt(m_Alpha.dc, 0, 0, XRES, YRES, m_Base.dc, 0, 0, SRCCOPY);

	//2. 이 알파에다가 히어로 찍고 (trans)
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

	// 핵심은 알파 베이스는 투명취급되서 알파위에 찍은 픽셀만 화면에 찍히는것! []=--------
	//3.알파브렌드 함수로 베이스에다가 알파를 찍기 (alphablend)
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
	if (m_uExplode.bTrigger == FALSE) return; //폭발 중이 아님 안찍음

	TransparentBlt(m_Base.dc,
		m_Explde.pt.x,
		m_Explde.pt.y,//찍을 목적지 위치 xy
		m_uExplode.size, //m_u
		m_Explde.bit.bmHeight, //m_
		m_Explde.dc,//소스의 dc
		m_uExplode.Frame * m_uExplode.size,//소스의 x 좌표로 처음엔0이다
		0,///y 좌표는 처음 처음부터 다찍을거니 
		m_uExplode.size,//찍을 소스의 너비
		m_Explde.bit.bmHeight,//소스의 높이
		RGB(0, 0, 255)//투명값은 분홍색으루다가 햇음 그림에서 .. 
	);


}
void Render2DSystem::DrawTitle()
{	//base dc에 bg dc 를찍을거임
	BitBlt(m_Base.dc,//dest dc
		0, 0, //어디에다가 찍을건지 좌표
		m_Title.bit.bmWidth,//찍을 가로 길이
		m_Title.bit.bmHeight,
		m_Title.dc,//src dc
		0, 0, //소스 어디서부터 찍을건지 좌표
		SRCCOPY //고대로 찍으라는 옵션 
	);
}

void Render2DSystem::DrawTextTitle()
{
	int x = m_rtClient.right / 2 - 280;
	int y = 150;
	WCHAR title[] = L"PENGSU's ADV";

	SetBkMode(m_Base.dc, TRANSPARENT); //글자 배경을 투명하게 

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

	//두번찍어서 입체감있게 

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
		RGB(255, 0, 255));//흰색
}
void Render2DSystem::DrawFade()
{
	//1. 알파dc 에다가 검은색찍고
	BitBlt(m_Alpha.dc, 0, 0, XRES, YRES, m_Fade.dc, 0, 0, SRCCOPY);
	//2. 알파 브렌드 함수로 베이스에다가 알파를찍기 
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

	//base dc에 bg dc 를찍을거임
	BitBlt(m_hDCMain,//dest dc
		0, 0, //어디에다가 찍을건지 좌표
		m_BaseRenderTarget->m_BitMap.bmWidth,//찍을 가로 길이
		m_BaseRenderTarget->m_BitMap.bmHeight,
		m_BaseRenderTarget->m_hDC,//src dc
		0, 0, //소스 어디서부터 찍을건지 좌표
		SRCCOPY //고대로 찍으라는 옵션 
	);
}

void Render2DSystem::DrawHeroAlpha()
{
	//1.일단 지금까지 베이스를 알파에다가 다찍음 (bitblt)
	BitBlt(m_Alpha.dc, 0, 0, XRES, YRES, m_Base.dc, 0, 0, SRCCOPY);

	//2. 이 알파에다가 히어로 찍고 (trans)
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
