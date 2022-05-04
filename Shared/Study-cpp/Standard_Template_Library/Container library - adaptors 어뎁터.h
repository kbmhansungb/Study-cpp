#pragma once

/*

	2021 11 26
	C17기준 버전이 올라가면 또 바뀔듯 하다.
	https://en.cppreference.com/w/cpp/container/queue

*/
#include <queue> // queue, priority_queue
#include <stack> // stack
namespace c17_adapters
{ 
	void adapters_test()
	{
		/*
			stack

			template<
				class T,
				class Container = std::deque<T>
			> class stack;

			LIFO(후입 선출) == FILO 데이터 구조를 말함
			 스택은 스택의 맨 위라고 하는 기본 컨테이너의 뒷면에서 요소를 푸시하고 팝

			T는 저장되는 엘리먼트,
			컨테이너의 벨류타입과 저장되는 벨류타입이 다를 경우 행동하지 않음.

			Container는 엘리먼트를 저장하기 위한 컨테이너 타입.
			back, push_back, pop_back을 요구함.
		*/
		{
			std::stack<int> stack;
			std::stack<int> other(std::deque<int>({ 1, 2, 3 }));
			int val = 3;

			decltype(stack)::container_type		container_type;
			decltype(stack)::value_type			value_type;
			decltype(stack)::size_type			size_type;
			decltype(stack)::reference			reference_type = val;
			decltype(stack)::const_reference	const_reference_type = val;

			// 맴버 함수
			// 엘리먼트 접근
			decltype(stack)::value_type front = stack.top();		// 맨위 반환
			// Capacity (용량)
			bool is_empty = stack.empty();							// 비어있는지 확인
			decltype(stack)::size_type size = stack.size();			// 크기 확인

			stack.pop();											// 맨앞 제거
			stack.emplace(val);										// 끝에 생성
			stack.push(val);										// 끝에 입력
			stack.swap(other);										// 컨테이너 교체

			stack._Get_container();									// const 컴테이러 참조 반환
		}

		/*
			queue

			template<
				class T,
				class Container = std::deque<T>
			> class queue;

			FIFI(선입 선출) 데이터 구조를 말한다. 클래스 템플릿은 기본 컨테이너에 대한 래퍼 역활을 함.
			큐는 기본 컨테이너의 뒤쪽에 있는 요소를 푸시하고 앞쪽에서 팝

			T는 저장되는 엘리먼트, 
			컨테이너의 벨류타입과 저장되는 벨류타입이 다를 경우 행동하지 않음.

			Container는 엘리먼트를 저장하기 위한 컨테이너 타입.
			back, front, push_back, pop_front를 요구함
		*/
		{
			std::queue<int> queue;
			std::queue<int> other(std::deque<int>({ 1, 2, 3 }));
			int val = 3;

			decltype(queue)::container_type		container_type;
			decltype(queue)::value_type			value_type;
			decltype(queue)::size_type			size_type;
			decltype(queue)::reference			reference_type = val;
			decltype(queue)::const_reference	const_reference_type = val;

			// 맴버 함수
			// 엘리먼트 접근
			decltype(queue)::value_type front = queue.front();		// 시작 반환
			decltype(queue)::value_type back = queue.back();		// 마지막 반환
			// Capacity (용량)
			bool is_empty = queue.empty();							// 비어있는지 확인
			decltype(queue)::size_type size = queue.size();			// 크기 확인

			queue.pop();											// 맨앞 제거
			queue.emplace(val);										// 끝에 생성
			queue.push(val);										// 끝에 입력
			queue.swap(other);										// 컨테이너 교체

			queue._Get_container();									// const 컴테이러 참조 반환
		}

		/*
			priority_queue

			template<
			    class T,
			    class Container = std::vector<T>,
			    class Compare = std::less<typename Container::value_type>
			> class priority_queue;

			T는 저장되는 엘리먼트,
			컨테이너의 벨류타입과 저장되는 벨류타입이 다를 경우 행동하지 않음.

			Container는 엘리먼트를 저장하기 위한 컨테이너 타입.
			front, push_back, pop_back을 요구함

			Compare은 순서를 정하기 위한 Functor 클래스
			a op b가 true인 경우 a가 앞에, 뒤에 b가 오도록 정렬함
			true, true, ture, false 일때 정렬함
		*/
		{
			std::priority_queue<int> priority_queue;
			std::priority_queue<int> other;
			int val = 3;

			decltype(priority_queue)::container_type	container_type;
			decltype(priority_queue)::value_compare		compare;
			decltype(priority_queue)::value_type		value_type;
			decltype(priority_queue)::size_type			size_type;
			decltype(priority_queue)::reference			reference_type = val;
			decltype(priority_queue)::const_reference	const_reference_type = val;

			// 맴버 함수
			// 엘리먼트 접근
			decltype(priority_queue)::value_type front = priority_queue.top();	// 맨위 반환
			// Capacity (용량)
			bool is_empty = priority_queue.empty();								// 비어있는지 확인
			decltype(priority_queue)::size_type size = priority_queue.size();	// 크기 확인

			priority_queue.pop();												// 맨앞 제거
			priority_queue.emplace(val);										// 정렬 생성
			priority_queue.push(val);											// 정렬 입력
			priority_queue.swap(other);											// 컨테이너 교체
		}
	}

}