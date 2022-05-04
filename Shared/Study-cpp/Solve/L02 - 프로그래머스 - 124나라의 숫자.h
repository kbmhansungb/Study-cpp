#pragma once

/*

	�ǻ� �ڵ�.
	
	3�������� ���� ���ϸ鼭.
	list�� ���� �Ǵ� char�� �߰�( ���� ��ȯ�� ���� �ڸ��� ���� �����ϹǷ� �տ��� �Է� )

	string�� ���ͷ����͸� �̿��Ͽ� ����

	��... �׷��� Level 2�ΰ�. �ȵǳ�.
	�ٷ� ��������� ���� �ð��� ��Ƹ԰� �����ɸ���.

*/

#include <string>
#include <list>

using namespace std;

string solution(int n)
{
	list<int> nums;
	do
	{
		n -= 1; // 1->0���� ����
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