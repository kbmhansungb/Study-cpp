#pragma once

#include <concepts>

// attribute�� �߰��ϰ� �����ϴ� ���� �Ұ����ϴ�.
// test_two�� private���� �ٲ㵵 �������� �ʴ���.
class is_allow
{
};

class test_class :
	public is_allow
{
	int a;
};

class test_two :
	virtual public test_class,
	public is_allow
{

};
void test()
{
	constexpr int class_size = sizeof(test_class);
	constexpr bool is_derived = std::is_base_of_v<is_allow, test_class>;
	constexpr bool os_derived2 = std::is_base_of_v<is_allow, test_two>;
}