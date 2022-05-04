#pragma once

// �ǻ��ڵ�
// ���� Ž������ ��� ������ ����� ���� �б⸦ �����.
// ������ ��� �б⿡�� ������ �˻��Ѵ�.
//
// +1. �����̵� ���Ҵ� { A, C, F, J, M, N, R, T }�� �ϳ��̴�.
// ������ �ִ� ����� ���� 8!

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
		int now_index; // ���� �ε����� ���� �������� ó���ؾ� �� �ε����� ����.

		State() :
			state(Characters.size(), ' '), now_index(0)
		{
		}

		// ���� ĳ���Ͱ� �ִ� �������� ����� ���ϴ�,, �Ķ���� ������ �� �����ϰ� ����.
		State(const State& before_state, int put_now_character_index) :
			state(before_state.state), now_index(before_state.now_index)
		{
			state[put_now_character_index] = Characters[now_index];
			now_index++;
		}
	};
private:
	//�߸��� �����Ͱ� �Ѿ�� �ʴ´ٴ� �����Ͽ� �ۼ��Ѵ�.
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
		// �����̱⿡ ��ĭ ������ ������ 0�� ��ȯ�ؾ� �Ѵ�. 
		return abs(a_pos - b_pos) - 1;
	}
	bool check_condition(const State& s, int i)
	{
		int condition = atoi(&data[i][4]);
		int interval = get_interval(s, data[i][0], data[i][2]);

		switch (data[i][3]) // "?~?(op)(num)�� ������ ������. �� �ڸ����� �ݵ�� ���ڸ����� �����Ѵ�.
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
		// ���� ����
		if (s.now_index >= 8)
		{
			if (check_all_condition(s))
				answer++;
		}
		// ��ȭ ����
		else
		{
			for (int i = 0; i < 8; ++i)
			{
				// ��� �ִ� ��쿡�� ���� �ܰ踦 ������.
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

// �ٸ������ Ǯ�̸� ���� 10�� �̻� �� ������...
// next permetant�� �����ΰ�?

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

// ���ڷ� ��ȯ�ؼ� Ǫ�� �͵� ��������,,,