#pragma once

/*

https://programmers.co.kr/learn/courses/30/lessons/77484

11:10 시작
11:31 종료

1. { 맞은 수, 맞은 수 + 0의 갯수 }를 구함.
	// 로또의 갯수가 적으므로, 별도의 정렬은 필요하지 않아 보임.
	1. lottos를 읽으면서 0이 아닐 경우 win_nums에 값이 있는지 확인. 있다면 correct 크기를 증가.
	2. 0이라면 unkown 크기를 증가.
	3. 탐색 종료후 answer에 [0] = correct, [1] = correct + unkown 하면 돔.
2. 로또 순위로 변환
	1. 로또 순위로 변환은 min(7 - n, 6); 으로 간단하게 구할 수 있음.

문제를 읽고 이해하는데 시간이 많이 걸린다. 이 부분은 어떻게 해결 할 수 있는가?
문제를 많이 풀어보는 방법박에 없는거 같다.

*/

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(vector<int> lottos, vector<int> win_nums) {

    //    1. { 맞은 수, 맞은 수 + 0의 갯수 }를 구함.
    //	    // 로또의 갯수가 적으므로, 별도의 정렬은 필요하지 않아 보임.
    //	    1. lottos를 읽으면서 0이 아닐 경우 win_nums에 값이 있는지 확인. 있다면 correct 크기를 증가.
    //	    2. 0이라면 unkown 크기를 증가.
    //	    3. 탐색 종료후 answer에 [0] = correct + unkown, [1] = correct 하면 됨. // 최고 순위, 최저 순위를 반환해야 하므로.
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

    //    2. 로또 순위로 변환
    //	        1. 로또 순위로 변환은 min(7 - n, 6); 으로 간단하게 구할 수 있음.
    for (int i = 0; i < answer.size(); ++i)
    {
        answer[i] = min(7 - answer[i], 6);
    }

    return answer;
}