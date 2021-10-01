#pragma once
#include "predefines.h"
#include "SystemBase.h"

// uint64 EntityID;
struct EntityDTRecord
{
	// 맵같은 경우 SubEntity가 있다.
	uint32 m_NumSubEntity;
	vector<uint64> m_vSubEntityID;
	// ComponentSystemIndex(8bit), ComponentIndex(24bit)
	uint32 m_NumComponent;
	vector<uint32> m_vComponentDTID;
};

// uint32 ComponentID;
struct Render2DComponentDTRecord
{
	LPCWCHAR m_2DTextrueFilePath;
	//vectorActivationOperation
};

class ETableManager : public SystemBase
{
//**************************************************************************************************//
//																									//
//						Property Area																//
//																									//
//**************************************************************************************************//
private:
	// TODO : 나중에 Entity 타입별로 다시 분리해야함
	unordered_map<uint64, EntityDTRecord> m_mapEntityTable;
	
	// TODO : 기억이 안나.ㅠㅠ
	unordered_map<uint32, Render2DComponentDTRecord> m_mapRender2DComponentTable;

//**************************************************************************************************//
//																									//
//						Method Area																	//
//																									//
//**************************************************************************************************//

// 초기화 함수
protected:
	virtual void SetSystemOperationSlot() override;
public:
	bool Init();


// Getter, Setter 
public:
	LPCWCHAR GetFilePathByComponentDTID(int componentDTID) const;

	inline const unordered_map<uint32, Render2DComponentDTRecord>* GetRender2DComponentAssetTable() const
	{
		return &m_mapRender2DComponentTable;
	}


private:
// Operations
	// Table 파일을 로드하는 함수.
	bool LoadTableFromFile();

// Propertys 
	DECLARE_SINGLE(ETableManager)
};

