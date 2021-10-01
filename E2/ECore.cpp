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
	// _CRTDBG_ALLOC_MEM_DF : DF(define) �Ҵ��ϴ� �޸𸮸� üũ��.
	// _CRTDBG_LEAK_CHECK_DF : ������ �޸𸮸� üũ
	// *����� ���*�� �����ϰ� �޸� ������ ������ ��� -> ����� �ǿ� ������ �ǰ��ִ� ��ġ�� ǥ�õȴ�.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	// ��ҿ� �ּ����� �����ΰ� ������� �ʴ´�.
	// ����� ��忡�� �޸� ������ �߰��ϸ� ������ �޸� ��� ��ȣ�� ����� ���â�� ǥ�ŵȴ�.
	// ǥ�õ� �޸� ��Ϲ�ȣ�� �Ʒ��� �Է��ϸ� �ش� �ڵ尡 ��µǴ� �������� ���ܰ� �߻��Ѵ�.
	// ������ ǥ�õ� �޸� ����� ��ȣ�� �Ʒ��� �Ű������� �ѱ�� �ش� ��ġ�� �̵��Ѵ�.
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
	ReleaseDC(m_hWnd, m_hDC);//�������� dc �� Ǯ���ش�.

	//SAFE_DEL(pPlayer);
	//SAFE_DEL(pStore);
	//SAFE_DEL(pAccountHandler);
	//DESTROY_SINGLE(ResourceManager);
}

bool ECore::Init(HINSTANCE hInst)
{
	// ���ڷ� ���� ���� �ν��Ͻ� �ڵ带 ����
	m_hInst = hInst;

	// ������â Ŭ����(����) ���
	MyRegisterClass();

	// �ػ� ����
	m_RS.Wideth = 1200;
	m_RS.Height = 900;

	// ������ ���� â ���� // 
	CreateWnd();

	// ������ �簢�� ���ϱ� 
	GetClientRect(m_hWnd, &m_rtClient);

	//���� Ŭ������ �� dc�� hwdn�� ������ // ������ �Ҹ��ڿ���
	m_hDC = GetDC(m_hWnd);

	// ���� �ý��� �ʱ�ȭ
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

	// �����Ʈ �Ŵ���
	// ���� �Ŵ���
		//���Ӹ��
		//���� 
		// ����
		// ���̾� (������ ������ ��� �⺻���� 0�� ���̾�)
		// ��������
		// HUD(�������� ���� ���߿� ����)
		// 
	// ���� �Ŵ���
	// 
	// 
	// AssetManage���� Ÿ��Ʋȭ�� ���� 

	return true;
}

void ECore::BeginPlay()
{
	// ��� ������Ʈ �ý����� ƽ�� ȣ���ϴ� ����...// ���� ��� �ý����� ƽ�� �������� ����
	//vector<SystemBase*>::const_iterator Iter;
	//Iter = m_pGI->GetComponentSystems()->begin();

	//vector<SystemBase*>::const_iterator EndIter;
	//EndIter = m_pGI->GetComponentSystems()->end();

	//// TODO : �� ���� Enum���� ��ü�ؾ��Ѵ�.
	//int ComponentSystemTickIndex = 0; 

	//// ��� Component System�� Tick �Լ��� �����մϴ�.
	//// Tick ó���� ���� �Լ��� �ƹ� ���� ���� �Լ��� ȣ��Ǿ��ٰ� ��ȯ�մϴ�.
	//for (Iter; Iter != EndIter; Iter++)
	//{
	//	(*Iter)->GetSystemOperationByIndex(ComponentSystemTickIndex)();
	//}

	
	GET_SINGLE(EJobManager)->InitThreadPool();
}

