#include "ETableManager.h"
#include "EEntityTable.h"
#include "ERender2DComponentTable.h"

DEFINITION_SINGLE(ETableManager)

ETableManager::ETableManager()
	: SystemBase()
{

}

ETableManager::~ETableManager()
{

}


// Job = 0,
// Entity = 1,
// Input = 2,
// Movement = 3,
// Network = 4,
// Render2D = 5,
// Timer = 6,
// UnitController = 7,
// World = 8,
// GameMode = 9,
// Collision = 10,
// UnitStatus = 11
bool ETableManager::LoadTableFromFile()
{
	//**************************************************************************************************//
	// 엔티티 로드																						//
	//**************************************************************************************************//
	
	// 1 
	EntityDTRecord RenderTarget_Record;
	RenderTarget_Record.m_NumSubEntity = 0;
	RenderTarget_Record.m_NumComponent = 3;
	RenderTarget_Record.m_vComponentDTID.push_back(RenderBase_2DRenderCompDTID);
	RenderTarget_Record.m_vComponentDTID.push_back(AlphaBase_2DRenderCompDTID);
	RenderTarget_Record.m_vComponentDTID.push_back(FadeBase_2DRenderCompDTID);
	m_mapEntityTable.insert(make_pair(RenderTarget_EntityDTID, RenderTarget_Record));

	// 2
	EntityDTRecord LobbyHUD_Record;
	LobbyHUD_Record.m_NumSubEntity = 0;
	LobbyHUD_Record.m_NumComponent = 1;
	LobbyHUD_Record.m_vComponentDTID.push_back(Lobby_2DRenderCompDTID);
	m_mapEntityTable.insert(make_pair(LobbyHUD_EntityDTID, LobbyHUD_Record));

	// 3
	EntityDTRecord PlayHUD_Record;
	PlayHUD_Record.m_NumSubEntity = 0;
	PlayHUD_Record.m_NumComponent = 5;
	PlayHUD_Record.m_vComponentDTID.push_back(Press_2DRenderCompID);
	PlayHUD_Record.m_vComponentDTID.push_back(Ready_2DRenderCompID);
	PlayHUD_Record.m_vComponentDTID.push_back(Start_2DRenderCompID);
	PlayHUD_Record.m_vComponentDTID.push_back(Pause_2DRenderCompID);
	PlayHUD_Record.m_vComponentDTID.push_back(Clear_2DRenderCompID);
	m_mapEntityTable.insert(make_pair(PlayHUD_EntityDTID, PlayHUD_Record));

	// 4
	EntityDTRecord Playe_Record;
	Playe_Record.m_NumSubEntity = 0;
	Playe_Record.m_NumComponent = 1;
	Playe_Record.m_vComponentDTID.push_back(Player_2DRenderCompDTID);
	m_mapEntityTable.insert(make_pair(Player_EntityDTID, Playe_Record));

	// 5
	EntityDTRecord Enemy_Record;
	Enemy_Record.m_NumSubEntity = 0;
	Enemy_Record.m_NumComponent = 1;
	Enemy_Record.m_vComponentDTID.push_back(Enemy_2DRenderCompDTID);
	m_mapEntityTable.insert(make_pair(Enemy_EntityDTID, Enemy_Record));

	// 6
	EntityDTRecord Bullet_Record;
	Bullet_Record.m_NumSubEntity = 0;
	Bullet_Record.m_NumComponent = 1;
	Bullet_Record.m_vComponentDTID.push_back(Bullet_2DRenderCompDTID);
	m_mapEntityTable.insert(make_pair(Bullet_EntityDTID, Bullet_Record));

	// 7
	EntityDTRecord Explode_Record;
	Explode_Record.m_NumSubEntity = 0;
	Explode_Record.m_NumComponent = 1;
	Explode_Record.m_vComponentDTID.push_back(Explode_2DRenderCompDTID);
	m_mapEntityTable.insert(make_pair(Explode_EntityDTID, Explode_Record));

	// 8
	EntityDTRecord BG_1_Record;
	BG_1_Record.m_NumSubEntity = 0;
	BG_1_Record.m_NumComponent = 1;
	BG_1_Record.m_vComponentDTID.push_back(BG_1_2DRenderCompDTID);
	m_mapEntityTable.insert(make_pair(BG_1_EntityDTID, BG_1_Record));

	// 9
	EntityDTRecord BG_2_Record;
	BG_2_Record.m_NumSubEntity = 0;
	BG_2_Record.m_NumComponent = 1;
	BG_2_Record.m_vComponentDTID.push_back(BG_2_2DRenderCompDTID);
	m_mapEntityTable.insert(make_pair(BG_2_EntityDTID, BG_2_Record));

	// 10
	EntityDTRecord BG_3_Record;
	BG_3_Record.m_NumSubEntity = 0;
	BG_3_Record.m_NumComponent = 1;
	BG_3_Record.m_vComponentDTID.push_back(BG_3_2DRenderCompDTID);
	m_mapEntityTable.insert(make_pair(BG_3_EntityDTID, BG_3_Record));

	//**************************************************************************************************//
	// 컴포넌트 로드																						//
	//**************************************************************************************************//
	// 1
	Render2DComponentDTRecord RanderBase__Render2DComponentRecord;
	RanderBase__Render2DComponentRecord.m_2DTextrueFilePath = RanderBase_BmpPath;
	m_mapRender2DComponentTable.insert(make_pair(RenderBase_2DRenderCompDTID, RanderBase__Render2DComponentRecord));

	// 2
	Render2DComponentDTRecord AlphaBase_Render2DComponentRecord;
	AlphaBase_Render2DComponentRecord.m_2DTextrueFilePath = AlphaBase_BmpPath;
	m_mapRender2DComponentTable.insert(make_pair(AlphaBase_2DRenderCompDTID, AlphaBase_Render2DComponentRecord));

	// 3
	Render2DComponentDTRecord FadeBase_Render2DComponentRecord;
	FadeBase_Render2DComponentRecord.m_2DTextrueFilePath = Fade_BmpPath;
	m_mapRender2DComponentTable.insert(make_pair(FadeBase_2DRenderCompDTID, FadeBase_Render2DComponentRecord));

	// 4
	Render2DComponentDTRecord Lobby_Render2DComponentRecord;
	Lobby_Render2DComponentRecord.m_2DTextrueFilePath = LobbyBmpPath;
	m_mapRender2DComponentTable.insert(make_pair(Lobby_2DRenderCompDTID, Lobby_Render2DComponentRecord));

	// 5
	Render2DComponentDTRecord Press_Render2DComponentRecord;
	Press_Render2DComponentRecord.m_2DTextrueFilePath = PressBmpPath;
	m_mapRender2DComponentTable.insert(make_pair(Press_2DRenderCompID, Press_Render2DComponentRecord));

	// 6
	Render2DComponentDTRecord Ready_Render2DComponentRecord;
	Ready_Render2DComponentRecord.m_2DTextrueFilePath = ReadyBmpPath;
	m_mapRender2DComponentTable.insert(make_pair(Ready_2DRenderCompID, Ready_Render2DComponentRecord));

	// 7
	Render2DComponentDTRecord Start_Render2DComponentRecord;
	Start_Render2DComponentRecord.m_2DTextrueFilePath = StartBmpPath;
	m_mapRender2DComponentTable.insert(make_pair(Start_2DRenderCompID, Start_Render2DComponentRecord));

	// 8
	Render2DComponentDTRecord Pause_Render2DComponentRecord;
	Pause_Render2DComponentRecord.m_2DTextrueFilePath = PauseBmpPath;
	m_mapRender2DComponentTable.insert(make_pair(Pause_2DRenderCompID, Pause_Render2DComponentRecord));

	// 9
	Render2DComponentDTRecord Clear_Render2DComponentRecord;
	Clear_Render2DComponentRecord.m_2DTextrueFilePath = ClearBmpPath;
	m_mapRender2DComponentTable.insert(make_pair(Clear_2DRenderCompID, Clear_Render2DComponentRecord));

	// 10
	Render2DComponentDTRecord Player_Render2DComponentRecord;
	Player_Render2DComponentRecord.m_2DTextrueFilePath = Player_BmpPath;
	m_mapRender2DComponentTable.insert(make_pair(Player_2DRenderCompDTID, Player_Render2DComponentRecord));

	// 11
	Render2DComponentDTRecord Enemy_Render2DComponentRecord;
	Enemy_Render2DComponentRecord.m_2DTextrueFilePath = Enemy_BmpPath;
	m_mapRender2DComponentTable.insert(make_pair(Enemy_2DRenderCompDTID, Enemy_Render2DComponentRecord));

	// 12
	Render2DComponentDTRecord Bullet_Render2DComponentRecord;
	Bullet_Render2DComponentRecord.m_2DTextrueFilePath = Bullet_BmpPath;
	m_mapRender2DComponentTable.insert(make_pair(Bullet_2DRenderCompDTID, Bullet_Render2DComponentRecord));

	// 13
	Render2DComponentDTRecord Explode_Render2DComponentRecord;
	Explode_Render2DComponentRecord.m_2DTextrueFilePath = Explode_BmpPath;
	m_mapRender2DComponentTable.insert(make_pair(Explode_2DRenderCompDTID, Explode_Render2DComponentRecord));

	// 14
	Render2DComponentDTRecord BG_1_Render2DComponentRecord;
	BG_1_Render2DComponentRecord.m_2DTextrueFilePath = BG_1;
	m_mapRender2DComponentTable.insert(make_pair(BG_1_2DRenderCompDTID, BG_1_Render2DComponentRecord));

	// 15
	Render2DComponentDTRecord BG_2_Render2DComponentRecord;
	BG_2_Render2DComponentRecord.m_2DTextrueFilePath = BG_2;
	m_mapRender2DComponentTable.insert(make_pair(BG_2_2DRenderCompDTID, BG_2_Render2DComponentRecord));

	// 16
	Render2DComponentDTRecord BG_3_Render2DComponentRecord;
	BG_3_Render2DComponentRecord.m_2DTextrueFilePath = BG_3;
	m_mapRender2DComponentTable.insert(make_pair(BG_3_2DRenderCompDTID, BG_3_Render2DComponentRecord));

	//	unordered_map<LPCWCHAR, const _PlayerDataTableRecord *>::const_iterator iter = m_mapPlayerDataRecord.find(assetOwner->GetID());
//
//	// 다 뒤져도 해당 문자열로 등록된 키가 없다는 말이다.
//	if (iter == m_mapPlayerDataRecord.end())
//		return nullptr;
//
//	// End가 아니면 값을 찾은거다.
//	// 반복자는 찾은 노드를 포인팅하고 있다.
//	return iter->second;

	// TODO : 여기에 파일로부터 Talble 로드룰 추가하세요.
	// m_mapKey.insert(make_pair(m_pNewCreatedKey->strName, m_pNewCreatedKey)); // 삽입

	return true;
}

void ETableManager::SetSystemOperationSlot()
{
}

bool ETableManager::Init()
{
	LoadTableFromFile();
	return true;
}

LPCWCHAR ETableManager::GetFilePathByComponentDTID(int componentDTID) const
{

	//	unordered_map<LPCWCHAR, LPCWCHAR>::const_iterator iter = m_mapKey.find(strKey);

	//	// 다 뒤져도 해당 문자열로 등록된 키가 없다는 말이다.!
	//	if (iter == m_mapKey.end())
	//		return nullptr;

	//	return iter->second;

	unordered_map<uint32, Render2DComponentDTRecord>::const_iterator iter = m_mapRender2DComponentTable.find(componentDTID);

	// 찾는 요소가 없으면 null반환
	if (iter == m_mapRender2DComponentTable.end())
		return nullptr;

	// End가 아니면 값을 찾은거다.
	// 반복자는 찾은 노드를 포인팅하고 있다.
	
	return iter->second.m_2DTextrueFilePath;
}