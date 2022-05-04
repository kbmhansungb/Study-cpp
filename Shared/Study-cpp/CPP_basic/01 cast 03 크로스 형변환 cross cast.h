#pragma once

/*

	2021 11 26

	// �������� �ǹ�
	cross cast (side cast)	: Left -> Right, �Ǵ� �ݴ��� ��Ȳ���� dynamic_cast�� �ϴ� ��츦 ����.
							  ũ�ν�ĳ��Ʈ�� reinterpret_cast�Ǵ� static_cast�� �ƴ� dynamic_cast������ �۵�

							  �ֻ��� �θ� Ŭ������ ����� ���� virtual�� ���̾Ƹ�� ��Ȳ������ �ٷ� �ֻ��� �θ� Ŭ������ ĳ��Ʈ ������.
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
	/// ���̾Ƹ�� ����� ��Ȳ����
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
	/// �ߺ����� ���߻�� ��Ȳ����
	/// </summary>
	class Child2 : public Left, public Right2
	{
		char child[6] = { "child" };
	};

	void cross_cast_test()
	{
		// �ߺ����� ���� ��� ��Ȳ����
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
			// �������� cross cast�� �۵��Ѵ�.
		}

		// ���̾Ƹ�� ��� ��Ȳ����
		{
			Child child;
			Child* p_child = &child;
			// Parent* p_parent_by_child = dynamic_cast<Parent*>(p_child); // Parent�� �ΰ��� ������ ��ȣ�ϴٴ� ������ ������ ��ü�� �Ұ����ϴ�.
																		   // Parent�� ĳ���� �ϱ� ���ؼ��� Left�� Right�� �ϳ��� ���� �Ѵ�.
			Left* p_left = dynamic_cast<Left*>(p_child);
			Parent* p_parent_by_left = dynamic_cast<Parent*>(p_left);

			Right* p_right = dynamic_cast<Right*>(p_child);
			Parent* p_parent_by_right = dynamic_cast<Parent*>(p_right);

			// cross cast
			Right* p_right_by_left = dynamic_cast<Right*>(p_left);
			Right* p_right_by_left_parent = dynamic_cast<Right*>(p_parent_by_left);
			Left* p_left_by_right = dynamic_cast<Left*>(p_right);
			Left* p_left_by_right_parent = dynamic_cast<Left*>(p_parent_by_right);
			// �������� cross cast�� �۵��Ѵ�.
		}
	}
}