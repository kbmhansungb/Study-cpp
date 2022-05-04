#pragma once

// 의사코드
// 완전 탐색으로 모든 가능한 경우의 수를 분기를 만든다.
// 가능한 모든 분기에서 조건을 검사한다.
//
// +1. 다행이도 원소는 { A, C, F, J, M, N, R, T }중 하나이다.
// 가능한 최대 경우의 수는 8!

#include <string>
#include <vector>
using namespace std;

static vector<char> Characters = { 'A', 'C', 'F', 'J', 'M', 'N', 'R', 'T' };
struct GroupPhoto
{
	int n;
	vector<string> data;
	
	int answer;
	GroupPhoto(const int& n, const vector<string>& data) :
		n(n), data(data), answer(0)
	{
		dfs(State());
	}

	struct State
	{
		vector<char> state;
		int now_index; // 현재 인덱스는 현재 시점에서 처리해야 될 인덱스를 말함.

		State() :
			state(Characters.size(), ' '), now_index(0)
		{
		}

		// 현재 캐릭터가 있는 상태인지 디버깅 못하니,, 파라메터 전달할 때 신중하게 하자.
		State(const State& before_state, int put_now_character_index) :
			state(before_state.state), now_index(before_state.now_index)
		{
			state[put_now_character_index] = Characters[now_index];
			now_index++;
		}
	};
private:
	//잘못된 데이터가 넘어가지 않는다는 가정하에 작성한다.
	int get_interval(const State& s, char a, char b)
	{
		int a_pos = -1, b_pos = -1;

		for (int i = 0; i < 8; ++i)
		{
			if (s.state[i] == a)
			{
				a_pos = i;
				break;
			}
		}
		for (int i = 0; i < 8; ++i)
		{
			if (s.state[i] == b)
			{
				b_pos = i;
				break;
			}
		}
		// 간격이기에 한칸 떨어져 있으면 0을 반환해야 한다. 
		return abs(a_pos - b_pos) - 1;
	}
	bool check_condition(const State& s, int i)
	{
		int condition = atoi(&data[i][4]);
		int interval = get_interval(s, data[i][0], data[i][2]);

		switch (data[i][3]) // "?~?(op)(num)의 구조를 따른다. 각 자리수는 반드시 한자리임을 보장한다.
		{
		case '<':
			return interval < condition;
			break;
		case '=':
			return interval == condition;
			break;
		case '>':
			return interval > condition;
			break;
		}
		return true;
	}
	bool check_all_condition(const State& s)
	{
		for (int i = 0; i < n; ++i)
		{
			if (check_condition(s, i) == false) return false;
		}
		return true;
	}
	void dfs(State s)
	{
		// 종료 조건
		if (s.now_index >= 8)
		{
			if (check_all_condition(s))
				answer++;
		}
		// 분화 조건
		else
		{
			for (int i = 0; i < 8; ++i)
			{
				// 비어 있는 경우에만 다음 단계를 진행함.
				if (s.state[i] == ' ')
					dfs(State(s, i));
			}
		}
	}
};

//void solve()
//{
//	int n = 2;
//	vector<string> data = { "N~F=0", "R~T>2" };
//	auto gp = GroupPhoto(n, data);
//	int answer = gp.answer;
//}

// 다른사람의 풀이를 보이 10배 이상 더 빨랐다...
// next permetant는 무엇인가?

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void solve()
{
	int n = 0;
	vector<string> data;

	int perm[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	while (next_permutation(perm, perm + 8));
}

// 숫자로 변환해서 푸는 것도 빠르구나,,,