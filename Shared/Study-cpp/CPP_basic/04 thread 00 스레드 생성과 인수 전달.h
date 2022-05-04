#pragma once

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

namespace c17_thread
{
	/*
	
		스레드는 값을 받지 못하므로 포인터를 넘겨야 한다.
	
	*/
	void worker(std::vector<int>::iterator start, std::vector<int>::iterator end, int* result)
	{
		for (auto it = start; it < end; ++it)
			*result += *it;

		// cout로 하면 출력이 뒤섞이게 된다.
		//std::cout << "쓰레드" << std::this_thread::get_id() << "에서 계산한 결과 : " << *result << std::endl;
		// printf로 하면 한번에 출력하게 된다. printf가 필요하기도 하는구나...
		printf("쓰레드%x에서 계산한 결과 : %d\n", (std::this_thread::get_id()), (int)(*result));
	}
	void get_thread_return()
	{
		std::vector<int> data(10000);
		std::transform(data.begin(), data.end(), data.begin(),
			[a = 0](int ptr) mutable -> int
		{
			return ptr = a++;
		});

		std::vector<int> partial_sums(4);
		std::vector<std::thread> workers;
		for (int i = 0; i < 4; i++) {
			workers.push_back(std::thread(worker, data.begin() + i * 2500,
				data.begin() + (i + 1) * 2500, &partial_sums[i]));
		}

		for (int i = 0; i < 4; i++) {
			workers[i].join();
		}

		int total = 0;
		for (int i = 0; i < 4; i++) {
			total += partial_sums[i];
		}
		std::cout << "전체 합 : " << total << std::endl;

	}
}

namespace c17_thread
{
	void func1()
	{
		for (int i = 0; i < 10; i++)
		{
			std::cout << "쓰레드 1 작동중!" << std::endl;
		}
	}

	void func2()
	{
		for (int i = 0; i < 10; i++)
		{
			std::cout << "쓰레드 2 작동중!" << std::endl;
		}
	}

	void func3()
	{
		for (int i = 0; i < 10; i++)
		{
			std::cout << "쓰레드 3 작동중!" << std::endl;
		}
	}

	void thread_call()
	{
		// 스레드 실행.
		std::thread t1(func1);
		std::thread t2(func2);
		std::thread t3(func3);

		// 스레드가 종료될때까지 기다려라.
		t1.join(); // join은 쓰레드가 종료될 때 반환하는 메서드 이다. 
		t2.join(); // t2가 먼저 끝나도 t1에서 join이 반환할 때 까지 대기하게 된다.
		t3.detach(); // detach는 실행시키고 잊어버리는 것이다. 스레드는 알아서 종료되면 돌아간다.

		/*
			스레드를 생성하고 join또는 detach 하지 않는 다면 예외를 발생한다.
		*/
	}


}