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
	// �̷��� �ϸ� lhs�� ���� rh
}

int main()
{
	// std::move�� std::forward�� ���� �������� �� �� ����Ʈ��, ���డ�� �ڵ嵵 �������� �ʴ´�.
	// �׳� ĳ������ �����ϴ� �ϼ��̴�.
	// std::move�� �׻� ���������� ĳ�����ϰ�,
	// std::forward�� ������ ���� ���������� ĳ�����Ѵ�.

	int o = 1;
	auto&& r = o; // �̰� ������ ���� �ƴϰ� �ȴ�.
	int&& a = std::move(o);
	std::cout << a << std::endl;

	std::string&& rhs = "opq";
	std::string n("Test");
	std::string w;
	//// �ް� ������ ���� �Ѿ��.
	//rhs_test(w, n);
	w = std::move(n); // �̷��� �ϸ� n�� Test���� w�� �̵��ǰ� n�� ���� �������. �̵������ϰ� �ʱ�ȭ �ϱ� �����ΰ�.
	n = w; // �̷��� �ϸ� �翬�ϰ� ���� �����ȴ�.

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