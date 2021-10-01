#pragma once
#include "Predefines.h"

class EGameInstance;

class ECore
{
private:
	// 메인 윈도우로부터 빌려온 객체들
	HINSTANCE m_hInst;
	HDC m_hDC;
	HWND m_hWnd;
	RECT m_rtClient;	// 화면 client 영역 사각형
	EGameInstance* m_pGI;

	// 게임 코어 데이터, Static함수인 WinProc에서 사용되므로 Static변수여야 한다.
	static bool m_bLoop;

	// 게임앱 기본설정
private:
	RESOLUTION m_RS;

	// 게임 정보
private:
	float AccumDelta;

// Getter, Setter
public:

// 외부로 호출되는 초기화, 엔트리 함수들
public:
	bool Init(HINSTANCE hInst);
	void BeginPlay();
	int Run();

	// 1. 윈도우 프로시져 함수는 반드시 전역함수만 가능하다. (#주의# static 함수는 static 멤버 변수만 접근가능)
	// 2. 용도 - 주 창의 메시지를 처리합니다.
	//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
	//  WM_PAINT    - 주 창을 그립니다.
	//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// 내부에서만 호출되는 초기화 함수들
private:
	ATOM MyRegisterClass();
	// 기본생성 데스크탑 프로그램의 InitInstance함수를 대체한다.
	BOOL CreateWnd();
	
	// 게임을 시작하는데 필요한 고정된 첫번째 맵을 설정한다.
	bool SetStartLevel();

	// GameLoopFunctions
	void InputProcess();
	void AIProcess();
	void Tick();
	void CalculateCollision();

	// 임시 구현을 위해서 분리하지 않은 함수들
	void LoadAsset();

	DECLARE_SINGLE(ECore)
};