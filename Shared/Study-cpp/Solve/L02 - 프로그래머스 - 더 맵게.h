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
        // �ΰ� ���� ������ ���� �� ����.
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

// ��... priority que�� Ǫ�°�  ������,,,
// sad...

#include <queue>
int solution2(vector<int> scoville, int K) {
    int answer = 0;
    int needHot;
    // �ǹ�,, int�� ���, vector������ que��, ������ �ʿ��� �� ū �켱������ �ڷΰ����� ������,,
    priority_queue<int, vector<int>, greater<int>> pq(scoville.begin(), scoville.end());
    // �³�? �� ã�� ���� �ڳ�,

    while (pq.top() < K) {
        if (pq.size() == 1) return answer = -1;
        needHot = pq.top(); pq.pop();
        pq.push(needHot + pq.top() * 2);
        pq.pop(); answer++;
    }

    return answer;
}