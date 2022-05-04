#pragma once

#include <vector>
#include <iostream>
#include <list>

// 소수인지 확인하기.

/// <summary>
/// 소수인지 확인 하는 메서드
/// 전체 검사를 한다.
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
/// 약수를 만들어 divisor_list에 추가하는 메서드 
/// </summary>
/// <param name="num"></param>
/// <param name="divisor_list"></param>
void make_divisor(int num, std::list<int>& divisor_list)
{
    for (int i = 1; i <= num; ++i)
    {
        if (num % i == 0)
        {
            // 약수인 경우 추가
            divisor_list.push_back(i);
        }
    }
}
