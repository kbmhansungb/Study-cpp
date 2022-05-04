#pragma once

/*

	의사 코드.
	
	3진법으로 값을 구하면서.
	list에 대응 되는 char를 추가( 진수 변환은 뒤의 자리수 부터 생성하므로 앞에다 입력 )

	string을 이터레이터를 이용하여 생성

	오... 그래서 Level 2인가. 안되네.
	바로 집어넣으면 괸히 시간만 잡아먹고 오래걸린다.

*/

#include <string>
#include <list>

using namespace std;

string solution(int n)
{
	list<int> nums;
	do
	{
		n -= 1; // 1->0으로 맵핑
		nums.push_front(n % 3);
		n /= 3;
	} while (n != 0);

	char pair[] = "124";
	string answer(nums.size(), '1');
	int index = 0;
	for (auto it = nums.begin(); it != nums.end(); ++it)
	{
		answer[index] = pair[*it];

		index++;
	}

	return answer;
}

void solve()
{
	for (int i = 1; i < 10; ++i)
	{
		auto s = solution(i);
		int a = 0;
	}
}