#pragma once

#include <utility>
/*
	1. 망할 enable_if 어떻게 사용하냐,
*/

template <typename T,
	typename = typename std::enable_if<std::is_integral<T>::value, T>::type
>
void enable_test(T insert)
{

}

void test1()
{
	int c = 0;
	enable_test(c); //int를 넘기는게 아니면 오류난다.
}


/*
https://stackoverflow.com/questions/406081/why-should-i-avoid-multiple-inheritance-in-c


	static_cast에서 모호성을 이용하여 배타적 상속을 할 수 있을 것으로 보인다.
*/


namespace
{
	class BaseClass
	{
	};
	template <typename Base, typename Derived>
	constexpr bool cast_test()
	{
		static_cast<BaseClass>(std::declval<Derived>());
		return true;
	}

	class Base1 : public BaseClass
	{
	public:
	};

	class Base2 : public BaseClass
	{
	public:
	};

	class Derived :
		public Base1,
		public Base2
	{

	};
}

void test2()
{
	Derived a;
	//static_cast<BaseClass>(std::declval<Derived>());
	//constexpr auto b = cast_test<BaseClass, Derived>();
}

template <typename Base, typename Derived>
struct allow_static_cast
{
	using type = decltype(static_cast<Base>(std::declval<Derived>()));
};

class A {};
template <typename T,
	typename = typename allow_static_cast<A, T>::type
>
class A_condition
{

};

class B1 : public A {};

class B2 : public A {};

class C : 
	public B1
	, public B2
	//, public A_condition<C>
{
};
// 일단 원하는 대로 오류는 낼 수 있다.
// 다만 사람이 알아볼 수 있는 오류는 아니다.

template <typename Base, typename Derived>
inline constexpr bool is_static_castable() { return false; }
//constexpr bool t = std::is_convertible<C, A>::value;
template <typename T>
inline constexpr bool is_static_castable() { return true; }

/*
	is_convertible로 스테틱 케스트를 검사할 수 있다.
*/

class a {};
template <typename = void>
class b1 : public a 
{
public:

};

class b2 : public a
{
};
class c 
	//: 
	//public b1<std::enable_if<std::is_convertible<c, a>::value, c>::type> // 상속하는 단계에서 조건을 검사하는 것은 일단 불가능 하다. 비쥬얼 스튜디오에서 만들어 주지 않는 이상?
{
};
using t = std::enable_if<true, c>::type;