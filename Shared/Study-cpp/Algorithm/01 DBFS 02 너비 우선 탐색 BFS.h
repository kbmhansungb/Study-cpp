#pragma once

/*

	BFS 너비 우선 탐색
	현재 정점에 연결된 가까운 점들부터 탐색
	큐를 이용해서 구현

*/

namespace
{
#include <queue>
	struct State
	{

	};
	void bfs()
	{
		// 선입 후출의 구조..
		std::queue<State> queue;
		while (queue.empty())
		{
			// 
			State s = queue.front(); queue.pop();
			// 종료 조건
			if (true)
			{

			}
			// 반환 조건
			else
			{

			}
		}
	}

#include <algorithm>
	void priority_bfs()
	{
		// 우선순위 규를 이용해 구현
		// 자료형,
		// 컨테이너타입,
		// true면 뒤로 오는 조건,
		std::priority_queue<int, std::vector<int>, std::greater<int>> priority_queue;
		while (priority_queue.empty())
		{
			// 
			int s = priority_queue.top(); priority_queue.pop();
			// 종료 조건
			if (true)
			{

			}
			// 반환 조건
			else
			{

			}
		}

		// 참고로 낮은 우선순위들이 먼저 만들어진다면,
		// multiset보다 저렴하다.
	}
}