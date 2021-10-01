#pragma once

// 테이블 로딩, 컴포넌트 생성, 리소스 로딩은 모두 별개로 이뤄진다.
// 순서는 테이블 -> 컴포넌트 생성,리소스 로딩 (현재는 더미 리소스가 없어서 생성 즉시 바로 같이 로딩함)
// Entity Type은 Entity ID에 포함되어 있다. // 앞의 16비트
// @1 EntityDTID // 유일 식별자
// @2 NumSubEntityDTID // 속성값
// @3 NumComponentDTID // 속성값
// @4 StringList_SubEntityDTID // 구분문자 ; // 속성값
// @5 StringList_ComponentDTID // 구분문자 ; // 속성값

//**************************************************************************************************//
// 1행 RenderTarget
// 1열 // RenderTarget = 0
#define RenderTarget_EntityDTID 0x0000'0000'0000'0001
// 2열
#define  RenderTarget_NumSubEntityDTID 0
// 3열
#define  RenderTarget_NumComponentDTID 3
// 4열
// NULL
// 5열 // 컴포넌트DTID 리스트 string 압축
#define RenderBase_2DRenderCompDTID 0x0500'0001
#define AlphaBase_2DRenderCompDTID 0x0500'0002
#define FadeBase_2DRenderCompDTID 0x0500'0003
//**************************************************************************************************//

//**************************************************************************************************//
// 2행 LobbyHUD
// 1열 // HUD = 1
#define LobbyHUD_EntityDTID 0x0001'0000'0000'0002
// 2열
#define  LobbyHUD_NumSubEntityDTID 0
// 3열
#define  LobbyHUD_NumComponentDTID 1
// 4열
// NULL
// 5열 // 컴포넌트DTID 리스트 string 압축
#define Lobby_2DRenderCompDTID 0x0500'0004
//**************************************************************************************************//

//**************************************************************************************************//
// 3행 PlayHUD 
// 1열 // HUD = 1
#define PlayHUD_EntityDTID 0x0001'0000'0000'0003
// 2열
#define  PlayHUD_NumSubEntityDTID 0
// 3열
#define  PlayHUD_NumComponentDTID 1
// 4열
// NULL
// 5열 // 컴포넌트DTID 리스트 string 압축
#define Press_2DRenderCompID 0x0500'0005
#define Ready_2DRenderCompID 0x0500'0006
#define Start_2DRenderCompID 0x0500'0007
#define Pause_2DRenderCompID 0x0500'0008
#define Clear_2DRenderCompID 0x0500'0009
//**************************************************************************************************//

//**************************************************************************************************//
// 4행 // Player
// 1열 // PlayerCharacter = 4
#define Player_EntityDTID 0x0004'0000'0000'0004
// 2열
#define  Player_NumSubEntityDTID 0
// 3열
#define  Player_NumComponentDTID 1
// 4열
// NULL
// 5열 // 컴포넌트DTID 리스트 string 압축
#define Player_2DRenderCompDTID 0x0500'000a
//**************************************************************************************************//

//**************************************************************************************************//
// 5행 // Enemy
// 1열 EnemyCharacter = 6
#define Enemy_EntityDTID 0x0000'0000'0000'0005
// 2열
#define  Enemy_NumSubEntityDTID 0
// 3열
#define  Enemy_NumComponentDTID 1
// 4열
// NULL
// 5열 // 컴포넌트DTID 리스트 string 압축
#define Enemy_2DRenderCompDTID 0x0500'000b
//**************************************************************************************************//


//**************************************************************************************************//
// 6행 // Bullet
// 1열 DamageObject = 10
#define Bullet_EntityDTID 0x0000'0000'0000'0006
// 2열
#define  Bullet_NumSubEntityDTID 0
// 3열
#define  Bullet_NumComponentDTID 1
// 4열
// NULL
// 5열 // 컴포넌트DTID 리스트 string 압축
#define Bullet_2DRenderCompDTID 0x0500'000c
//**************************************************************************************************//

// 7행 // 애니메이션 // 스크롤(크게크게)
//**************************************************************************************************//
// explode
// VisualEffect = 9
#define Explode_EntityDTID 0x0000'0000'0000'0007
// 2열
#define  Explode_NumSubEntityDTID 0
// 3열
#define  Explode_NumComponentDTID 1
// 4열
// NULL
// 5열 // 컴포넌트DTID 리스트 string 압축
#define Explode_2DRenderCompDTID 0x0500'000d
//**************************************************************************************************//

//**************************************************************************************************//
// 8행 // BG_1
// Level = 12
#define BG_1_EntityDTID 0x000c'0000'0000'0008
// 2열
#define  BG_1_NumSubEntityDTID 0
// 3열
#define  BG_1_NumComponentDTID 1
// 4열
// NULL
// 5열 // 컴포넌트DTID 리스트 string 압축
#define BG_1_2DRenderCompDTID 0x0500'000e
//**************************************************************************************************//

// 9행 // 애니메이션 // 스크롤
//**************************************************************************************************//
// BG_2
// StaticObject =2
#define BG_2_EntityDTID 0x000c'0000'0000'0009
// 2열
#define  BG_2_NumSubEntityDTID 0
// 3열
#define  BG_2_NumComponentDTID 1
// 4열
// NULL
// 5열 // 컴포넌트DTID 리스트 string 압축
#define BG_2_2DRenderCompDTID 0x0500'000f
//**************************************************************************************************//

// 10행 // 애니메이션 // 여러장
//**************************************************************************************************//
// BG_3
// StaticObject =2
#define BG_3_EntityDTID 0x000c'0000'0000'000a
// 2열
#define BG_3_NumSubEntityDTID 0
// 3열
#define BG_3_NumComponentDTID 1
// 4열
// NULL
// 5열 // 컴포넌트DTID 리스트 string 압축
#define BG_3_2DRenderCompDTID 0x0500'0010
//**************************************************************************************************//

// 11행 // 타이틀
//**************************************************************************************************//
// BG_3
// StaticObject =2
#define BG_3_EntityDTID 0x000c'0000'0000'000a
// 2열
#define BG_3_NumSubEntityDTID 0
// 3열
#define BG_3_NumComponentDTID 1
// 4열
// NULL
// 5열 // 컴포넌트DTID 리스트 string 압축
#define BG_3_2DRenderCompDTID 0x0500'0010
//**************************************************************************************************//

// 레벨 서브 엔티티
// 게임모드
	// 플레이어 타입
	// HUD
	// 플레이어 컨트롤러
	// 게임 스테이트
	// 플레이어 스테이트
	// 관찰자 클래스



















