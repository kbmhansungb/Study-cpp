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
	// ��ȯ���� ���� ���Ǵ� �Է����� ����.
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
		//std::string str2 = custom_string"Ar"; �ݴ�� �ϴ� ���� �ȵ�..
	}
}