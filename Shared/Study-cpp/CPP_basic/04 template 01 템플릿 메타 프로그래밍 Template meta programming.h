#pragma once

/*

https://modoocode.com/221

 이렇게 템플릿을 통해서 타입이 마치 인자 인것 처럼 사용하는 것을 
 바로 일반화 프로그래밍 (generic programming) 혹은 그냥 제너릭 
 프로그래밍 이라고 부릅니다.

 array를 생각해보자, 그럼 간단하다.

*/

#include <iostream>
#include <typeinfo>

template <int N>
struct Int {
	static const int num = N;
};

template <typename T, typename U>
struct add {
	typedef Int<T::num + U::num> result;
};

void template_meta_programming() 
{
	typedef Int<1> one;
	typedef Int<2> two;

	typedef add<one, two>::result three;

	std::cout << "Addtion result : " << three::num << std::endl;
}

// 3라는 결과를 반환한다.

/*
	
	템플릿 메타 프로그래밍 (Template Meta Programming - TMP)
	또한 타입은 반드시 컴파일 타임에 확정되어야 하므로, 컴파일 타임에 모든 연산이 끝나게 됩니다. 
	이렇게 타입을 가지고 컴파일 타임에 생성되는 코드로 프로그래밍을 하는 것을 메타 프로그래밍(meta programming) 
	이라고 합니다. C++ 의 경우 템플릿을 가지고 이러한 작업을 하기 때문에 템플릿 메타 프로그래밍, 줄여서 TMP 라고 부릅니다.
*/

/* 컴파일 타임 팩토리얼 계산 */
#include <iostream>
template <int N>
struct Factorial 
{
	static const int result = N * Factorial<N - 1>::result;
};

template <>
struct Factorial<1> 
{
	static const int result = 1;
};

void tmp() 
{
	std::cout << "6! = 1*2*3*4*5*6 = " << Factorial<6>::result << std::endl;
}

/*

TMP 를 왜 쓰는가?
한 가지 재미있는 사실은어떠한 C++ 코드도 템플릿 메타 프로그래밍 코드로 변환할 수 있다는 점입니다
(물론 엄청나게 코드가 길어지겠지만요). 게다가 템플릿 메타 프로그래밍으로 작성된 코드는 모두 컴파일 타임에 
모든 연산이 끝나기 때문에 프로그램 실행 속도를 향상 시킬 수 있다는 장점이 있습니다 
(당연히도 컴파일 시간은 엄청 늘어나게 됩니다).

그 뿐만이 아니라, 템플릿 메타 프로그래밍으로 작성된 코드는 버그를 찾는 것이 매우 힘듭니다. 
일단 기본적으로 '컴파일' 타임에 연산하는 것이기 때문에 디버깅이 불가능 하고, 
C++ 컴파일러에 특성 상 템플릿 오류 시에 엄청난 길이의 오류를 내뿜게 됩니다.

따라서 TMP 를 이용하는 경우는 꽤나 제한적이지만, 많은 C++ 라이브러리들이 TMP 를 이용해서 구현되었고 
(Boost 라이브러리), TMP 를 통해서 컴파일 타임에 여러 오류들을 잡아낼 수 도 있고 
(Ex. 단위나 통화 일치 여부등등) 속도가 매우 중요한 프로그램의 경우 TMP 를 통해서 런타임 속도도 향상 시킬 수 있습니다.

*/

int gcd(int a, int b) {
	if (b == 0) {
		return a;
	}

	return gcd(b, a % b);
}

#include <iostream>

template <int X, int Y>
struct GCD {
	static const int value = GCD<Y, X% Y>::value;
};

template <int X>
struct GCD<X, 0> {
	static const int value = X;
};

void TMP_GCD() {
	std::cout << "gcd (36, 24) :: " << GCD<36, 24>::value << std::endl;
}

//////////////////////////////////////////////////

/*
문제 1
N 번째 피보나치 수를 나타내는 TMP 를 만들어보세요.
참고로 피보나치 수는, N 번째 항이 N - 1 번째 항과 N - 2 번째
항의 합으로 정의되는 수 입니다. 참고로 1, 1, 2, 3, 5, ...
로 진행됩니다.(난이도 : 하)
*/
namespace
{
	template <int N>
	struct Fibonacci
	{
		static const int Num = Fibonacci<N - 1>::num + Fibonacci<N - 2>::num;
	};
	template <>
	struct Fibonacci<1>
	{
		static const int Num = 1;
	};
	template <>
	struct Fibonacci<2>
	{
		static const int Num = 1;
	};
}

/*
문제 2
TMP 를 사용해서 어떤 수가 소수인지 아닌지를 판별하는 프로그램을 만들어보세요. 
(난이도 : 상) 참고로 이 문제는 다음 강좌에서 다룰 예정입니다!
*/
namespace
{
	/*
	
		3을 검사한다고 할때.
		2, 가 소수일 경우, (1 초과) 나누어 떨어지면 소수가 아니고 나누어 떨어지지 않으면 소수이다.

		5를 검사한다고 할때.
		4(소수아님 제외), 3(소수), 2(소수)에서 소수만을 나누어 검사하고, 나누어 떨어지지 않으면 소수이다.

		6을 검사한다고 할때.
		5, 4, 3, 2에서 5에서 나누어 떨어지지 않으므로 3을 검사하는데 나누어 떨어지므로 소수가 아니다.
	
	*/

	template <int N>
	struct is_prime
	{
		template <int I>
		static constexpr bool can_divide()
		{
			// 소수일 때는나누어 떨어지는지 검사하고 아니라면 false를 반환
			return is_prime<I>::is_true ? N % I == 0 : false;
		}

		template <int I>
		static constexpr bool extend()
		{
			return can_divide<I>() || extend<I - 1>();
		}
		template <>
		static constexpr bool extend<1>()
		{
			return false;
		}

		static constexpr bool is_true = extend<N - 1>() == false;
	};
}