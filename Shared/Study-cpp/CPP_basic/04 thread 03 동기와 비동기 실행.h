#pragma once

/*

예를 들어서 여러분이 하드 디스크에서 파일을 읽는다고 생각해봅시다. SSD 가 아니라, 하드 디스
크를 사용한다면, 임의의 위치에 쓰여져 있는 파일을 읽는데 시간이 상당해 오래 걸립니다.

왜냐하면 하드 디스크의 경우 헤드 라고 부르는 장치가 디스크에 파일이 쓰여져 있는 실제 위치 까지
가야 하기 때문이죠. 이는 하드 디스크에 있는 모터가 디스크를 돌려서 헤드를 정해진 구역에 위치
시킵니다.

보통 사용하는 7200rpm 하드 디스크의 경우 (여기서 rpm 은 모터가 돌아가는 속도를 말합니다),
평균 4.17 밀리초가 걸린다고 합니다. 램에서 데이터를 읽어내는데 50 나노초가 걸리는 것에 비해
대략 8만배 정도 느린 셈입니다.

-------------------------------------------------------------------------------------------

string txt = read("a.txt"); // 5ms
string result = do_something_with_txt(txt); // 5ms
do_other_computation(); // 5ms 걸림 (CPU 로 연산을 수행함)

read 함수가 파일이 하드 디스크에서 읽어지는 동안 기다리기
때문입니다. 다시 말해 read 함수는 파일 읽기가 끝나기 전 까지 리턴하지 않고, CPU 는 아무것도
하지 않은 채 가만히 기다리게 됩니다.

이렇게, 한 번에 하나씩 순차적으로 실행 되는 작업을 동기적 (synchronous) 으로 실행 된다고
부릅니다.

만일 read 함수가 CPU 를 계속 사용한다면, 동기적으로 작업을 수행해도 문제될 것이 없습니다.
하지만 실제로는 read 함수가 하드 디스크에서 데이터를 읽어오는 동안 CPU 는 아무런 작업도
하지 않기 때문에, 그 시간에 오히려 CPU 를 놀리지 않고 do_other_computation 과 같은
작업을 수행하는 것이 더 바람직합니다.

-------------------------------------------------------------------------------------------

void file_read(string* result) {
	string txt = read("a.txt"); // (1)
	*result = do_something_with_txt(txt);
}
int main() {
	string result;
	thread t(file_read, &result);
	do_other_computation(); // (2)
	t.join();
}

위 코드의 수행 시간은 어떻게 될까요? 예를 들어서 쓰레드 t 를 생성한 뒤에 바로 새로운 쓰레드에서
file_read 함수를 실행한다고 해봅시다.

이와 같이 프로그램의 실행이, 한 갈래가 아니라 여러 갈래로 갈라져서 동시에 진행되는 것을 비동
기적(asynchronous) 실행 이라고 부릅니다. 자바스크립트와 같은 언어들은 언어 차원에서 비동
기적 실행을 지원하지만, C++ 의 경우 위와 같이 명시적으로 쓰레드를 생성해서 적절히 수행해야
했었습니다.

하지만 C++ 11 표준 라이브러리를 통해 매우 간단히 비동기적 실행을 할 수 있게 해주는 도구를
제공하고 있습니다.

-------------------------------------------------------------------------------------------


*/

#include <thread>
#include <future>
#include <functional>
namespace c17_asynchronous
{
	int some_task(int x) { return 10 + x; }
	void test()
	{
		std::packaged_task<int(int)> task(some_task);
		// promise로 부터 future을 설정함.
		std::future<int> start = task.get_future();
		std::thread t(std::move(task), 5); // 복사 생성이 불가능 하므로, 명시적으로 std::move를 해줘야함...
		// ...
		t.join();
	}
	void async()
	{
		auto f1 = std::async([]() {return 3; }); // future<int>로 형식연역된다.

		f1.get();
	}
}