#pragma once

// C++14�̻��� ���� ������,,,

//
// � ���� bind���ٴ� ���ٰ� �� ������,
// ���������� ����, �ϴ�.
// 

#include <functional>
int plus(int a)
{
	return a + 1;
}
int test(int a)
{
	return a;
}

void bind_and_lamda()
{
	// 1�� ���� ���� test�� �����Ҷ�

	auto bind = std::bind(test, std::bind(plus, 3));
	// �ش����̴�. �˾ƺ��� �����.

	auto lamda = [a = 3]()
	{
		test(a + 1);
	};
	// �������� �ܼ�������.
	// �׸��� �ξ� ������.
}