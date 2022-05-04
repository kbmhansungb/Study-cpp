#pragma once

/*

	2021 11 26

	// 개념적인 의미
	cross cast (side cast)	: Left -> Right, 또는 반대의 상황에서 dynamic_cast를 하는 경우를 말함.
							  크로스캐스트는 reinterpret_cast또는 static_cast가 아닌 dynamic_cast에서만 작동

							  최상위 부모 클래스의 상속이 전부 virtual면 다이아몬드 상황에서도 바로 최상위 부모 클래스로 캐스트 가능함.
	https://stackoverflow.com/questions/35959921/what-is-side-cast-or-cross-cast-in-dynamic-cast-in-c/51669399

*/

namespace C17_cross_cast
{
	class Parent
	{
	public:
		virtual ~Parent() {}
		char parent[7] = { "parent" };
	};
	class Left : public Parent
	{
	public:
		char left[5] = { "left" };
	};
	class Right : public Parent
	{
	public:
		char right[6] = { "right" };
	};
	/// <summary>
	/// 다이아몬드 상속의 상황에서
	/// </summary>
	class Child : public Left, public Right
	{
		char child[6] = { "child" };
	};
	class Right2
	{
	public:
		virtual ~Right2() {}
		char right[6] = { "right" };
	};
	/// <summary>
	/// 중복없는 다중상속 상황에서
	/// </summary>
	class Child2 : public Left, public Right2
	{
		char child[6] = { "child" };
	};

	void cross_cast_test()
	{
		// 중복없는 다중 상속 상황에서
		{
			Child2 child;
			Child2* p_child = &child;
			Parent* p_parent_by_child = dynamic_cast<Parent*>(p_child);

			Left* p_left = dynamic_cast<Left*>(p_child);
			Parent* p_parent_by_left = dynamic_cast<Parent*>(p_left);

			Right2* p_right = dynamic_cast<Right2*>(p_child);

			// cross cast
			Right2* p_right_by_left = dynamic_cast<Right2*>(p_left);
			Left* p_left_by_right = dynamic_cast<Left*>(p_right);
			// 문제없이 cross cast가 작동한다.
		}

		// 다이아몬드 상속 상황에서
		{
			Child child;
			Child* p_child = &child;
			// Parent* p_parent_by_child = dynamic_cast<Parent*>(p_child); // Parent가 두개기 때문에 모호하다는 이유로 컴파일 자체가 불가능하다.
																		   // Parent로 캐스팅 하기 위해서는 Left와 Right중 하나를 골라야 한다.
			Left* p_left = dynamic_cast<Left*>(p_child);
			Parent* p_parent_by_left = dynamic_cast<Parent*>(p_left);

			Right* p_right = dynamic_cast<Right*>(p_child);
			Parent* p_parent_by_right = dynamic_cast<Parent*>(p_right);

			// cross cast
			Right* p_right_by_left = dynamic_cast<Right*>(p_left);
			Right* p_right_by_left_parent = dynamic_cast<Right*>(p_parent_by_left);
			Left* p_left_by_right = dynamic_cast<Left*>(p_right);
			Left* p_left_by_right_parent = dynamic_cast<Left*>(p_parent_by_right);
			// 문제없이 cross cast가 작동한다.
		}
	}
}