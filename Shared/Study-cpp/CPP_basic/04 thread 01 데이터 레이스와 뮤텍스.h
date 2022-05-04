#pragma once

/*

	경쟁 상태 (Race Condition)
	경쟁 상태란 하나의 변수를 여러개의 스레드가 데이터를 입력하는 상태를 말함.

	뮤텍스 (mutex)와 데드락(deadlock)
	생산자 - 소비자 패턴
	condition_variable

	// CPU 간단 소개
	CPU의 레지스터(register)라는 곳에 데이터를 기록한 다음에 연산을 수행.
	64비트 컴퓨터의 경우, 레지스터의 크기들은 8바이트에 불과,
	일반적인 연산에서 사용되는 범용 레지스터의 경우 16개 밖에 없음. 32비트에서는 8개임...

	이 문제를 해결하기 위한게
	뮤텍스(mutex)
	뮤텍스란 상호 배제 (mutual exclusion)라는 단어에서 따온 말.
	m.lock() 과 m.unlock() 사이에 한 쓰레드만이 유일하게 실행할 수 있는 코드 부분을 임계 영역(critical section)이라 한다.

	-------------------------------------------------------------------------------------------
	데드락을 피하기 위해서는 다음과 같은 가이드 라인이 제시된다 (C++ Concurrency In Action)

	중첩된 Lock을 사용하는 것을 피해라
	모든 쓰레드들이 최대 1개의 Lock만을 소유한다면 데드락 상황이 발생하는 것을 피할 수 있다.
	또한 대부분의 디자인에서는 1개의 Lock으로도 충분하다. 만일 여러개의 Lock을 필요로 한다면, 정말 필요로 하는지를 물어보자.

	Lock을 소유하고 있을 때 유저 코드를 호출하는 것을 피해라.
	유저 코드에서 Lock을 소유할 수 도 있기에 중첩된 Lock을 얻는 것을 피하려면 Lock 소유시 유저 코드를 호출하는 것을 지양 해야 한다.
	-> 메서도 호출울 지향하라는 뜻인가

	Lock들을 언제나 정해진 순서로 흭득해라.
	여러개의 Lock들을 획득해야 할 상황이 온다면, 반드시 락을 정해진 순서로 흭득해라.
	m1, m2 & m1, m2 순으로 lock했다면 데드락은 발생하지 않았을 것이다.

*/
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

void worker(int& result, std::mutex& m) {
	for (int i = 0; i < 10000; ++i)
	{
		m.lock();
		// 락을 통하여 한 쓰레드만이 유일하게 실행할 수 있는 부분을
		// 임계영역(critical section)이라고 한다.
		result += 1;
		m.unlock();
		// 실수로 unlock을 선언하지 않으면 아무 쓰레드도 연산을 진행하지 못한다.
		// 이러한 상황을 데드락(deadlock)이라고 한다.
	}
}

void worker2(int& result, std::mutex& m)
{
	for (int i = 0; i < 10000; i++)
	{
		std::lock_guard<std::mutex> lock(m);
		result += 1;
	}
	// 락가드를 통하여 언락을 자동으로 할 수 있다.
	// 락가드만 있는 상황에서 뮤텍스를 전혀 고려할 필요가 없는 걸까?
}

void test()
{
	int counter = 0;
	std::mutex m;

	std::vector<std::thread> workers;
	for (int i = 0; i < 4; ++i)
	{
		workers.push_back(std::thread(worker, std::ref(counter), std::ref(m)));
	}

	for (int i = 0; i < 4; ++i)
	{
		workers[i].join();
	}

	std::cout << " Coutner 최종 값 : " << counter << std::endl;
}

// 데드락 (Deadlock)

void deadlock1(std::mutex& m1, std::mutex& m2)
{
	for (int i = 0; i < 10000; ++i)
	{
		std::lock_guard<std::mutex> lock1(m1);
		std::lock_guard<std::mutex> lock2(m2);
		// ...
	}
}

void deadlock2(std::mutex& m1, std::mutex& m2)
{
	for (int i = 0; i < 10000; ++i)
	{
		std::lock_guard<std::mutex> lock2(m2);
		std::lock_guard<std::mutex> lock1(m1);
		// ...
	}
}

// 동시에 실행 했다고 했을 때 
// 메서드 1에서 m1을 락하고 m2를 락할려고 했으나 deadlock2에서 락되어 대기한다.
// 메서드 2에서 m2를 락하고 m1을 락할려고 했으나 deadlock1에서 락되어 대기한다.
// !! 교착상태. 데드락 이라 한다.

// 우선권을 주어 데디락을 막을 수 있다.
// 다만 한 쓰레드만 계속해서 돌아가는 기아 상태(starvation)이 발생할 수 있다.

void worker1(std::mutex& m1, std::mutex& m2) {
	for (int i = 0; i < 10; ++i)
	{
		m1.lock();
		m2.lock();

		std::cout << "Worker1 Hi!" << i << std::endl;

		m2.unlock();
		m1.unlock();
	}
}

void worker2(std::mutex& m1, std::mutex& m2) {
	for (int i = 0; i < 10; ++i)
	{
		while (true)
		{
			m2.lock();

			// m1이 이미 lock되어 있다면 포기하고 기다린다.
			if (!m1.try_lock())
			{
				m2.unlock();
				continue;
			}
			std::cout << "Worker2 Hi!" << i << std::endl;

			m1.unlock();
			m2.unlock();

			break;
		}
	}
}