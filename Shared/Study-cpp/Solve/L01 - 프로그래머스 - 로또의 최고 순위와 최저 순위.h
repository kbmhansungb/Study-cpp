#pragma once

/*

https://programmers.co.kr/learn/courses/30/lessons/77484

11:10 ����
11:31 ����

1. { ���� ��, ���� �� + 0�� ���� }�� ����.
	// �ζ��� ������ �����Ƿ�, ������ ������ �ʿ����� �ʾ� ����.
	1. lottos�� �����鼭 0�� �ƴ� ��� win_nums�� ���� �ִ��� Ȯ��. �ִٸ� correct ũ�⸦ ����.
	2. 0�̶�� unkown ũ�⸦ ����.
	3. Ž�� ������ answer�� [0] = correct, [1] = correct + unkown �ϸ� ��.
2. �ζ� ������ ��ȯ
	1. �ζ� ������ ��ȯ�� min(7 - n, 6); ���� �����ϰ� ���� �� ����.

������ �а� �����ϴµ� �ð��� ���� �ɸ���. �� �κ��� ��� �ذ� �� �� �ִ°�?
������ ���� Ǯ��� ����ڿ� ���°� ����.

*/

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(vector<int> lottos, vector<int> win_nums) {

    //    1. { ���� ��, ���� �� + 0�� ���� }�� ����.
    //	    // �ζ��� ������ �����Ƿ�, ������ ������ �ʿ����� �ʾ� ����.
    //	    1. lottos�� �����鼭 0�� �ƴ� ��� win_nums�� ���� �ִ��� Ȯ��. �ִٸ� correct ũ�⸦ ����.
    //	    2. 0�̶�� unkown ũ�⸦ ����.
    //	    3. Ž�� ������ answer�� [0] = correct + unkown, [1] = correct �ϸ� ��. // �ְ� ����, ���� ������ ��ȯ�ؾ� �ϹǷ�.
    vector<int> answer(2);
    int correct = 0, unkown = 0;
    for (const auto& n : lottos)
    {
        if (n != 0)
        {
            if (find(win_nums.begin(), win_nums.end(), n) != win_nums.end())
                correct += 1;
        }
        else
            unkown += 1;
    }
    answer[0] = correct + unkown; answer[1] = correct;

    //    2. �ζ� ������ ��ȯ
    //	        1. �ζ� ������ ��ȯ�� min(7 - n, 6); ���� �����ϰ� ���� �� ����.
    for (int i = 0; i < answer.size(); ++i)
    {
        answer[i] = min(7 - answer[i], 6);
    }

    return answer;
}