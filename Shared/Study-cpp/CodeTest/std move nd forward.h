#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <cctype>
decltype(auto) Test(std::string&& str)
{
}

void rhs_test(std::string& to, std::string& from)
{
	to = std::move(from);
	// 이렇게 하면 lhs의 값이 rh
}

int main()
{
	// std::move와 std::forward는 실행 시점에서 단 한 바이트도, 실행가능 코드도 산출하지 않는다.
	// 그냥 캐스팅을 수행하는 하수이다.
	// std::move는 항상 오른값으로 캐스팅하고,
	// std::forward는 가능할 때만 오른값으로 캐스팅한다.

	int o = 1;
	auto&& r = o; // 이거 오른값 참조 아니게 된다.
	int&& a = std::move(o);
	std::cout << a << std::endl;

	std::string&& rhs = "opq";
	std::string n("Test");
	std::string w;
	//// 왼값 참조로 값이 넘어간다.
	//rhs_test(w, n);
	w = std::move(n); // 이렇게 하면 n의 Test값이 w로 이동되고 n의 값은 사라진다. 이동생성하고 초기화 하기 때문인가.
	n = w; // 이렇게 하면 당연하게 복사 생성된다.

	std::vector<int> vec = { 0, 1, 2, 3, 4 };
	for (const auto& elum : vec)
	{

	}

	std::list<int> vec;
	vec.insert(vec.begin(), 3);
}

std::string solution(std::string s) {
	std::sort(s.begin(), s.end());
	std::reverse(s.begin(), s.end());

	return s;
}