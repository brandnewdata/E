#pragma once
#include "LockMacro.h"
#include <queue>
#include "EJob.h"

// [하지만 예외가 있다.]
// 큐에 자료를 넣고 빼는 동작만 수행한 후에 바로 반환하므로 스핀락방식이 더 좋음
// 스레드가 잠들었다가 컨텍스트 스위칭 오버헤드 vs 스레드가 무의미한 루프를 도는 스핀락 오버헤드
// 게임의 경우 스핀락 대기시간이 짧아서 스핀락으로 스레드가 잠드는 것을 막는 편이 더 좋다. 

using namespace std;

class EJobQueue
{
public:
	void Push(EJob item)
	{
		WRITE_LOCK;
		m_Jobs.push(item);
	}

	EJob Pop()
	{
		WRITE_LOCK;
		if (m_Jobs.empty())
			return EJob(1, 0, 0, 0);

		EJob ret = m_Jobs.front();
		m_Jobs.pop();
		return ret;
	}

	void PopAll(OUT vector<EJob>& items)
	{
		WRITE_LOCK;
		while (m_Jobs.empty() == false)
		{
			items.push_back(Pop());
		}
	}

	void Clear()
	{
		WRITE_LOCK;
		m_Jobs = queue<EJob>();
	}

private:
	USE_LOCK;
	queue<EJob> m_Jobs;
};


