#pragma once

/*

아이디의 규칙, 3자 이상 15자 이하.
아이디는 알파벳 소문자, 숫자 빼기(-), 및 줄(_), 마침표(.)만 사용가능
마침표(.)는 처음과 끝에 사용할 수 없음.

1단계 new_id의 모든 대문자를 대응되는 소문자로 치환합니다.
2단계 new_id에서 알파벳 소문자, 숫자, 빼기(-), 밑줄(_), 마침표(.)를 제외한 모든 문자를 제거합니다.
3단계 new_id에서 마침표(.)가 2번 이상 연속된 부분을 하나의 마침표(.)로 치환합니다.
4단계 new_id에서 마침표(.)가 처음이나 끝에 위치한다면 제거합니다.
5단계 new_id가 빈 문자열이라면, new_id에 "a"를 대입합니다.
6단계 new_id의 길이가 16자 이상이면, new_id의 첫 15개의 문자를 제외한 나머지 문자들을 모두 제거합니다.
	 만약 제거 후 마침표(.)가 new_id의 끝에 위치한다면 끝에 위치한 마침표(.) 문자를 제거합니다.
7단계 new_id의 길이가 2자 이하라면, new_id의 마지막 문자를 new_id의 길이가 3이 될 때까지 반복해서 끝에 붙입니다.

4:40 시작
5:02 그냥 시키는 데로 작성했으면 되는 문제...

*/

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string solution(string new_id) {
    // 1단계
    for (int i = 0; i < new_id.size(); ++i)
        if (isupper(new_id[i]))
            new_id[i] = tolower(new_id[i]);

    // 2단계
    new_id.erase(remove_if(new_id.begin(), new_id.end(), [](char ch) -> bool 
        {
            if (islower(ch) ||
                isdigit(ch) ||
                ch == '-' ||
                ch == '_' ||
                ch == '.'
                )
            {
                return false;
            }
            else
            {
                return true;
            }
        }),
        new_id.end());

    // 3단계
    char before_ch = 0;
    new_id.erase(remove_if(new_id.begin(), new_id.end(), [&before_ch](char ch) -> bool
        {
            bool remove_result = false;
            if (before_ch == '.' && ch == '.')
                remove_result = true;

            before_ch = ch;
            return remove_result;
        }),
        new_id.end());

    // 4단계
    // 음.. 최적화할 요소가 남아있는거 같기는 하지만..
    if (new_id.size() > 0)
    {
        if (new_id[0] == '.')
            new_id.erase(new_id.begin());
    }
    if (new_id.size() > 0)
    {
        if (new_id[new_id.size() - 1] == '.')
            new_id.erase(--new_id.end());
    }

    // 5단계
    if (new_id.size() == 0)
        new_id = "a";

    // 6단계
    if (new_id.size() > 15)
        new_id.resize(15);
    if (new_id[new_id.size() - 1] == '.')
        new_id.erase(--new_id.end());

    // 7단계
    if (new_id.size() < 3)                      // 만일 크기가 2 라면
    {
        new_id.resize(3, new_id[new_id.size() - 1]);                       
    }
    return new_id;
}