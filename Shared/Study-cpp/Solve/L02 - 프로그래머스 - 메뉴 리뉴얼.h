#pragma once
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*

    2021 11 29
    11:30 풀기 시작    
    11:52 알고리즘 완성 디버그 시작
    11:57 술먹고 푸니, 문제가 안읽히는 건가.. 알고리즘 잘못짬.

*/
struct Course
{
    string order;
    int count;

    // 직접 입력 해주자..
    //Course(const string& order) :
    //    order(order), count(0)
    //{
    //}

    bool course_include_order(const std::string& order)
    {
        for (auto& ch : this->order)
        {
            if (order.find(ch) == std::string::npos) return false;
        }
        return true;
    }
    bool operator<(const Course& rhs)
    {
        return count < rhs.count;
    }
};

vector<string> solution(vector<string> orders, vector<int> course) {
    // 코스 생성
    vector<Course> courses(orders.size());
    for (int i = 0; i < orders.size(); ++i)
    {
        courses[i].order = orders[i];
        courses[i].count = 0;
    }
    // 코스 주문 횟수 생성
    for (int i = 0; i < orders.size(); ++i)
    {
        for (int j = 0; j < courses.size(); ++j)
        {
            if (courses[j].course_include_order(orders[i]))
            {
                courses[j].count += 1;
            }
        }
    }
    // 조건에 부합하지 않으면 제거
    courses.erase(remove_if(courses.begin(), courses.end(), [&course](Course& c)
        {
            if (find(course.begin(), course.end(), c.count) != course.end())
                return false;
            else
                return true;
        }
    ), courses.end());

    // 정렬후 반환
    vector<string> answer(courses.size());
    for (int i = 0; i < courses.size(); ++i)
        answer[i] = courses[i].order;
    sort(answer.begin(), answer.end());
    return answer;
}