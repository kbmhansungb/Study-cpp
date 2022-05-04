#pragma once

/*

	���� ���� (Race Condition)
	���� ���¶� �ϳ��� ������ �������� �����尡 �����͸� �Է��ϴ� ���¸� ����.

	���ؽ� (mutex)�� �����(deadlock)
	������ - �Һ��� ����
	condition_variable

	// CPU ���� �Ұ�
	CPU�� ��������(register)��� ���� �����͸� ����� ������ ������ ����.
	64��Ʈ ��ǻ���� ���, ���������� ũ����� 8����Ʈ�� �Ұ�,
	�Ϲ����� ���꿡�� ���Ǵ� ���� ���������� ��� 16�� �ۿ� ����. 32��Ʈ������ 8����...

	�� ������ �ذ��ϱ� ���Ѱ�
	���ؽ�(mutex)
	���ؽ��� ��ȣ ���� (mutual exclusion)��� �ܾ�� ���� ��.
	m.lock() �� m.unlock() ���̿� �� �����常�� �����ϰ� ������ �� �ִ� �ڵ� �κ��� �Ӱ� ����(critical section)�̶� �Ѵ�.

	-------------------------------------------------------------------------------------------
	������� ���ϱ� ���ؼ��� ������ ���� ���̵� ������ ���õȴ� (C++ Concurrency In Action)

	��ø�� Lock�� ����ϴ� ���� ���ض�
	��� ��������� �ִ� 1���� Lock���� �����Ѵٸ� ����� ��Ȳ�� �߻��ϴ� ���� ���� �� �ִ�.
	���� ��κ��� �����ο����� 1���� Lock���ε� ����ϴ�. ���� �������� Lock�� �ʿ�� �Ѵٸ�, ���� �ʿ�� �ϴ����� �����.

	Lock�� �����ϰ� ���� �� ���� �ڵ带 ȣ���ϴ� ���� ���ض�.
	���� �ڵ忡�� Lock�� ������ �� �� �ֱ⿡ ��ø�� Lock�� ��� ���� ���Ϸ��� Lock ������ ���� �ڵ带 ȣ���ϴ� ���� ���� �ؾ� �Ѵ�.
	-> �޼��� ȣ��� �����϶�� ���ΰ�

	Lock���� ������ ������ ������ ŉ���ض�.
	�������� Lock���� ȹ���ؾ� �� ��Ȳ�� �´ٸ�, �ݵ�� ���� ������ ������ ŉ���ض�.
	m1, m2 & m1, m2 ������ lock�ߴٸ� ������� �߻����� �ʾ��� ���̴�.

*/
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

void worker(int& result, std::mutex& m) {
	for (int i = 0; i < 10000; ++i)
	{
		m.lock();
		// ���� ���Ͽ� �� �����常�� �����ϰ� ������ �� �ִ� �κ���
		// �Ӱ迵��(critical section)�̶�� �Ѵ�.
		result += 1;
		m.unlock();
		// �Ǽ��� unlock�� �������� ������ �ƹ� �����嵵 ������ �������� ���Ѵ�.
		// �̷��� ��Ȳ�� �����(deadlock)�̶�� �Ѵ�.
	}
}

void worker2(int& result, std::mutex& m)
{
	for (int i = 0; i < 10000; i++)
	{
		std::lock_guard<std::mutex> lock(m);
		result += 1;
	}
	// �����带 ���Ͽ� ����� �ڵ����� �� �� �ִ�.
	// �����常 �ִ� ��Ȳ���� ���ؽ��� ���� ����� �ʿ䰡 ���� �ɱ�?
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

	std::cout << " Coutner ���� �� : " << counter << std::endl;
}

// ����� (Deadlock)

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

// ���ÿ� ���� �ߴٰ� ���� �� 
// �޼��� 1���� m1�� ���ϰ� m2�� ���ҷ��� ������ deadlock2���� ���Ǿ� ����Ѵ�.
// �޼��� 2���� m2�� ���ϰ� m1�� ���ҷ��� ������ deadlock1���� ���Ǿ� ����Ѵ�.
// !! ��������. ����� �̶� �Ѵ�.

// �켱���� �־� ������� ���� �� �ִ�.
// �ٸ� �� �����常 ����ؼ� ���ư��� ��� ����(starvation)�� �߻��� �� �ִ�.

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

			// m1�� �̹� lock�Ǿ� �ִٸ� �����ϰ� ��ٸ���.
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