#pragma once

#include <iostream>
class A {
public:
	A() { std::cout << "A 의 생성자 호출!" << std::endl; }
	A(int a) {}
};
class B {
public:
	B(A a) { std::cout << "B 의 생성자 호출!" << std::endl; }
	B(A a, int c) {}
};
void test_uniform() {
	//A a(); // ? -> 아무것도 출력하지 않음.. 객체 a를 만드는 것이 아니라 함수의 정의처럼 보이기 때문에, 함수의 정의라고 생각함.
	//A a(3); // 이 경우에는 객체를 생성함...

	//// 중괄호 초기화로 해결 가능..
	//A aa{}; // 이제 객체를 생성함.
	//B b(A()); // 뭐가 출력될까요? // 골때리눼에
	//B b{A()};
	//B b(A(), 3); // 이 경우에도 객체를 생성함...

	// 다만 중괄호 생성자는 일부 암시적 형변환을 허용하지 않음.
	//		전부 데이터 손실이 있는 경우들을 말함.
	//		부동 소수점 타입에서 정수 타입으로의 변환
	//		long double에서 double혹은 float으로의 변환, double에서 float으로의 변환
	//		정수 타입에서 부동 소수점 타입으로의 변환

	using namespace std::literals;
	auto list = { "m"s, ""s }; // 이렇게 해줘야 string형 initializer_list를 사용하는 구나..
}
