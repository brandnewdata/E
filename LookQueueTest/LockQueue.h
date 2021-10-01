#pragma once
#include <queue>
#include <mutex>
#include <utility> // move ���

using namespace std;
template<typename T>
class LockQueue
{
public:
	LockQueue() { }

	LockQueue(const LockQueue&) = delete;
	LockQueue& operator=(const LockQueue&) = delete;

	void Push(T value)
	{
		lock_guard<mutex> lock(_mutex);
		_queue.push(std::move(value));
		_conVar.notify_one();
	}

	//  ��¸Ű������� �޾Ƽ� �̵��������� pop�� ������� �޾ư������Ѵ�.
	bool TryPop(T& value)
	{
		lock_guard<mutex> lock(_mutex);
		if (_queue.empty())
			return false;

		value = std::move(_queue.front());
		_queue.pop();
		return true;
	}

	//  ��¸Ű������� �޾Ƽ� �̵��������� pop�� ������� �޾ư������Ѵ�.
	void WaitPop(T& value)
	{
		// �����尡 ť�� ���ؽ� �������� ������ ���� �ڵ�� ������ �� �˴ϴ�.
		unique_lock<mutex> lock(_mutex);
		// ���ؽ� �������� �ִ��� ������ �������� ���ϸ�
		// ������ �� ���� lock�� �����ϸ鼭 wait �մϴ�.
		_conVar.wait(lock, [this] {return _queue.empty() == false; });
		value = std::move(_queue.front()); // pop�� ���� �̵��������� �����Ѵ�.
		_queue.pop();
	}

private:
	queue<T> _queue;
	// ���� �����尡 ��mutex��ü�� �����ڰ� �ƴϸ� ��mutex�� �ᱺ 
	// ������ ��Ģ : ��Ƽ�������� ������ �տ� _�� ����.
	// ũƼ�� ���ǿ� ������ �� ����. 
	// lock�ϴ� ����� �������� �ִµ� lock_quard(c++11 ����)�� ���߿� �ϳ�.
	mutex _mutex;
	// ���ε��ص� �Լ��� ���� ��ȯ�ϴ� �������� ��ٸ���  _conVar.wait�� ���ؼ� �ʿ���.
	condition_variable _conVar;
};


