#pragma once
#include "Predefines.h"

class GameState
{
private:
	int m_nGameScore;
	int m_nLevelScore;
	int m_nStageScore;

public:
	// Getters
	inline int GetGameScore() const
	{
		return m_nGameScore;
	}

	inline int GetLevelScore() const
	{
		return m_nLevelScore;
	}

	inline int GetStageScore() const
	{
		return m_nStageScore;
	}

};

