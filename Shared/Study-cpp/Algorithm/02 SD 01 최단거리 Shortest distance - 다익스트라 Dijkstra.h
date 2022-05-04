#pragma once

/*
https://programmers.co.kr/learn/courses/30/lessons/72413
합승 택시 요금 문제.
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

    // 잘못된 fars를 보내지 않는다는 전제하에,
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

        // 시작지점 등록
        make_distance_and_index(que, 0, start);

        // distance가 짧은 순서대로 처리
        int distance, index, new_distance;
        while (que.empty() != true) // 큐가 있는한 계산
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

            // 노드 나누기
            for (int new_index = 0; new_index < num_of_node; ++new_index)
            {
                if (new_index != index &&                                       // 자기자신으로는 보낼 수 없다
                    far_matrix[index][new_index] != numeric_limits<int>::max()  // 연결되어 있어야 보낼 수 있다.
                    )
                {
                    new_distance = distance + far_matrix[index][new_index];
                }
                else
                    continue;

                if (new_distance < field[new_index]) // 새로운 디스턴스가 짧은 때에만 의미가 있다.
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
    // 합승 요금의 결과는 a -> b의 경우와 b->a의 경우 두가지로 나누어 진다.

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