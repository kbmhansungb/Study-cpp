#pragma once

/*

	- copyright -

	Data	: 2021 12 04
	name	: bum moo, kim
	email	: kbmhansungb@gmail.com

	 Only copyright notice is required,
	and commercial use and secondary creations are free.

	- note -
	����. ������ �� �ִ� �κ��� ������ ������,,
		ex) void func(this*, int)�϶�, auto f = std::bind_front(this); f(3);�� ȣ���ϴ� ������ ��� �����ϴٰ� �Ǵܵȴ�.
	����. �⺻�� delegate�� �Ҵ� ������ �ڵ����� ���ִ� ������ �����,
*/
#include <vector>
#include <algorithm>
#include <assert.h>

#include <functional>

namespace lstd
{
	class delenode;
	template <typename... Args>
	class delegate;

	/*
		����1. ��������ڿ� �̵��������� ���, ��� �ൿ�� ���� �ʴ´�.
			�� �ű� �� ���� ��ü�̴�.
	*/
	class delenode
	{
		using default_delegate = delegate<>*;
		std::vector<default_delegate> binded_delegate;
	public:
		delenode() = default;
		delenode(const delenode& rhs) {};
		delenode(delenode&& rhs) noexcept {};

		/*
			�۵�1. �������� ������ �ڱ� �ڽ��� ���ε� �� ��ü���� �����Ѵ�.
		*/
		~delenode();

		struct private_accessor
		{
			static void add_unique_delegate(delenode* delenode, delegate<>* delegate)
			{
				auto delegate_iter = std::find(
					delenode->binded_delegate.begin(), 
					delenode->binded_delegate.end(), 
					delegate
				);

				if (delegate_iter != delenode->binded_delegate.end()) 
					return;

				delenode->binded_delegate.emplace_back(delegate);
			}
			static void remove_delegate(delenode* delenode, delegate<>* delegate)
			{
				delenode->binded_delegate.erase(
					std::remove(delenode->binded_delegate.begin(),
								delenode->binded_delegate.end(),
								delegate), 
					delenode->binded_delegate.end()
				);
			}
		};
		friend private_accessor;
	};

	/*
		����1. ��������ڿ� �̵��������� ���, ��� �ൿ�� ���� �ʴ´�.
			�� �ű� �� ���� ��ü�̴�.
		����2. ��������Ʈ�� ���ε� �ϴ� invoker�� �����ϴ�.
			�� ���� delenode�� ���� method�� ������ ���ε� �� �� ����.
	*/
	template <typename... Args>
	class delegate final : public delenode
	{
		using free_type = delenode*;
		using free_thiscall_type = void(delenode::*)(Args...);
		using pair = std::pair<free_type, free_thiscall_type>;

		std::vector<pair> invokers;

	public:
		delegate() = default;
		delegate(const delegate& rhs) {};
		delegate(delegate&& rhs) noexcept {};

		~delegate()
		{
			auto d_this = reinterpret_cast<delegate<>*>(this);
			for (auto& invoke : invokers)
			{
				private_accessor::remove_delegate(invoke.first, d_this);
			}
		}
		/*
			����1. delegate�� �Ϻ������� ���� �ʰ�, ��������Ͽ� �����Ѵ�.
		*/
		void invoke(Args... args)
		{
			for (pair& invoke : invokers)
			{
				// �Ϻ������� ������� �ʴ´�.
				(invoke.first->*invoke.second)(args...);
			}
		}
		template<typename Context>
		void add_invoker(Context* context, void(Context::* func)(Args...))
		{
			auto d_type = (free_type)(context);
			auto d_func = (free_thiscall_type)(func);
			auto d_this = reinterpret_cast<delegate<>*>(this);
			assert(d_type != this); // �ڱ��ڽſ��� ���ε� �� ���� ����.

			auto iter = std::find_if(invokers.begin(), invokers.end(),
				[d_type, d_func](pair& invoke)
				{
					if (invoke.first == d_type &&
						invoke.second == d_func)
						return true;
					else
						return false;
				}
			);

			if (iter == invokers.end())
			{
				invokers.emplace_back(std::make_pair(d_type, d_func));
				private_accessor::add_unique_delegate(d_type, d_this);
			}
		}
		template <typename Context, typename CastType>
		void add_invoker(Context* context, void(CastType::* func)(Args...))
		{
			add_invoker(static_cast<CastType*>(context), func);
		}
		template <typename Context>
		void remove_invoker(Context* context, void(Context::* func)(Args...))
		{
			auto d_type = (free_type)(context);
			auto d_func = (free_thiscall_type)(func);
			auto d_this = reinterpret_cast<delegate<>*>(this);
			assert(d_type != this); // �ڱ��ڽſ��Լ� remove�� ȣ���ϴ� ���� ����� �����̴�.

			int context_num = 0;
			invokers.erase(std::remove_if(invokers.begin(), invokers.end(),
				[&context_num, d_type, d_func](pair& invoke)
				{
					if (d_type == invoke.first)
					{
						++context_num;

						if (d_func == invoke.second)
							return true;
					}
					return false;
				}), invokers.end());

			if (context_num == 1)
			{
				private_accessor::remove_delegate(d_type, d_this);
			}
		}
		void remove_node(delenode* context)
		{
			auto d_type = (free_type)(context);
			auto d_this = reinterpret_cast<delegate<>*>(this);

			 invokers.erase(std::remove_if(invokers.begin(), invokers.end(),
				[d_type](pair& invoke)
				{
					if (invoke.first == d_type)
						return true;
					else
						return false;
				}), invokers.end());

			private_accessor::remove_delegate(d_type, d_this);
		}
	};

	delenode::~delenode()
	{
		while(binded_delegate.size() != 0)
			binded_delegate[0]->remove_node(this);
	}
}

class TestClass : public lstd::delenode
{
public:
	void call_test(int a)
	{
		int c = a;
	}
};
void delegate_test()
{
	{
		lstd::delegate<int> delegate1;
		lstd::delegate<int> delegate2;
		{
			TestClass node1;
			TestClass node2;
			delegate1.add_invoker(&node1, &TestClass::call_test);
			delegate1.add_invoker(&node2, &TestClass::call_test);
			delegate2.add_invoker(&node1, &TestClass::call_test);
			delegate2.add_invoker(&node2, &TestClass::call_test);

			delegate1.invoke(3);
			delegate2.invoke(3);
		}
	}
	{
		TestClass node1;
		TestClass node2;
		{
			lstd::delegate<int> delegate1;
			lstd::delegate<int> delegate2;
			delegate1.add_invoker(&node1, &TestClass::call_test);
			delegate1.add_invoker(&node2, &TestClass::call_test);
			delegate2.add_invoker(&node1, &TestClass::call_test);
			delegate2.add_invoker(&node2, &TestClass::call_test);

			delegate1.invoke(3);
			delegate2.invoke(3);
		}

		auto a = std::bind_front(&TestClass::call_test, node1);
		a(3);
	}
}