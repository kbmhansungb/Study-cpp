#pragma once

/*

	BFS �ʺ� �켱 Ž��
	���� ������ ����� ����� ������� Ž��
	ť�� �̿��ؼ� ����

*/

namespace
{
#include <queue>
	struct State
	{

	};
	void bfs()
	{
		// ���� ������ ����..
		std::queue<State> queue;
		while (queue.empty())
		{
			// 
			State s = queue.front(); queue.pop();
			// ���� ����
			if (true)
			{

			}
			// ��ȯ ����
			else
			{

			}
		}
	}

#include <algorithm>
	void priority_bfs()
	{
		// �켱���� �Ը� �̿��� ����
		// �ڷ���,
		// �����̳�Ÿ��,
		// true�� �ڷ� ���� ����,
		std::priority_queue<int, std::vector<int>, std::greater<int>> priority_queue;
		while (priority_queue.empty())
		{
			// 
			int s = priority_queue.top(); priority_queue.pop();
			// ���� ����
			if (true)
			{

			}
			// ��ȯ ����
			else
			{

			}
		}

		// ����� ���� �켱�������� ���� ��������ٸ�,
		// multiset���� �����ϴ�.
	}
}