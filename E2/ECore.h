#pragma once
#include "Predefines.h"

class EGameInstance;

class ECore
{
private:
	// ���� ������κ��� ������ ��ü��
	HINSTANCE m_hInst;
	HDC m_hDC;
	HWND m_hWnd;
	RECT m_rtClient;	// ȭ�� client ���� �簢��
	EGameInstance* m_pGI;

	// ���� �ھ� ������, Static�Լ��� WinProc���� ���ǹǷ� Static�������� �Ѵ�.
	static bool m_bLoop;

	// ���Ӿ� �⺻����
private:
	RESOLUTION m_RS;

	// ���� ����
private:
	float AccumDelta;

// Getter, Setter
public:

// �ܺη� ȣ��Ǵ� �ʱ�ȭ, ��Ʈ�� �Լ���
public:
	bool Init(HINSTANCE hInst);
	void BeginPlay();
	int Run();

	// 1. ������ ���ν��� �Լ��� �ݵ�� �����Լ��� �����ϴ�. (#����# static �Լ��� static ��� ������ ���ٰ���)
	// 2. �뵵 - �� â�� �޽����� ó���մϴ�.
	//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
	//  WM_PAINT    - �� â�� �׸��ϴ�.
	//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// ���ο����� ȣ��Ǵ� �ʱ�ȭ �Լ���
private:
	ATOM MyRegisterClass();
	// �⺻���� ����ũž ���α׷��� InitInstance�Լ��� ��ü�Ѵ�.
	BOOL CreateWnd();
	
	// ������ �����ϴµ� �ʿ��� ������ ù��° ���� �����Ѵ�.
	bool SetStartLevel();

	// GameLoopFunctions
	void InputProcess();
	void AIProcess();
	void Tick();
	void CalculateCollision();

	// �ӽ� ������ ���ؼ� �и����� ���� �Լ���
	void LoadAsset();

	DECLARE_SINGLE(ECore)
};