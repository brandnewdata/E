#include "ECore.h"
#include "CoreSystems.h"
#include "Render2DSystem.h"
#include "EMovementSystem.h"
#include "EJobManager.h"
#include "ETableManager.h"
#include "MutiThreading.h"

DEFINITION_SINGLE(ECore)
bool ECore::m_bLoop = true;

ECore::ECore()
{
	// _CRTDBG_ALLOC_MEM_DF : DF(define) 할당하는 메모리를 체크함.
	// _CRTDBG_LEAK_CHECK_DF : 누수된 메모리를 체크
	// *디버그 모드*로 실행하고 메모리 누수가 있으면 출력 -> 디버그 탭에 누수가 되고있는 위치가 표시된다.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	// 평소에 주석으로 가려두고 사용하지 않는다.
	// 디버그 모드에서 메모리 누수를 발견하면 누수된 메모리 블록 번호가 디버그 출력창에 표신된다.
	// 표시된 메모리 블록번호를 아래에 입력하면 해당 코드가 출력되는 시점에서 예외가 발생한다.
	// 위에서 표시된 메모리 블록의 번호를 아래에 매개변수로 넘기면 해당 위치로 이동한다.
	//_CrtSetBreakAlloc(1733);


	//pStore = new Store();
	//pAccountHandler = new BAccountHandler();
	//pPlayer = new Player();

}

ECore::~ECore()
{
	DESTROY_SINGLE(EJobManager);
	DESTROY_SINGLE(EGameInstance);
	DESTROY_SINGLE(Render2DSystem);
	DESTROY_SINGLE(EMovementSystem);
	DESTROY_SINGLE(EInputManager);
	DESTROY_SINGLE(ETimer);
	DESTROY_SINGLE(ETableManager);
	ReleaseDC(m_hWnd, m_hDC);//수동으로 dc 를 풀어준다.

	//SAFE_DEL(pPlayer);
	//SAFE_DEL(pStore);
	//SAFE_DEL(pAccountHandler);
	//DESTROY_SINGLE(ResourceManager);
}

bool ECore::Init(HINSTANCE hInst)
{
	// 인자로 받은 메인 인스턴스 핸드를 저장
	m_hInst = hInst;

	// 윈도우창 클래스(스펙) 등록
	MyRegisterClass();

	// 해상도 설정
	m_RS.Wideth = 1200;
	m_RS.Height = 900;

	// 윈도우 메인 창 생성 // 
	CreateWnd();

	// 윈도우 사각형 구하기 
	GetClientRect(m_hWnd, &m_rtClient);

	//게임 클래스에 쓸 dc를 hwdn로 얻어오기 // 해제는 소멸자에서
	m_hDC = GetDC(m_hWnd);

	// 서브 시스템 초기화
	if (GET_SINGLE(ETableManager)->Init() == false)
		return false;
	if (GET_SINGLE(ETimer)->Init() == false)
		return false;
	if (GET_SINGLE(EInputManager)->Init() == false)
		return false;
	if (GET_SINGLE(EMovementSystem)->Init() == false)
		return false;
	if (GET_SINGLE(Render2DSystem)->Init(m_hDC) == false)
		return false;
	if (GET_SINGLE(EGameInstance)->Init() == false)
		return false;
	m_pGI = GET_SINGLE(EGameInstance);
	if (GET_SINGLE(EJobManager)->Init() == false)
		return false;

	// 무브먼트 매니저
	// 월드 매니저
		//게임모드
		//레벨 
		// 지역
		// 레이어 (지정이 없으면 모두 기본으로 0번 레이어)
		// 스테이지
		// HUD(렌더에서 가장 나중에 찍힘)
		// 
	// 렌더 매니저
	// 
	// 
	// AssetManage한테 타이틀화면 레벨 

	return true;
}

void ECore::BeginPlay()
{
	// 모든 컴포넌트 시스템의 틱을 호출하는 구문...// 아직 모든 시스템의 틱이 구현되지 않음
	//vector<SystemBase*>::const_iterator Iter;
	//Iter = m_pGI->GetComponentSystems()->begin();

	//vector<SystemBase*>::const_iterator EndIter;
	//EndIter = m_pGI->GetComponentSystems()->end();

	//// TODO : 이 값은 Enum으로 대체해야한다.
	//int ComponentSystemTickIndex = 0; 

	//// 모든 Component System의 Tick 함수를 시작합니다.
	//// Tick 처리가 없는 함수는 아무 동작 없이 함수가 호출되었다가 반환합니다.
	//for (Iter; Iter != EndIter; Iter++)
	//{
	//	(*Iter)->GetSystemOperationByIndex(ComponentSystemTickIndex)();
	//}

	
	GET_SINGLE(EJobManager)->InitThreadPool();
}

