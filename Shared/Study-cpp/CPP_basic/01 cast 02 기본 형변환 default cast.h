#pragma once

/*

	2021 11 26

	static_cast			: 우리가 흔히 생각하는, 언어적 차원에서 지원하는 일반적인 타입 변환 일반적으로 업캐스팅

						  유도 클래스의 포인터 및 참조형 데이터를 기초 클래스의 포인터 및 참조형 데이터로 뿐만 아니라,
						  기초 클래스의 포인터 및 참조형 데이터도 유도 클래스의 포인터 및 참조형 데이터로
						  아무런 조건 없이 형 변환시켜주지만, 그에 대한 책임은 프로그래머가 져야 한다.

	dynamic_cast		: 파생 클래스 사이에서의 캐스팅
						  조건. 포인터 또는 참조이거나 void*이여야 한다.
						  조건. dynamic_cast를 사용할 자료형은 다형 클래스 형식이여야 한다.
						  컴파일 시간이 아닌 런타임에 안정성을 검사하도록 컴파일러가 바이너리 코드를 생성

	const_cast			: 객체의 상수성(const)를 없애는 타입 변환,
						  ex) const *int -> *int
						  const cast는 개체 형식에 대한 포인터, 참조, 맴버 포인터의 경우에만 가능함.

	reinterpret_cast	: 위험을 감수하고 하는 캐스팅으로 서로 관련이 없는 포인터들 사이의 캐스팅,

						  reinterpret_cast<new_type>(expression)
						  expression에 해당하는 것을 new_type으로 비트단위로 바꾸는 것 입니다.
						  조건. 포인터만 가능하다.


	https://musket-ade.tistory.com/entry/C-C-%ED%98%95-%EB%B3%80%ED%99%98-%EC%97%B0%EC%82%B0%EC%9E%90-staticcast-constcast-dynamiccast-reinterpretcast
	https://blockdmask.tistory.com/242

*/

namespace C17_default_cast
{
	// 부모 클래스
	class Parent
	{
	public:
		char parent[7] = "parent";
		// dynamic cast를 지원하기 위해서는 다형식 클래스여야한다.
		// 아닐 경우 컴파일 자체가 안된다.
		virtual ~Parent() = default;
	};
	// 자식 클래스
	class Child : public Parent // private으로 확장하는 경우
								// 형변환시 : 엑세스 할 수 없는 기본 클래스 ...으로 부터의 형변환은 허용하지 않는다.
								// 컴파일 자체가 안된다.
	{
	public:
		char child[6] = "child";
	};


	void cast_test()
	{
		Parent p;
		Child c;
		Parent* pp = &p;
		Child* pc = &c;

		//////
		// 부모에서 자식으로 형변환 (다운 캐스팅)
		// Parent -> Child

		// 정적 형변환의 경우
		// Child p_to_c_s = static_cast<Child>(p); // 형변환의 사용이 적절하지 않으므로 컴파일 자체가 안된다.

		// 동적 형변환의 경우
		// Child p_to_c_d = dynamic_cast<Child>(p); // 포인터, 참조, void*가 아니므로 컴파일 자체가 안된다.

		//////
		// 자식에서 부모로 형벼환 (업 캐스팅)
		// Child -> Parent

		// 정적 형변환의 경우
		Parent c_to_p_s = static_cast<Parent>(c);

		// 동적 형변환의 경우
		// Parent c_to_p_d = dynamic_cast<Parent>(c); // 포인터, 참조, void*가 아니므로 컴파일 자체가 안된다.

		//////
		// 부모 포인터에서 자식 포인터로 형변환 (다운 캐스팅)
		// Parent ptr -> Child ptr

		// 정적 형변환의 경우
		Child* pp_to_c_s = static_cast<Child*>(pp); // 되기는 하나 실제로 사용하면 오류를 발생시킨다. 
													//(정삭적으로 작동 할 수도 있으나, 불가능 한 것으로 생각해야함)

		// 동적 형변환의 경우
		Child* pp_to_c_d = dynamic_cast<Child*>(pp); // 캐스팅이 가능한 경우 nullptr이 아닌 값을 반환하고 불가능 하다면 nullptr을 반환한다.

		//////
		// 자식 포인터에서 부모 포인터로 형변환 (업 캐스팅)
		// Child ptr -> Parent ptr

		// 정적 형변환의 경우
		Parent* pc_to_p_s = static_cast<Parent*>(pc); // 가능

		// 동적 형변환의 경우
		Parent* pc_to_p_d = dynamic_cast<Parent*>(pc); // 가능


		//////
		// const cast

		const int const_int = 3;
		//const_cast<int>(const_int) = 3;			// const cast는 개체 형식에 대한 포인터, 참조, 맴버 포인터의 경우에만 가능함.
		(*const_cast<int*>(&const_int)) = 3;

		//////
		// reinterpret cast
		int rint = 3;
		float* prfloat = reinterpret_cast<float*>(&rint);
	}
}