#pragma once

#include <string>
#include <vector>
#include <algorithm>
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

    // 이렇게 하니 오류나네,, 중복조합.. 방법이 없는 것인가?
    // 중복되는게 쫌 많나보네,,
    // 중복조합 구해서 푸는 것보다 느릴 수가 있냐,,,
    int answer = 0;
    vector<bool> visit(max_num);
    do
    {
        for (int i = 1; i <= numbers.size(); ++i)
        {
            int num = stoi(numbers.substr(0, i));
            if (visit[num] == false)
            {
                visit[num] = true;
                if (is_prim[num] == true)
                    answer += 1;
            }
        }
    } while (prev_permutation(numbers.begin(), numbers.end()));

    return answer;
}