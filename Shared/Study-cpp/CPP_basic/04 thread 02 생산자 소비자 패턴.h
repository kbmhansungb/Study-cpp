#pragma once

/*

	생산자(Producer) 소비자 (Consumer) 패턴
	멀티 쓰레드 프로그램에서 가장 많이 등장하는 생산자 - 소비자 패턴,

	생산자의 경우, 무언가 처리할 일을 받아오는 쓰레드를 의미,
	ex) 인터넷에서 페이지를 긁어오는 쓰레드

	소비자의 경우, 받은 일을 처리하는 쓰레드를 의미,
	ex) 긁어온 페이지를 분석하는 쓰레드가 해당

	소비자가 필요한경우에만 작동하도록 하는 것이 condition_variable이다.
	어떠 어떠한 조건을 만족할 때 까지 자라! 라는 명령

	생산자 소비자 페턴은 네트워크에서 주로 사용하기 때문에 예시 자체도 네트워크이다.
	https://modoocode.com/270

	조건 변수 (condition_variable)
	어떠 어떠한 조건을 만족할 때 대기하라라는 메서드
		1. cv->wait(unique_lock, condition function(boo())으로 notify될 때 까지 대기
		2. 대기하고 있는 스레드를 깨우고 싶다면 cv->notify_one(), 또는 cv->notify_all()을 이용하여 알려준다.
			condition function	true	:	두번째 부터, unique_lock의 mutex를 lock한다.
								false	:	mutex를 unlock, while문에 의해 다시한번 wait를 호출한다.
								
								1) 당연하게도 excepthion을 throw하면 안된다.
								2) 그외,	wait_for	: 지정된 시간 초과 기간동안 조건 변수가 깨어날 때까지 스레드를 차단.
											wait_untile	: 지정된 시점에 도달 하기 전까지 조건 변수가 깨어날 때까지 스레드를 차단.	
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
			// 웹사이트를 다운로드 하는데 걸리는 시간이라 생각하면 된다.
			// 각 쓰레드 별로 다운로드 하는데 걸리는 시간이 다르다.
			std::this_thread::sleep_for(std::chrono::milliseconds(100 * index));
			std::string content = "웹사이트 : " + std::to_string(i) + " from thread(" +
				std::to_string(index) + ")\n";

			// data 는 쓰레드 사이에서 공유되므로 critical section 에 넣어야 한다.
			m->lock();
			downloaded_pages->push(content);
			m->unlock();

			// consumer 에게 content 가 준비되었음을 알린다.
			cv->notify_one();
			/*
				만약에 페이지를 하나 다운 받았다면,
				잠자고 있는 쓰레드들 중 하나를 깨워서 일을 시켜야겠죠?
				(만약에 모든 쓰레드들이 일을 하고 있는 상태라면 아무 일도 일어나지 않습니다.)
				notify_one 함수는 말 그대로,조건이 거짓인 바람에 자고 있는 쓰레드 중
				하나를 깨워서 조건을 다시 검사하게 해줍니다.
				만일 조건이 참이 된다면 그 쓰레드가 다시 일을 시작하겠지요.
			*/
		}
	}

	void consumer(std::queue<std::string>* downloaded_pages, std::mutex* m,
		int* num_processed, std::condition_variable* cv) {
		while (*num_processed < 25)
		{
			std::unique_lock<std::mutex> lk(*m);
			/*
				참고로 기존의 lock_guard 와는 다르게 unique_lock 을 정의하였는데,
				사실 unique_lock 은 lock_guard 와 거의 동일합니다.
				다만, lock_guard 의 경우 생성자 말고는 따로 lock 을 할 수 없는데,
				unique_lock 은 unlock 후에 다시 lock 할 수 있습니다.

				덧붙여 unique_lock 을 사용한 이유는 cv->wait 가 unique_lock 을 인자로 받기 때문입니다.
			*/

			cv->wait(
				lk, [&] { return downloaded_pages->empty() == false || *num_processed == 25; });
			// condition_variable의 wait 함수의 결과가 참이 될 때까지 기다린다.
			// 여기서는 다운로드된 페이지가 있거나 원소의 개수가 25개가 된다면 작동되도록 했다.

			if (*num_processed == 25) {
				lk.unlock();
				return;
			}
			/*
				cv.wait 후에 아래 num_processed 가 25 인지 확인하는 구문이 추가되었는데,
				이는 wait 에서 탈출한 이유가 모든 페이지 처리를 완료해서 인지, 아니면
				정말 downloaded_pages 에 페이지가 추가됬는지 알 수 없기 때문입니다.
				만일 모든 페이지 처리가 끝나서 탈출한 것였다면, 그냥 쓰레드를 종료해야 합니다.
			*/

			// 맨 앞의 페이지를 읽고 대기 목록에서 제거한다.
			std::string content = downloaded_pages->front();
			downloaded_pages->pop();

			(*num_processed)++;
			lk.unlock();

			// content 를 처리한다.
			std::cout << content;
			std::this_thread::sleep_for(std::chrono::milliseconds(80));
		}
	}

	int solve() {
		// 현재 다운로드한 페이지들 리스트로, 아직 처리되지 않은 것들이다.
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

		// 나머지 자고 있는 쓰레드들을 모두 깨운다.
		cv.notify_all();

		for (int i = 0; i < 3; i++) {
			consumers[i].join();
		}
	}
}

// https://en.cppreference.com/w/cpp/thread/condition_variable
// 좀더 알고 싶다면,
// 여기서의 예제가 좀더 알기 쉽게 되어있다.

// `std::mutex` 대신 `std::shared_mutex`를 사용해야 합니다. 크기는 8바이트이고 성능은 `std::mutex`보다 높습니다.
// https://developercommunity.visualstudio.com/t/c-stdmutex-size-on-x64-86-is-80-bytes/334696
// https://docs.microsoft.com/ko-kr/cpp/standard-library/shared-mutex?view=msvc-170

#include <shared_mutex>

std::shared_mutex s;
void temp()
{
	// lock shared, 스레드가 뮤텍스의 공유 소유권을 가져올 때까지 호출 스레드를 차단.
	// unlock_shared 메서드는 스레드를 호출하여 가져온 뮤텍스의 공유 소유권을 해제합니다.
	// try_lock_shared 메서드는 차단 없이 뮤텍스에 대한 공유 소유권을 가져오려고 시도합니다. 
	// 반환 형식은bool로 변환할 수 있으며, true면 메서드가 소유권을 가져옵니다.
}