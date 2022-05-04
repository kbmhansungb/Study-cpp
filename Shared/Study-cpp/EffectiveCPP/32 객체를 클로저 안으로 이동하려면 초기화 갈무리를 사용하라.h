#pragma once

// C++14에서는
// 초기화 갈무리(init capture)라는 것이 있다.

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
		// 이렇게 클로저에 복사하여 집어넣을 수 있다.

		// 이렇게도 할 수 있다.
		auto func = [pw = std::make_unique<Widget>()]()
		{ return pw->is_vaild(); };
		// 이런 초기화 갈무리를 일반화된 람다 갈무리(generalized lambda capture)라고 부르기도 한다.

		// std::bind란 무엇인가?
		auto f1 = [](auto x) { return x; };
		// 위의 함수는 x를 전달하는 함수이다.
		auto f2 = [](auto&& x) {return x; };
		// 이러면 어떻게 될까?
		// 왼값이면 왼값을 받고 오른 값이면 오른 값을 받는다.
		auto f3 = [](auto&& x) { return temp_func(std::forward<decltype(x)>(x)); };

		// 왼값 오른값, 완벽전달 보편참조 오지게 헷갈리네,
		// decltype(x)은 왼괎이면 왼값의 형식을 나타내고, 오른값이면 오른값의 형식을 나타낸다.
	}
};