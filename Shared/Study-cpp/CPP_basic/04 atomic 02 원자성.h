#pragma once

// https://modoocode.com/271 ??? ����ӵ��� ����.

/*

    �� ��ǻ�ʹ� ��� �������� ��Ű�� ��� ���� �ʴ´�.

    ���±��� �������� �ڵ带 �ۼ��ϸ�, �����Ϸ��� �� �ڵ带 �״�� ����� ������ ����, CPU ��
    �ش� ������ ��� �״�� �����Ų�ٰ� �����ϼ��� ���Դϴ�.
    �׷��� �̰� ����� �ƴ϶� �Ѵٸ� �������� ���� �� �����Ű���?

    int a = 0;          | foo():                            | 
    int b = 0;          |   mov eax, DWORD PTR b[rip]       |   eax�� *(int*) b[rip] ��������
    void foo() {        |   move DWORD PTR b[rip], 1        |   *(int*) b[rip] = 1
        a = b + 1;      |   add eax, 1                      |   eax += 1
        b = 1;          |   mov DWORD PTR a[rip], eax       |   *(int*) a[rip] = eax
    }                   |   ret                             |

    �� �۾� (��Ź - ���� - ����) �� ������ ����, ���� �۾��� �����ϴ� ������� ���ÿ� ���� ���� 
    �۾��� ���ÿ� �����ϴ� ���� ���������̴�(pipelining) �̶�� �մϴ�.
    CPU �� ���������Դϴ�. ���� CPU ���� ��ɾ ������ �� ���� �ܰ踦 ��ġ�� �˴ϴ�. ��ɾ
    �о�� �ϰ� (fetch), ���� ��ɾ ���� ���� �ؼ��ؾ� �ϰ� (decode), �ؼ��� ��ɾ �����ϰ�
    (execute), ���������� ����� ��� ������ (write).
    CPU ���� ��Ȯ�� ������ ������� ��ɾ ó���մϴ�.

    �� ���� �����Ϸ��� ���ġ�� �ұ�?

     �� ���� �� ����ִ� ����, �� �����Ϸ����� ��ɾ ���ġ�ϴ°� �ƴ϶�� ���Դϴ�. ���� ��
    ������ ���� �� ����� �����غ��ô�.
    
    // ���� a = 0, b = 0;
    a = 1; // ĳ�ÿ� ����
    b = 1; // ĳ�ÿ� ����

     a = 1 �� ��� ���� a �� ĳ�ÿ� �����Ƿ�, �ſ� ���� �ɸ��ϴ�. �ݸ鿡 b = 1; �� ��� ���� b
    �� ĳ�ÿ� �ֱ� ������ ������ ó���� �� �ְ�����. ���� CPU ���� �� �ڵ尡 ����� ��, b =
    1; �� a = 1; ���� ���� ����� �� �ֽ��ϴ�.
    ����, �ٸ� �����忡�� a �� 0 �ε�, b �� 1 �� ������ ������ �� �ִٴ� ���Դϴ�

    �� ������ �Ͼ�� �ϴ°�?

    �ƴ�, �̷��� ��ɾ� ������ ���� ���� �ٲٰ� ������ CPU ������ ��ɾ���� ����� �� ������
    �������� �ʴ´ٸ�, ����ü ������ ���� �� �������?
    C++ �� ��� ��ü���� ���� ����(modification order) ��� ���� ������ �� �ֽ��ϴ�. ����
    ������ �ϴ� ����, ���࿡ � ��ü�� ���� �ǽð����� Ȯ���� �� �ִ� ���������� ���𰡰� �ִٰ�
    �Ͽ��� ��, �ش� ��ü�� ���� ��ȭ�� ����� ���̶� ���� �˴ϴ�. (���� ������ �������� �ʰ�, ������
    ���� ������ �ִٰ� �����غ��ô�.)

     ��� �����忡�� ������ ���� ������ ���Ǹ� �Ѵٸ� ������ ���� �����ϴ�. �� ���� ���� ���̳ĸ�,
    ���� �ð��� ���� a �� ���� �����ߴٰ� �ؼ� ���� ��� ��������� ������ ���� ������ �ʿ�� ����
    ��� ���Դϴ�.

     ������ ������ ���� �ð��� ������ ���� �о��� �� �ٸ� ���� �����ص� �ȴٴ� ���� ���� �������
    �ϴ�. ������, �� ������ ������ �� ���� ������ �� ������ �Ʒ� �׸� ó�� CPU ĳ�ð� �� �ھ��
    �����ϱ� �����Դϴ�.


    �� ���ڼ�(atomicity)

    �ռ� �̾߱� �ߵ���, C++ ���� ��� ��������� ���� ������ �����ؾ߸� �ϴ� ���� 
    �ٷ� ��� ������� ������ �� �� ��� �Ͽ����ϴ�.
    
    �������� ������ �ƴ� ��쿡�� ��� �����忡�� ���� ���� ������ ������ �� ������ ������� �ʱ⿡ 
    �������� ���� ������ ����ȭ ����� ���ؼ� ó���ؾ� �մϴ�. ���� �̸� ��Ű�� �ʴ´ٸ�, 
    ���α׷��� ���ǵ��� ���� �ൿ(undefined behavior)�� �� �� �ֽ��ϴ�.
    
    �׷��ٸ� ������ �̶�� ���� �����ϱ��?
    �̹� �̸����� �����ϼ̰�����, ������ �����̶�, CPU �� ��ɾ� 1 ���� ó���ϴ� �������, 
    �߰��� �ٸ� �����尡 ����� ������ ���� ���� ������ ���մϴ�. 
    ��, �� ������ �� ���� �ߴ� �� ���� �� ���� �� ������ �ߴ� Ȥ�� �� �ߴ� �� ������ �� �ֽ��ϴ�.
    ��ġ ����ó�� �ɰ� �� ���� �ؼ� ������(atomic) �̶�� �մϴ�.

    std::atomic<int> x;
    x.is_lock_free() == true�� ���, mutex�� lock�� unlock ���� �ش� ������ �ùٸ��� ������ �� �ִٴ� �ǹ�.


    memory_order_relaxed�� ���� �ٸ� ������ relaxed �޸� ������� CPU ������� ��ġ�� �����ϱ� ����.
    ���� CPU�� ���� ���� ����� �߱��� �� ����.

    memory_order_relaxed�� �ش� �޸� ����� �ڷ��Ӱ� ���ġ�ǵ��� ��.
    memory_order_release�� �ش� ��� ������ ��� �޸� ��ɵ��� �ش� ��� ���ķ� ���ġ �Ǵ� ���� ����.
    memory_order_acquire�� �ش� ��� �ڿ� ���� ��� �޸� ��ɵ��� �ش� ��� ���� ���ġ �Ǵ� ���� ����.

    memory_order_acq_rel�� release�� acquire�� ��� ������.

    memory_order_seq_cst�� �޸� ����� ������ �ϰ���(sequential consistency)�� ������. atomic�� �⺻ �޸� ��� ������.
        ������ �ϰ���(sequential consistency)�� �޸� ��� ���ġ�� ����, ��� �����忡�� ��� ������ ������ ���� ������ �� �ִ�,
        CPU�� �۵��ϴ� ����̶� �����ϸ� ��.

         ������ ��Ƽ �ھ� �ý��ۿ��� memory_order_seq_cst �� �ϳ� ��� �����̶�� ���Դϴ�. ����
        Ȥ�� AMD �� x86(-64) CPU �� ��쿡�� ��� ���� ������ �ϰ����� ����Ǽ� memory_order_-
        seq_cst �� �����ϴ��� �� ���̰� �׷��� ũ�� �ʽ��ϴ�. ������ ARM �迭�� CPU �� ����
        ��� ������ �ϰ����� �����ϱ� ���ؼ��� CPU �� ����ȭ ����� �ſ� Ů�ϴ�. ���� �ش� �����
        ���� �� �ʿ� �� ���� ����ؾ� �մϴ�.

    ����� memory_order_consume �� �ٷ��� �ʾҴµ� 
        C++ 17 ����, memory_order_consume�� ���ǰ� ��¦ ���� �߿� �ֱ⿡ memory_order_consume �� ����� ������� �ʽ��ϴ�.

    https://popcorntree.tistory.com/22 ??
    atomic�� ������ �ڷ� ũ�⸦ �����ϳ�?

    ?? atomic<type>�� type�� �ڷ� ũ��� ����??
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

        // �ƹ��� ��µ� ���� �ʰ� ���� 40000�� ���´�.
        std::cout << "Counter ���� �� : " << counter << std::endl;
    }

    void t1(std::atomic<int>* a, std::atomic<int>* b) {
        b->store(1, std::memory_order_relaxed); // b = 1 (����)
        int x = a->load(std::memory_order_relaxed); // x = a (�б�)
        printf("x : %d \n", x);
    }
    void t2(std::atomic<int>* a, std::atomic<int>* b) {
        a->store(1, std::memory_order_relaxed); // a = 1 (����)
        int y = b->load(std::memory_order_relaxed); // y = b (�б�)
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

            ���� ���� �������� ���� �� ����.
            memory_order_relaxed�� ���� �ٸ� ������ relaxed �޸� ������� CPU ������� ��ġ�� �����ϱ� ����.
            ���� CPU�� ���� ���� ����� �߱��� �� ����.

            ������ ���� ��Ȳ���� ���� �� ����.
                void worker(std::atomic<int>* counter) {
                    for (int i = 0; i < 10000; i++) {
                    // �ٸ� ����� ����
                    counter->fetch_add(1, memory_order_relaxed);
                    }
                }
                ����Ǿ��� ���� 1�� �����ϸ� �Ǵ� ��Ȳ.

            memory_order_relaxed�� cpu�� �ʹ� ���� ������ �ο��Ͽ� �� ��� �뵵�� �ϳ� ������.
        */
    }

    std::atomic<bool> is_ready;
    std::atomic<int> data[3];
    //int c = sizeof(int[3]);
    //int a = sizeof(data);
    void producer() {
        data[0].store(1, std::memory_order_relaxed);        // �� �� �����Ӱ� ���ġ �Ǵ� ����
        data[1].store(2, std::memory_order_relaxed);        // �� ��
        data[2].store(3, std::memory_order_relaxed);        // �� ��
        is_ready.store(true, std::memory_order_release);    // �� �ش� ��� ������ �޸� ����� ���ķ� ���ġ �Ǵ� ���� ����
    }
    void consumer() {
        // data �� �غ�� �� ���� ��ٸ���.
        while (!is_ready.load(std::memory_order_acquire)) {                                 // �� �ش� ��� ������ �޸� ����� �������� ���ġ �Ǵ� ���� ����
        }                                                                                   // ��
        std::cout << "data[0] : " << data[0].load(std::memory_order_relaxed) << std::endl;  // �� �� �����Ӱ� ���ġ �Ǵ� ����
        std::cout << "data[1] : " << data[1].load(std::memory_order_relaxed) << std::endl;  // �� ��
        std::cout << "data[2] : " << data[2].load(std::memory_order_relaxed) << std::endl;  // �� ��
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