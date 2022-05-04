#pragma once

/*

	2021 11 26
	C17���� ������ �ö󰡸� �� �ٲ�� �ϴ�.
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

			LIFO(���� ����) == FILO ������ ������ ����
			 ������ ������ �� ����� �ϴ� �⺻ �����̳��� �޸鿡�� ��Ҹ� Ǫ���ϰ� ��

			T�� ����Ǵ� ������Ʈ,
			�����̳��� ����Ÿ�԰� ����Ǵ� ����Ÿ���� �ٸ� ��� �ൿ���� ����.

			Container�� ������Ʈ�� �����ϱ� ���� �����̳� Ÿ��.
			back, push_back, pop_back�� �䱸��.
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

			// �ɹ� �Լ�
			// ������Ʈ ����
			decltype(stack)::value_type front = stack.top();		// ���� ��ȯ
			// Capacity (�뷮)
			bool is_empty = stack.empty();							// ����ִ��� Ȯ��
			decltype(stack)::size_type size = stack.size();			// ũ�� Ȯ��

			stack.pop();											// �Ǿ� ����
			stack.emplace(val);										// ���� ����
			stack.push(val);										// ���� �Է�
			stack.swap(other);										// �����̳� ��ü

			stack._Get_container();									// const �����̷� ���� ��ȯ
		}

		/*
			queue

			template<
				class T,
				class Container = std::deque<T>
			> class queue;

			FIFI(���� ����) ������ ������ ���Ѵ�. Ŭ���� ���ø��� �⺻ �����̳ʿ� ���� ���� ��Ȱ�� ��.
			ť�� �⺻ �����̳��� ���ʿ� �ִ� ��Ҹ� Ǫ���ϰ� ���ʿ��� ��

			T�� ����Ǵ� ������Ʈ, 
			�����̳��� ����Ÿ�԰� ����Ǵ� ����Ÿ���� �ٸ� ��� �ൿ���� ����.

			Container�� ������Ʈ�� �����ϱ� ���� �����̳� Ÿ��.
			back, front, push_back, pop_front�� �䱸��
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

			// �ɹ� �Լ�
			// ������Ʈ ����
			decltype(queue)::value_type front = queue.front();		// ���� ��ȯ
			decltype(queue)::value_type back = queue.back();		// ������ ��ȯ
			// Capacity (�뷮)
			bool is_empty = queue.empty();							// ����ִ��� Ȯ��
			decltype(queue)::size_type size = queue.size();			// ũ�� Ȯ��

			queue.pop();											// �Ǿ� ����
			queue.emplace(val);										// ���� ����
			queue.push(val);										// ���� �Է�
			queue.swap(other);										// �����̳� ��ü

			queue._Get_container();									// const �����̷� ���� ��ȯ
		}

		/*
			priority_queue

			template<
			    class T,
			    class Container = std::vector<T>,
			    class Compare = std::less<typename Container::value_type>
			> class priority_queue;

			T�� ����Ǵ� ������Ʈ,
			�����̳��� ����Ÿ�԰� ����Ǵ� ����Ÿ���� �ٸ� ��� �ൿ���� ����.

			Container�� ������Ʈ�� �����ϱ� ���� �����̳� Ÿ��.
			front, push_back, pop_back�� �䱸��

			Compare�� ������ ���ϱ� ���� Functor Ŭ����
			a op b�� true�� ��� a�� �տ�, �ڿ� b�� ������ ������
			true, true, ture, false �϶� ������
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

			// �ɹ� �Լ�
			// ������Ʈ ����
			decltype(priority_queue)::value_type front = priority_queue.top();	// ���� ��ȯ
			// Capacity (�뷮)
			bool is_empty = priority_queue.empty();								// ����ִ��� Ȯ��
			decltype(priority_queue)::size_type size = priority_queue.size();	// ũ�� Ȯ��

			priority_queue.pop();												// �Ǿ� ����
			priority_queue.emplace(val);										// ���� ����
			priority_queue.push(val);											// ���� �Է�
			priority_queue.swap(other);											// �����̳� ��ü
		}
	}

}