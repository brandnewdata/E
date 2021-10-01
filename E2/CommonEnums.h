#pragma once

namespace EActiveOperation
{
	enum
	{
		True = 0,
		False = 1
	};
}

namespace EEntityType
{
	enum
	{
		RenderTarget = 0,
		HUD = 1,
		StaticObject = 2,
		MovableObject = 3,
		PlayerCharacter = 4,
		NonePlayerCharacter = 5,
		EnemyCharacter = 6,
		Item = 7,
		Buliding = 8,
		VisualEffect = 9,
		DamageObject = 10,
		Level = 11
	};
}
namespace EComponentSystemIndex
{
	enum
	{
		Job = 0,
		Entity = 1,
		Input = 2,
		Movement = 3,
		Network = 4,
		Render2D = 5,
		Timer = 6,
		UnitController = 7,
		World = 8,
		GameMode = 9,
		Collision = 10,
		UnitStatus = 11
	};
}

namespace EGameState
{
	enum
	{
		TITLE,
		GAME_READY,
		GAME_START,
		GAME_MAIN,//실제 게임 화면 스테이지 1 ,2,3,4, ...
		STAGE_CLEAR,
		GAME_OVER
	};
}
