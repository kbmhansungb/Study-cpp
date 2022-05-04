#pragma once

/*
	
	람다
	https://docs.microsoft.com/ko-kr/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170

	[] () keyward exception-specification() -> trailing-return-type

*/
namespace c17_lambda
{
	struct S { void lambda_test(int i) ; };
	void S::lambda_test(int i)
	{
		/*
		    []          : 아무것도 캡쳐 안함
		    [&a, b]     : a 는 레퍼런스로 캡쳐하고 b 는 (변경 불가능한) 복사본으로 캡쳐
		    [&]         : 외부의 모든 변수들을 레퍼런스로 캡쳐
		    [=]         : 외부의 모든 변수들을 복사본으로 캡쳐
		    [a = 3]     : a 를 3으로 초기화 하고 갈무리 저장
		*/

		[&, i] {}; // ok
		//[&, &i] {}; // error &에는 &i가 포함돔
		//[=, this] {}; // error =에서는 this를 사용할 수 없음. this가 이미 복사되었기 때문.
		[=, *this] {}; // ok, S를 복사해서 보내는 것임.
		//[i, i] {}; // error i가 중복됨
		//[this] {};
	}

	struct K { void lambda_test(int i); };
	void K::lambda_test(int i)
	{
		/*
			C++14에서 매개 변수 형식이 제네릭인 경우 키워드를 형식 지정자로 사용할 수 auto 있습니다.
			이 키워드는 함수 호출 연산자를 템플릿으로 만들도록 컴파일러에 지시합니다. 매개 변수 목록의 
			각 auto 인스턴스는 고유 형식 매개 변수와 동일합니다.

			템플릿처럼 반환형식에 따라 만들도록 지시 가능.
		*/
		auto i = [](auto a) {};
	}

	struct N { void lambda_test(int i); };
	void N::lambda_test(int i)
	{
		/*
		
		*/
		auto i = [i]() { /*i = 3;*/ }; // i는 constant처럼 사용됨.
		auto j = [i]() mutable { i = 3; }; // mutable을 이용하여 캡쳐 절을 변경 가능함.

		/*
			lambda를 constepr함수처럼 사용할 수 있음.
		*/
		auto l = [i]() constexpr -> int { return 5; };
		constexpr int m = l();
	}

	struct R { void lambda_test(int i); };
	void R::lambda_test(int i)
	{
		/*

		*/
		auto j = [i]() noexcept { throw 5; }; // 되기는 하나 경고 생성
		//auto k = [i]() throw(int) { throw 5; }; // int형 오류 throw 정확히 무슨 의미인지 잘 모르겠음.
	}
}