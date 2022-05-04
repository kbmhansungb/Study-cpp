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
		S(const S& rhs) { /*���� ������*/ };
		S(S&& rhs) { /*�̵� ������*/ };
	};

	struct test_struct
	{
		std::string str;
		test_struct(const std::string& s) : str(s)
		{
			std::cout << "�⺻ ������" << std::endl;
		}
		test_struct(const test_struct& rhs)
		{
			std::cout << "���� ������" << std::endl;
			str = rhs.str;
		}
		test_struct(test_struct&& rhs) noexcept
		{
			std::cout << "�̵� ������" << std::endl;
			str.swap(rhs.str);
		}

		void swap(test_struct& b)
		{
			std::cout << "���ڿ��� ������" << std::endl;
			std::string temp = this->str;
			str = b.str;
			b.str = temp;
		}
		void move_swap(test_struct& b)
		{
			std::cout << "���ڿ��� ref�� �ٲ�" << std::endl;
			std::string temp = std::move(this->str);
			str = b.str;
			b.str = temp;
		}
	};

	void move_forward_test()
	{
		/*
			l-value		: ���ʰ� ������ �Ѵ� �� �� �ִ�.
			r-value		: �����ʸ� �����ϴ�.
		*/


		// C++11 ���� �������� ���������� �ٲپ��ִ� move�Լ��� ����
		// move�� ��� �ϵ� �����ʰ� ����ȯ�� �����Ѵ�.
		// �� ��� ����Ʈ�ڵ嵵 ���굵 �������� �ʴ´�.

		int a = 3;					// �������� 3�̶�� ���ͷ��� �Ҵ��ߴ�.
		int&& b = std::move(a);		// std::move�� ���Ͽ� �������� ���������� ��ȯ�ؼ� ��ȯ

		auto lambda = []() { return 1; };
		int&& c = lambda();			// �̷��� rhs�� �������� �������� �ʰ�, ������ �����ų �� �ִ�.

		/*
		
			�̵������ڰ� �ݵ�� ������ �ƴ϶�� ���� �������.
			
			1. ������� ���ο� ������ �ȿ� �����Ҵ� �� ���縦 ���� �ʰ�,
			������ �ȿ� ���۷����� �ű�� ���� �۾����� �����ϵ���
			����ȭ �߱� ������ ����.
			
		*/

		{
			std::cout << "test_struct s;" << std::endl;
			std::cout << "test_struct new_s = construct_only_copy(s);" << std::endl;
			test_struct s("string");
			test_struct other("other");
			
			s.swap(other);
			s.move_swap(other);

			/*
			
				�����Ͽ� �ű�� ��� �ӽ÷� ���ڿ��� ������ ��ü�� �����ϰ� ������
				�ܼ��ϰ� �ű�� �����̶��, ���ڿ��� ����Ű�� �����͸� �ű�� ������ ����ȭ�� �����ϴ�.

				�ٸ� �̷��� �����͸� �ű�� ������� ���� ��ġ �ʴ� ������ �߻� �� �� �ִ�.
			
				�̵������ڳ� �̵� ���� �����ڸ� ȣ���� �� �̵��� ����Ǵ� ������
				std::move�� ȣ���Ѵٰ� �̵��� �Ǵ� ���� �ƴϴ�.

			*/
		}
	}


	template <typename T>
	void wrapper(T u) {
		g(u);
	}
	template <typename T>
	void ref_wrapper(T& u) {
		g(u);
	}
	template <typename T>
	void universal_wrapper(T&& u) {
		g(u);
	}
	template <typename T>
	void perfect_wrapper(T&& u) {
		g(std::forward<T>(u));
	}
	struct A { int a; };
	void g(A& a)		{ std::cout << "������ ���۷��� ȣ��" << std::endl; }
	void g(const A& a)	{ std::cout << "������ ��� ���۷��� ȣ��" << std::endl; }
	void g(A&& a)		{ std::cout << "������ ���۷��� ȣ��" << std::endl; }
	void perfect_forwarding() 
	{
		A a;
		const A ca;
		std::cout << "���� --------" << std::endl;
		g(a);
		g(ca);
		g(A());
		A&& rra = A();
		rra.a = 3; // ���� �ٲ� �� ����. ������������ ������ ó�� ó���Ǵ� ������ �ִٰ� ��.
		g(rra);
		std::cout << "Wrapper -----" << std::endl;
		wrapper(a);
		wrapper(ca);
		wrapper(A());
		/*
			���� --------
			������ ���۷��� ȣ��
			������ ��� ���۷��� ȣ��
			������ ���۷��� ȣ��
			Wrapper -----
			������ ���۷��� ȣ��
			������ ���۷��� ȣ��
			������ ���۷��� ȣ��

			���� ��� ���� ���������� �޵��� ����Ǿ���.
			��°�� �ΰ�?
			���ø� ���� T�� ���۷����� �ƴ� �Ϲ����� Ÿ���̶�� const�� �����Ѵ�.
			�� T �� ���� �� class A �� �߷е˴ϴ�.
			���� �� �� ��� ���� �� ������ ���۷����� ȣ���ϴ� g �� ȣ���Ͽ����ϴ�.

			�׷��ٰ� warp�� &�����ڸ� ���̸� A()�� ��� ������ �߻��Ѵ�.
			�̸� �ذ��ϱ� ����,

			T&, constT&�� ��� ��츦 ������ ������ ���ŷο� ���̴�.
			���ڰ� 2���� �Ѿ�� 4���� ����� ���� �����.

			�̸� �ذ��ϱ� ���� ��������(universal reference)�� Ȱ���Ѵ�.
		*/

		std::cout << "ref Wrapper -----" << std::endl;
		ref_wrapper(a);
		ref_wrapper(ca);
		//ref_wrapper(A()); error

		std::cout << "universal Wrapper -----" << std::endl;
		universal_wrapper(a);
		universal_wrapper(ca);
		universal_wrapper(A());

		std::cout << "perfect Wrapper -----" << std::endl;
		perfect_wrapper(a);
		perfect_wrapper(ca);
		perfect_wrapper(A()); // �ܼ��ϰ� A�� �߷еȴ�. ����?
		/*
			������ ���۷��� ȣ��
			������ ��� ���۷��� ȣ��
			������ ���۷��� ȣ��
			
			���������� ������ ���۷����� �ٸ���
			template�Ǵ� auto������ �����ϴ�.

			�ް��̸� �ް� ������, �������̸� ������ ������ �Ѵ�.
			C++ 11 ������ ������ ���� ���۷��� ��ħ ��Ģ (reference collapsing rule) �� ���� T �� Ÿ���� �߷�
			& == 1, && == 0 �϶� OR����� ����.
			&	&		1		&
			&	&&		1		&
			&&	&		1		&
			&&	&&		0		&&

			���ø�Ÿ��		|	����Ÿ��	|	�߷�����	|	��������				|	������ ���
			T				|	A(lv)		|	A			|	A						|	ok : �ٸ� �Ź� ���簡 �̷����
			T				|	const A		|	A			|	A						|	ok : ���ø������� �����ڰ� �ƴ� ��� const�Ӽ��� ���õ�.
			T				|	A(rv)		|	A			|	A						|	ok

			T&				|	A(lv)		|	A			|	A&						|	ok
			T&				|	const A		|	const A		|	const A&				|	ok
			T&				|	A(rv)		|	A			|	A&						|	error : rv�� lv ref�� ������ �� ����.
			
			T&&				|	A(lv)		|	A&			|	A& &&			A&		|	ok
			T&&				|	const A		|	const A&	|	const A& &&		A&		|	ok
			T&&				|	A(rv)		|	A			|	A&&						|	ok : ����Ե�, ������ ������ ��������� ������ ���۷����� ȣ���Ѵ�. �������� ���������� ó���ȴ�.
																								 1) & && -> & �����ΰ��� ����Ȯ��. 
																								 2) ������ ������ �������̱� �������� ����Ȯ��


			���� �������� ��� �������� �����ϱ� ���ؼ��� std::forward�� �������� �Ѵ�.

			// �ϴ� ��Ȯ�� ���ظ� ���ϰڴ�. �������� �ܿ쵵�� ����.

			struct remove_reference {
			    using type                 = A;
			    using _Const_thru_ref_type = const A;
			};
			using remove_reference_t = typename remove_reference<A>::type;

			A&& forward(remove_reference_t<A>& a) noexcept { return static_cast<A>(a); }
		*/
		auto&& ra = a;
		auto&& f_r1 = std::forward<A&>(ra);		// & ra -> && & ra	-> & ra
		auto&& f_r3 = std::forward<A>(rra);		// rra	-> && rra	-> && rra

		//auto&& f_r2 = std::forward<A&>(ra);		// & ra -> & ra	-> && & ra -> & ra
		//auto&& f_r4 = std::forward<A&>(rra);
	}
}