#pragma once
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*

    2021 11 29
    11:30 Ǯ�� ����    
    11:52 �˰��� �ϼ� ����� ����
    11:57 ���԰� Ǫ��, ������ �������� �ǰ�.. �˰��� �߸�«.

*/
struct Course
{
    string order;
    int count;

    // ���� �Է� ������..
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
    // �ڽ� ����
    vector<Course> courses(orders.size());
    for (int i = 0; i < orders.size(); ++i)
    {
        courses[i].order = orders[i];
        courses[i].count = 0;
    }
    // �ڽ� �ֹ� Ƚ�� ����
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
    // ���ǿ� �������� ������ ����
    courses.erase(remove_if(courses.begin(), courses.end(), [&course](Course& c)
        {
            if (find(course.begin(), course.end(), c.count) != course.end())
                return false;
            else
                return true;
        }
    ), courses.end());

    // ������ ��ȯ
    vector<string> answer(courses.size());
    for (int i = 0; i < courses.size(); ++i)
        answer[i] = courses[i].order;
    sort(answer.begin(), answer.end());
    return answer;
}