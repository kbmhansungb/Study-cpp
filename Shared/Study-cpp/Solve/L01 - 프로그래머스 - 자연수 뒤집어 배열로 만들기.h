#pragma once

/*
https://programmers.co.kr/learn/courses/30/lessons/12932?language=cpp

내가 작성한 아래 코드보다, 위의 코드가 훨씬 빠르다,,

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
    // 10진수를 숫자로 만들면 뒤집어서 나오닌까,, to string, 정렬 두번 반복하면,, 위의 계산을 하고 다시 변환하고, 이를 다시 푸는 과정을 반복하게 되닌까.
    // 그냥 변환만 하는 것이 더 빠르구나,,
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