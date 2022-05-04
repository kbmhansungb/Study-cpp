#pragma once
/*
	
	�⺻ ������ ��� (default capture mode)�� �� ������,
	�ϳ��� ������ ���� ������ ��� �̰�,
	�� �ϳ��� ���� ���� ������ ��� �̴�.

*/

#include <vector>
#include <functional>
#include <algorithm>

class test_class
{
public:
	using FilterContainer = std::vector<std::function<bool(int)>>;
	FilterContainer filters;

	test_class()
	{
		filters.emplace_back(
			[](int value) { return value % 5 == 0; }
		);

		// divisor�� ����������� ����ؾ� �ȴٸ�

		int divisor = 3;
		filters.emplace_back(
			[&](int value) { return value % divisor == 0; }
			// ??? �̰� �������� �ǳ�,
		);
		// ��� ���� ������ ���� �� ����.
		// ������ �ൿ�� ������.

		filters.emplace_back(
			[&divisor](int value) { return value % divisor == 0; }
		);
		// �̰͵� ���� ���������� ����� ������.

		if (std::all_of(
			filters.begin(), filters.end(),
			[&](int value) { return value % divisor == 0; }
		))
		{
			// ...
		}
		// filters�� ���� ���� ���� ��쿡�� �����ϵ��� �� �� ������,
		// �̸� ����ϴ� ���α׷��Ӱ� divisor�� �̿��ϴ� ���ٸ� �߰��ϴ� ������ �����ϰ�,
		// divisor���۷����� �Ҹ�� �޼��带 �Է��� ���ɼ��� �ִ�.

		filters.emplace_back(
			[=](int value) { return value % divisor == 0; }
		);
		// �̷��� �ϸ� divisor�� �����ؼ� �����ϱ⿡ ����� ������ ������,
		// �������� ��� �ҽǵ� ���ɼ��� �ִ�.
	}
};

class test_class2
{
public:
	using FilterContainer = std::vector<std::function<bool(int)>>;
	FilterContainer filters;

	int divisor = 0;

	test_class2()
	{
		filters.emplace_back(
			[=](int value) { return value % divisor; }
		);
		// >>> �����ϵǸ�
		auto currentObjectPtr = this;
		filters.emplace_back(
			[currentObjectPtr](int value)
			{return value % currentObjectPtr->divisor; }
		);
		// �̷������� �����ϰ� �ȴ�.
		// �ν��Ͻ� ���� �� ptr�� ���͸� ����ϰ�, �ν��Ͻ��� �����ϸ� ����� ���� �� �����Ͱ� �����ϰ� �ȴ�.
		
		// �����ؼ� �����ϸ� �̷��� ������ �ذ� �� �� �ִ�.
		auto divisor_copy = divisor;
		filters.emplace_back(
			[divisor_copy](int value)
			{ return value % divisor_copy == 0; }
		);
		// c++ 14���� ���� ���� ����� �ִ�.
		filters.emplace_back(
			[divisor = divisor](int value)
			{ return value % divisor == 0; }
		);
	}

	void add_divisor_filter()
	{
		static int divisor = 1;

		filters.emplace_back(
			[=](int value)
			{ return value % divisor == 0; }
		);

		++divisor;

		// �̷��� �ۼ��ϸ� ���Ͱ� �߰��� �� ���� ��� divisor���� �����ϴ� ����� �����´�.
		// ���ΰ�?
		// ������ �Ǹ� ������ ���� ����� �������� �����̴�.
		auto copy_ptr = this;
		filters.emplace_back(
			[copy_ptr](int value)
			{ return value % divisor == 0; } // divisor�� �Լ��� static ������ ����Ų��.
		);

		// ���ٴ� �����ؼ� ����ؾ� �Ѵ�.
	}
};