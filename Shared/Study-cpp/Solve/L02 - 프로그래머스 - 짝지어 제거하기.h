#pragma once


/*

	2021 11 29
    10:31 시작
    11:00 알고리즘은 맞음.. 효율성 테스트 에서 실패.
    11:12 최적화에 애먹음. 아직 못고침.
    11:28 최적화 실패,, 어떻게 풀었을까?

    순환문을 돌면서, 중복되는 문자열을 제거해 나간다.
    더이상 순환할 수 없다면 결과를 반환한다.

    ... stack으로 풀었구나.

    기억하자.
    하나씩 읽으면서 중복된 문자열을 제거할 때. stack 구조를 이용하면 된다.
    일반화를 어떻게 시키지?..

*/
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int solution(string s)
{
    // 실제 문자열을 복사하지 않고 중복된 것만 찾아서 제거.
    vector<bool> will_removed(s.size());
    queue<int> order;
    for (int i = 0; i < s.size(); ++i) order.push(i);

    bool in_roop = true;
    while (in_roop)
    {
        bool is_changed = false;

        queue<int> next_order;
        int before_index = -1;
        int now_index = -1;
        while (order.empty() == false)
        {
            if (before_index != -1)
                next_order.push(before_index);

            before_index = now_index;
            now_index = order.front(); order.pop();

            if (before_index != -1)
            {
                if (s[before_index] == s[now_index])
                {
                    is_changed = true;

                    will_removed[before_index] = true;
                    will_removed[now_index] = true;

                    before_index = -1;
                    now_index = -1;
                }
            }
        }
        order = move(next_order);

        if (is_changed == false)
            in_roop = false;
    }

    // 중복된 결과를 제거.
    // 이부분은 마음에 든다.
    s.erase(remove_if(s.begin(), s.end(), [start_index = 0, &will_removed](char ch) mutable
        {
            return will_removed[start_index++];
        }), s.end());

    if (s.size() == 0)
        return 1;
    else
        return 0;
}