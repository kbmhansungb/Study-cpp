#pragma once

#include <utility>
/*
	1. ���� enable_if ��� ����ϳ�,
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
	enable_test(c); //int�� �ѱ�°� �ƴϸ� ��������.
}


/*
https://stackoverflow.com/questions/406081/why-should-i-avoid-multiple-inheritance-in-c


	static_cast���� ��ȣ���� �̿��Ͽ� ��Ÿ�� ����� �� �� ���� ������ ���δ�.
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
// �ϴ� ���ϴ� ��� ������ �� �� �ִ�.
// �ٸ� ����� �˾ƺ� �� �ִ� ������ �ƴϴ�.

template <typename Base, typename Derived>
inline constexpr bool is_static_castable() { return false; }
//constexpr bool t = std::is_convertible<C, A>::value;
template <typename T>
inline constexpr bool is_static_castable() { return true; }

/*
	is_convertible�� ����ƽ �ɽ�Ʈ�� �˻��� �� �ִ�.
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
	//public b1<std::enable_if<std::is_convertible<c, a>::value, c>::type> // ����ϴ� �ܰ迡�� ������ �˻��ϴ� ���� �ϴ� �Ұ��� �ϴ�. ����� ��Ʃ������� ����� ���� �ʴ� �̻�?
{
};
using t = std::enable_if<true, c>::type;