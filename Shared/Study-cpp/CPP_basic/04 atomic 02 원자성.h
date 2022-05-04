#pragma once

// https://modoocode.com/271 ??? 연산속도의 차이.

/*

    ● 컴퓨터는 사실 여러분이 시키는 대로 하지 않는다.

    여태까지 여러분이 코드를 작성하면, 컴파일러가 그 코드를 그대로 기계어로 번역한 다음, CPU 가
    해당 번역된 기계어를 그대로 실행시킨다고 생각하셨을 것입니다.
    그런데 이게 사실이 아니라 한다면 여러분은 믿을 수 있으신가요?

    int a = 0;          | foo():                            | 
    int b = 0;          |   mov eax, DWORD PTR b[rip]       |   eax에 *(int*) b[rip] 가져오기
    void foo() {        |   move DWORD PTR b[rip], 1        |   *(int*) b[rip] = 1
        a = b + 1;      |   add eax, 1                      |   eax += 1
        b = 1;          |   mov DWORD PTR a[rip], eax       |   *(int*) a[rip] = eax
    }                   |   ret                             |

    한 작업 (세탁 - 건조 - 개기) 이 끝나기 전에, 다음 작업을 시작하는 방식으로 동시에 여러 개의 
    작업을 동시에 실행하는 것을 파이프라이닝(pipelining) 이라고 합니다.
    CPU 도 마찬가지입니다. 실제 CPU 에서 명령어를 실행할 때 여러 단계를 거치게 됩니다. 명령어를
    읽어야 하고 (fetch), 읽은 명령어가 무엇 인지 해석해야 하고 (decode), 해석된 명령어를 실행하고
    (execute), 마지막으로 결과를 써야 하지요 (write).
    CPU 역시 정확히 동일한 방법으로 명령어를 처리합니다.

    ● 과연 컴파일러만 재배치를 할까?

     한 가지 더 재미있는 점은, 꼭 컴파일러만이 명령어를 재배치하는게 아니라는 점입니다. 예를 들어서
    다음과 같은 두 명령을 생각해봅시다.
    
    // 현재 a = 0, b = 0;
    a = 1; // 캐시에 없음
    b = 1; // 캐시에 있음

     a = 1 의 경우 현재 a 가 캐시에 없으므로, 매우 오래 걸립니다. 반면에 b = 1; 의 경우 현재 b
    가 캐시에 있기 때문에 빠르게 처리할 수 있겠지요. 따라서 CPU 에서 위 코드가 실행될 때, b =
    1; 가 a = 1; 보다 먼저 실행될 수 있습니다.
    따라서, 다른 쓰레드에서 a 는 0 인데, b 가 1 인 순간을 관찰할 수 있다는 것입니다

    ● 무엇을 믿어야 하는가?

    아니, 이렇게 명령어 순서도 뒤죽 박죽 바꾸고 심지어 CPU 에서도 명령어들을 제대로 된 순서로
    실행하지 않는다면, 도대체 무엇을 믿을 수 있을까요?
    C++ 의 모든 객체들은 수정 순서(modification order) 라는 것을 정의할 수 있습니다. 수정
    순서라 하는 것은, 만약에 어떤 객체의 값을 실시간으로 확인할 수 있는 전지전능한 무언가가 있다고
    하였을 때, 해당 객체의 값의 변화를 기록한 것이라 보면 됩니다. (물론 실제로 존재하지 않고, 가상의
    수정 순서가 있다고 생각해봅시다.)

     모든 쓰레드에서 변수의 수정 순서에 동의만 한다면 문제될 것이 없습니다. 이 말이 무슨 말이냐면,
    같은 시간에 변수 a 의 값을 관찰했다고 해서 굳이 모든 쓰레드들이 동일한 값을 관찰할 필요는 없다
    라는 점입니다.

     쓰레드 간에서 같은 시간에 변수의 값을 읽었을 때 다른 값을 리턴해도 된다는 점은 조금 충격적입
    니다. 하지만, 이 조건을 강제할 수 없는 이유는 그 이유는 아래 그림 처럼 CPU 캐시가 각 코어별로
    존재하기 때문입니다.


    ● 원자성(atomicity)

    앞서 이야기 했듯이, C++ 에서 모든 쓰레드들이 수정 순서에 동의해야만 하는 경우는 
    바로 모든 연산들이 원자적 일 때 라고 하였습니다.
    
    원자적인 연산이 아닌 경우에는 모든 쓰레드에서 같은 수정 순서를 관찰할 수 있음이 보장되지 않기에 
    여러분이 직접 적절한 동기화 방법을 통해서 처리해야 합니다. 만일 이를 지키지 않는다면, 
    프로그램이 정의되지 않은 행동(undefined behavior)을 할 수 있습니다.
    
    그렇다면 원자적 이라는 것이 무엇일까요?
    이미 이름에서 짐작하셨겠지만, 원자적 연산이란, CPU 가 명령어 1 개로 처리하는 명령으로, 
    중간에 다른 쓰레드가 끼어들 여지가 전혀 없는 연산을 말합니다. 
    즉, 이 연산을 반 정도 했다 는 있을 수 없고 이 연산을 했다 혹은 안 했다 만 존재할 수 있습니다.
    마치 원자처럼 쪼갤 수 없다 해서 원자적(atomic) 이라고 합니다.

    std::atomic<int> x;
    x.is_lock_free() == true인 경우, mutex의 lock과 unlock 없이 해당 연산을 올바르게 수행할 수 있다는 의미.


    memory_order_relaxed는 서로 다른 변수의 relaxed 메모리 연산까지 CPU 마음대로 배치가 가능하기 때문.
    따라서 CPU에 가장 빠른 방법을 추구할 수 있음.

    memory_order_relaxed는 해당 메모리 명령이 자류롭게 재배치되도록 함.
    memory_order_release는 해당 명령 이전의 모든 메모리 명령들이 해당 명령 이후로 재배치 되는 것을 금지.
    memory_order_acquire는 해당 명령 뒤에 오는 모든 메모리 명령들이 해당 멸령 위로 재배치 되는 것을 금지.

    memory_order_acq_rel는 release와 acquire를 모두 수행함.

    memory_order_seq_cst는 메모리 명령의 순차적 일관성(sequential consistency)를 보장함. atomic의 기본 메모리 명령 설정임.
        순차적 일관성(sequential consistency)란 메모리 명령 재배치도 없고, 모든 쓰레드에서 모든 시점에 동일한 값을 관찰할 수 있는,
        CPU가 작동하는 방식이라 생각하면 됨.

         문제는 멀티 코어 시스템에서 memory_order_seq_cst 가 꽤나 비싼 연산이라는 것입니다. 인텔
        혹은 AMD 의 x86(-64) CPU 의 경우에는 사실 거의 순차적 일관성이 보장되서 memory_order_-
        seq_cst 를 강제하더라도 그 차이가 그렇게 크지 않습니다. 하지만 ARM 계열의 CPU 와 같은
        경우 순차적 일관성을 보장하기 위해서는 CPU 의 동기화 비용이 매우 큽니다. 따라서 해당 명령은
        정말 꼭 필요 할 때만 사용해야 합니다.

    참고로 memory_order_consume 은 다루지 않았는데 
        C++ 17 현재, memory_order_consume의 정의가 살짝 수정 중에 있기에 memory_order_consume 의 사용이 권장되지 않습니다.

    https://popcorntree.tistory.com/22 ??
    atomic은 별도의 자료 크기를 차지하나?

    ?? atomic<type>과 type의 자료 크기는 같다??
*/

