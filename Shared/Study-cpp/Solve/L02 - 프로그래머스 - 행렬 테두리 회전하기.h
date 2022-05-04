#pragma once

/*
    
    1. ����� �����. (�ȸ��� Ǯ �� �ִ� ����� �ִ� �� ������.. �ð��� �Ƴ���.)
    2. ȸ���� ������ ��, ���� ���� ���� ���Ϳ� �߰��Ѵ�.
    
*/

#include <iostream>
void print(int x, int y)
{
    std::cout << "( " << x << ", " << y << " )" << std::endl;
}

#include <string>
#include <vector>
using namespace std;

vector<int> solution(int rows, int columns, vector<vector<int>> queries) 
{
    // 1. ����� �����.
    vector<vector<int>> mat = vector<vector<int>>(rows, vector<int>(columns, 0));
    int start = 1;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
        {
            mat[i][j] = start;
            start++;
        }

    // 2. ȸ���� ������ ��, ���� ���� ���� ���Ϳ� �߰��Ѵ�.
    vector<int> vector;
    // querie�� x1, y1, x2, y2�� ���� ������. ����Ե� -1 ����� �Ѵ�.
    for (int i = 0; i < queries.size(); ++i)
    {
        int x_s = queries[i][0] - 1, y_s = queries[i][1] - 1,
            x_e = queries[i][2] - 1, y_e = queries[i][3] - 1;

        //
        int before_num = 0, now_num = mat[x_s][y_s];
        int min = now_num;

        int x_b = 0, y_b = 0, x_n = x_s, y_n = y_s;
        // �������� �̵�
        for (int j = y_s + 1; j <= y_e; ++j)
        {
            x_b = x_n;
            y_b = y_n;
            x_n = x_s;
            y_n = j;

            before_num = now_num;
            now_num = mat[x_n][y_n];

            mat[x_n][y_n] = before_num;
            min = std::min(min, before_num);
        }
        // �Ʒ��� �̵�
        for (int j = x_s + 1; j <= x_e; ++j)
        {
            x_b = x_n;
            y_b = y_n;
            x_n = j;
            y_n = y_e;

            before_num = now_num;
            now_num = mat[x_n][y_n];

            mat[x_n][y_n] = before_num;
            min = std::min(min, before_num);
        }
        // ���� �̵�
        for (int j = y_e - 1; j >= y_s; --j)
        {
            x_b = x_n;
            y_b = y_n;
            x_n = x_e;
            y_n = j;

            before_num = now_num;
            now_num = mat[x_n][y_n];

            mat[x_n][y_n] = before_num;
            min = std::min(min, before_num);
        }
        // ���� �̵�
        for (int j = x_e - 1; j >= x_s; --j)
        {
            x_b = x_n;
            y_b = y_n;
            x_n = j;
            y_n = y_s;

            before_num = now_num;
            now_num = mat[x_n][y_n];

            mat[x_n][y_n] = before_num;
            min = std::min(min, before_num);

        }
        vector.push_back(min);
    }

    return vector;
}

void solve()
{
    auto v = solution(6, 6,
        {
            {2, 2, 5, 4},
            {3, 3, 6, 6},
            {5, 1, 6, 3},
        });
    int a = 0;
}