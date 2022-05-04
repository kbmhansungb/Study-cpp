#pragma once

#include <random>
#include <iostream>

/*

https://www.youtube.com/watch?v=BaEillNU3Nk
양자역학에서 발견한 시뮬레이션 우주를 보고 만들어봄.


[x, p] = ih
(위치, 운동량 = 질량*속도)

xp - px = ih <<< 가 불확정성 원리.

미분은 행렬이다아아, 
전치행렬이란 대각선을 기준으로 대칭이동 시켜준것 B, B^T
dT/dx = - d/dx 미분연산자에 어떻게 행렬연산을 할 수 있는 것인가?

운동량은 행렬이다.
[x, p] = ih

p = h/i * d/dx = mv (질량 * 속도)
i는 허수이고, h는, 6.626*10^-34kg*m^3/s 아주작은 값을 가지는 플랑크 상수 <- 증명할수없는 공리라고 한다.

10분 13초 부터,,
플랑크 상수를 f의 가장 작은 단위라고 하면, 
float의 가장 작은 단위는 FLT_MIN이다.

컴퓨터로,, 이것을 볼라면, 미분 값이 FLT_MIN만큼의 차이를 발생시킨 다는 사실을 보면 된다.

*/

void make_float_error()
{
	float h = FLT_MIN;

	// float 오류 만들기. 덧셈을
	float num1 = 0.0f;
	float num2 = 0.1f;

	// 0.1을 10번 더함
	std::cout << "오류 만들기" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		num1 = num1 + num2;
		printf("%d : %.38f\n", i, num1);
	}

	// 안되네,, 머쓱, 정확하게 만들면,, 오류가 날거 같기는 한데, 준비해야 할게 많아보임.
	std::cout << "테스트" << std::endl;
	for(float i = 0; i < 1; i += 0.1f)
	{
		float x = (float)rand();
		float p = (float)rand();
		float error = (0.0f + i) - (0.0f + i);
			//( x * ( p * ( i + i ) ) ) - ( ( p * ( i + i ) ) * x );

		printf("%.38f\n", error);
	}
}