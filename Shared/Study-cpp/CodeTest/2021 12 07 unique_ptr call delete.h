#pragma once

#include <memory>
#include <iostream>

class TEST_BLOCK
{
public:
	TEST_BLOCK()
	{
		std::cout << "생성자 호출" << std::endl;
	}
	~TEST_BLOCK()
	{
		std::cout << "소멸자 호출" << std::endl;
	}
};

void unique_ptr_call_delete_test()
{
	std::unique_ptr<TEST_BLOCK>&& test_blcok = std::make_unique<TEST_BLOCK>();

	// 오른쪽 값에 대해 유니큐 ptr은 소멸자를 호출하다.
}