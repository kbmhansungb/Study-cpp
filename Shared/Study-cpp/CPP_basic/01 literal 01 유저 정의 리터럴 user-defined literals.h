#pragma once

#include <string>
/*
	User-defined literals
	https://en.cppreference.com/w/cpp/language/user_literal
*/
namespace c17_literal_operator_override
{
	int operator""custom_operator(unsigned long long literal)
	{
		return -1;
	}
	// 반환형에 따라 허용되는 입력형이 있음.
	//int operator""custom_operator(int a)
	//{
	//}

	std::string operator""custom_string(const char* pc, size_t s)
	{
		return std::string(pc, s);
	}

	void literal_operaotr_override()
	{
		int num = 32custom_operator;
		std::string str = "Ar"custom_string;
		//std::string str2 = custom_string"Ar"; 반대로 하는 것은 안됨..
	}
}