int ECore::Run()
{
   // �޽��� ����ü ����
   MSG msg = {};

   BeginPlay();
   GET_SINGLE(ETimer)->Reset();
   // TODO : ������ ��ġ�� �̵��ϱ� 
   int Render2DComponentID = (EComponentSystemIndex::Render2D << 24);

   // m_bLoop�� msg.message != WM_QUIT ����ü��
   while (m_bLoop)
   {
	   // �޽��� ť�� �޽����� ������ �������� ������ �ٷ� ��ȯ�մϴ�.
	   if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	   {
		   TranslateMessage(&msg);	// �޽����� ������ ���·� �����մϴ�.
		   DispatchMessage(&msg);   // �޽��� ���� ������ ó���� �մϴ�.
	   }

	   GET_SINGLE(ETimer)->Tick();
	   AccumDelta += (GET_SINGLE(ETimer)->DeltaTime());
	   if (AccumDelta > 0.015f)
	   {
		   AccumDelta = 0.f;
		   // TODO : �ǰ� ������ �κ��ΰ� ������ ������ ó���� �����̸� ũ������ ������ �ȴ�.
		   GET_SINGLE(EJobManager)->PushJob(0, Render2DComponentID, 0, EActiveOperation::True);
	   }

	   //else
	   // 1. �ʱ�ȭ �Լ��� �ܺο��� ȣ����. �ʱ�ȭ �Լ��� �����ϸ� �ٷ� ���� ���μ���
	   // 2. ������ �޽����� Input Manager���� ó����
	   // 3. Timer ó���� Callback���� ó����
	   // 4. �Է¿� ���� ó��, InputManager�� Update�� ���� ���� �ҷ��� InputState�� �����Ѵ�.
	   // 5. InputManager�� ���ε�� Eventó��
	   // 6. ��� ��ü�� InputProcess() �����Լ� ����
	   InputProcess();
	   // 7. AI ���� ����
	   AIProcess();
	   // 8. ��� ��ü�� Tick()�Լ� ȣ��
	   Tick();
	   // 10. �浹ó��
	   CalculateCollision();
   }

   GET_SINGLE(EJobManager)->DestroyThreadPool();
	return (int) msg.wParam;
}


//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
LRESULT ECore::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	// App�� �����Ҷ� �ѹ��� ����Ǵ� �ʱ�ȭ ����
	case WM_CREATE:
	{
		// ���� ���� ������ �޽��� ó�� �̸� �߰�
	}
	break;
	// �̰Ŵ� ��������� ���ܵ� ���� ��� ����.
	case WM_KEYDOWN:
	{
			/*if (g_game.KeyCheck() == TRUE)
			{
				break;
			}*/
			switch (wParam)
			{
			case VK_ESCAPE:
				DestroyWindow(hWnd);//���� �޽����� �ߵ��ϴ��Լ�
				break;
		// �ҹ��ڷ� �ϸ� ����� �۵��� �� �ȴ�. �׷��� �빮�ڷ� �ϸ� �ҹ��� �Է±��� Ŀ���Ѵ�.
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
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		// �� ������ flase�� ���� ������ ����ȴ�.
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
	wcex.lpfnWndProc = WndProc;	// class ���ο� ������� �����Լ�
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_E2));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr; // MAKEINTRESOURCEW(IDC_E2); // �̺κ��� ����� �޴��ٰ� ����� 
	wcex.lpszClassName = WND_CLASS_NAME;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL ECore::CreateWnd()
{
	// ���⼭ ������ ������ Ŭ���̾�Ʈ ������ �Ʒ����� �ٽ� �����ǹǷ� �߿����� �ʴ�.
	// �⺻�ڵ�� ��ü�ص� �����ϴ�.
	// param 4,5 App ������â�� ����ũ�� ȭ�� ���� � ��ǥ�� ��������(����Ʈž�� ��ġ)
   // param 6,7 ������ Ŭ���̾�Ʈ ������ ũ��
	m_hWnd = CreateWindowW(WND_CLASS_NAME, WND_TITLE_NAME, 
		WS_OVERLAPPEDWINDOW,
			100, 100, m_RS.Wideth, m_RS.Height, nullptr, nullptr, m_hInst, nullptr);

	// ������â ������ �����ϸ� �ٷ� ��ȯ
	if (!m_hWnd)
	{
		return FALSE;
	}
	

	// ���� Ŭ���̾�Ʈ ������ Rect ����ü�� ����
	RECT rcClient = { 0, 0, m_RS.Wideth, m_RS.Height };

	// ���� �������� ũ�Ⱑ Ŭ���̾�Ʈ ������ �ǵ��� ũ�⸦ ����(���� ������ ũ��, ������ ��� ��Ÿ��, �޴� ����)
	// AdjustWindowRect()�Լ��� ������â ��ü������ ũ��� ����� ������.
	// Rect ����ü���� ��üâ ũ�Ⱑ ���ϸ鼭 ������ client ������ ũ�Ⱑ ����ȴ�.
	AdjustWindowRect(&rcClient, WS_OVERLAPPEDWINDOW, FALSE);

	// ���� rc�� Ŭ���̾�Ʈ �簢���� ������ ������ ������ �����  �ٽü���
	// https://imagej.tistory.com/83
	// https://goodgaym.tistory.com/22
	SetWindowPos(m_hWnd, NULL,
		100, 100,		//  ������ ��ġ(X, Y)
		(rcClient.right - rcClient.left), (rcClient.bottom - rcClient.top), // ������ ũ��(����, ����) 
		SWP_NOZORDER | SWP_NOMOVE	// ���̺��� ���� | �̵� ����
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
