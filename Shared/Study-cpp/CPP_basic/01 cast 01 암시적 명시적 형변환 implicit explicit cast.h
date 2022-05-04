#pragma once

/*

	2021 11 26

	암시적 형변환		: 자동적으로 캐스팅 되는 것
	(자동적 형변환)

	명시적 형변환		: 프로그래머가 형변환을 직접 나타낸 것.
	(강제 형변환)
						  ex) (type)value
						  포인터의 경우 모든 타입에 대해 강제적인 형변환이 가능함.

	https://killu.tistory.com/24
*/
#include <cstdio>
namespace C17_implicit_explicit_cast
{
	void cast_test()
	{
		// 암시적 형변환 implicit cast

		char c = 0;
		short s = 0;
		int i = 0;
		long l = 0;
		float f = 0;
		double d = 0;
		unsigned int ui = 0;

		int long_to_int = l;		// int형으로 케스팅 됨.
		
		auto i_op_l = i + l;		// 나타낼수 있는 범위가 더큰 타입으로 캐스팅 됨.
		auto l_op_i = l + i;

		auto ui_op_i = ui + i;		// 타입과 unsigned 타입의 경우 unsigned 타입으로 캐스팅 됨.
		auto i_op_ui = i + ui;

		auto l_op_f = l + f;		// 정수와 실수의 경우 실수를 우선으로 캐스팅함.
		auto f_op_l = f + l;

		auto ui_op_f = ui + f;		// 같은 원리로 unsigned 타입과 실수의 경우 실수를 우선으로 캐스팅함.
		auto f_op_ui = f + ui;

		int by_l = l;				// 집어넣을 라는 변수의 타입이 다를 경우 왼쪽 변수의 타입으로 형변환됨

		short num1 = 10, num2 = 20; // 정수의 승격(Integral Promotion)'에 의한 자동 형 변환
		auto num_add = num1 + num2; // int형 크기보다 작은 자료형인 경우 CPU가 계산하기 편한 int형으로 형변환 됨.

		// 명시적 형변환 explicit cast

		auto int_by_l = (int)l; // l을 i로 명시적 형변환함

		// 포인터의 경우 모든 타입에 대해 강제적인 형변환이 가능함.
		// 설명 생략.
	}

	struct Cast_struct
	{
		Cast_struct() {}
		Cast_struct(int a) {}
	};
	Cast_struct operator+ (const Cast_struct& a, const int& b)
	{
		return b;
	}
	struct Empty_struct
	{
	};
	void s_cast_test()
	{
		// 자료형의 캐스팅

		int a = 0;
		Cast_struct A;
		
		A = (Cast_struct)a; // 생성자를 이용하여 형변환함.
							// 생성자가 없고, 형변환을 허용하지 않으면 캐스팅 자체가 되지 않음.

		Empty_struct* p_es;
		p_es = (Empty_struct*)(&a);	// 포인터의 경우 강제형변환이 가능함.
									// 어떤 타입으로든 캐스트가 가능하지만 안정성을 보장해주지 않음.

		Cast_struct B;
		B = (Cast_struct)a + 3;		// 다음식의 연산은 operator에 의해 이루어짐.

	}
}