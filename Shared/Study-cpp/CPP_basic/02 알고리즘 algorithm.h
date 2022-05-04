#pragma once

/*

참고로 sort 에 들어가는 반복자의 경우 반드시 
임의접근 반복자(RandomAccessIterator) 타입을 만족해야 하므로, 
우리가 봐왔던 컨테이너들 중에선 벡터와 데크만 가능하고 
나머지 컨테이너는 sort 함수를 적용할 수 없습니다. 
(예를 들어 리스트의 경우 반복자 타입이 양방향 반복자(BidirectionalIterator) 이므로 안됩니다)

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

        std::cout << "정렬 전 ----" << std::endl;
        print(vec.begin(), vec.end());
        std::sort(vec.begin(), vec.end(), int_compare());
        // a > b이므로 a 가 더클 때 앞에 온다
        // 큰 순서대로 내려오는 것을 내림차순이라 한다.
        std::cout << "정렬 후 ----" << std::endl;
        print(vec.begin(), vec.end());
    }
}

namespace Partial_sort
{
    void solve()
    {
        std::vector<int> vec = { 5, 3, 1, 6, 4, 7, 2 };
        std::partial_sort(vec.begin(), vec.begin() + 3, vec.end());
        // [start, end) 원소들 중에서
        // [start, middle)까지 원소들이 전체 원소들 중에서 제장 작은 애들 순으로 정렬,
        // 5, 3, 1, 6, 4, 7, 2
        // 1, 2, 3 ...
        // 앞의 3곳에 가작 작은 녀석들을 넣게됨.
        /*
        만약에 우리가 전체 배열을 정렬할 필요가 없을 경우, 
        예를 들어서 100 명의 학생 중에서 상위 10 명의 학생의 성적순을 보고 싶다,
        이런 식이면 굳이 sort 로 전체를 정렬 할 필요 없이 
        partial_sort 로 10 개만 정렬 하는 것이 더 빠르게 됩니다.
        */
    }
}

namespace Stable_sort
{
    /*
    
    sort 함수의 경우 정렬 과정에서 원소들 간의 상대적 위치를 랜덤하게 바꿔버리지만 
    stable_sort 의 경우 그 순서를 처음에 넣었던 상태 그대로 유지함을 알 수 있습니다.

    당연히도 이러한 제약 조건 때문에 stable_sort 는 그냥 sort 보다 좀 더 오래걸립니다. 
    C++ 표준에 따르면 sort 함수는 최악의 경우에서도 O(n log n) 이 보장되지만 stable_sort 
    의 경우 최악의 경우에서 O(n (log n)^2) 으로 작동하게 됩니다. 조금 더 느린 편이지요.

    // 그냥 입력 순서를 유지하면서 정렬한다는 뜻, 그게 그말인가??

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
        // 오류 날 수 있음. num_delete를 외부로 빼던가 해야함.
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

        // remove나 remove_if는 실제로 지우는 작업을 하지 않는다. 대신 뒤로 지워질 값을 이동시키고, 지워져야 되는 부분의 시작 iterator를 반환한다.

        vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd()),
            vec.end());
        // 클래스 호출 로 전달하면 맴버 변수를 사용 할 수 있게 된다.
        /*
        사실 C++ 표준에 따르면 remove_if 에 전달되는 함수 객체의 경우 이전의 호출에 의해 내부 상태가 달라지면 안됩니다. 
        다시 말해, 위 처럼 함수 객체 안에 인스턴스 변수 (num_delete) 를 넣는 것은 원칙상 안된다는 것이지요.

        그 이유는 remove_if 를 실제로 구현 했을 때, 해당 함수 객체가 여러번 복사 될 수 있기 때문입니다. 
        물론, 이는 어떻게 구현하냐에 따라서 달라집니다. 예를 들어 아래 버전을 살펴볼까요.

        다시 한 번 말하자면, 함수 객체에는 절대로 특정 상태를 저장해서 이에 따라 결과가 달라지는 루틴을 짜면 안됩니다.
        위 처럼 이해하기 힘든 오류가 발생할 수 도 있습니다.
        */

        // 더 간단하게 클래스 생성하지 말고 람다함수로 처리하자.

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

            //&num_erased하면 스택에서 num_erased의 정의를 찾는다. 이런 경우
            // this를 해주면 맴버변수에 접근할 수 있게 된다.
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
                []          : 아무것도 캡쳐 안함
                [&a, b]     : a 는 레퍼런스로 캡쳐하고 b 는 (변경 불가능한) 복사본으로 캡쳐
                [&]         : 외부의 모든 변수들을 레퍼런스로 캡쳐
                [=]         : 외부의 모든 변수들을 복사본으로 캡쳐
                [a = 3]     : a 를 3으로 초기화 하고 갈무리 저장
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

        // vec2 에는 6 개의 0 으로 초기화 한다.
        std::vector<int> vec2(6, 0);

        std::cout << "처음 vec 과 vec2 상태 ------" << std::endl;
        print(vec.begin(), vec.end());
        print(vec2.begin(), vec2.end());

        std::cout << "vec 전체에 1 을 더한 것을 vec2 에 저장 -- " << std::endl;
        std::transform(vec.begin(), vec.end(), vec2.begin(),
            [](int i) { return i + 1; });
        print(vec.begin(), vec.end());
        print(vec2.begin(), vec2.end());

        // 조금이라도 빨리, 조금이라도 쉽게 쓰면 이득인가,,
    }
}