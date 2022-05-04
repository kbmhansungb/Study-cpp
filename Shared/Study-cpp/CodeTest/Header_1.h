#pragma once

#include <vector>
#include <iostream>
#include <list>

// �Ҽ����� Ȯ���ϱ�.

/// <summary>
/// �Ҽ����� Ȯ�� �ϴ� �޼���
/// ��ü �˻縦 �Ѵ�.
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
bool is_prime(int num)
{
	if (num < 2) return false;
	for (int i = 2; i < num; ++i)
	{
		if (num % i == 0) return false;
	}
	return true;
}
//bool is_prime(int num)
//{
//	if (num < 2) return false;
//	for (int i = 2; i <= sqrt(num); ++i)
//	{
//		if (num % i == 0) return false;
//	}
//	return true;
//}


/// <summary>
/// ����� ����� divisor_list�� �߰��ϴ� �޼��� 
/// </summary>
/// <param name="num"></param>
/// <param name="divisor_list"></param>
void make_divisor(int num, std::list<int>& divisor_list)
{
    for (int i = 1; i <= num; ++i)
    {
        if (num % i == 0)
        {
            // ����� ��� �߰�
            divisor_list.push_back(i);
        }
    }
}
