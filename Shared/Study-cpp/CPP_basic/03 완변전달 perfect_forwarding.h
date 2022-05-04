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
	void universal_wrapper(T&& u) {
		g(std::forward<T>(u));
	}
	class A {};
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
		universal_wrapper(a);
		universal_wrapper(ca);
		universal_wrapper(A());
		/*
			������ ���۷��� ȣ��
			������ ��� ���۷��� ȣ��
			������ ���۷��� ȣ��
			
			���������� ������ ���۷����� �ٸ���
			template�Ǵ� auto������ �����ϴ�.

			�ް��̸� �ް� ������, �������̸� ������ ������ �Ѵ�.

			& == 1, && == 0 �϶� OR����� ����.
			&	&		1		&
			&	&&		1		&
			&&	&		1		&
			&&	&&		0		&&

			A			|	A&			->
			const A&	|	const A&	->
			A(rhs)		|	A		->

			forward�� 
		*/
		auto&& temp1 = a;
		auto&& temp2 = ca;
		auto&& temp3 = A();
	}
}