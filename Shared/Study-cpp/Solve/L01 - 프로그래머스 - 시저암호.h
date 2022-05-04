#pragma once

/*
https://programmers.co.kr/learn/courses/30/lessons/12926

s라는 문자열을, n의 크기마늠 밀어라,
다만, 공백은 밀어도 공백,
소문자는 z 에서 넘어가도 소문자.
대문자도 마찬가지 인가?
https://www.google.com/search?q=%EC%8B%9C%EC%A0%80%EC%95%94%ED%98%B8&oq=%EC%8B%9C%EC%A0%80%EC%95%94%ED%98%B8&aqs=chrome..69i57j0i512l9.2002j0j7&sourceid=chrome&ie=UTF-8
그런거 같네,

11:15 ?? 테스트 케이스에서 막힘. 왜지?
11:37 n이 1이상 25이하인 자연수라면서,, 거지같네,, 문제가 잘못되긴 했지만. 제한조건이 틀린 경우도 있다는것을 기억하자.

*/

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string solution(string s, int n) {
    for (size_t i = 0; i < s.size(); ++i)
    {
        if ('Z' >= s[i] && s[i] >= 'A')
        {
            s[i] += n;
            if (s[i] > 'Z')
                s[i] -= 26;
        }
        else if ('z' >= s[i] && s[i] >= 'a')
        {
            s[i] += n;
            if (s[i] > 'z')
                s[i] -= 26;
        }
        else
        {
        }
    }
    s.erase(remove_if(s.begin(), s.end(), [](char ch)
        {
            if (isupper(ch) || islower(ch) || ch == ' ')
                return false;
            else
                return true;
        }), s.end());
    return s;
}