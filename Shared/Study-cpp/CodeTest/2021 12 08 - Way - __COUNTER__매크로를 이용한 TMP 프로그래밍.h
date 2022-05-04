#pragma once

/*
	의문 1 상속되어 생성될 때 마다 카운트를 증가시킬 수 있는 방법이 있는가?
*/
#define field index<__COUNTER__>
template <int num>
struct index
{
	constexpr static int get_count() { return num; }
};
struct test
{
	field a;
	field b;
	field c;
};
struct test2
{
	field a;
	field b;
	field c;
};
void test_func()
{
	test a;
	int a1 = a.a.get_count();
	int a2 = a.b.get_count();
	int a3 = a.c.get_count();
	test b;
	int b1 = b.a.get_count();
	int b2 = b.b.get_count();
	int b3 = b.c.get_count();
	// 의 index값을 가질 수 있게 할 수 있는가?

	// 그러기 위해서는 위에서 선언한 index가 아래서 선언한 index와 달라야 한다.
	// 매번 호출 시마다 클래스를 달라지게 할 수 있는가?

	// __counter__ 매크로를 이용하면 달라지게 할 수 있다.
	// 나는 아직도 모르는게 너무 많다.

	// 클래스를 매크로로 감싸는 것은 우아하지 않다. 템플릿에 카운터를 넣자.
}