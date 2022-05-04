#pragma once

/*
	
	2011 12 25

*/

#include <thread>
#include <functional>
#include <queue>
#include <vector>
#include <mutex>
namespace c17_thread_pool_v1
{

	class Thread_pool
	{
	private:
		// �����带 �����ϴ� ����
		std::vector<std::thread> threads;
		// ������ �����ϴ� jobť
		std::queue<std::function<void()>> jobs;

		// queue�� ��Ƽ ������ ȯ�濡�� �������� �ʱ� ������..
		// condition_variable�� mutex�� �����.
		std::condition_variable cv_jobs;
		std::mutex m_jobs;

		// ��� �����带 �����Ű�� ���� �ɹ� ����
		bool stop_all;

		void work_thread()
		{
			while (true)
			{
				std::unique_lock lock(this->m_jobs);

				cv_jobs.wait(lock, [this] () -> bool
					{ 
						return this->jobs.empty() == false || this->stop_all == true; 
					});

				if (this->stop_all == true)
				{
					return;
				}

				// ������ ���� ������ ������ ������ job�� �ϳ��� ó����.
				auto job = std::move(jobs.front());
				jobs.pop();

				// que�� �ٲ�����,, ���� que�� ������� �Ѱ��ش�.
				lock.unlock();

				job();
			}
		}

	public:
		Thread_pool(size_t num_threads) :
			stop_all(false)
		{
			printf("this ref : %d\n", (int)this);
			threads.reserve(num_threads);
			for (int i = 0; i < num_threads; ++i)
				threads.emplace_back([this] 
					{ 
						this->work_thread(); 
					});
		}

		~Thread_pool()
		{
			printf("close is called\n");

			// ���Ḧ ���ؼ� ��� �����带 ������.
			stop_all = true;
			this->cv_jobs.notify_all();

			// ������ ���� Ȯ��.
			for (auto& thread : threads)
				thread.join();
		}

		void enqueue_job(std::function<void()> job)
		{
			if (stop_all)
			{
				throw std::runtime_error("ThreadPool�� ��� ������.");
			}
			{
				printf("enqueue job.\n");
				std::lock_guard lock(this->m_jobs);
				//job();
				jobs.emplace(std::move(job));
				//auto get = std::move(jobs.front());
				//jobs.pop();
				//get();
			}

			this->cv_jobs.notify_one();
		}
	};
}

int main()
{

}