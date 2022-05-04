#pragma once

#include <vector>

using namespace std;

/*
여러 장의 그림을 난이도 순으로 컬러링북에 넣고 싶었던 어피치는 
영역이 많으면 색칠하기가 까다로워 어려워진다는 사실을 발견하고 
그림의 난이도를 영역의 수로 정의하였다. 
(영역이란 상하좌우로 연결된 같은 색상의 공간을 의미한다.)

그림에 몇 개의 영역이 있는지와 가장 큰 영역의 넓이는 얼마인지 계산하는 프로그램을 작성해보자.
*/

/*
	컬러링북 데이터,
	컬러링 영역은 재귀함수로 색칠.
	영역이 등록되어 있으면 검사에서 제외.
*/
struct ColorBookSection
{
	vector<vector<int>> picture; // 복사해야 되는게 마음에 안들기는 하지만,,,

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
		// 섹션 데이터가 0이면 없는 것을 의미한다.
	}

	void find_section(int x, int y, int type, int now_section = 0)
	{
		if (
			(0 <= x && x < m) == false ||	// 범위 내에 있는지 검사.
			(0 <= y && y < n) == false ||
			picture[x][y] != type ||
			type == 0 ||
			section_data[x][y] != 0
			)
		{
			// 0이 아니라면 이미 등록된 섹션, 검사하면 안됨.
			// 흠...
		}
		else
		{
			// 색칠하는 공간 이라면
			{
				// 현재 섹션이 0이라면
				if (now_section == 0)
				{
					section_nums += 1;
					section_size.resize(section_nums);
					now_section = section_nums;
				}
				// 섹션을 등록하고, 섹션 사이즈를 증가하고 종료.
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