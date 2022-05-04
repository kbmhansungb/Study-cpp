#pragma once

/*

���̵��� ��Ģ, 3�� �̻� 15�� ����.
���̵�� ���ĺ� �ҹ���, ���� ����(-), �� ��(_), ��ħǥ(.)�� ��밡��
��ħǥ(.)�� ó���� ���� ����� �� ����.

1�ܰ� new_id�� ��� �빮�ڸ� �����Ǵ� �ҹ��ڷ� ġȯ�մϴ�.
2�ܰ� new_id���� ���ĺ� �ҹ���, ����, ����(-), ����(_), ��ħǥ(.)�� ������ ��� ���ڸ� �����մϴ�.
3�ܰ� new_id���� ��ħǥ(.)�� 2�� �̻� ���ӵ� �κ��� �ϳ��� ��ħǥ(.)�� ġȯ�մϴ�.
4�ܰ� new_id���� ��ħǥ(.)�� ó���̳� ���� ��ġ�Ѵٸ� �����մϴ�.
5�ܰ� new_id�� �� ���ڿ��̶��, new_id�� "a"�� �����մϴ�.
6�ܰ� new_id�� ���̰� 16�� �̻��̸�, new_id�� ù 15���� ���ڸ� ������ ������ ���ڵ��� ��� �����մϴ�.
	 ���� ���� �� ��ħǥ(.)�� new_id�� ���� ��ġ�Ѵٸ� ���� ��ġ�� ��ħǥ(.) ���ڸ� �����մϴ�.
7�ܰ� new_id�� ���̰� 2�� ���϶��, new_id�� ������ ���ڸ� new_id�� ���̰� 3�� �� ������ �ݺ��ؼ� ���� ���Դϴ�.

4:40 ����
5:02 �׳� ��Ű�� ���� �ۼ������� �Ǵ� ����...

*/

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string solution(string new_id) {
    // 1�ܰ�
    for (int i = 0; i < new_id.size(); ++i)
        if (isupper(new_id[i]))
            new_id[i] = tolower(new_id[i]);

    // 2�ܰ�
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

    // 3�ܰ�
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

    // 4�ܰ�
    // ��.. ����ȭ�� ��Ұ� �����ִ°� ����� ������..
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

    // 5�ܰ�
    if (new_id.size() == 0)
        new_id = "a";

    // 6�ܰ�
    if (new_id.size() > 15)
        new_id.resize(15);
    if (new_id[new_id.size() - 1] == '.')
        new_id.erase(--new_id.end());

    // 7�ܰ�
    if (new_id.size() < 3)                      // ���� ũ�Ⱑ 2 ���
    {
        new_id.resize(3, new_id[new_id.size() - 1]);                       
    }
    return new_id;
}