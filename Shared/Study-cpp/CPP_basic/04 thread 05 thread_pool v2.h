#pragma once

/*
	2021 12 25
	사용하기 쉽게, 이해하기 쉽게, 보기 쉽게 하기 위해 
	최소단위로 쪼개는 것은 매우 중요하다.
*/

#include <utility>

#include <queue>
#include <functional>
#include <future>

#include <condition_variable>
#include <mutex>

namespace thread_pool
{
	class jobs
	{
		std::queue<std::function<void()>> function_queues;
	};

	template <typename T>
	concept is_worker 
		= (
			true
		);

	class workers
	{
		std::condition_variable condtion_variable;
		std::vector<std::thread> worker_threads;
	public:
		workers(int num_of_thread)
		{
		}
	};

	template <
		typename Workers, 
		typename Jobs
	>
	requires 
	is_worker<Workers>
	class job_worker
	{

	};

	job_worker<workers, jobs> a;
}

///*
//	
//	2011 11 28
//	씹어먹는 C++에서 가져옴.
//*/
//
//#include <chrono>
//#include <condition_variable>
//#include <cstdio>
//#include <functional>
//#include <future>
//#include <mutex>
//#include <queue>
//#include <thread>
//#include <vector>
//
//namespace c17_thread_pool_v2
//{
//	class ThreadPool {
//	public:
//		ThreadPool(size_t num_threads);
//		~ThreadPool();
//		// job 을 추가한다.
//		template <class F, class... Args>
//		std::future<decltype(std::invoke(declval<F>(), declval<Args>()...))> EnqueueJob(
//			F&& f, Args&&... args);
//	private:
//		// 총 Worker 쓰레드의 개수.
//		size_t num_threads_;
//		// Worker 쓰레드를 보관하는 벡터.
//		std::vector<std::thread> worker_threads_;
//		// 할일들을 보관하는 job 큐.
//		std::queue<std::function<void()>> jobs_;
//		// 위의 job 큐를 위한 cv 와 m.
//		std::condition_variable cv_job_q_;
//		std::mutex m_job_q_;
//		// 모든 쓰레드 종료
//		bool stop_all;
//		// Worker 쓰레드
//		void WorkerThread();
//	};
//	ThreadPool::ThreadPool(size_t num_threads)
//		: num_threads_(num_threads), stop_all(false) {
//		worker_threads_.reserve(num_threads_);
//		for (size_t i = 0; i < num_threads_; ++i) {
//			worker_threads_.emplace_back([this]() { this->WorkerThread(); });
//		}
//	}
//	void ThreadPool::WorkerThread() {
//		while (true) {
//			std::unique_lock<std::mutex> lock(m_job_q_);
//			cv_job_q_.wait(lock, [this]() { return !this->jobs_.empty() || stop_all; });
//			if (stop_all && this->jobs_.empty()) {
//				return;
//			}
//			// 맨 앞의 job 을 뺀다.
//			std::function<void()> job = std::move(jobs_.front());
//			jobs_.pop();
//			lock.unlock();
//			// 해당 job 을 수행한다 :)
//			job();
//		}
//	}
//	ThreadPool::~ThreadPool() {
//		stop_all = true;
//		cv_job_q_.notify_all();
//		for (auto& t : worker_threads_) {
//			t.join();
//		}
//	}
//	template <class F, class... Args>
//	std::future<decltype(std::invoke(declval<F>(), declval<Args>()...))>
//		ThreadPool::EnqueueJob(
//			F&& f, 
//			Args&&... args
//		) 
//	{
//		if (stop_all)
//		{
//			throw std::runtime_error("ThreadPool 사용 중지됨");
//		}
//		using return_type = typename std::invoke_result<F, Args...>::type;
//		auto job = std::make_shared<std::packaged_task<return_type()>>(
//			std::bind(std::forward<F>(f), std::forward<Args>(args)...));
//		std::future<return_type> job_result_future = job->get_future();
//		{
//			std::lock_guard<std::mutex> lock(m_job_q_);
//			jobs_.push([job]() { (*job)(); });
//		}
//		cv_job_q_.notify_one();
//		return job_result_future;
//	}
//}