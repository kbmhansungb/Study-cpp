#pragma once

/*

	2021 11 26

	�Ͻ��� ����ȯ		: �ڵ������� ĳ���� �Ǵ� ��
	(�ڵ��� ����ȯ)

	����� ����ȯ		: ���α׷��Ӱ� ����ȯ�� ���� ��Ÿ�� ��.
	(���� ����ȯ)
						  ex) (type)value
						  �������� ��� ��� Ÿ�Կ� ���� �������� ����ȯ�� ������.

	https://killu.tistory.com/24
*/
#include <cstdio>
namespace C17_implicit_explicit_cast
{
	void cast_test()
	{
		// �Ͻ��� ����ȯ implicit cast

		char c = 0;
		short s = 0;
		int i = 0;
		long l = 0;
		float f = 0;
		double d = 0;
		unsigned int ui = 0;

		int long_to_int = l;		// int������ �ɽ��� ��.
		
		auto i_op_l = i + l;		// ��Ÿ���� �ִ� ������ ��ū Ÿ������ ĳ���� ��.
		auto l_op_i = l + i;

		auto ui_op_i = ui + i;		// Ÿ�԰� unsigned Ÿ���� ��� unsigned Ÿ������ ĳ���� ��.
		auto i_op_ui = i + ui;

		auto l_op_f = l + f;		// ������ �Ǽ��� ��� �Ǽ��� �켱���� ĳ������.
		auto f_op_l = f + l;

		auto ui_op_f = ui + f;		// ���� ������ unsigned Ÿ�԰� �Ǽ��� ��� �Ǽ��� �켱���� ĳ������.
		auto f_op_ui = f + ui;

		int by_l = l;				// ������� ��� ������ Ÿ���� �ٸ� ��� ���� ������ Ÿ������ ����ȯ��

		short num1 = 10, num2 = 20; // ������ �°�(Integral Promotion)'�� ���� �ڵ� �� ��ȯ
		auto num_add = num1 + num2; // int�� ũ�⺸�� ���� �ڷ����� ��� CPU�� ����ϱ� ���� int������ ����ȯ ��.

		// ����� ����ȯ explicit cast

		auto int_by_l = (int)l; // l�� i�� ����� ����ȯ��

		// �������� ��� ��� Ÿ�Կ� ���� �������� ����ȯ�� ������.
		// ���� ����.
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
		// �ڷ����� ĳ����

		int a = 0;
		Cast_struct A;
		
		A = (Cast_struct)a; // �����ڸ� �̿��Ͽ� ����ȯ��.
							// �����ڰ� ����, ����ȯ�� ������� ������ ĳ���� ��ü�� ���� ����.

		Empty_struct* p_es;
		p_es = (Empty_struct*)(&a);	// �������� ��� ��������ȯ�� ������.
									// � Ÿ�����ε� ĳ��Ʈ�� ���������� �������� ���������� ����.

		Cast_struct B;
		B = (Cast_struct)a + 3;		// �������� ������ operator�� ���� �̷����.

	}
}