#pragma once

namespace
{
	bool is_prime(int N) 
	{
		if (N == 2) return true;
		if (N == 3) return true;

		for (int i = 2; i <= N / 2; i++) {
			if (N % i == 0) return false;
		}

		return true;
	}
}

/*

	아니 미친,, 더 간단하게 푸네??
	인줄 알았는데,, 아니네,, 더럽게 복잡하게 푸네,

*/

/*

https://modoocode.com/222

단위(Unit) 라이브러리
C++ 코드를 작성하는 이유는 여러가지가 있겠지만, 그 중 하나로 바로 여러 수치 계산을 
사용하는데에도 많이 사용합니다. 예를 들어서 인공위성의 궤도를 계산한다던지, 
입자의 운동을 계산한다던지 말이지요. 이러한 물리적 수치 계산 시에 꼭 필요한 것이 바로 '단위' 입니다.

단위라 하면 쉽게 말해 킬로그램 (kg), 미터 (m), 초 (s) 등을 생각하시면 됩니다. 
이러한 것들을 계산하는 프로그램들의 경우, double 이나 float 변수에 들어가는 
값에는 '단위' 가 붙어서 들어가겠지요.

예를 들어서 핸드폰의 가속도 센서에서 부터 데이터를 받는 프로그램은 아마도 
m/s^2 단위로 데이터를 받겠지요. 혹은 시계로 부터 데이터를 받는 프로그램은 
s 단위로 데이터를 받을 것 입니다.

float v;        // 속도; m/s
float a;        // 가속도; m/s^2
std::cout << v + a;  // ???
만약에 v 가 속도를 나타내는 값이고, 
a 가 가속도를 나타내는 값이라면, 
v + a 는 불가능한 연산입니다.

만약에 프로그래머가 저러한 코드를 썻다면 분명히 실수일 것입니다. 
물론 C++ 컴파일러 입장에서는 그냥 두 개의 float 변수를 더한 것이기 때문에 
문제 없이 컴파일 됩니다. 하지만 프로그램을 돌리게 된다면 골치아픈 문제가 발생하겠지요.

실제로, NASA 의 경우 단위를 잘못 처리해서 1조원 짜리 화성 탐사선을 날려먹은 경우가 있습니다. 
이 경우 1조원 자리 버그 이겠네요.

여러분 이라면 이러한 실수를 어떻게 막을 것인가요? 
일단 가장 먼저 드는 생각으로 단위 데이터를 일반적인 변수에 보관하지 말고 
클래스를 만들어서 클래스 객체에서 보관하는 것입니다. 그리고 operator+ 
등으로 연산자들을 오버로딩 한 뒤에, 연산 시에 객체 끼리 단위를 체크해서 
단위가 맞지 않으면 적절히 처리하면 됩니다.

물론 이 방법은 꽤나 괜찮아 보이지만 한 가지 문제가 있습니다. 
만일 틀린 단위를 연산하는 코드가 매우 드물게 일어난다면 어떨까요? 
즉 런타임에서 그 문제를 발견하지 못한 채 넘어갈 수 있다는 점입니다.

가장 이상적인 상황은 단위가 맞지 않는 연산을 수행하는 코드가 있다면 
아예 컴파일 시에 오류를 발생시켜버리는 것입니다. 
그렇다면 적어도 틀린 단위를 연산하는 일은 막을 수 있게 되고,
프로그램을 실행 시키면서 기다리는 수고를 줄일 수 있게 되지요.

*/

#include <iostream>
#include <typeinfo>

template <int X, int Y>
struct GCD {
    static const int value = GCD<Y, X% Y>::value;
};

template <int X>
struct GCD<X, 0> {
    static const int value = X;
};

template <int N, int D = 1>
struct Ratio {
private:
    const static int _gcd = GCD<N, D>::value;

public:
    typedef Ratio<N / _gcd, D / _gcd> type;
    static const int num = N / _gcd;
    static const int den = D / _gcd;
};
template <class R1, class R2>
struct _Ratio_add {
    using type = Ratio<R1::num* R2::den + R2::num * R1::den, R1::den* R2::den>;
};

