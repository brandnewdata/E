#pragma once
#include "WindowsCommon.h" // 윈도웅 프로그램에 기본적으로 사용되는 헤더들
#include "stl_datastructure.h" // stl, 자료구조 알고리즘
#include "Types.h" // 편의성을 위한 형 재선언
#include "DirectX.h" // DirectX 사용을 위한 헤더와 형재선언
#include "Macros.h" // 자동화 매크로들
#include "MutiThreading.h" // 멀티스레딩에 필요한 헤더들
#include "Utils.h" // 디거깅, 편의성등
#include "resource.h" // 기본 리소스
#include "CommonEnums.h" // 게임 전체에서 사용되는 이넘들
#include "SystemBase.h" // 모드 Component System의 추상 클래스

using namespace std;

// 윈도우 클래스 이름, 윈도우 타이틀 이름
#define WND_CLASS_NAME _T("E2_WND_CLASS")
#define WND_TITLE_NAME WND_CLASS_NAME

// 화면 크기 해상도
struct _Resolution
{
	int Wideth;
	int Height;
};
using RESOLUTION = struct _Resolution;
using PRESOLUTION = RESOLUTION*;

// 파일로드 해야하는 수치 데이터를 대체하는 임시 구조체
struct _PropertyDatas
{
	int Wideth;
};
using PROPERTY_DATAS = struct _PropertyDatas;
using PPROPERTY_DATAS = PROPERTY_DATAS* ;

// 파일로드 해야하는 Asset 데이터의 경로를 관리하는 임시 구조체
struct _AssetDatas
{
	string BG_Stage_1 = "d/ss";
};
using ASSET_DATAS = struct _AssetDatas;
using PASSET_DATAS = ASSET_DATAS *;

// Asset 유형 
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

// 레벨 유형
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


//편의성 함수들 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// T앞에 typename을 적어줘야 한다. 언제부터 변경된거 같은데 시간 엄청 버렷네;;
// 메모리를 직접 지우는 함수
template <typename T>
void Safe_Delete_pVectorList(T& p)
{
	typename T::iterator iter;
	// 새운 반복자를 만들어서 end값 비교용으로 한다.
	// 복잡한 자료형 문제를 피하기 위해서 형식을 맞춘 것으로 보임
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		// 벡터에 들어있는 포인터 값을 사용해서 메모리를 해제한다.
		SAFE_DEL((*iter));
	}

	// 벡터 저장된 모든 요소를 제거
	p.clear();
}

// 위의 수정형 Release가 구현된 class에 경우 이함수로 vector를 해제한다.
// 그런데 이렇게 하면 본체는 누가 지우냐 ;; 잘못 생각했나?
template <typename T>
void Safe_Release_VectorList(T& p)
{
	typename T::iterator iter;
	// 새운 반복자를 만들어서 end값 비교용으로 한다.
	// 복잡한 자료형 문제를 피하기 위해서 형식을 맞춘 것으로 보임
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		// 벡터에 들어있는 포인터 값을 사용해서 메모리를 해제한다.
		SAFE_RELEASE((*iter));
	}

	// 벡터 저장된 모든 요소를 제거
	p.clear();
}

// map에 저장된 요소에 할당된 메모리를 해제하고 map에 저장된 요소들도 지운다.
template <typename T>
void Safe_Del_Map(T& p)
{
	typename T::iterator iter;
	// 새운 반복자를 만들어서 end값 비교용으로 한다.
	// 복잡한 자료형 문제를 피하기 위해서 형식을 맞춘 것으로 보임
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		// 노드의 첫번째는 키값이고 2번째는 데이터를 할당한 메모리의 포인터이므로 이렇게 해제한다.
		// (second에는 data가 들어가지만 대부분 포인터값을 저장하므로) 
		SAFE_DEL(iter->second);
	}

	// map 저장된 모든 요소를 제거
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

// TODO : 잘 적용 됬는지 검증하기
const float ATK_Type_Weight_Table[ATK_Type::End][DF_Type::End] =
{
{150.f, 130.f, 70.f },
{100.f, 110.f, 140.f},
{70.f, 80.f, 200.f}
};

