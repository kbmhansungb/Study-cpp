#pragma once

template <template <typename... Args> typename A>
void template_template_typename_typename()
{

}

template <typename... Args>
struct Struct 
{...};

void test()
{
	Struct<int> a;


}


template <typename T, int N>
class IteratorSpecificier {};

template <typename T>
class IteratorSpecificier<T, 1> {...};

template <typename T, int N>
class TestClass
{
	using Iterator = IteratorSpecificier<T, N>;
};


#include <memory>
#include <functional>
struct test_struct
{
	test_struct(int a) {}
};

void func(int a)
{

}

void test()
{

	std::make_unique<test_struct>(3);
}