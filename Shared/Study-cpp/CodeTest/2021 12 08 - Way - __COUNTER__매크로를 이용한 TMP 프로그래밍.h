#pragma once

/*
	�ǹ� 1 ��ӵǾ� ������ �� ���� ī��Ʈ�� ������ų �� �ִ� ����� �ִ°�?
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
	// �� index���� ���� �� �ְ� �� �� �ִ°�?

	// �׷��� ���ؼ��� ������ ������ index�� �Ʒ��� ������ index�� �޶�� �Ѵ�.
	// �Ź� ȣ�� �ø��� Ŭ������ �޶����� �� �� �ִ°�?

	// __counter__ ��ũ�θ� �̿��ϸ� �޶����� �� �� �ִ�.
	// ���� ������ �𸣴°� �ʹ� ����.

	// Ŭ������ ��ũ�η� ���δ� ���� ������� �ʴ�. ���ø��� ī���͸� ����.
}