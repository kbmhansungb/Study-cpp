#pragma once

#include <thread>
#include <queue>
#include <list>
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <memory>

namespace lstd
{
	struct TaskContainer
	{
		using func_type = std::function<void()>;
	private:

		std::queue<func_type> tasks;
		std::mutex mutex;
	public:
		TaskContainer() = default;
		~TaskContainer() = default;

		inline std::mutex& get_mutex() { return mutex; }
		inline bool is_empty() { return tasks.empty(); }
		inline void pop_front(func_type& func) { func = std::move(tasks.front()), tasks.pop(); }
	};

	struct ThreadContainer
	{
	private:
		std::shared_ptr<TaskContainer> now_task_container;
		std::vector<std::thread> threads;
		std::condition_variable notify;
		bool stop_condition;
	public:
		ThreadContainer(size_t pool_size) :
			now_task_container(nullptr),
			stop_condition(false)
		{
			threads.reserve(pool_size);
			for (size_t i = 0; i < pool_size; ++i)
				threads.emplace_back([this]() { this->work_by_thread(); });
		}
		~ThreadContainer()
		{
			stop_condition = true;
			notify.notify_all();
			for (auto& thread : threads)
				thread.join();
		}
	private:
		inline void work_by_thread()
		{
			while (true) {
				std::unique_lock<std::mutex> lock(this->now_task_container->get_mutex());
				notify.wait(lock, [this]() { return !this->now_task_container->is_empty() || stop_condition; });

				// 스레드를 종료하는 시점.
				if (stop_condition && this->now_task_container->is_empty()) 
					return;

				TaskContainer::func_type task;
				this->now_task_container->pop_front(task);
				lock.unlock();

				task();
			}
		}
	};

	struct ThreadPool
	{
	private:
	public:
	};
}