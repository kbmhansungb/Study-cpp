#pragma once

/*

	2021 11 25
	dfs�� �Ϲ� ����

*/

/// <summary>
/// + �⺻�� ����
/// </summary>
struct dfs
{
	// 1.
	// DFS�� �۵��ϸ鼭 �ֱ������� �˻��ؾߵ�
	// ������ �����ϹǷν� this�� ��Ptr�ϳ���
	// ������ ��������� ���ϼ� ����.
	// (���� ������ ������Ű�� �����鼭)
#pragma region Input
	int N[5] = { 0, 1, 2, 3, 4 };
#pragma endregion

	// 2.
	// ��ȯ�� �ڷ����� ����� ������ ���� ����.
#pragma region Output
	int last_index = 0;
	int Ns[5 * 5][2] = { 0, 0, };
#pragma endregion

	// 3.
	// �������� �Ķ���͸� �̿��Ͽ�
	// Input�� �ʵ带 �ϼ���Ŵ.
	// �Ǵ� �ٷ� dfs�� ������ ����� Output
	// ������ �ʱ�ȭ �� �� ����.
	dfs()
	{
		call(State());
	}

	// 4.
	// dfs�� �� �б��������� �ൿ�� �����ϱ� ����
	// ������ ���� ��Ƽ� ����
	// �б��� ������¸� ��� ���� ��������.
	struct State
	{
		int now_index;
		bool visit[5];
		int num[2];

		// 5. 
		// �ʱ� ����(���ۻ���)�� ����� ������.
		State() :
			now_index(0)
		{
			for (int i = 0; i < 5; ++i)
				visit[i] = false;
			for (int i = 0; i < 2; ++i)
				num[0] = 0;
		}

		// 6.
		// ���� ���¸� ����� ������.
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
	// DFS�� ����� �޼���. �̷μ� DFS�� �����ȴ�.
	void call(State s)
	{
		// 8.
		// ���� ����.
		// ���⼭ DFS�� ���� �����ȴ�.
		if (s.now_index < 2)
		{
			Ns[last_index][0] = s.num[0];
			Ns[last_index][1] = s.num[1];
			last_index++;
		}

		// 9. 
		// ��ȭ ����.
		// ���⼭ ������ DFS�� �Ѿ�� �ȴ�.
		// ��ȭ�� ���ǿ� ���� �ߴ����� ��ȭ���� �����ϸ�
		// ���� ȿ�������� ����� �� �ִ�.
		else
		{
			for (int i = 0; i < 5; ++i)
				call(State(s, i));
		}
	}
};


/*

	DFS (���� �켱 Ž��)
	���� �������� �� �� �ִ� ������� ���鼭 Ž��
	1. �������� ����
	2. ����Լ��� ����

*/

namespace
{
	// ����� ȣ���� ���� �۵���
	void dfs()
	{
		// ���� ����
		if (true)
		{

		}
		// ��ȭ ����
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
			// ������ ������
			// State�� ����� ���� ������ top()�� �̿��ϸ� ��.
			State s = stack.top(); stack.pop();
			// ���� ����
			if (true)
			{

			}
			// ��ȭ ����
			else
			{

			}
		}
	}
}