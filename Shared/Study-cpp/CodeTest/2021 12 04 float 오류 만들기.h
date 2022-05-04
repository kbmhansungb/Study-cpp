#pragma once

#include <random>
#include <iostream>

/*

https://www.youtube.com/watch?v=BaEillNU3Nk
���ڿ��п��� �߰��� �ùķ��̼� ���ָ� ���� ����.


[x, p] = ih
(��ġ, ��� = ����*�ӵ�)

xp - px = ih <<< �� ��Ȯ���� ����.

�̺��� ����̴پƾ�, 
��ġ����̶� �밢���� �������� ��Ī�̵� �����ذ� B, B^T
dT/dx = - d/dx �̺п����ڿ� ��� ��Ŀ����� �� �� �ִ� ���ΰ�?

����� ����̴�.
[x, p] = ih

p = h/i * d/dx = mv (���� * �ӵ�)
i�� ����̰�, h��, 6.626*10^-34kg*m^3/s �������� ���� ������ �ö�ũ ��� <- �����Ҽ����� ������� �Ѵ�.

10�� 13�� ����,,
�ö�ũ ����� f�� ���� ���� ������� �ϸ�, 
float�� ���� ���� ������ FLT_MIN�̴�.

��ǻ�ͷ�,, �̰��� �����, �̺� ���� FLT_MIN��ŭ�� ���̸� �߻���Ų �ٴ� ����� ���� �ȴ�.

*/

void make_float_error()
{
	float h = FLT_MIN;

	// float ���� �����. ������
	float num1 = 0.0f;
	float num2 = 0.1f;

	// 0.1�� 10�� ����
	std::cout << "���� �����" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		num1 = num1 + num2;
		printf("%d : %.38f\n", i, num1);
	}

	// �ȵǳ�,, �Ӿ�, ��Ȯ�ϰ� �����,, ������ ���� ����� �ѵ�, �غ��ؾ� �Ұ� ���ƺ���.
	std::cout << "�׽�Ʈ" << std::endl;
	for(float i = 0; i < 1; i += 0.1f)
	{
		float x = (float)rand();
		float p = (float)rand();
		float error = (0.0f + i) - (0.0f + i);
			//( x * ( p * ( i + i ) ) ) - ( ( p * ( i + i ) ) * x );

		printf("%.38f\n", error);
	}
}