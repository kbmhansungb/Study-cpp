#pragma once

/*

����� sort �� ���� �ݺ����� ��� �ݵ�� 
�������� �ݺ���(RandomAccessIterator) Ÿ���� �����ؾ� �ϹǷ�, 
�츮�� ���Դ� �����̳ʵ� �߿��� ���Ϳ� ��ũ�� �����ϰ� 
������ �����̳ʴ� sort �Լ��� ������ �� �����ϴ�. 
(���� ��� ����Ʈ�� ��� �ݺ��� Ÿ���� ����� �ݺ���(BidirectionalIterator) �̹Ƿ� �ȵ˴ϴ�)

list<int> l;
sort(l.begin(), l.end());

*/

#include <algorithm>
#include <iostream>
#include <vector>

namespace Test
{
    template <typename Iter>
    void print(Iter begin, Iter end)
    {
        while (begin != end) {
            std::cout << *begin << " ";
            begin++;
        }
        std::cout << std::endl;
    }
    struct int_compare
    {
        bool operator()(const int& a, const int& b) const { return a > b; }
    };
    void solve() {
        std::vector<int> vec;
        vec.push_back(5);
        vec.push_back(3);
        vec.push_back(1);
        vec.push_back(6);
        vec.push_back(4);
        vec.push_back(7);
        vec.push_back(2);

        std::cout << "���� �� ----" << std::endl;
        print(vec.begin(), vec.end());
        std::sort(vec.begin(), vec.end(), int_compare());
        // a > b�̹Ƿ� a �� ��Ŭ �� �տ� �´�
        // ū ������� �������� ���� ���������̶� �Ѵ�.
        std::cout << "���� �� ----" << std::endl;
        print(vec.begin(), vec.end());
    }
}

namespace Partial_sort
{
    void solve()
    {
        std::vector<int> vec = { 5, 3, 1, 6, 4, 7, 2 };
        std::partial_sort(vec.begin(), vec.begin() + 3, vec.end());
        // [start, end) ���ҵ� �߿���
        // [start, middle)���� ���ҵ��� ��ü ���ҵ� �߿��� ���� ���� �ֵ� ������ ����,
        // 5, 3, 1, 6, 4, 7, 2
        // 1, 2, 3 ...
        // ���� 3���� ���� ���� �༮���� �ְԵ�.
        /*
        ���࿡ �츮�� ��ü �迭�� ������ �ʿ䰡 ���� ���, 
        ���� �� 100 ���� �л� �߿��� ���� 10 ���� �л��� �������� ���� �ʹ�,
        �̷� ���̸� ���� sort �� ��ü�� ���� �� �ʿ� ���� 
        partial_sort �� 10 ���� ���� �ϴ� ���� �� ������ �˴ϴ�.
        */
    }
}

namespace Stable_sort
{
    /*
    
    sort �Լ��� ��� ���� �������� ���ҵ� ���� ����� ��ġ�� �����ϰ� �ٲ�������� 
    stable_sort �� ��� �� ������ ó���� �־��� ���� �״�� �������� �� �� �ֽ��ϴ�.

    �翬���� �̷��� ���� ���� ������ stable_sort �� �׳� sort ���� �� �� �����ɸ��ϴ�. 
    C++ ǥ�ؿ� ������ sort �Լ��� �־��� ��쿡���� O(n log n) �� ��������� stable_sort 
    �� ��� �־��� ��쿡�� O(n (log n)^2) ���� �۵��ϰ� �˴ϴ�. ���� �� ���� ��������.

    // �׳� �Է� ������ �����ϸ鼭 �����Ѵٴ� ��, �װ� �׸��ΰ�??

    */
}

namespace Remove_if
{
    struct is_odd {
        int num_delete;

        is_odd() : num_delete(0) {}

        bool operator()(const int& i) {
            if (num_delete >= 2) return false;

            if (i % 2 == 1) {
                num_delete++;
                return true;
            }

            return false;
        }
        // ���� �� �� ����. num_delete�� �ܺη� ������ �ؾ���.
    };

