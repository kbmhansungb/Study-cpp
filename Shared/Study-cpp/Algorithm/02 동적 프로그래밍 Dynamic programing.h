#pragma once

/*
	Dynamic programming

	1) Recursion (��� ȣ��)
	int dfs(int nowh, int noww) { ...

	2) �޸�ȭ ���
	int[][] dp = new int[h+1][w+1];
	int dfs(...
	��µ� �۷ι� ������ ������ �����Ǵ� ���� �볳�� �� �����Ƿ�
	class dfs {
		int [h+1][w+1]dp;
		int dfs(...
	������ �ɹ��Լ��� �޸� �����ϴ� ������ ¥��.

	3) Bottom-up
	�޸�ȭ DFS�� ������ �Ʒ��� �������� ����� ���.
	�Ʒ����� ���� �ö󰡴� ����� ����� ����ϸ� ��͸� ������� �ʾƵ� ����Ǯ�̰� ������.
	for(int i = 0; i < h; i++)
		for(int j = 0; j < w; j++)
		...

*/

/*
	Knapsack

	���Կ� ��ġ��� 2���� �Ű������� �ִ� ���� �ٸ� ������ �������� �ִ�.
	������ ���Ը� ���� �ʴ� ������ �賶�� ������ �����ؼ� ���� ��
	��ġ�� �հ谡 �ִ밡 �Ƿ��� � ������ �־�� �ϴ°�?
*/
#include <vector>

// dfs�� Ǯ��
// - Terminal Condition: ��͸� ����� �ϴ� ���� (�ִ� ���� �ʰ�, ������ �� ���� ����) 
// - �� ������ ���濡 ���� �ʴ� ���� ���濡 �ִ� ���� �ɰ��� DFS
// select�� ������� n���� �Ѿ����.
//
// dfs(0, 0)�� �Է��ϸ�
// ���ô� ��Ե� ���ư��� �ڵ尰����,, ���������� ��ƴٰ� ��������.
// ��������
//
//int dfs(int n, int w)
//{
//	if (w > maxw) return -value[n - 1];
//	if (n >= weight.size()) return 0;
//	return std::max(dfs(n + 1, w), dfs(n + 1, w + weight[n]) + value[n]);
//}

// dfs�� ©���� �������� �ʰ� ��ȭ�Ǵ� ���ǰ� ���õǴ� �������� �ۼ��ϰ�,
// ����� �۵��ϱ� ���ؼ� ���õǴ� ������ �տ�, ��ȭ �Ǵ� ������ �ڿ�,(���Ҹ��ΰ�?)
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

		// �ʱ���� �����
		State(int size) : selection(size), now_weight(0), now_value(0) {};
		// ���õǾ��� �� �߰��ϴ� ���
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
		// ���� ����
		if (
			now_index >= weight.size() // ���̻� ������ �� ���ٸ�, �����ϴ°��� �����ϴ�.
			&& state.now_weight == maxw // ���� ���Կ� �ִ� ���԰� ���ٸ�, ���̻� �߰��� �� �ִ� ���� ����.
			)
		{
			if (result_capture.now_value < state.now_value)
				result_capture = state;
		}
		// ��ȭ ����
		else
		{
			// ���� �ε����� ���� ���� �ʴ´�.
			dfs(state, now_index + 1);
			// ���� �ε����� ���� �ִ´�.
			// ���԰� ã�ٸ� ���� ���� ���Ѵ�.
			if (state.now_weight + weight[now_index] <= maxw)
				dfs(State(state, now_index, weight[now_index], value[now_index]),
					now_index + 1
				);
		}
	}

	// now_weight�� now_value�� ��Ʈ��Ʈ ���·� ���� �� �ִ�.
	int result_capture_i = 0;
	void dfs_only_value(int now_weight, int now_value, int now_index)
	{
		// ���� ����
		if (now_index >= weight.size()
			&& now_weight == maxw
			)
		{
			if (result_capture_i < now_value) result_capture_i = now_value;
		}
		// ��ȭ ����
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