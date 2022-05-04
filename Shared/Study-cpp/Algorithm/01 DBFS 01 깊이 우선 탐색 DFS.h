#pragma once

/*

	2021 11 25
	dfs의 일반 구조

*/

/// <summary>
/// + 기본형 예시
/// </summary>
struct dfs
{
	// 1.
	// DFS가 작동하면서 주기적으로 검사해야될
	// 변수를 정의하므로써 this의 생Ptr하나로
	// 스택의 생성비용을 줄일수 있음.
	// (전역 공간을 오염시키지 않으면서)
#pragma region Input
	int N[5] = { 0, 1, 2, 3, 4 };
#pragma endregion

	// 2.
	// 반환할 자료형을 여기다 구현할 수도 있음.
#pragma region Output
	int last_index = 0;
	int Ns[5 * 5][2] = { 0, 0, };
#pragma endregion

	// 3.
	// 생성자의 파라메터를 이용하여
	// Input의 필드를 완성시킴.
	// 또는 바로 dfs의 스택을 만들어 Output
	// 변수를 초기화 할 수 있음.
	dfs()
	{
		call(State());
	}

	// 4.
	// dfs의 각 분기지점에서 행동을 결정하기 위한
	// 변수의 들을 담아서 전달
	// 분기의 현재상태를 담는 것이 직관적임.
	struct State
	{
		int now_index;
		bool visit[5];
		int num[2];

		// 5. 
		// 초기 상태(시작상태)를 만드는 생성자.
		State() :
			now_index(0)
		{
			for (int i = 0; i < 5; ++i)
				visit[i] = false;
			for (int i = 0; i < 2; ++i)
				num[0] = 0;
		}

		// 6.
		// 다음 상태를 만드는 생성자.
		State(const State& s, int select_what) :
			now_index(s.now_index + 1)
		{
			for (int i = 0; i < 5; ++i)
				visit[i] = s.visit[i];
			visit[select_what] = true;
			for (int i = 0; i < 2; ++i)
			{
				num[i] = s.num[i];
			}
			num[now_index] = select_what;
		}
	};

	// 7.
	// DFS를 만드는 메서드. 이로서 DFS가 생성된다.
	void call(State s)
	{
		// 8.
		// 종료 조건.
		// 여기서 DFS의 끝이 결정된다.
		if (s.now_index < 2)
		{
			Ns[last_index][0] = s.num[0];
			Ns[last_index][1] = s.num[1];
			last_index++;
		}

		// 9. 
		// 분화 조건.
		// 여기서 다음번 DFS로 넘어가게 된다.
		// 분화시 조건에 따라 중단할지 분화할지 결정하면
		// 보다 효율적으로 계산할 수 있다.
		else
		{
			for (int i = 0; i < 5; ++i)
				call(State(s, i));
		}
	}
};


/*

	DFS (깊이 우선 탐색)
	현재 정점에서 갈 수 있는 점들까지 들어가면서 탐색
	1. 스택으로 구현
	2. 재귀함수로 구현

*/

namespace
{
	// 재귀적 호출을 통해 작동함
	void dfs()
	{
		// 종료 조건
		if (true)
		{

		}
		// 분화 조건
		else
		{
			dfs();
		}
	}

#include <stack>
	struct State
	{

	};
	void dfs_stack()
	{
		std::stack<State> stack;

		while (stack.empty())
		{
			// 스택을 가져옴
			// State를 만들고 싶지 않으면 top()을 이용하면 됨.
			State s = stack.top(); stack.pop();
			// 종료 조건
			if (true)
			{

			}
			// 분화 조건
			else
			{

			}
		}
	}
}