#pragma once


/*

	2021 11 29
    10:31 ����
    11:00 �˰����� ����.. ȿ���� �׽�Ʈ ���� ����.
    11:12 ����ȭ�� �ָ���. ���� ����ħ.
    11:28 ����ȭ ����,, ��� Ǯ������?

    ��ȯ���� ���鼭, �ߺ��Ǵ� ���ڿ��� ������ ������.
    ���̻� ��ȯ�� �� ���ٸ� ����� ��ȯ�Ѵ�.

    ... stack���� Ǯ������.

    �������.
    �ϳ��� �����鼭 �ߺ��� ���ڿ��� ������ ��. stack ������ �̿��ϸ� �ȴ�.
    �Ϲ�ȭ�� ��� ��Ű��?..

*/
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int solution(string s)
{
    // ���� ���ڿ��� �������� �ʰ� �ߺ��� �͸� ã�Ƽ� ����.
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

    // �ߺ��� ����� ����.
    // �̺κ��� ������ ���.
    s.erase(remove_if(s.begin(), s.end(), [start_index = 0, &will_removed](char ch) mutable
        {
            return will_removed[start_index++];
        }), s.end());

    if (s.size() == 0)
        return 1;
    else
        return 0;
}