    void solve()
    {
        std::vector<int> vec = { 5, 3, 1, 6, 4, 7, 2 };
        //vec.erase(remove(vec.begin(), vec.end(), 3), vec.end());
        
        int num_erased = 1;
        vec.erase(std::remove_if(vec.begin(), vec.end(), [&num_erased](const int& val) -> bool
            { 
                return val == 4 || val == 2; 
            }),
            vec.end());

        // remove�� remove_if�� ������ ����� �۾��� ���� �ʴ´�. ��� �ڷ� ������ ���� �̵���Ű��, �������� �Ǵ� �κ��� ���� iterator�� ��ȯ�Ѵ�.

        vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd()),
            vec.end());
        // Ŭ���� ȣ�� �� �����ϸ� �ɹ� ������ ��� �� �� �ְ� �ȴ�.
        /*
        ��� C++ ǥ�ؿ� ������ remove_if �� ���޵Ǵ� �Լ� ��ü�� ��� ������ ȣ�⿡ ���� ���� ���°� �޶����� �ȵ˴ϴ�. 
        �ٽ� ����, �� ó�� �Լ� ��ü �ȿ� �ν��Ͻ� ���� (num_delete) �� �ִ� ���� ��Ģ�� �ȵȴٴ� ��������.

        �� ������ remove_if �� ������ ���� ���� ��, �ش� �Լ� ��ü�� ������ ���� �� �� �ֱ� �����Դϴ�. 
        ����, �̴� ��� �����ϳĿ� ���� �޶����ϴ�. ���� ��� �Ʒ� ������ ���캼���.

        �ٽ� �� �� �����ڸ�, �Լ� ��ü���� ����� Ư�� ���¸� �����ؼ� �̿� ���� ����� �޶����� ��ƾ�� ¥�� �ȵ˴ϴ�.
        �� ó�� �����ϱ� ���� ������ �߻��� �� �� �ֽ��ϴ�.
        */

        // �� �����ϰ� Ŭ���� �������� ���� �����Լ��� ó������.

    }

    class SomeClass {
        std::vector<int> vec;

        int num_erased;

    public:
        SomeClass() {
            vec.push_back(5);
            vec.push_back(3);
            vec.push_back(1);
            vec.push_back(2);
            vec.push_back(3);
            vec.push_back(4);

            num_erased = 1;

            //&num_erased�ϸ� ���ÿ��� num_erased�� ���Ǹ� ã�´�. �̷� ���
            // this�� ���ָ� �ɹ������� ������ �� �ְ� �ȴ�.
            vec.erase(std::remove_if(vec.begin(), vec.end(),
                [this, dividor = 2](int i) {
                    if (num_erased >= 2)
                        return false;
                    else if (i % dividor == 1) {
                        num_erased++;
                        return true;
                    }
                    return false;
                }),
                vec.end());

            /*
                []          : �ƹ��͵� ĸ�� ����
                [&a, b]     : a �� ���۷����� ĸ���ϰ� b �� (���� �Ұ�����) ���纻���� ĸ��
                [&]         : �ܺ��� ��� �������� ���۷����� ĸ��
                [=]         : �ܺ��� ��� �������� ���纻���� ĸ��
                [a = 3]     : a �� 3���� �ʱ�ȭ �ϰ� ������ ����
            */
        }
    };
}

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace transform
{
    template <typename Iter>
    void print(Iter begin, Iter end) {
        while (begin != end) {
            std::cout << "[" << *begin << "] ";
            begin++;
        }
        std::cout << std::endl;
    }

    void transform_solve() {
        std::vector<int> vec;
        vec.push_back(5);
        vec.push_back(3);
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        vec.push_back(4);

        // vec2 ���� 6 ���� 0 ���� �ʱ�ȭ �Ѵ�.
        std::vector<int> vec2(6, 0);

        std::cout << "ó�� vec �� vec2 ���� ------" << std::endl;
        print(vec.begin(), vec.end());
        print(vec2.begin(), vec2.end());

        std::cout << "vec ��ü�� 1 �� ���� ���� vec2 �� ���� -- " << std::endl;
        std::transform(vec.begin(), vec.end(), vec2.begin(),
            [](int i) { return i + 1; });
        print(vec.begin(), vec.end());
        print(vec2.begin(), vec2.end());

        // �����̶� ����, �����̶� ���� ���� �̵��ΰ�,,
    }
}