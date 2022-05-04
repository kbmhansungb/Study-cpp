#pragma once

#include <vector>

using namespace std;

/*
���� ���� �׸��� ���̵� ������ �÷����Ͽ� �ְ� �;��� ����ġ�� 
������ ������ ��ĥ�ϱⰡ ��ٷο� ��������ٴ� ����� �߰��ϰ� 
�׸��� ���̵��� ������ ���� �����Ͽ���. 
(�����̶� �����¿�� ����� ���� ������ ������ �ǹ��Ѵ�.)

�׸��� �� ���� ������ �ִ����� ���� ū ������ ���̴� ������ ����ϴ� ���α׷��� �ۼ��غ���.
*/

/*
	�÷����� ������,
	�÷��� ������ ����Լ��� ��ĥ.
	������ ��ϵǾ� ������ �˻翡�� ����.
*/
struct ColorBookSection
{
	vector<vector<int>> picture; // �����ؾ� �Ǵ°� ������ �ȵ��� ������,,,

	int m;
	int n;

	int section_nums;
	vector<int> section_size;
	vector<vector<int>> section_data;

	ColorBookSection(int m, int n, vector<vector<int>>& picture) :
		picture(picture), m(m), n(n)
	{
		section_nums = 0;
		section_data = vector<vector<int>>(m, vector<int>(n, 0));
		// ���� �����Ͱ� 0�̸� ���� ���� �ǹ��Ѵ�.
	}

	void find_section(int x, int y, int type, int now_section = 0)
	{
		if (
			(0 <= x && x < m) == false ||	// ���� ���� �ִ��� �˻�.
			(0 <= y && y < n) == false ||
			picture[x][y] != type ||
			type == 0 ||
			section_data[x][y] != 0
			)
		{
			// 0�� �ƴ϶�� �̹� ��ϵ� ����, �˻��ϸ� �ȵ�.
			// ��...
		}
		else
		{
			// ��ĥ�ϴ� ���� �̶��
			{
				// ���� ������ 0�̶��
				if (now_section == 0)
				{
					section_nums += 1;
					section_size.resize(section_nums);
					now_section = section_nums;
				}
				// ������ ����ϰ�, ���� ����� �����ϰ� ����.
				section_data[x][y] = now_section;
				section_size[now_section - 1]++;
			}

			find_section(x + 1, y, type, now_section);
			find_section(x - 1, y, type, now_section);
			find_section(x, y + 1, type, now_section);
			find_section(x, y - 1, type, now_section);
		}
	}
};
#include <algorithm>

void solution() 
{
	vector<vector<int>> picture =
	{
		{1, 1, 1, 0},
		{1, 2, 2, 0},
		{1, 0, 0, 1},
		{0, 0, 0, 1},
		{0, 0, 0, 3},
		{0, 0, 0, 3},
	};
	ColorBookSection test(6, 4, picture);
	for(int i = 0; i < 6; ++i)
		for (int j = 0; j < 4; ++j)
		{
			test.find_section(i, j, picture[i][j]);
		}
	int number_of_area = test.section_size.size();
	int max_size_of_one_area = *std::max_element(test.section_size.begin(), test.section_size.end());

}