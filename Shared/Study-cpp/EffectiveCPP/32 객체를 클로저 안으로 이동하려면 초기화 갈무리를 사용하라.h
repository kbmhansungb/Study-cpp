#pragma once

// C++14������
// �ʱ�ȭ ������(init capture)��� ���� �ִ�.

#include <memory>

int temp_func(int a)
{
	return a;
}
class Widget
{
public:
	bool is_vaild() { return true; }
	void func()
	{
		auto pw = std::make_unique<Widget>();
		auto func = [copy = std::move(pw)]()
		{ return copy->is_vaild(); };
		// �̷��� Ŭ������ �����Ͽ� ������� �� �ִ�.

		// �̷��Ե� �� �� �ִ�.
		auto func = [pw = std::make_unique<Widget>()]()
		{ return pw->is_vaild(); };
		// �̷� �ʱ�ȭ �������� �Ϲ�ȭ�� ���� ������(generalized lambda capture)��� �θ��⵵ �Ѵ�.

		// std::bind�� �����ΰ�?
		auto f1 = [](auto x) { return x; };
		// ���� �Լ��� x�� �����ϴ� �Լ��̴�.
		auto f2 = [](auto&& x) {return x; };
		// �̷��� ��� �ɱ�?
		// �ް��̸� �ް��� �ް� ���� ���̸� ���� ���� �޴´�.
		auto f3 = [](auto&& x) { return temp_func(std::forward<decltype(x)>(x)); };

		// �ް� ������, �Ϻ����� �������� ������ �򰥸���,
		// decltype(x)�� �ށ��̸� �ް��� ������ ��Ÿ����, �������̸� �������� ������ ��Ÿ����.
	}
};