
#include <iostream>

#include "ptr.h"
#include <memory>

struct construct
{
	int a;
	construct()
	{
		std::cout << "shared_ptr 생성자가 호출됨" << std::endl;
	}
	~construct()
	{
		std::cout << "shared_ptr 소멸자가 호출됨" << std::endl;
	}
};
struct construct2 : public lstd::use_safe_ptr<construct2>
{
	int a;
	construct2()
	{
		std::cout << "safe_ptr 생성자가 호출됨" << std::endl;
	}
	~construct2()
	{
		std::cout << "safe_ptr 소멸자가 호출됨" << std::endl;
	}
};

int main()
{
	std::cout << "shared, weak test" << std::endl;
	construct* row_ptr_construct = nullptr;
	construct2* row_ptr_construct2 = nullptr;
	std::cout << "스텍1" << std::endl;
	{
		std::cout << "스텍2 : 참조를 생성함." << std::endl; {
			std::weak_ptr<construct> weak_ptr;
			lstd::safe_ptr<construct2> safe_ptr;
			std::cout << "스텍3 : 메모리를 할당함." << std::endl; {
				std::shared_ptr<construct> shared_ptr = std::make_shared<construct>(); shared_ptr->a = 3;
				construct2 use_safe_ptr; use_safe_ptr.a = 3;
				safe_ptr = use_safe_ptr.get_safe_ptr();
				weak_ptr = shared_ptr;
				row_ptr_construct = shared_ptr.get();
				row_ptr_construct2 = &use_safe_ptr;
				std::cout << "construct : " << row_ptr_construct->a << ", construct2 : " << row_ptr_construct2->a << std::endl;
			} std::cout << "스텍3 종료" << std::endl;
			std::cout << "construct : " << row_ptr_construct->a << ", construct2 : " << row_ptr_construct2->a << std::endl;
		} std::cout << "스텍2 종료" << std::endl;
		std::cout << "weak ptr의 참조까지 사라지면, 특이한 값을 반환한다." << std::endl;
		std::cout << "construct : " << row_ptr_construct->a << ", construct2 : " << row_ptr_construct2->a << std::endl;
	} std::cout << "스텍1 종료" << std::endl;

	int a = 3;
	int* a_ptr = &a;
	memset(&a, 0, sizeof(int));

	constexpr size_t shared_size = sizeof(std::shared_ptr<construct>);
	constexpr size_t weak_size = sizeof(std::weak_ptr<construct>);
	constexpr size_t safe_ptr = sizeof(lstd::safe_ptr<construct2>);
}

/*

	shared, weak test
	스텍1
	스텍2 : 참조를 생성함.
	스텍3 : 메모리를 할당함.
	shared_ptr 생성자가 호출됨
	safe_ptr 생성자가 호출됨
	construct : 3, construct2 : 3
	safe_ptr 소멸자가 호출됨
	shared_ptr 소멸자가 호출됨
	스텍3 종료
	construct : 3, construct2 : 3
	스텍2 종료
	weak ptr의 참조까지 사라지면, 특이한 값을 반환한다.
	construct : -572662307, construct2 : 3
	스텍1 종료
	
	D:\VisualStudio\CodeTest\CodeTest\Debug\Lib.exe(프로세스 18260개)이(가) 종료되었습니다(코드: 0개).
	디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.
	이 창을 닫으려면 아무 키나 누르세요...

*/