#pragma once

/*
    
    1. 행렬을 만든다. (안만들어도 풀 수 있는 방법이 있는 것 같지만.. 시간을 아끼자.)
    2. 회전을 적용한 후, 가장 작은 값을 벡터에 추가한다.
    
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
    // 1. 행렬을 만든다.
    vector<vector<int>> mat = vector<vector<int>>(rows, vector<int>(columns, 0));
    int start = 1;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
        {
            mat[i][j] = start;
            start++;
        }

    // 2. 회전을 적용한 후, 가장 작은 값을 벡터에 추가한다.
    vector<int> vector;
    // querie는 x1, y1, x2, y2의 값을 가진다. 놀랍게도 -1 해줘야 한다.
    for (int i = 0; i < queries.size(); ++i)
    {
        int x_s = queries[i][0] - 1, y_s = queries[i][1] - 1,
            x_e = queries[i][2] - 1, y_e = queries[i][3] - 1;

        //
        int before_num = 0, now_num = mat[x_s][y_s];
        int min = now_num;

        int x_b = 0, y_b = 0, x_n = x_s, y_n = y_s;
        // 우측으로 이동
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
        // 아래로 이동
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
        // 좌측 이동
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
        // 위로 이동
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