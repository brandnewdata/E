#pragma once

// ���̺� �ε�, ������Ʈ ����, ���ҽ� �ε��� ��� ������ �̷�����.
// ������ ���̺� -> ������Ʈ ����,���ҽ� �ε� (����� ���� ���ҽ��� ��� ���� ��� �ٷ� ���� �ε���)
// Entity Type�� Entity ID�� ���ԵǾ� �ִ�. // ���� 16��Ʈ
// @1 EntityDTID // ���� �ĺ���
// @2 NumSubEntityDTID // �Ӽ���
// @3 NumComponentDTID // �Ӽ���
// @4 StringList_SubEntityDTID // ���й��� ; // �Ӽ���
// @5 StringList_ComponentDTID // ���й��� ; // �Ӽ���

//**************************************************************************************************//
// 1�� RenderTarget
// 1�� // RenderTarget = 0
#define RenderTarget_EntityDTID 0x0000'0000'0000'0001
// 2��
#define  RenderTarget_NumSubEntityDTID 0
// 3��
#define  RenderTarget_NumComponentDTID 3
// 4��
// NULL
// 5�� // ������ƮDTID ����Ʈ string ����
#define RenderBase_2DRenderCompDTID 0x0500'0001
#define AlphaBase_2DRenderCompDTID 0x0500'0002
#define FadeBase_2DRenderCompDTID 0x0500'0003
//**************************************************************************************************//

//**************************************************************************************************//
// 2�� LobbyHUD
// 1�� // HUD = 1
#define LobbyHUD_EntityDTID 0x0001'0000'0000'0002
// 2��
#define  LobbyHUD_NumSubEntityDTID 0
// 3��
#define  LobbyHUD_NumComponentDTID 1
// 4��
// NULL
// 5�� // ������ƮDTID ����Ʈ string ����
#define Lobby_2DRenderCompDTID 0x0500'0004
//**************************************************************************************************//

//**************************************************************************************************//
// 3�� PlayHUD 
// 1�� // HUD = 1
#define PlayHUD_EntityDTID 0x0001'0000'0000'0003
// 2��
#define  PlayHUD_NumSubEntityDTID 0
// 3��
#define  PlayHUD_NumComponentDTID 1
// 4��
// NULL
// 5�� // ������ƮDTID ����Ʈ string ����
#define Press_2DRenderCompID 0x0500'0005
#define Ready_2DRenderCompID 0x0500'0006
#define Start_2DRenderCompID 0x0500'0007
#define Pause_2DRenderCompID 0x0500'0008
#define Clear_2DRenderCompID 0x0500'0009
//**************************************************************************************************//

//**************************************************************************************************//
// 4�� // Player
// 1�� // PlayerCharacter = 4
#define Player_EntityDTID 0x0004'0000'0000'0004
// 2��
#define  Player_NumSubEntityDTID 0
// 3��
#define  Player_NumComponentDTID 1
// 4��
// NULL
// 5�� // ������ƮDTID ����Ʈ string ����
#define Player_2DRenderCompDTID 0x0500'000a
//**************************************************************************************************//

//**************************************************************************************************//
// 5�� // Enemy
// 1�� EnemyCharacter = 6
#define Enemy_EntityDTID 0x0000'0000'0000'0005
// 2��
#define  Enemy_NumSubEntityDTID 0
// 3��
#define  Enemy_NumComponentDTID 1
// 4��
// NULL
// 5�� // ������ƮDTID ����Ʈ string ����
#define Enemy_2DRenderCompDTID 0x0500'000b
//**************************************************************************************************//


//**************************************************************************************************//
// 6�� // Bullet
// 1�� DamageObject = 10
#define Bullet_EntityDTID 0x0000'0000'0000'0006
// 2��
#define  Bullet_NumSubEntityDTID 0
// 3��
#define  Bullet_NumComponentDTID 1
// 4��
// NULL
// 5�� // ������ƮDTID ����Ʈ string ����
#define Bullet_2DRenderCompDTID 0x0500'000c
//**************************************************************************************************//

// 7�� // �ִϸ��̼� // ��ũ��(ũ��ũ��)
//**************************************************************************************************//
// explode
// VisualEffect = 9
#define Explode_EntityDTID 0x0000'0000'0000'0007
// 2��
#define  Explode_NumSubEntityDTID 0
// 3��
#define  Explode_NumComponentDTID 1
// 4��
// NULL
// 5�� // ������ƮDTID ����Ʈ string ����
#define Explode_2DRenderCompDTID 0x0500'000d
//**************************************************************************************************//

//**************************************************************************************************//
// 8�� // BG_1
// Level = 12
#define BG_1_EntityDTID 0x000c'0000'0000'0008
// 2��
#define  BG_1_NumSubEntityDTID 0
// 3��
#define  BG_1_NumComponentDTID 1
// 4��
// NULL
// 5�� // ������ƮDTID ����Ʈ string ����
#define BG_1_2DRenderCompDTID 0x0500'000e
//**************************************************************************************************//

// 9�� // �ִϸ��̼� // ��ũ��
//**************************************************************************************************//
// BG_2
// StaticObject =2
#define BG_2_EntityDTID 0x000c'0000'0000'0009
// 2��
#define  BG_2_NumSubEntityDTID 0
// 3��
#define  BG_2_NumComponentDTID 1
// 4��
// NULL
// 5�� // ������ƮDTID ����Ʈ string ����
#define BG_2_2DRenderCompDTID 0x0500'000f
//**************************************************************************************************//

// 10�� // �ִϸ��̼� // ������
//**************************************************************************************************//
// BG_3
// StaticObject =2
#define BG_3_EntityDTID 0x000c'0000'0000'000a
// 2��
#define BG_3_NumSubEntityDTID 0
// 3��
#define BG_3_NumComponentDTID 1
// 4��
// NULL
// 5�� // ������ƮDTID ����Ʈ string ����
#define BG_3_2DRenderCompDTID 0x0500'0010
//**************************************************************************************************//

// 11�� // Ÿ��Ʋ
//**************************************************************************************************//
// BG_3
// StaticObject =2
#define BG_3_EntityDTID 0x000c'0000'0000'000a
// 2��
#define BG_3_NumSubEntityDTID 0
// 3��
#define BG_3_NumComponentDTID 1
// 4��
// NULL
// 5�� // ������ƮDTID ����Ʈ string ����
#define BG_3_2DRenderCompDTID 0x0500'0010
//**************************************************************************************************//

// ���� ���� ��ƼƼ
// ���Ӹ��
	// �÷��̾� Ÿ��
	// HUD
	// �÷��̾� ��Ʈ�ѷ�
	// ���� ������Ʈ
	// �÷��̾� ������Ʈ
	// ������ Ŭ����



















