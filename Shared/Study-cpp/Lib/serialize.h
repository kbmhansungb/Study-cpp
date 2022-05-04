#pragma once

/*
https://ko.wikipedia.org/wiki/%EC%A7%81%EB%A0%AC%ED%99%94
직렬화란 데이터 구조나 오브젝트 상태를 -> 버퍼, 네트워크 링크 간 전송 하기 위한 포맷으로 변환하는 과정.

반대의 경우 역직렬화 (deserialization) 이라고 한다.
https://itprogramming119.tistory.com/entry/Jquery-serialize-%EC%A7%81%EB%A0%AC%ED%99%94-%EB%B0%A9%EB%B2%95

내가 원하는건 c++에서 c#만큼은 아니여도 비슷하게 직렬화 하는 방법이다.

템플릿 메타 프로그래밍,
https://stackoverflow.com/questions/5623910/compile-time-counter-for-template-classes?rq=1
템플릿 인스턴스화 수를 구하는 방법인데 이것은.
https://www.thecodingforums.com/threads/calculate-number-of-template-instantiations.755092/

템플릿의 특수화는 같은 공간 안에서만 가능함.
*/

/*
	*** 예제 코드 ***

	원하는 폼.
	class Parent : public serialize<Parent>
	{
		using serialize<Parent>::Field;
	}
*/
// 직렬화에서 타입을 알 필요가 있나?
// 메모리 위치랑, 바이트 주소만 알면 된다.
// 컴파일 타임에 작동하도록 만들려고 했는데, 도저히 못만들겠다아.

#include "serialize1.h"


// 이것이 현재 내가 생각할 수 있는 최선의 방법이다.
#include <string>
#include <algorithm>
void test()
{
	std::string s;
}

class Parent
{
	int a;

	template <typename Stream>
	void sequence(Stream& stream)
	{
		stream.sequence(a);
	}

	virtual void save()
	{
		// call sequcne
	}
};
class TestClass : public Parent
{
	int a;
	int b;
	float c;

	template <typename Stream>
	void sequence(Stream& stream)
	{
		Parent::sequence(stream);

		stream.sequence(a);
		stream.sequence(b);
		stream.sequence(c);
	}

	virtual void save() override
	{
		// call sequence
	}
};