#pragma once

/*
	
*/
#include <iostream>
#include <string>
namespace c17_move_forward
{
	struct S
	{
		S() = default;
		S(const S& rhs) { /*복사 생성자*/ };
		S(S&& rhs) { /*이동 연산자*/ };
	};

	struct test_struct
	{
		std::string str;
		test_struct(const std::string& s) : str(s)
		{
			std::cout << "기본 생성자" << std::endl;
		}
		test_struct(const test_struct& rhs)
		{
			std::cout << "복사 생성자" << std::endl;
			str = rhs.str;
		}
		test_struct(test_struct&& rhs) noexcept
		{
			std::cout << "이동 생성자" << std::endl;
			str.swap(rhs.str);
		}

		void swap(test_struct& b)
		{
			std::cout << "문자열을 생성함" << std::endl;
			std::string temp = this->str;
			str = b.str;
			b.str = temp;
		}
		void move_swap(test_struct& b)
		{
			std::cout << "문자열의 ref만 바꿈" << std::endl;
			std::string temp = std::move(this->str);
			str = b.str;
			b.str = temp;
		}
	};

	void move_forward_test()
	{
		/*
			l-value		: 왼쪽과 오른쪽 둘다 올 수 있다.
			r-value		: 오른쪽만 가능하다.
		*/


		// C++11 부터 좌측값을 우측값으로 바꾸어주는 move함수를 제공
		// move는 어떠한 일도 하지않고 형변환만 수행한다.
		// 즉 어떠한 바이트코드도 연산도 수행하지 않는다.

		int a = 3;					// 좌측값에 3이라는 리터럴을 할당했다.
		int&& b = std::move(a);		// std::move를 통하여 좌측값을 우측값으로 변환해서 반환

		auto lambda = []() { return 1; };
		int&& c = lambda();			// 이렇게 rhs를 좌측값에 저장하지 않고, 수명을 연장시킬 수 있다.

		/*
		
			이동생성자가 반드시 빠르게 아니라는 점을 기억하자.
			
			1. 만들어진 새로운 데이터 안에 동적할당 및 복사를 하지 않고,
			데이터 안에 레퍼런스를 옮기는 등의 작업만을 수행하도록
			최적화 했기 때문에 빠름.
			
		*/

		{
			std::cout << "test_struct s;" << std::endl;
			std::cout << "test_struct new_s = construct_only_copy(s);" << std::endl;
			test_struct s("string");
			test_struct other("other");
			
			s.swap(other);
			s.move_swap(other);

			/*
			
				복사하여 옮기는 경우 임시로 문자열을 저장할 객체를 생성하게 되지만
				단순하게 옮기는 목적이라면, 문자열을 가리키는 포인터만 옮기는 것으로 최적화가 가능하다.

				다만 이렇게 포인터를 옮기는 방식으로 인해 원치 않는 문제가 발생 할 수 있다.
			
				이동생성자나 이동 대입 연산자를 호출할 때 이동이 수행되는 것이지
				std::move를 호출한다고 이동이 되는 것은 아니다.

			*/
		}
	}


	template <typename T>
	void wrapper(T u) {
		g(u);
	}
	template <typename T>
	void universal_wrapper(T&& u) {
		g(std::forward<T>(u));
	}
	class A {};
	void g(A& a)		{ std::cout << "좌측값 레퍼런스 호출" << std::endl; }
	void g(const A& a)	{ std::cout << "좌측값 상수 레퍼런스 호출" << std::endl; }
	void g(A&& a)		{ std::cout << "우측값 레퍼런스 호출" << std::endl; }
	void perfect_forwarding() 
	{
		A a;
		const A ca;
		std::cout << "원본 --------" << std::endl;
		g(a);
		g(ca);
		g(A());
		std::cout << "Wrapper -----" << std::endl;
		wrapper(a);
		wrapper(ca);
		wrapper(A());
		/*
			원본 --------
			좌측값 레퍼런스 호출
			좌측값 상수 레퍼런스 호출
			우측값 레퍼런스 호출
			Wrapper -----
			좌측값 레퍼런스 호출
			좌측값 레퍼런스 호출
			좌측값 레퍼런스 호출

			위의 경우 전부 좌측값만을 받도록 설계되었다.
			어째서 인가?
			템플릿 인자 T가 레퍼런스가 아닌 일반적인 타입이라면 const를 무시한다.
			즉 T 가 전부 다 class A 로 추론됩니다.
			따라서 위 세 경우 전부 다 좌측값 레퍼런스를 호출하는 g 를 호출하였습니다.

			그렇다고 warp를 &참조자를 붙이면 A()의 경우 오류를 발생한다.
			이를 해결하기 위해,

			T&, constT&의 모든 경우를 만들기란 굉장히 번거로운 일이다.
			인자가 2개만 넘어가도 4가지 경우의 수가 생긴다.

			이를 해결하기 위해 보편참조(universal reference)를 활용한다.
		*/
		universal_wrapper(a);
		universal_wrapper(ca);
		universal_wrapper(A());
		/*
			좌측값 레퍼런스 호출
			좌측값 상수 레퍼런스 호출
			우측값 레퍼런스 호출
			
			보편참조는 우측값 레퍼런스와 다르게
			template또는 auto에서만 가능하다.

			왼값이면 왼값 참조로, 오른값이면 오른값 참조를 한다.

			& == 1, && == 0 일때 OR연산과 같다.
			&	&		1		&
			&	&&		1		&
			&&	&		1		&
			&&	&&		0		&&

			A			|	A&			->
			const A&	|	const A&	->
			A(rhs)		|	A		->

			forward는 
		*/
		auto&& temp1 = a;
		auto&& temp2 = ca;
		auto&& temp3 = A();
	}
}