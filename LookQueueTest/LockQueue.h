#pragma once
#include <queue>
#include <mutex>
#include <utility> // move 사용

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

	//  출력매개변수를 받아서 이동대입으로 pop의 결과값을 받아가도록한다.
	bool TryPop(T& value)
	{
		lock_guard<mutex> lock(_mutex);
		if (_queue.empty())
			return false;

		value = std::move(_queue.front());
		_queue.pop();
		return true;
	}

	//  출력매개변수를 받아서 이동대입으로 pop의 결과값을 받아가도록한다.
	void WaitPop(T& value)
	{
		// 스레드가 큐의 뮤텍스 소유권이 없으면 역시 코드는 실행이 안 됩니다.
		unique_lock<mutex> lock(_mutex);
		// 뮤텍스 소유권이 있더라도 조건을 만족하지 못하면
		// 만족할 때 까지 lock을 유지하면서 wait 합니다.
		_conVar.wait(lock, [this] {return _queue.empty() == false; });
		value = std::move(_queue.front()); // pop한 값을 이동대입으로 전달한다.
		_queue.pop();
	}

private:
	queue<T> _queue;
	// 현재 스레드가 이mutex객체의 소유자가 아니면 이mutex로 잠군 
	// 네이임 규칙 : 멀티스레딩용 변수는 앞에 _만 붙임.
	// 크티컬 섹션에 접근할 수 없다. 
	// lock하는 방법이 여러가지 있는데 lock_quard(c++11 이후)도 그중에 하나.
	mutex _mutex;
	// 바인드해둔 함수가 참을 반환하는 시점까지 기다리는  _conVar.wait를 위해서 필요함.
	condition_variable _conVar;
};


