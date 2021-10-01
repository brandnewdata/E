// LookQueueTest.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "LockQueue.h"


LockQueue<_int32> q;

void Push()
{
	while (true)
	{
		_int32 value = rand() % 100;
		q.Push(value);

		this_thread::sleep_for(10ms);
	}
}

void Pop()
{
	while (true)
	{
		_int32 data = 0;
		if (q.TryPop(data))
			cout << data << endl;
	}
}


int main()
{
	thread t1(Push);
	thread t2(Pop);
	thread t3(Pop);


	t1.join();
	t2.join();
	t3.join();
}
