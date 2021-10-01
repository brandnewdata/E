#pragma once
#include "WindowsCommon.h" // ������ ���α׷��� �⺻������ ���Ǵ� �����
#include "stl_datastructure.h" // stl, �ڷᱸ�� �˰���
#include "Types.h" // ���Ǽ��� ���� �� �缱��
#include "DirectX.h" // DirectX ����� ���� ����� ���缱��
#include "Macros.h" // �ڵ�ȭ ��ũ�ε�
#include "MutiThreading.h" // ��Ƽ�������� �ʿ��� �����
#include "Utils.h" // ��ű�, ���Ǽ���
#include "resource.h" // �⺻ ���ҽ�
#include "CommonEnums.h" // ���� ��ü���� ���Ǵ� �̳ѵ�
#include "SystemBase.h" // ��� Component System�� �߻� Ŭ����

using namespace std;

// ������ Ŭ���� �̸�, ������ Ÿ��Ʋ �̸�
#define WND_CLASS_NAME _T("E2_WND_CLASS")
#define WND_TITLE_NAME WND_CLASS_NAME

// ȭ�� ũ�� �ػ�
struct _Resolution
{
	int Wideth;
	int Height;
};
using RESOLUTION = struct _Resolution;
using PRESOLUTION = RESOLUTION*;

// ���Ϸε� �ؾ��ϴ� ��ġ �����͸� ��ü�ϴ� �ӽ� ����ü
struct _PropertyDatas
{
	int Wideth;
};
using PROPERTY_DATAS = struct _PropertyDatas;
using PPROPERTY_DATAS = PROPERTY_DATAS* ;

// ���Ϸε� �ؾ��ϴ� Asset �������� ��θ� �����ϴ� �ӽ� ����ü
struct _AssetDatas
{
	string BG_Stage_1 = "d/ss";
};
using ASSET_DATAS = struct _AssetDatas;
using PASSET_DATAS = ASSET_DATAS *;

// Asset ���� 
namespace AssetType
{
	enum
	{
		None,
		Sprite, Begin = 1,
		Sound,
		Mission, End = 3
	};
}

// ���� ����
namespace LevelType
{
	enum
	{
		None,
		Loading, Begin =1,
		Title,
		Play,
		Quit, End = 4
	};
}


namespace StageClearScore
{
	enum
	{
		None = 0,
		Lv1, Begin = 1000,
		Lv2 = 3000,
		Lv3 = 5000,
		Lv4 = 7000,
		Lv5, End = 10000,
	};
}

enum
{
	DIR_LEFT,
	DIR_RIGHT
};


//���Ǽ� �Լ��� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// T�տ� typename�� ������� �Ѵ�. �������� ����Ȱ� ������ �ð� ��û ���ǳ�;;
// �޸𸮸� ���� ����� �Լ�
template <typename T>
void Safe_Delete_pVectorList(T& p)
{
	typename T::iterator iter;
	// ���� �ݺ��ڸ� ���� end�� �񱳿����� �Ѵ�.
	// ������ �ڷ��� ������ ���ϱ� ���ؼ� ������ ���� ������ ����
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		// ���Ϳ� ����ִ� ������ ���� ����ؼ� �޸𸮸� �����Ѵ�.
		SAFE_DEL((*iter));
	}

	// ���� ����� ��� ��Ҹ� ����
	p.clear();
}

// ���� ������ Release�� ������ class�� ��� ���Լ��� vector�� �����Ѵ�.
// �׷��� �̷��� �ϸ� ��ü�� ���� ����� ;; �߸� �����߳�?
template <typename T>
void Safe_Release_VectorList(T& p)
{
	typename T::iterator iter;
	// ���� �ݺ��ڸ� ���� end�� �񱳿����� �Ѵ�.
	// ������ �ڷ��� ������ ���ϱ� ���ؼ� ������ ���� ������ ����
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		// ���Ϳ� ����ִ� ������ ���� ����ؼ� �޸𸮸� �����Ѵ�.
		SAFE_RELEASE((*iter));
	}

	// ���� ����� ��� ��Ҹ� ����
	p.clear();
}

// map�� ����� ��ҿ� �Ҵ�� �޸𸮸� �����ϰ� map�� ����� ��ҵ鵵 �����.
template <typename T>
void Safe_Del_Map(T& p)
{
	typename T::iterator iter;
	// ���� �ݺ��ڸ� ���� end�� �񱳿����� �Ѵ�.
	// ������ �ڷ��� ������ ���ϱ� ���ؼ� ������ ���� ������ ����
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		// ����� ù��°�� Ű���̰� 2��°�� �����͸� �Ҵ��� �޸��� �������̹Ƿ� �̷��� �����Ѵ�.
		// (second���� data�� ������ ��κ� �����Ͱ��� �����ϹǷ�) 
		SAFE_DEL(iter->second);
	}

	// map ����� ��� ��Ҹ� ����
	p.clear();
}

namespace ATK_Type
{
	enum
	{
		None,
		Slash, Begin = 1,
		Pierce,
		Magic,
		End
	};
}

namespace DF_Type
{
	enum
	{
		None,
		Cloth, Begin = 1,
		Leather,
		MetalPlate,
		End
	};
}

// TODO : �� ���� ����� �����ϱ�
const float ATK_Type_Weight_Table[ATK_Type::End][DF_Type::End] =
{
{150.f, 130.f, 70.f },
{100.f, 110.f, 140.f},
{70.f, 80.f, 200.f}
};

