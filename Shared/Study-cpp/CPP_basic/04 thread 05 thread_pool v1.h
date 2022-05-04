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
		// 쓰레드를 보관하는 벡터
		std::vector<std::thread> threads;
		// 할일을 보관하는 job큐
		std::queue<std::function<void()>> jobs;

		// queue는 멀티 쓰레드 환경에서 안전하지 않기 때문에..
		// condition_variable과 mutex를 사용함.
		std::condition_variable cv_jobs;
		std::mutex m_jobs;

		// 모든 스레드를 종료시키기 위한 맴버 변수
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

				// 루프에 의해 조건이 충족될 때마다 job을 하나씩 처리함.
				auto job = std::move(jobs.front());
				jobs.pop();

				// que를 바꿨으니,, 이제 que의 지배권을 넘겨준다.
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

			// 종료를 위해서 모든 쓰레드를 정리함.
			stop_all = true;
			this->cv_jobs.notify_all();

			// 쓰레드 종료 확인.
			for (auto& thread : threads)
				thread.join();
		}

		void enqueue_job(std::function<void()> job)
		{
			if (stop_all)
			{
				throw std::runtime_error("ThreadPool이 사용 중지됨.");
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