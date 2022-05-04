#pragma once
/*
	
	기본 갈무리 모드 (default capture mode)는 두 가지로,
	하나는 참조에 의한 갈무리 모드 이고,
	또 하나는 값에 의한 갈무리 모드 이다.

*/

#include <vector>
#include <functional>
#include <algorithm>

class test_class
{
public:
	using FilterContainer = std::vector<std::function<bool(int)>>;
	FilterContainer filters;

	test_class()
	{
		filters.emplace_back(
			[](int value) { return value % 5 == 0; }
		);

		// divisor를 실행시점에서 계산해야 된다면

		int divisor = 3;
		filters.emplace_back(
			[&](int value) { return value % divisor == 0; }
			// ??? 이게 컴파일이 되네,
		);
		// 대상에 대한 참조를 잃을 수 있음.
		// 미정의 행동을 유발함.

		filters.emplace_back(
			[&divisor](int value) { return value % divisor == 0; }
		);
		// 이것도 위와 마찬가지인 결과를 가져옴.

		if (std::all_of(
			filters.begin(), filters.end(),
			[&](int value) { return value % divisor == 0; }
		))
		{
			// ...
		}
		// filters가 전부 위와 같은 경우에만 실행하도록 할 수 있으나,
		// 이를 사용하는 프로그래머가 divisor을 이용하는 람다를 추가하는 것으로 이해하고,
		// divisor레퍼런스가 소멸된 메서드를 입력할 가능성이 있다.

		filters.emplace_back(
			[=](int value) { return value % divisor == 0; }
		);
		// 이렇게 하면 divisor를 복사해서 저장하기에 대상을 잃지는 않으나,
		// 포인터의 경우 소실될 가능성이 있다.
	}
};

class test_class2
{
public:
	using FilterContainer = std::vector<std::function<bool(int)>>;
	FilterContainer filters;

	int divisor = 0;

	test_class2()
	{
		filters.emplace_back(
			[=](int value) { return value % divisor; }
		);
		// >>> 컴파일되면
		auto currentObjectPtr = this;
		filters.emplace_back(
			[currentObjectPtr](int value)
			{return value % currentObjectPtr->divisor; }
		);
		// 이런식으로 전달하게 된다.
		// 인스턴스 생성 후 ptr을 필터를 등록하고, 인스턴스를 제거하면 대상을 잃은 생 포인터가 존재하게 된다.
		
		// 복사해서 전달하면 이러한 문제는 해결 할 수 있다.
		auto divisor_copy = divisor;
		filters.emplace_back(
			[divisor_copy](int value)
			{ return value % divisor_copy == 0; }
		);
		// c++ 14에는 좀더 나은 방법이 있다.
		filters.emplace_back(
			[divisor = divisor](int value)
			{ return value % divisor == 0; }
		);
	}

	void add_divisor_filter()
	{
		static int divisor = 1;

		filters.emplace_back(
			[=](int value)
			{ return value % divisor == 0; }
		);

		++divisor;

		// 이렇게 작성하면 필터가 추가될 때 마다 모든 divisor들이 증가하는 결과를 가져온다.
		// 왜인가?
		// 컴파일 되면 다음과 같은 결과를 가져오기 때문이다.
		auto copy_ptr = this;
		filters.emplace_back(
			[copy_ptr](int value)
			{ return value % divisor == 0; } // divisor는 함수의 static 변수를 가르킨다.
		);

		// 람다는 조심해서 사용해야 한다.
	}
};