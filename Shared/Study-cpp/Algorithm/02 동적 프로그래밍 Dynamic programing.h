#pragma once

/*
	Dynamic programming

	1) Recursion (재귀 호출)
	int dfs(int nowh, int noww) { ...

	2) 메모화 재귀
	int[][] dp = new int[h+1][w+1];
	int dfs(...
	라는데 글로벌 영역에 변수가 생성되는 것을 용납할 수 없으므로
	class dfs {
		int [h+1][w+1]dp;
		int dfs(...
	식으로 맴버함수로 메모리 접근하는 구조로 짜자.

	3) Bottom-up
	메모화 DFS는 위에서 아래로 내려가는 하향식 방법.
	아래에서 위로 올라가는 상향식 방법을 사용하면 재귀를 사용하지 않아도 문제풀이가 가능함.
	for(int i = 0; i < h; i++)
		for(int j = 0; j < w; j++)
		...

*/

/*
	Knapsack

	무게와 가치라는 2개의 매개변수가 있는 서로 다른 물건이 여러개가 있다.
	일정한 무게를 넘지 않는 선에서 배낭에 물건을 선택해서 넣을 때
	가치의 합계가 최대가 되려면 어떤 물건을 넣어야 하는가?
*/
#include <vector>

// dfs로 풀기
// - Terminal Condition: 재귀를 멈춰야 하는 조건 (최대 무게 초과, 다음에 볼 물건 없음) 
// - 이 물건을 가방에 넣지 않는 경우와 가방에 넣는 경우로 쪼개어 DFS
// select의 사이즈는 n으로 넘어가야함.
//
// dfs(0, 0)을 입력하면
// 예시는 어떻게든 돌아가는 코드같은데,, 유지보수가 어렵다고 느껴진다.
// 개선히지
//
//int dfs(int n, int w)
//{
//	if (w > maxw) return -value[n - 1];
//	if (n >= weight.size()) return 0;
//	return std::max(dfs(n + 1, w), dfs(n + 1, w + weight[n]) + value[n]);
//}

// dfs를 짤때는 복합하지 않게 분화되는 조건과 선택되는 조건으로 작성하고,
// 제대로 작동하기 위해서 선택되는 조건을 앞에, 분화 되는 조건을 뒤에,(뭔소리인가?)
struct make_selection
{
	std::vector<int> weight = { 3, 5, 1, 2, 3 };
	std::vector<int> value = { 2, 3, 2, 3, 6 };
	int maxw = 10;

	struct State
	{
		std::vector<bool> selection;
		int now_weight;
		int now_value;

		// 초기상태 만들기
		State(int size) : selection(size), now_weight(0), now_value(0) {};
		// 선택되었을 때 추가하는 방식
		State(const State& base, int select_index, int add_w, int add_v) :
			selection(base.selection),
			now_weight(base.now_weight),
			now_value(base.now_value)
		{
			selection[select_index] = true;
			now_weight += add_w;
			now_value += add_v;
		}
	};

	State result_capture;
	void dfs(State state, int now_index)
	{
		// 선택 조건
		if (
			now_index >= weight.size() // 더이상 선택할 게 없다면, 종료하는것이 마땅하다.
			&& state.now_weight == maxw // 현재 무게와 최대 무게가 같다면, 더이상 추가할 수 있는 것이 없다.
			)
		{
			if (result_capture.now_value < state.now_value)
				result_capture = state;
		}
		// 분화 조건
		else
		{
			// 현재 인덱스를 집어 넣지 않는다.
			dfs(state, now_index + 1);
			// 현재 인덱스를 집어 넣는다.
			// 무게가 찾다면 집어 넣지 못한다.
			if (state.now_weight + weight[now_index] <= maxw)
				dfs(State(state, now_index, weight[now_index], value[now_index]),
					now_index + 1
				);
		}
	}

	// now_weight와 now_value를 스트럭트 형태로 만들 수 있다.
	int result_capture_i = 0;
	void dfs_only_value(int now_weight, int now_value, int now_index)
	{
		// 선택 조건
		if (now_index >= weight.size()
			&& now_weight == maxw
			)
		{
			if (result_capture_i < now_value) result_capture_i = now_value;
		}
		// 분화 조건
		else
		{
			dfs_only_value(now_weight, now_value, now_index + 1);
			if (now_weight + weight[now_index] <= maxw)
				dfs_only_value(now_weight + weight[now_index], now_value + value[now_index], now_index + 1);
		}
	}
};
void solution()
{

}