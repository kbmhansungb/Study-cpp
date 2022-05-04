#pragma once
#include <iostream>
#include <list>

// ����� ����� divisor_list�� �߰��ϴ� �޼���
void make_divisor(int num, std::list<int>& divisor_list)
{
    for (int i = 1; i <= num; ++i)
    {
        if (num % i == 0)
        {
            // ����� ��� �߰�
            divisor_list.push_back(i);
        }
    }
}

// ����Ʈ�� ���� ��ȯ
int list_sum(const std::list<int>& list)
{
    int result = 0;
    for (const auto& elum : list)
        result += elum;
    return result;
}

// [a, b]�� �������� 
// ����� ������ ¦���� ��� ���ϰ�,
// Ȧ���� ��� �� ����� ��ȯ�ϴ� �޼���
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