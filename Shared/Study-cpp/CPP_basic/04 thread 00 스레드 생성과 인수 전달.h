#pragma once

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

namespace c17_thread
{
	/*
	
		������� ���� ���� ���ϹǷ� �����͸� �Ѱܾ� �Ѵ�.
	
	*/
	void worker(std::vector<int>::iterator start, std::vector<int>::iterator end, int* result)
	{
		for (auto it = start; it < end; ++it)
			*result += *it;

		// cout�� �ϸ� ����� �ڼ��̰� �ȴ�.
		//std::cout << "������" << std::this_thread::get_id() << "���� ����� ��� : " << *result << std::endl;
		// printf�� �ϸ� �ѹ��� ����ϰ� �ȴ�. printf�� �ʿ��ϱ⵵ �ϴ±���...
		printf("������%x���� ����� ��� : %d\n", (std::this_thread::get_id()), (int)(*result));
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
		std::cout << "��ü �� : " << total << std::endl;

	}
}

namespace c17_thread
{
	void func1()
	{
		for (int i = 0; i < 10; i++)
		{
			std::cout << "������ 1 �۵���!" << std::endl;
		}
	}

	void func2()
	{
		for (int i = 0; i < 10; i++)
		{
			std::cout << "������ 2 �۵���!" << std::endl;
		}
	}

	void func3()
	{
		for (int i = 0; i < 10; i++)
		{
			std::cout << "������ 3 �۵���!" << std::endl;
		}
	}

	void thread_call()
	{
		// ������ ����.
		std::thread t1(func1);
		std::thread t2(func2);
		std::thread t3(func3);

		// �����尡 ����ɶ����� ��ٷ���.
		t1.join(); // join�� �����尡 ����� �� ��ȯ�ϴ� �޼��� �̴�. 
		t2.join(); // t2�� ���� ������ t1���� join�� ��ȯ�� �� ���� ����ϰ� �ȴ�.
		t3.detach(); // detach�� �����Ű�� �ؾ������ ���̴�. ������� �˾Ƽ� ����Ǹ� ���ư���.

		/*
			�����带 �����ϰ� join�Ǵ� detach ���� �ʴ� �ٸ� ���ܸ� �߻��Ѵ�.
		*/
	}


}