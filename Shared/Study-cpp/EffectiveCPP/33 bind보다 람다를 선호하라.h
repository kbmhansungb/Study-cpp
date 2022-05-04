#pragma once

// C++14이상을 쓰기 때문에,,,

//
// 어떤 경우등 bind보다는 람다가 더 빠르고,
// 유지보수도 쉽고, 하다.
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
	// 1을 더한 값을 test로 수행할때

	auto bind = std::bind(test, std::bind(plus, 3));
	// 극단적이다. 알아보기 힘들다.

	auto lamda = [a = 3]()
	{
		test(a + 1);
	};
	// 극적으로 단순해진다.
	// 그리고 훨씬 빠르다.
}