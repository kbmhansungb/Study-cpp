#pragma once
#include <iostream>
#include <memory>
#include <mutex>

class Widget
{
public:
};

int f1(std::shared_ptr<Widget> spw)
{

}
double f2(std::unique_ptr<Widget> upw)
{

}
bool f3(Widget* pw)
{

}

template <
	typename FuncType,
	typename MuxType,
	typename PtrType>
	//	auto lockAndCall(FuncType func, MuxType& mutex, PtrType ptr) -> decltype(func(ptr))
	//{
	//	using MuxGuard = std::lock_guard<MuxType>;
	//
	//	MuxGuard g(mutex);
	//	return func(ptr);
	//}
	decltype(auto) lockAndCall(FuncType func, MuxType& mutex, PtrType ptr)
{
	using MuxGuard = std::lock_guard<MuxType>;

	MuxGuard g(mutex);
	return func(ptr);
}

int main()
{
	std::mutex f1m, f2m, f3m; //f1, f2, f3�� ���ؽ�

	using MuxGuard = std::lock_guard<std::mutex>;

	{
		MuxGuard g(f1m);
		auto result = f1(0);
	}
	// ...
	// �̷��� �ۼ��ϸ� ���ؽ��� Ǫ�� ������ �ݺ��ϰ� �ȴ�.
	// �ҽ� �ڵ� �ߺ��� ���̱� ���ؼ�
	// 
	//lockAndCall(f0, f1m, 0);		// ���ø����� �� ����� ������ �μ������ ã�� ���ؼ� ������ ���� �ʴ´�.
	//lockAndCall(f1, f2m, NULL);
	lockAndCall(f2, f3m, nullptr);
}