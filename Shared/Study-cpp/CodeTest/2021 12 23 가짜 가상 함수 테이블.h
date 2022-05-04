#pragma once

//struct Func1
//{
//	void (Func1::*func)() = nullptr;
//};
//
//struct FuncA1 : public Func1 {};
//struct FuncB1 : public Func1 {};
//
//struct Derived1 :
//	public FuncA1,
//	public FuncB1
//{};
//
//constexpr auto size11 = sizeof(Func1);
//constexpr auto size12 = sizeof(FuncA1);
//constexpr auto size13 = sizeof(FuncB1);
//constexpr auto size14 = sizeof(Derived1);


struct Func2
{
	virtual void func() = 0;
};

struct FuncA2 : public Func2 {};
struct FuncB2 : public Func2 {};

struct Derived2 :
	public FuncA2,
	public FuncB2
{
	virtual void func() override
	{
	}
	//virtual void FuncB2::func() override
	//{
	//}
};

constexpr auto size21 = sizeof(Func2);
constexpr auto size22 = sizeof(FuncA2);
constexpr auto size23 = sizeof(FuncB2);
constexpr auto size24 = sizeof(Derived2);

int main()
{
	Derived2 d2;
}