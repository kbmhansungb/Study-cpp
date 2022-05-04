#pragma once

#include <vector>
#include <set>

using namespace std;

int solution(vector<int> scoville, int K) {
    multiset<int> foods;
    for (int i = 0; i < scoville.size(); ++i)
    {
        foods.insert(scoville[i]);
    }

    int answer = 0;

    while (*foods.begin() <= K)
    {
        // 두개 보다 적으면 섞을 수 없다.
        if (foods.size() < 2)
            return -1;

        int a = *foods.begin();
        foods.erase(foods.begin());
        int b = *foods.begin();
        foods.erase(foods.begin());

        foods.insert(a + b * 2);

        answer++;
    }

    return answer;
}

// 흠... priority que로 푸는게  빠르네,,,
// sad...

#include <queue>
int solution2(vector<int> scoville, int K) {
    int answer = 0;
    int needHot;
    // 의미,, int를 담는, vector형태의 que에, 정렬이 필요할 때 큰 우선순위가 뒤로가도록 만들어라,,
    priority_queue<int, vector<int>, greater<int>> pq(scoville.begin(), scoville.end());
    // 맞나? 더 찾아 봐야 겠네,

    while (pq.top() < K) {
        if (pq.size() == 1) return answer = -1;
        needHot = pq.top(); pq.pop();
        pq.push(needHot + pq.top() * 2);
        pq.pop(); answer++;
    }

    return answer;
}