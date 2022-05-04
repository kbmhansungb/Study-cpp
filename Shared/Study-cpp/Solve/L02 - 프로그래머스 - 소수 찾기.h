#pragma once

/*
https://programmers.co.kr/learn/courses/30/lessons/42839

�Ҽ��� ��� �����̳� �ϳ�,
���ڸ� ����� ��� �ϳ�.

17:50 ����
18:06 ����� ����.
18:16 �߸� �ۼ��ߵ�,,,
18:53 �ߺ� ���տ��� ������,,

https://twpower.github.io/90-combination-by-using-next_permutation
���� ����� ���� �������� ����..

�����Ҹ��� �ڵ尡 ���µ�,,,

*/

#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int solution(string numbers) {
    // �Ҽ� �����
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

    // �ߺ� ���� ���ϱ�
    set<int> can_make;
    for (int combination_size = 1; combination_size <= numbers.size(); ++combination_size)
    {
        // �ߺ� ���� �����
        vector<int> num(numbers.size());
        for (int num_index = 0; num_index < combination_size; ++num_index)
            num[num_index] = 1;

        do
        {

            // �ߺ������� �������� ��Ʈ�� �����
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

            // �ߺ����� ����
            sort(sub_str.begin(), sub_str.end());

            do
            {
                // �������� Ȯ��
                int this_num = stoi(sub_str);
                if (is_prim[this_num] == true)
                    can_make.insert(this_num);

            } while (next_permutation(sub_str.begin(), sub_str.end()));

        } while (prev_permutation(num.begin(), num.end()));
    }

    return can_make.size();
}