int ECore::Run()
{
   // 메시지 구조체 선언
   MSG msg = {};

   BeginPlay();
   GET_SINGLE(ETimer)->Reset();
   // TODO : 적절한 위치로 이동하기 
   int Render2DComponentID = (EComponentSystemIndex::Render2D << 24);

   // m_bLoop가 msg.message != WM_QUIT 를대체함
   while (m_bLoop)
   {
	   // 메시지 큐에 메시지가 있으면 꺼내오고 없으면 바로 반환합니다.
	   if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	   {
		   TranslateMessage(&msg);	// 메시지를 적절한 형태로 가공합니다.
		   DispatchMessage(&msg);   // 메시지 따라서 지정된 처리를 합니다.
	   }

	   GET_SINGLE(ETimer)->Tick();
	   AccumDelta += (GET_SINGLE(ETimer)->DeltaTime());
	   if (AccumDelta > 0.015f)
	   {
		   AccumDelta = 0.f;
		   // TODO : 되게 위험한 부분인게 이전의 렌더링 처리가 아직이면 크래쉬의 원인이 된다.
		   GET_SINGLE(EJobManager)->PushJob(0, Render2DComponentID, 0, EActiveOperation::True);
	   }

	   //else
	   // 1. 초기화 함수는 외부에서 호출함. 초기화 함수가 실패하면 바로 종료 프로세스
	   // 2. 윈도우 메시지는 Input Manager에서 처리함
	   // 3. Timer 처리는 Callback으로 처리됨
	   // 4. 입력에 대한 처리, InputManager의 Update를 가장 먼저 불러서 InputState를 설정한다.
	   // 5. InputManager에 바인드된 Event처리
	   // 6. 모든 객체의 InputProcess() 가상함수 실행
	   InputProcess();
	   // 7. AI 로직 수행
	   AIProcess();
	   // 8. 모든 객체의 Tick()함수 호출
	   Tick();
	   // 10. 충돌처리
	   CalculateCollision();
   }

   GET_SINGLE(EJobManager)->DestroyThreadPool();
	return (int) msg.wParam;
}


//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
LRESULT ECore::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	// App이 시작할때 한번만 실행되는 초기화 구간
	case WM_CREATE:
	{
		// 게임 관련 윈도우 메시지 처리 미리 추가
	}
	break;
	// 이거는 참고용으로 남겨둠 이제 사용 안함.
	case WM_KEYDOWN:
	{
			/*if (g_game.KeyCheck() == TRUE)
			{
				break;
			}*/
			switch (wParam)
			{
			case VK_ESCAPE:
				DestroyWindow(hWnd);//종료 메시지를 발동하는함수
				break;
		// 소문자로 하면 제대로 작동이 안 된다. 그런데 대문자로 하면 소문자 입력까지 커버한다.
			case 'P':
				//g_game.UpdatePause();
				break;
			case VK_F3:
				//g_game.ToggleFrame();
				break;
			default:
				break;
			}
	}	
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		// 이 변수가 flase면 게임 루프가 종료된다.
		m_bLoop = false; 
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

ATOM ECore::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;	// class 내부에 만들어진 전역함수
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_E2));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr; // MAKEINTRESOURCEW(IDC_E2); // 이부분을 지우면 메뉴바가 사라짐 
	wcex.lpszClassName = WND_CLASS_NAME;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL ECore::CreateWnd()
{
	// 여기서 설정한 윈도우 클라이언트 영역은 아래에서 다시 설정되므로 중요하지 않다.
	// 기본코드로 대체해도 무관하다.
	// param 4,5 App 윈도우창이 데스크톱 화면 위에 어떤 좌표에 생성될지(레프트탑의 위치)
   // param 6,7 윈도우 클라이어트 영역의 크기
	m_hWnd = CreateWindowW(WND_CLASS_NAME, WND_TITLE_NAME, 
		WS_OVERLAPPEDWINDOW,
			100, 100, m_RS.Wideth, m_RS.Height, nullptr, nullptr, m_hInst, nullptr);

	// 윈도우창 생성에 실패하면 바로 반환
	if (!m_hWnd)
	{
		return FALSE;
	}
	

	// 현재 클라이언트 영역을 Rect 구조체로 만듬
	RECT rcClient = { 0, 0, m_RS.Wideth, m_RS.Height };

	// 현재 윈도우의 크기가 클라이언트 영역이 되도록 크기를 조정(현재 윈도우 크기, 윈도우 모양 스타일, 메뉴 여부)
	// AdjustWindowRect()함수는 윈도우창 전체영역의 크기와 모양을 설정함.
	// Rect 구조체에는 전체창 크기가 변하면서 수정된 client 영역의 크기가 저장된다.
	AdjustWindowRect(&rcClient, WS_OVERLAPPEDWINDOW, FALSE);

	// 얻어온 rc의 클라이언트 사각형의 사이즈 정보로 윈도우 사이즈를  다시세팅
	// https://imagej.tistory.com/83
	// https://goodgaym.tistory.com/22
	SetWindowPos(m_hWnd, NULL,
		100, 100,		//  변경할 위치(X, Y)
		(rcClient.right - rcClient.left), (rcClient.bottom - rcClient.top), // 변경할 크기(가로, 세로) 
		SWP_NOZORDER | SWP_NOMOVE	// 깊이변경 금지 | 이동 금지
	);
	 
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return TRUE;
}

bool ECore::SetStartLevel()
{

	return false;
}

void ECore::InputProcess()
{
}

void ECore::AIProcess()
{
}

void ECore::LoadAsset()
{
}

void ECore::Tick()
{
}

void ECore::CalculateCollision()
{
}
