#pragma once

#include <iostream>
#include <tuple>

enum class ENUM_CLASS
{
	A,
	B,
};

template <typename T>
constexpr auto enum_to_int(const T& tuple) noexcept
{
	return (int)tuple;
}
#define get(TYPE, tuple) std::get<enum_to_int(TYPE)>(tuple);

//template <typename ENUM, typename... _Types>
//constexpr auto get(const ENUM literal, std::tuple<_Types...>& tuple) noexcept
//{
//	return std::get<enum_to_int(literal)>(tuple);
//	//return std::get<0>(tuple);
//}

class TestClass
{
public:
};

int main()
{
	auto tuple = std::tuple<int, double, int>();
	constexpr auto e = ENUM_CLASS::A;
	//auto z = std::get<static_cast<int>(ENUM_CLASS::A)>(tuple);
	auto z = std::get<static_cast<int>(e)>(tuple);
	auto a = std::get<enum_to_int(ENUM_CLASS::A)>(tuple);

	//// literal���� �Ķ���ͷ� ���� �� ������ �̷������� �ڵ带 �ۼ��ϴ°� �����ϴ�.
	//auto b = get(ENUM_CLASS::A, tuple);

	auto result = get(ENUM_CLASS::A, tuple);
	// ��ũ�η� �����ϴ°� ������ �׸� Ŀ ������ �ʴ´�.

	// static_cast�� �̿��ϴ°� ���� �ո������� ���δ�.

	// �̷� ������ Ŀ���� �Ҹ��ڸ� ����� �� �ִ�.
	auto delefunc = [](TestClass* tc)
	{
		delete tc;
	};
	std::unique_ptr<TestClass, decltype(delefunc)> TestUnique(new TestClass, delefunc);
}