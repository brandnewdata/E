#pragma once
#include "LockMacro.h"
#include <queue>
#include "EJob.h"

// [������ ���ܰ� �ִ�.]
// ť�� �ڷḦ �ְ� ���� ���۸� ������ �Ŀ� �ٷ� ��ȯ�ϹǷ� ���ɶ������ �� ����
// �����尡 �����ٰ� ���ؽ�Ʈ ����Ī ������� vs �����尡 ���ǹ��� ������ ���� ���ɶ� �������
// ������ ��� ���ɶ� ���ð��� ª�Ƽ� ���ɶ����� �����尡 ���� ���� ���� ���� �� ����. 

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


