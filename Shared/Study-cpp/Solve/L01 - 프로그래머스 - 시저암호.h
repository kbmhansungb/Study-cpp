#pragma once

/*
https://programmers.co.kr/learn/courses/30/lessons/12926

s��� ���ڿ���, n�� ũ�⸶�� �о��,
�ٸ�, ������ �о ����,
�ҹ��ڴ� z ���� �Ѿ�� �ҹ���.
�빮�ڵ� �������� �ΰ�?
https://www.google.com/search?q=%EC%8B%9C%EC%A0%80%EC%95%94%ED%98%B8&oq=%EC%8B%9C%EC%A0%80%EC%95%94%ED%98%B8&aqs=chrome..69i57j0i512l9.2002j0j7&sourceid=chrome&ie=UTF-8
�׷��� ����,

11:15 ?? �׽�Ʈ ���̽����� ����. ����?
11:37 n�� 1�̻� 25������ �ڿ�����鼭,, ��������,, ������ �߸��Ǳ� ������. ���������� Ʋ�� ��쵵 �ִٴ°��� �������.

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