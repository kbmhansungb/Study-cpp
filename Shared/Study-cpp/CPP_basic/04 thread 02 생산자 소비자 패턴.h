#pragma once

/*

	������(Producer) �Һ��� (Consumer) ����
	��Ƽ ������ ���α׷����� ���� ���� �����ϴ� ������ - �Һ��� ����,

	�������� ���, ���� ó���� ���� �޾ƿ��� �����带 �ǹ�,
	ex) ���ͳݿ��� �������� �ܾ���� ������

	�Һ����� ���, ���� ���� ó���ϴ� �����带 �ǹ�,
	ex) �ܾ�� �������� �м��ϴ� �����尡 �ش�

	�Һ��ڰ� �ʿ��Ѱ�쿡�� �۵��ϵ��� �ϴ� ���� condition_variable�̴�.
	� ��� ������ ������ �� ���� �ڶ�! ��� ���

	������ �Һ��� ������ ��Ʈ��ũ���� �ַ� ����ϱ� ������ ���� ��ü�� ��Ʈ��ũ�̴�.
	https://modoocode.com/270

	���� ���� (condition_variable)
	� ��� ������ ������ �� ����϶��� �޼���
		1. cv->wait(unique_lock, condition function(boo())���� notify�� �� ���� ���
		2. ����ϰ� �ִ� �����带 ����� �ʹٸ� cv->notify_one(), �Ǵ� cv->notify_all()�� �̿��Ͽ� �˷��ش�.
			condition function	true	:	�ι�° ����, unique_lock�� mutex�� lock�Ѵ�.
								false	:	mutex�� unlock, while���� ���� �ٽ��ѹ� wait�� ȣ���Ѵ�.
								
								1) �翬�ϰԵ� excepthion�� throw�ϸ� �ȵȴ�.
								2) �׿�,	wait_for	: ������ �ð� �ʰ� �Ⱓ���� ���� ������ ��� ������ �����带 ����.
											wait_untile	: ������ ������ ���� �ϱ� ������ ���� ������ ��� ������ �����带 ����.	
*/

#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

namespace
{
	void producer(std::queue<std::string>* downloaded_pages, std::mutex* m,
		int index, std::condition_variable* cv) {
		for (int i = 0; i < 5; i++) {
			// ������Ʈ�� �ٿ�ε� �ϴµ� �ɸ��� �ð��̶� �����ϸ� �ȴ�.
			// �� ������ ���� �ٿ�ε� �ϴµ� �ɸ��� �ð��� �ٸ���.
			std::this_thread::sleep_for(std::chrono::milliseconds(100 * index));
			std::string content = "������Ʈ : " + std::to_string(i) + " from thread(" +
				std::to_string(index) + ")\n";

			// data �� ������ ���̿��� �����ǹǷ� critical section �� �־�� �Ѵ�.
			m->lock();
			downloaded_pages->push(content);
			m->unlock();

			// consumer ���� content �� �غ�Ǿ����� �˸���.
			cv->notify_one();
			/*
				���࿡ �������� �ϳ� �ٿ� �޾Ҵٸ�,
				���ڰ� �ִ� ������� �� �ϳ��� ������ ���� ���Ѿ߰���?
				(���࿡ ��� ��������� ���� �ϰ� �ִ� ���¶�� �ƹ� �ϵ� �Ͼ�� �ʽ��ϴ�.)
				notify_one �Լ��� �� �״��,������ ������ �ٶ��� �ڰ� �ִ� ������ ��
				�ϳ��� ������ ������ �ٽ� �˻��ϰ� ���ݴϴ�.
				���� ������ ���� �ȴٸ� �� �����尡 �ٽ� ���� �����ϰ�����.
			*/
		}
	}

