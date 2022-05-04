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

	//// literal만을 파라메터로 받을 수 있으면 이런식으로 코드를 작성하는게 가능하다.
	//auto b = get(ENUM_CLASS::A, tuple);

	auto result = get(ENUM_CLASS::A, tuple);
	// 매크로로 정의하는게 이점이 그리 커 보이지 않는다.

	// static_cast를 이용하는게 가장 합리적으로 보인다.

	// 이런 식으로 커스텀 소멸자를 등록할 수 있다.
	auto delefunc = [](TestClass* tc)
	{
		delete tc;
	};
	std::unique_ptr<TestClass, decltype(delefunc)> TestUnique(new TestClass, delefunc);
}