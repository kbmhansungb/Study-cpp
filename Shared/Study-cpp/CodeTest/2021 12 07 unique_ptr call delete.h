#pragma once

#include <memory>
#include <iostream>

class TEST_BLOCK
{
public:
	TEST_BLOCK()
	{
		std::cout << "������ ȣ��" << std::endl;
	}
	~TEST_BLOCK()
	{
		std::cout << "�Ҹ��� ȣ��" << std::endl;
	}
};

void unique_ptr_call_delete_test()
{
	std::unique_ptr<TEST_BLOCK>&& test_blcok = std::make_unique<TEST_BLOCK>();

	// ������ ���� ���� ����ť ptr�� �Ҹ��ڸ� ȣ���ϴ�.
}