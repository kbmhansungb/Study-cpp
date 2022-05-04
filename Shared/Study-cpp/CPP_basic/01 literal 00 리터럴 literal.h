#pragma once

/*
	2021 11 27
	literal
		literal constant : �ڵ忡 ���� ���Ե� ��, �� ���� ������ �� �����Ƿ� ����̴�.

		unsigned int			:	u(U)
		long					:	l(L)
		unsigned long			:	ul(uL, Ul, UL, lu, lU, Lu, LU)
		long long				:	ll(LL)
		unsinged long long		:	ull(uLL, Ull, ULL, llum llUm LLu, LLU)
		float					:	f(F)
		double					:	l(L)
	
		char					:	'a'
		const char*				:	"abs"
		
		base10(decimal)			:	0, 1, 2, ...
		base2(binary)			:	0b0, 0b1, 0b10, ....
		base8(octal)			:	00, 01, 02, ... 07, 010, ...
		base16(hexadecimal)		:	0x0, 0x1, 0x2, ... 0xF, 0x10, ...

	���ͷ� ������ �������̵�
*/
namespace c17_literal
{
	// literal constant
	bool Bool = true;
	int x = 3;

	float f = 3.14f; // float literal

	double pi = 3.141592; // double literal
	double avogadro = 6.02e23; // 6.02 x 10^23

	// ���ڿ� ���ڿ� ���ͷ�
	char c = 'c';
	auto cs = "abs";

	// ���� ���ͷ�
	int binary = 0b10; // 0b0 0b1 0b10 0b11 0b100
	int decimal = 10;
	int octal = 010;	// 00, 
	int hexadecimal = 0x10;   // 
}