#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

namespace c17_atomic
{
    void worker(std::atomic<int>& counter) {
        for (int i = 0; i < 10000; i++) {
            counter++;
        }
    }

    void solve() {
        std::atomic<int> counter(0);

        std::vector<std::thread> workers;
        for (int i = 0; i < 4; i++) {
            workers.push_back(std::thread(worker, std::ref(counter)));
        }

        for (int i = 0; i < 4; i++) {
            workers[i].join();
        }

        // 아무런 노력도 하지 않고 값은 40000이 나온다.
        std::cout << "Counter 최종 값 : " << counter << std::endl;
    }

    void t1(std::atomic<int>* a, std::atomic<int>* b) {
        b->store(1, std::memory_order_relaxed); // b = 1 (쓰기)
        int x = a->load(std::memory_order_relaxed); // x = a (읽기)
        printf("x : %d \n", x);
    }
    void t2(std::atomic<int>* a, std::atomic<int>* b) {
        a->store(1, std::memory_order_relaxed); // a = 1 (쓰기)
        int y = b->load(std::memory_order_relaxed); // y = b (읽기)
        printf("y : %d \n", y);
    }
    void memory_order_relaxed_test() {
        std::vector<std::thread> threads;
        std::atomic<int> a(0);
        std::atomic<int> b(0);
        threads.push_back(std::thread(t1, &a, &b));
        threads.push_back(std::thread(t2, &a, &b));
        for (int i = 0; i < 2; i++) {
            threads[i].join();
        }

        /*
            x : 1
            y : 0

            x : 0
            y : 1

            x : 1
            y : 1

            x : 0
            y : 0

            위와 같은 실행결과가 나올 수 있음.
            memory_order_relaxed는 서로 다른 변수의 relaxed 메모리 연산까지 CPU 마음대로 배치가 가능하기 때문.
            따라서 CPU에 가장 빠른 방법을 추구할 수 있음.

            다음과 같은 상황에서 사용될 수 있음.
                void worker(std::atomic<int>* counter) {
                    for (int i = 0; i < 10000; i++) {
                    // 다른 연산들 수행
                    counter->fetch_add(1, memory_order_relaxed);
                    }
                }
                어찌되었건 간에 1만 증가하면 되는 상황.

            memory_order_relaxed는 cpu에 너무 많은 자유를 부여하여 그 사용 용도는 꽤나 제한적.
        */
    }

    std::atomic<bool> is_ready;
    std::atomic<int> data[3];
    //int c = sizeof(int[3]);
    //int a = sizeof(data);
    void producer() {
        data[0].store(1, std::memory_order_relaxed);        // │ ┌ 자유롭게 재배치 되는 공간
        data[1].store(2, std::memory_order_relaxed);        // │ │
        data[2].store(3, std::memory_order_relaxed);        // │ └
        is_ready.store(true, std::memory_order_release);    // └ 해당 명령 이전의 메모리 명령이 이후로 재배치 되는 것을 막음
    }
    void consumer() {
        // data 가 준비될 때 까지 기다린다.
        while (!is_ready.load(std::memory_order_acquire)) {                                 // ┌ 해당 명령 이후의 메모리 명령이 이전으로 재배치 되는 것을 막음
        }                                                                                   // │
        std::cout << "data[0] : " << data[0].load(std::memory_order_relaxed) << std::endl;  // │ ┌ 자유롭게 재배치 되는 공간
        std::cout << "data[1] : " << data[1].load(std::memory_order_relaxed) << std::endl;  // │ │
        std::cout << "data[2] : " << data[2].load(std::memory_order_relaxed) << std::endl;  // │ └
    }
    void relaxed_and_relase_acquire() {
        std::vector<std::thread> threads;
        threads.push_back(std::thread(producer));
        threads.push_back(std::thread(consumer));
        for (int i = 0; i < 2; i++) {
            threads[i].join();
        }
    }

}