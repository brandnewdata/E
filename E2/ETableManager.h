#pragma once
#include "predefines.h"
#include "SystemBase.h"

// uint64 EntityID;
struct EntityDTRecord
{
	// �ʰ��� ��� SubEntity�� �ִ�.
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
	// TODO : ���߿� Entity Ÿ�Ժ��� �ٽ� �и��ؾ���
	unordered_map<uint64, EntityDTRecord> m_mapEntityTable;
	
	// TODO : ����� �ȳ�.�Ф�
	unordered_map<uint32, Render2DComponentDTRecord> m_mapRender2DComponentTable;

//**************************************************************************************************//
//																									//
//						Method Area																	//
//																									//
//**************************************************************************************************//

// �ʱ�ȭ �Լ�
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
	// Table ������ �ε��ϴ� �Լ�.
	bool LoadTableFromFile();

// Propertys 
	DECLARE_SINGLE(ETableManager)
};

