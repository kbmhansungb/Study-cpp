#pragma once
#include <iostream>
#include <list>

// 약수를 만들어 divisor_list에 추가하는 메서드
void make_divisor(int num, std::list<int>& divisor_list)
{
    for (int i = 1; i <= num; ++i)
    {
        if (num % i == 0)
        {
            // 약수인 경우 추가
            divisor_list.push_back(i);
        }
    }
}

// 리스트의 합을 반환
int list_sum(const std::list<int>& list)
{
    int result = 0;
    for (const auto& elum : list)
        result += elum;
    return result;
}

// [a, b]인 구간에서 
// 약수의 개수가 짝수인 경우 더하고,
// 홀수인 경우 뺀 결과를 반환하는 메서드
int solution(int left, int right) {
    int answer = 0;

    for (int i = left; i <= right; ++i)
    {
        std::list<int> divisor_list;
        make_divisor(i, divisor_list);

    }

    return answer;
}

int main()
{
}