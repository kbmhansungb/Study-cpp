#pragma once

/*
	
	����
	https://docs.microsoft.com/ko-kr/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170

	[] () keyward exception-specification() -> trailing-return-type

*/
namespace c17_lambda
{
	struct S { void lambda_test(int i) ; };
	void S::lambda_test(int i)
	{
		/*
		    []          : �ƹ��͵� ĸ�� ����
		    [&a, b]     : a �� ���۷����� ĸ���ϰ� b �� (���� �Ұ�����) ���纻���� ĸ��
		    [&]         : �ܺ��� ��� �������� ���۷����� ĸ��
		    [=]         : �ܺ��� ��� �������� ���纻���� ĸ��
		    [a = 3]     : a �� 3���� �ʱ�ȭ �ϰ� ������ ����
		*/

		[&, i] {}; // ok
		//[&, &i] {}; // error &���� &i�� ���Ե�
		//[=, this] {}; // error =������ this�� ����� �� ����. this�� �̹� ����Ǿ��� ����.
		[=, *this] {}; // ok, S�� �����ؼ� ������ ����.
		//[i, i] {}; // error i�� �ߺ���
		//[this] {};
	}

	struct K { void lambda_test(int i); };
	void K::lambda_test(int i)
	{
		/*
			C++14���� �Ű� ���� ������ ���׸��� ��� Ű���带 ���� �����ڷ� ����� �� auto �ֽ��ϴ�.
			�� Ű����� �Լ� ȣ�� �����ڸ� ���ø����� ���鵵�� �����Ϸ��� �����մϴ�. �Ű� ���� ����� 
			�� auto �ν��Ͻ��� ���� ���� �Ű� ������ �����մϴ�.

			���ø�ó�� ��ȯ���Ŀ� ���� ���鵵�� ���� ����.
		*/
		auto i = [](auto a) {};
	}

	struct N { void lambda_test(int i); };
	void N::lambda_test(int i)
	{
		/*
		
		*/
		auto i = [i]() { /*i = 3;*/ }; // i�� constantó�� ����.
		auto j = [i]() mutable { i = 3; }; // mutable�� �̿��Ͽ� ĸ�� ���� ���� ������.

		/*
			lambda�� constepr�Լ�ó�� ����� �� ����.
		*/
		auto l = [i]() constexpr -> int { return 5; };
		constexpr int m = l();
	}

	struct R { void lambda_test(int i); };
	void R::lambda_test(int i)
	{
		/*

		*/
		auto j = [i]() noexcept { throw 5; }; // �Ǳ�� �ϳ� ��� ����
		//auto k = [i]() throw(int) { throw 5; }; // int�� ���� throw ��Ȯ�� ���� �ǹ����� �� �𸣰���.
	}
}