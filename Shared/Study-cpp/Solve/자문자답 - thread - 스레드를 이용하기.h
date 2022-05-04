#pragma once

#include <thread>
#include <queue>
#include <list>
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>

class ThreadPool
{
public:
	ThreadPool(size_t num_threads) :
		stop_condition(false)
	{
		worker_threads.reserve(num_threads);
		for (size_t i = 0; i < num_threads; ++i)
		{
			worker_threads.emplace_back([this]() { this->work_by_thread(); });
		}
	}
	~ThreadPool()
	{
		stop_condition = true;
		worker_condition_variable.notify_all();

		for (auto& worker : worker_threads)
		{
			worker.join();
		}
	}

private:
	std::queue<std::function<void()>> jobs;
	std::vector<std::thread> worker_threads;

	std::mutex jobs_mutex;
	std::condition_variable worker_condition_variable;
	bool stop_condition;

	void work_by_thread()
	{
		while (true) {
			std::unique_lock<std::mutex> lock(this->jobs_mutex);
			worker_condition_variable.wait(lock, [this]() { return !this->jobs.empty() || stop_condition; });
			
			if (stop_condition && this->jobs.empty()) return;
			
			auto job = std::move(jobs.front());
			jobs.pop();
			lock.unlock();

			job();
		}
	}

public:
	void enqueue_job(std::function<void()> job)
	{
		if (stop_condition)
			throw std::runtime_error("Thread pool »ç¿ë ÁßÁöµÊ.");

		{
			std::lock_guard<std::mutex> lock(jobs_mutex);
			jobs.push(std::move(job));
		}
		worker_condition_variable.notify_one();
	}
};

void work(int t, int id) {
	printf("%d start \n", id);
	std::this_thread::sleep_for(std::chrono::seconds(t));
	//printf("%d end after %ds\n", id, t);
}
void thread_test()
{
	ThreadPool pool(16);

	for (int i = 0; i < 1000; i++) {
		pool.enqueue_job([i]() { work(i % 3 + 1, i); });
	}
}