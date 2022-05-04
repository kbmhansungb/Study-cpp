#pragma once

/*
https://ko.wikipedia.org/wiki/%EC%A7%81%EB%A0%AC%ED%99%94
����ȭ�� ������ ������ ������Ʈ ���¸� -> ����, ��Ʈ��ũ ��ũ �� ���� �ϱ� ���� �������� ��ȯ�ϴ� ����.

�ݴ��� ��� ������ȭ (deserialization) �̶�� �Ѵ�.
https://itprogramming119.tistory.com/entry/Jquery-serialize-%EC%A7%81%EB%A0%AC%ED%99%94-%EB%B0%A9%EB%B2%95

���� ���ϴ°� c++���� c#��ŭ�� �ƴϿ��� ����ϰ� ����ȭ �ϴ� ����̴�.

���ø� ��Ÿ ���α׷���,
https://stackoverflow.com/questions/5623910/compile-time-counter-for-template-classes?rq=1
���ø� �ν��Ͻ�ȭ ���� ���ϴ� ����ε� �̰���.
https://www.thecodingforums.com/threads/calculate-number-of-template-instantiations.755092/

���ø��� Ư��ȭ�� ���� ���� �ȿ����� ������.
*/

/*
	*** ���� �ڵ� ***

	���ϴ� ��.
	class Parent : public serialize<Parent>
	{
		using serialize<Parent>::Field;
	}
*/
// ����ȭ���� Ÿ���� �� �ʿ䰡 �ֳ�?
// �޸� ��ġ��, ����Ʈ �ּҸ� �˸� �ȴ�.
// ������ Ÿ�ӿ� �۵��ϵ��� ������� �ߴµ�, ������ ������ڴپ�.

#include "serialize1.h"


// �̰��� ���� ���� ������ �� �ִ� �ּ��� ����̴�.
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