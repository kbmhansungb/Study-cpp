#pragma once

/*
https://programmers.co.kr/learn/courses/30/lessons/12932?language=cpp

���� �ۼ��� �Ʒ� �ڵ庸��, ���� �ڵ尡 �ξ� ������,,

*/

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(long long n) {
    vector<int> answer;
    while (n) {
        answer.push_back(n % 10);
        n /= 10;
    }
    return answer;
    // 10������ ���ڷ� ����� ����� �����ѱ�,, to string, ���� �ι� �ݺ��ϸ�,, ���� ����� �ϰ� �ٽ� ��ȯ�ϰ�, �̸� �ٽ� Ǫ�� ������ �ݺ��ϰ� �Ǵѱ�.
    // �׳� ��ȯ�� �ϴ� ���� �� ��������,,
}

//#include <string>
//#include <vector>
//#include <algorithm>
//using namespace std;
//
//vector<int> solution(long long n) {
//    string s = to_string(n);
//    vector<int> answer(s.size());
//    transform(s.begin(), s.end(), answer.rbegin(), [](char ch) -> int { return ch - '0'; });
//    return answer;
//}