	void consumer(std::queue<std::string>* downloaded_pages, std::mutex* m,
		int* num_processed, std::condition_variable* cv) {
		while (*num_processed < 25)
		{
			std::unique_lock<std::mutex> lk(*m);
			/*
				����� ������ lock_guard �ʹ� �ٸ��� unique_lock �� �����Ͽ��µ�,
				��� unique_lock �� lock_guard �� ���� �����մϴ�.
				�ٸ�, lock_guard �� ��� ������ ����� ���� lock �� �� �� ���µ�,
				unique_lock �� unlock �Ŀ� �ٽ� lock �� �� �ֽ��ϴ�.

				���ٿ� unique_lock �� ����� ������ cv->wait �� unique_lock �� ���ڷ� �ޱ� �����Դϴ�.
			*/

			cv->wait(
				lk, [&] { return downloaded_pages->empty() == false || *num_processed == 25; });
			// condition_variable�� wait �Լ��� ����� ���� �� ������ ��ٸ���.
			// ���⼭�� �ٿ�ε�� �������� �ְų� ������ ������ 25���� �ȴٸ� �۵��ǵ��� �ߴ�.

			if (*num_processed == 25) {
				lk.unlock();
				return;
			}
			/*
				cv.wait �Ŀ� �Ʒ� num_processed �� 25 ���� Ȯ���ϴ� ������ �߰��Ǿ��µ�,
				�̴� wait ���� Ż���� ������ ��� ������ ó���� �Ϸ��ؼ� ����, �ƴϸ�
				���� downloaded_pages �� �������� �߰������ �� �� ���� �����Դϴ�.
				���� ��� ������ ó���� ������ Ż���� �Ϳ��ٸ�, �׳� �����带 �����ؾ� �մϴ�.
			*/

			// �� ���� �������� �а� ��� ��Ͽ��� �����Ѵ�.
			std::string content = downloaded_pages->front();
			downloaded_pages->pop();

			(*num_processed)++;
			lk.unlock();

			// content �� ó���Ѵ�.
			std::cout << content;
			std::this_thread::sleep_for(std::chrono::milliseconds(80));
		}
	}

	int solve() {
		// ���� �ٿ�ε��� �������� ����Ʈ��, ���� ó������ ���� �͵��̴�.
		std::queue<std::string> downloaded_pages;
		std::mutex m;
		std::condition_variable cv;

		std::vector<std::thread> producers;
		for (int i = 0; i < 5; i++) {
			producers.push_back(
				std::thread(producer, &downloaded_pages, &m, i + 1, &cv));
		}

		int num_processed = 0;
		std::vector<std::thread> consumers;
		for (int i = 0; i < 3; i++) {
			consumers.push_back(
				std::thread(consumer, &downloaded_pages, &m, &num_processed, &cv));
		}

		for (int i = 0; i < 5; i++) {
			producers[i].join();
		}

		// ������ �ڰ� �ִ� ��������� ��� �����.
		cv.notify_all();

		for (int i = 0; i < 3; i++) {
			consumers[i].join();
		}
	}
}

// https://en.cppreference.com/w/cpp/thread/condition_variable
// ���� �˰� �ʹٸ�,
// ���⼭�� ������ ���� �˱� ���� �Ǿ��ִ�.

// `std::mutex` ��� `std::shared_mutex`�� ����ؾ� �մϴ�. ũ��� 8����Ʈ�̰� ������ `std::mutex`���� �����ϴ�.
// https://developercommunity.visualstudio.com/t/c-stdmutex-size-on-x64-86-is-80-bytes/334696
// https://docs.microsoft.com/ko-kr/cpp/standard-library/shared-mutex?view=msvc-170

#include <shared_mutex>

std::shared_mutex s;
void temp()
{
	// lock shared, �����尡 ���ؽ��� ���� �������� ������ ������ ȣ�� �����带 ����.
	// unlock_shared �޼���� �����带 ȣ���Ͽ� ������ ���ؽ��� ���� �������� �����մϴ�.
	// try_lock_shared �޼���� ���� ���� ���ؽ��� ���� ���� �������� ���������� �õ��մϴ�. 
	// ��ȯ ������bool�� ��ȯ�� �� ������, true�� �޼��尡 �������� �����ɴϴ�.
}