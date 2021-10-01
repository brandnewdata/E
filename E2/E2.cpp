// E2.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "ECore.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	// 싱글턴 core 초기화 및 해제 시점 작성
	// 리소스 로딩, 데이터 초기화, 메인 윈도우 데이터 참조 등등
	if (GET_SINGLE(ECore)->Init(hInstance) == false)
	{
		// 초기화에 실패하면 싱글턴 클래스 메모리 해제하고 바로 winmain() 함수 반환
		DESTROY_SINGLE(ECore);
		return 0;
	}

	// 게임 루프 작동
	int iLoopExitFlag = GET_SINGLE(ECore)->Run();

	// Core메모리 해제
	// 하위 관리자들도 해제되면서 관리중이던 오브젝트들도 모두 해제됨
	DESTROY_SINGLE(ECore);

	return iLoopExitFlag;
}