template <class R1, class R2>
struct Ratio_add : _Ratio_add<R1, R2>::type {};

template <class R1, class R2>
struct _Ratio_subtract {
    using type = Ratio<R1::num* R2::den - R2::num * R1::den, R1::den* R2::den>;
};

template <class R1, class R2>
struct Ratio_subtract : _Ratio_subtract<R1, R2>::type {};

template <class R1, class R2>
struct _Ratio_multiply {
    using type = Ratio<R1::num* R2::num, R1::den* R2::den>;
};

template <class R1, class R2>
struct Ratio_multiply : _Ratio_multiply<R1, R2>::type {};

template <class R1, class R2>
struct _Ratio_divide {
    using type = Ratio<R1::num* R2::den, R1::den* R2::num>;
};

template <class R1, class R2>
struct Ratio_divide : _Ratio_divide<R1, R2>::type {};

template <typename U, typename V, typename W>
struct Dim {
    using M = U;
    using L = V;
    using T = W;

    using type = Dim<M, L, T>;
};

template <typename U, typename V>
struct add_dim_ {
    typedef Dim<typename Ratio_add<typename U::M, typename V::M>::type,
        typename Ratio_add<typename U::L, typename V::L>::type,
        typename Ratio_add<typename U::T, typename V::T>::type>
        type;
};

template <typename U, typename V>
struct subtract_dim_ {
    typedef Dim<typename Ratio_subtract<typename U::M, typename V::M>::type,
        typename Ratio_subtract<typename U::L, typename V::L>::type,
        typename Ratio_subtract<typename U::T, typename V::T>::type>
        type;
};

template <typename T, typename D>
struct quantity {
    T q;
    using dim_type = D;

    quantity operator+(quantity<T, D> quant) {
        return quantity<T, D>(q + quant.q);
    }

    quantity operator-(quantity<T, D> quant) {
        return quantity<T, D>(q - quant.q);
    }

    template <typename D2>
    quantity<T, typename add_dim_<D, D2>::type> operator*(quantity<T, D2> quant) {
        return quantity<T, typename add_dim_<D, D2>::type>(q * quant.q);
    }

    template <typename D2>
    quantity<T, typename subtract_dim_<D, D2>::type> operator/(
        quantity<T, D2> quant) {
        return quantity<T, typename subtract_dim_<D, D2>::type>(q / quant.q);
    }

    // Scalar multiplication and division
    quantity<T, D> operator*(T scalar) { return quantity<T, D>(q * scalar); }

    quantity<T, D> operator/(T scalar) { return quantity<T, D>(q / scalar); }

    quantity(T q) : q(q) {}
};

template <typename T, typename D>
std::ostream& operator<<(std::ostream& out, const quantity<T, D>& q) {
    out << q.q << "kg^" << D::M::num / D::M::den << "m^" << D::L::num / D::L::den
        << "s^" << D::T::num / D::T::den;

    return out;
}

void dim() {
    using one = Ratio<1, 1>;
    using zero = Ratio<0, 1>;

    quantity<double, Dim<one, zero, zero>> kg(2);
    quantity<double, Dim<zero, one, zero>> meter(3);
    quantity<double, Dim<zero, zero, one>> second(1);

    // F 의 타입은 굳이 알필요 없다!
    auto F = kg * meter / (second * second);
    std::cout << "2 kg 물체를 3m/s^2 의 가속도로 밀기 위한 힘의 크기는? " << F
        << std::endl;
}

/*

이것으로 템플릿 메타프로그래밍에 대한 강좌를 마치도록 하겠습니다. 
사실 실제 현업에서 템플릿 메타 프로그래밍을 활용하는 경우는 그다지 많지 않습니다. 
왜냐하면 일단 TMP 의 특성상복잡하고, 머리를 매우 많이 써야되고, 
무엇보다도 버그가 발생하였을 때 찾는 것이 매우 힘듧니다.

*/