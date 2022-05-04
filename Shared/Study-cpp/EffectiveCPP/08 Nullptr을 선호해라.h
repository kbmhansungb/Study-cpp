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
	std::mutex f1m, f2m, f3m; //f1, f2, f3용 뮤텍스

	using MuxGuard = std::lock_guard<std::mutex>;

	{
		MuxGuard g(f1m);
		auto result = f1(0);
	}
	// ...
	// 이렇게 작성하면 뮤텍스를 푸는 패턴을 반복하게 된다.
	// 소스 코드 중복을 줄이기 위해서
	// 
	//lockAndCall(f0, f1m, 0);		// 템플릿에서 이 방식은 적절한 인수목록을 찾지 못해서 컴파일 되지 않는다.
	//lockAndCall(f1, f2m, NULL);
	lockAndCall(f2, f3m, nullptr);
}