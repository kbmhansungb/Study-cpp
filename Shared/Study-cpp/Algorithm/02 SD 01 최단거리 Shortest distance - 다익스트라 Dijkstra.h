#pragma once

/*
https://programmers.co.kr/learn/courses/30/lessons/72413
�ս� �ý� ��� ����.
*/

#include <limits>
#include <string>
#include <vector>
#include <queue>
using namespace std;

struct DijstraSolve
{
    int num_of_node;
    vector<vector<int>> far_matrix;

    // �߸��� fars�� ������ �ʴ´ٴ� �����Ͽ�,
    DijstraSolve(int num_of_node, const vector<vector<int>>& fars) :
        num_of_node(num_of_node),
        far_matrix(num_of_node, vector<int>(num_of_node, numeric_limits<int>::max() ))
    {

        for(int i = 0; i < fars.size(); ++i)
        {
            far_matrix[fars[i][0]][fars[i][1]] = fars[i][2];
            far_matrix[fars[i][1]][fars[i][0]] = fars[i][2];
        }
    }

    using Distance_and_index = pair<int, int>;
    using Dijkstra_Que = priority_queue<Distance_and_index>;

    inline void make_distance_and_index(Dijkstra_Que& que, const int& distance, const int& index)
    {
        que.push(std::make_pair(distance, index));
    }
    inline const int& get_distance(const Distance_and_index& pair)
    {
        return pair.first;
    }
    inline const int& get_index(const Distance_and_index& pair)
    {
        return pair.second;
    }

    auto get_dijstra_field(int start)
    {
        vector<int> field = vector<int>(num_of_node, numeric_limits<int>::max());
        Dijkstra_Que que;

        // �������� ���
        make_distance_and_index(que, 0, start);

        // distance�� ª�� ������� ó��
        int distance, index, new_distance;
        while (que.empty() != true) // ť�� �ִ��� ���
        {
            distance = get_distance(que.top());
            index = get_index(que.top());
            que.pop();

            if (distance < field[index])
            {
                field[index] = distance;
            }
            else
                continue;

            // ��� ������
            for (int new_index = 0; new_index < num_of_node; ++new_index)
            {
                if (new_index != index &&                                       // �ڱ��ڽ����δ� ���� �� ����
                    far_matrix[index][new_index] != numeric_limits<int>::max()  // ����Ǿ� �־�� ���� �� �ִ�.
                    )
                {
                    new_distance = distance + far_matrix[index][new_index];
                }
                else
                    continue;

                if (new_distance < field[new_index]) // ���ο� ���Ͻ��� ª�� ������ �ǹ̰� �ִ�.
                {
                    make_distance_and_index(que, new_distance, new_index);
                }
            }
            //
        }

        return field;
    }
};

int solution() 
{
    // �ս� ����� ����� a -> b�� ���� b->a�� ��� �ΰ����� ������ ����.

    vector<vector<int>> far
        =
    {
        { 4, 1, 10 },
        { 3, 5, 24 },
        { 5, 6, 2 },
        { 3, 1, 41 },
        { 5, 1, 24 },
        { 4, 6, 50 },
        { 2, 4, 66 },
        { 2, 3, 22 },
        { 1, 6, 25 },
    };
    for (auto& vec : far)
    {
        vec[0] -= 1;
        vec[1] -= 1;
    }
    DijstraSolve dijstra(6, far);

    auto field = dijstra.get_dijstra_field(0);

    int answer = 0;
    return answer;
}