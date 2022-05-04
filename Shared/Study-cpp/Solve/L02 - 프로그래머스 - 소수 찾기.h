#pragma once

/*
https://programmers.co.kr/learn/courses/30/lessons/42839

소수를 담는 컨테이너 하나,
숫자를 만드는 방식 하나.

17:50 시작
18:06 디버그 시작.
18:16 잘못 작성했따,,,
18:53 중복 조합에서 막혔네,,

https://twpower.github.io/90-combination-by-using-next_permutation
조합 만드는 법을 익히도록 하자..

참고할만한 코드가 없는데,,,

*/

#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int solution(string numbers) {
    // 소수 만들기
    sort(numbers.rbegin(), numbers.rend());
    int max_num = stoi(numbers);
    vector<bool> is_prim(max_num + 1, true);
    is_prim[0] = false;
    is_prim[1] = false;
    for (int i = 2; i <= max_num; ++i)
    {
        if (is_prim[i] == true)
            for (int j = i * 2; j <= max_num; j += i)
            {
                is_prim[j] = false;
            }
    }

    // 중복 조합 구하기
    set<int> can_make;
    for (int combination_size = 1; combination_size <= numbers.size(); ++combination_size)
    {
        // 중복 조합 만들기
        vector<int> num(numbers.size());
        for (int num_index = 0; num_index < combination_size; ++num_index)
            num[num_index] = 1;

        do
        {

            // 중복조합을 바탕으로 스트링 만들기
            string sub_str; sub_str.resize(combination_size);
            for (int num_index = 0, sub_str_index = 0; num_index < num.size(); ++num_index)
            {
                if (num[num_index] != 0)
                {
                    sub_str[sub_str_index] = numbers[num_index];
                    ++sub_str_index;

                    if (sub_str_index >= combination_size)
                        break;
                }
            }

            // 중복조합 정리
            sort(sub_str.begin(), sub_str.end());

            do
            {
                // 숫자인지 확인
                int this_num = stoi(sub_str);
                if (is_prim[this_num] == true)
                    can_make.insert(this_num);

            } while (next_permutation(sub_str.begin(), sub_str.end()));

        } while (prev_permutation(num.begin(), num.end()));
    }

    return can_make.size();
}