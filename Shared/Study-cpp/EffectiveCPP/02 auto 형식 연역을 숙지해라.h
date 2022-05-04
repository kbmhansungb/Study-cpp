#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>

template<typename It>
void dwim(It b, It e) // dwim은 "do what I mean"으로
					  // DWIM (내 말대로 해) 컴퓨터 시스템은 사용자의 명시 적이지만 잠재적으로 잘못된 입력을 
					  // 맹목적으로 실행하지 않고 사소한 오류를 자동으로 수정하여 사용자가하려는 작업을 예상하려고 시도합니다.
{
	for (; b != e; ++b)
	{
		//typename std::iterator_traits<It>::value_type	 // 긴 타입명을 이용하는 것은 쉽지 않다.
		//	currValue = *b;

		auto currValue = *b; // auto 를 통해서 단순화 시킬 수 있다. 단 auto는 형식연역을 이용한다. 

	}
}

void processWidget(bool priority)
{

}

class Widget
{
public:
	//int z(0);
};

class Widget2
{
public:
	Widget2(int i, bool b) {}
	Widget2(std::initializer_list<bool> il) {}
};

//class Widget3
//{
//public:
//	Widget3() {};
//	Widget3(std::initializer_list<int> il) {};
//};
//
//Widget3 w31;
//Widget3 w32{};
//Widget3 w33(); // 함수 선언이 되버리네,

int main()
{
	// 1.
	std::vector<int> vec_dwim;
	dwim(vec_dwim.begin(), vec_dwim.end());

	// 2.
	// auto는 형식 연역을 사용하므로 컴파일러만 알던 형식을 지정할 수 있다.
	// 람다 표션식의 매개변수에도 auto를 적용할 수 있다.
	auto dereLess
		= [](
			const auto& p1,
			const auto& p2
			)
	{
		return *p1 < *p2;
	};
	// 이렇게 짜도 작동이 되네???

	std::vector<int> vec = { 0, 1 };
	bool result = dereLess(vec.begin() + 0, vec.begin() + 1);

	std::function<bool(const std::vector<int>::iterator&, const std::vector<int>::iterator)> func;
	func = dereLess;
	// 이렇게 람다식을 구현해야 되는 부분에서 auto의 용법은 굉장히 용의하다.

	// 
	// 	   auto로 담는 변수는 그 클로저와 같은 형식이며, 따라서 그 클로저에 요구되는 만큼의 메모리만 사용한다.
	// 
	// 	   std::function으로 선언된 변수의 형식은 std::function템플릿의 한 인스턴스이며, 그 크기는 임의의 주어진 서명에 대해 고정되어 있다.
	// 	   그런데 그 크기가 요구된 클러저를 저장하기에 부족할 수도 있으며, 그런 경우 std::function은 힙 메모리를 할당해서 클로저를 저장한다.
	//
	// 	   결과적으로 std::function 객체는 대체로 auto로 선언된 객체보다 메모리를 더 많이 소비한다.
	//
	//	   https://lunchballer.com/archives/284
	//

	std::vector<int> v;
	unsigned sz_u = v.size();
	// 32비트일 경우 문제 없지만, 64비트일 경우 오류가 발생한다.
	// auto를 통해서 이러한 문제를 해결 할 수 있다.
	auto sz_a = v.size();

	std::unordered_map<std::string, int> m;
	for (const std::pair<std::string, int>& p : m)
	{
		// p로 뭔가를 수행
		// 

	}
	// 이 코드의 문제점은 for문이 수행될 때 마다
	// std::pair<std::string, int> -> const std::pair<std::string, int>&
	// 하게 되는 내부적으로 매우복잡한 작업을 거치게 된다.
	// auto를 통하여 위의 문제를 해결 할 수 있다.
	for (const auto& p : m)
	{
		// p로 무언가를 수행.
	}

	// auto가 원치 않는 형식으로 연역될 때에는 명시적 형식의 초기치를 사용하라.
	std::vector<bool> features = { true };
	auto highPriority_0 = features[0];
	bool highPriority_1 = features[0];
	// auto는 bool을 가리키는 것이 아닌, std::vector<bool>::reference의 형이 된다.

	// 대상을 잃은 포인터(dangling pointer)
	processWidget(highPriority_0); // reference를 연역하는 문제를 해결하기 위해 사용하는 것이 '형식 명시 초기치 관용구'이다.

	// ????
	auto highPriority_2 = static_cast<bool>(features[0]);

	Widget w1;		// 기본 생성자를 호출
	Widget w2 = w1;	// 배정이 아님; 복사 생성자를 호출
	w1 = w2;		// 배정; 복사 배정 연산자 (operator =)를 호출

	//int z(0);

	//Widget2 wi2{10, 5.0f}; // 
	//Widget2 wi2 = {10, 5.0f}; // 
	// initializer_list<VALTYPE> 을 생성자의 함수로 받을 경우 중괄호 초기자는 최우선으로 이 생성자를 이용한다.
}