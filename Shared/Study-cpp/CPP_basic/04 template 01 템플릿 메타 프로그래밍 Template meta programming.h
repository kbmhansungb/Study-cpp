#pragma once

/*

https://modoocode.com/221

 �̷��� ���ø��� ���ؼ� Ÿ���� ��ġ ���� �ΰ� ó�� ����ϴ� ���� 
 �ٷ� �Ϲ�ȭ ���α׷��� (generic programming) Ȥ�� �׳� ���ʸ� 
 ���α׷��� �̶�� �θ��ϴ�.

 array�� �����غ���, �׷� �����ϴ�.

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

// 3��� ����� ��ȯ�Ѵ�.

/*
	
	���ø� ��Ÿ ���α׷��� (Template Meta Programming - TMP)
	���� Ÿ���� �ݵ�� ������ Ÿ�ӿ� Ȯ���Ǿ�� �ϹǷ�, ������ Ÿ�ӿ� ��� ������ ������ �˴ϴ�. 
	�̷��� Ÿ���� ������ ������ Ÿ�ӿ� �����Ǵ� �ڵ�� ���α׷����� �ϴ� ���� ��Ÿ ���α׷���(meta programming) 
	�̶�� �մϴ�. C++ �� ��� ���ø��� ������ �̷��� �۾��� �ϱ� ������ ���ø� ��Ÿ ���α׷���, �ٿ��� TMP ��� �θ��ϴ�.
*/

/* ������ Ÿ�� ���丮�� ��� */
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

TMP �� �� ���°�?
�� ���� ����ִ� �������� C++ �ڵ嵵 ���ø� ��Ÿ ���α׷��� �ڵ�� ��ȯ�� �� �ִٴ� ���Դϴ�
(���� ��û���� �ڵ尡 �������������). �Դٰ� ���ø� ��Ÿ ���α׷������� �ۼ��� �ڵ�� ��� ������ Ÿ�ӿ� 
��� ������ ������ ������ ���α׷� ���� �ӵ��� ��� ��ų �� �ִٴ� ������ �ֽ��ϴ� 
(�翬���� ������ �ð��� ��û �þ�� �˴ϴ�).

�� �Ӹ��� �ƴ϶�, ���ø� ��Ÿ ���α׷������� �ۼ��� �ڵ�� ���׸� ã�� ���� �ſ� ����ϴ�. 
�ϴ� �⺻������ '������' Ÿ�ӿ� �����ϴ� ���̱� ������ ������� �Ұ��� �ϰ�, 
C++ �����Ϸ��� Ư�� �� ���ø� ���� �ÿ� ��û�� ������ ������ ���հ� �˴ϴ�.

���� TMP �� �̿��ϴ� ���� �ϳ� ������������, ���� C++ ���̺귯������ TMP �� �̿��ؼ� �����Ǿ��� 
(Boost ���̺귯��), TMP �� ���ؼ� ������ Ÿ�ӿ� ���� �������� ��Ƴ� �� �� �ְ� 
(Ex. ������ ��ȭ ��ġ ���ε��) �ӵ��� �ſ� �߿��� ���α׷��� ��� TMP �� ���ؼ� ��Ÿ�� �ӵ��� ��� ��ų �� �ֽ��ϴ�.

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
���� 1
N ��° �Ǻ���ġ ���� ��Ÿ���� TMP �� ��������.
����� �Ǻ���ġ ����, N ��° ���� N - 1 ��° �װ� N - 2 ��°
���� ������ ���ǵǴ� �� �Դϴ�. ����� 1, 1, 2, 3, 5, ...
�� ����˴ϴ�.(���̵� : ��)
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
���� 2
TMP �� ����ؼ� � ���� �Ҽ����� �ƴ����� �Ǻ��ϴ� ���α׷��� ��������. 
(���̵� : ��) ����� �� ������ ���� ���¿��� �ٷ� �����Դϴ�!
*/
namespace
{
	/*
	
		3�� �˻��Ѵٰ� �Ҷ�.
		2, �� �Ҽ��� ���, (1 �ʰ�) ������ �������� �Ҽ��� �ƴϰ� ������ �������� ������ �Ҽ��̴�.

		5�� �˻��Ѵٰ� �Ҷ�.
		4(�Ҽ��ƴ� ����), 3(�Ҽ�), 2(�Ҽ�)���� �Ҽ����� ������ �˻��ϰ�, ������ �������� ������ �Ҽ��̴�.

		6�� �˻��Ѵٰ� �Ҷ�.
		5, 4, 3, 2���� 5���� ������ �������� �����Ƿ� 3�� �˻��ϴµ� ������ �������Ƿ� �Ҽ��� �ƴϴ�.
	
	*/

	template <int N>
	struct is_prime
	{
		template <int I>
		static constexpr bool can_divide()
		{
			// �Ҽ��� ���³����� ���������� �˻��ϰ� �ƴ϶�� false�� ��ȯ
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