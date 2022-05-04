#pragma once

#include <concepts>

// attribute를 추가하고 제거하는 것이 불가능하다.
// test_two를 private으로 바꿔도 숨겨지지 않느다.
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