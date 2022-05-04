#pragma once

#include <cassert>
#include <memory>

/*
	
	- copyright -

	Data	: 2021 12 04
	name	: bum moo, kim
	email	: kbmhansungb@gmail.com

	 Only copyright notice is required, 
	and commercial use and secondary creations are free.

	- note -
	문제. dynamic cast를 이용하기에, 런타임에서 사용한다고 생각되는데 constexpr이 필요할까?
	문제. ptr_block -> class_ptr -> ref의 구조를 가지므로 stl의 다른 ptr에 비해서 메모리를 호출하는데 있어 2배의 오버헤드를 필요로 한다.
		아무리 생각해도 오버해드가 2배가 되는 것을 고칠 수가 없다.
	참고. 댕글링 포인터를 처리하기 위해서, weak_ptr, shared_ptr을 이용할 수 있으나, safe_ptr은 use_safe_ptr에서 swap기능을 제공한다.
	참고. 그리고 weak_ptr의 참조횟수도 삭제되는데 영향을 미친다.
	문제. 컴파일에 필요한 시간을 가능한 줄일 수 있는 방법이 무었일까?
	개선. unique_ptr의 확장형으로 사용하면 어떨까? unique처럼 make_safe로 생성하고, safe_ptr을 가져오는 식으로.. 아무리 생각해도
	결론. 극한까지 최적화 해야하는 상황에서는 적합하지 않지만 빠르게 만들고, 안정성이 보장되어야 하는 상황에서는 적합하다고 생각된다.
	문제. 만일,, weak_ptr에서 swap기능을 제공할 수 있다면, 그때는 의미가 굉장히 없어진다.
	사용. unique_ptr에서 메모리 주소의 교체를 (swap) 필요로 할 때 (shared_ptr에서도 가능은 함) 매우 유의미하다고 판단.
	참고. shared_ptr과 weak_ptr의 크기는 8바이트이다. (메모리관리하는 블럭 포인터, 메모리 포인터), safe_ptr의 포인터는 4바이트이다. (메모리 포인터)

*/

namespace lstd
{
	/// <summary>
	/// 
	/// 1. ptr 메모리를 관리하는 블럭.
	/// 2. 이 ptr_block이 몇개의 참조를 가지는지 use_count를 가진다.
	/// 
	/// </summary>
	/// <typeparam name="Class">_Class의 포인터를 가진다.</typeparam>
	template <typename _Class>
	class ptr_block;

	/// <summary>
	/// 
	/// 1. ptr_block의 주소를 가진다.
	/// 2. safe_ptr이 파괴될 때 ptr_의use_count가 0이 되면 ptr_block을 파괴한다. 
	/// 3. block_ptr이 nullptr인 경우, 참조했던 대상이 없던 것을 의미한다.
	/// 4. block_ptr의 class_ptr이 nullptr인 경우, 참조했던 대상이 소멸되었다는 것을 의미한다.
	/// 
	/// </summary>
	/// <typeparam name="Type">_Class 템플릿 인자를 가지는 ptr_block을 가진다.</typeparam>
	template <typename _Class>
	class safe_ptr;

	/// <summary>
	/// safe ptr을 사용하기 위한 명시,
	/// 
	/// 1. 자기 자신의 safe_ptr을 가지고 있다.
	/// 2. 인스턴스 생성시, 자기 자신의 safe_ptr의 초기 ptr_block을 생성한다.
	/// 3. 인스턴스 파괴시, safe_ptr의 use_count가 0이 아니라면, ptr_block의 class_ptr을 nullptr로 설정한다.
	/// 
	/// </summary>
	/// <typeparam name="Parent"></typeparam>
	template <typename _BeginClass>
	class use_safe_ptr;

	template <typename _Class>
	struct safe_ptr_types
	{
		using class_type = _Class;
		using class_ptr_type = class_type*;
		using block_type = ptr_block<_Class>;
		using block_ptr_type = block_type*;
		using safe_ptr_type = safe_ptr<_Class>;
		using use_safe_ptr_type = use_safe_ptr<_Class>;
		using use_safe_ptr_ptr_type = use_safe_ptr_type*;
	};

	template <typename _Class>
	class ptr_block final
	{
		using types = safe_ptr_types<_Class>;
		friend safe_ptr<_Class>;
		friend use_safe_ptr<_Class>;

		/// <summary>
		/// 이 ptr_block을 사용하는 safe_ptr의 개수를 나타낸다.
		/// </summary>
		size_t use_count;
		/// <summary>
		/// 인스턴스의 주소값을 가진다.
		/// </summary>
		typename types::class_ptr_type instance_ptr;

		ptr_block(size_t use_count, typename types::class_ptr_type instance_ptr) : use_count(use_count), instance_ptr(instance_ptr) {}
	public:
		constexpr inline size_t get_use_count() noexcept { return use_count; }
		constexpr inline typename types::class_ptr_type get_ptr() noexcept { return instance_ptr; }
	};

	template <typename _Class>
	class safe_ptr final
	{
		using types = typename safe_ptr_types<_Class>;
		friend use_safe_ptr<_Class>;

		typename types::block_ptr_type block_ptr;

		constexpr inline void create_ptr_block(typename types::class_ptr_type class_ptr) noexcept
		{
			// 메모리 부족으로 할당을 실패하는 경우는,, 상정하는 상황이 아니다.
			this->block_ptr = new typename types::block_type(1, class_ptr);

			//if (block_ptr = nullptr) assert("Fail to create ptr block.");
		}

		constexpr inline void delete_ptr_block() noexcept
		{
			delete this->block_ptr;
			this->block_ptr = nullptr;
		}

		constexpr inline void decrease_use_count() noexcept
		{
			// block_ptr이 nullptr이라면 어떠한 작업도 하지 않는다.
			if (this->block_ptr == nullptr) return;

			this->block_ptr->use_count -= 1;

			// use_count가 0이라면 ptr_block을 파괴한다.
			if (this->block_ptr->use_count == 0)
			{
				delete_ptr_block();
				return;
			}

			//// check safe
			//if (this->block_ptr->use_count < 0)
			//	assert("use count under 0 : undifined situation.");
		}

		constexpr inline void increase_use_count() noexcept
		{
			// block_ptr이 nullptr이라면 어떠한 작업도 하지 않는다.
			if (this->block_ptr == nullptr) return;

			this->block_ptr->use_count += 1;
		}

	public:
		/// <summary>
		/// 빈 safe_ptr을 만들면, 가리키는 대상이 없으므로 block_ptr은 nullptr이다.
		/// </summary>
		constexpr safe_ptr() noexcept : block_ptr(nullptr) {}
		
		/// <summary>
		/// use safe ptr로부터 safe ptr을 만드는 것은 허용되지 않는다.
		/// safe ptr로 부터 생성해야 한다.
		/// </summary>
		/// <param name="class_ptr"></param>
		safe_ptr(typename types::use_safe_ptr_ptr_type class_ptr) = delete;

		/// <summary>
		/// 복사 생성시 참조 갯수를 증가시킨다.
		/// </summary>
		/// <param name="ar"></param>
		constexpr safe_ptr(const typename types::safe_ptr_type& rhs) noexcept :
			block_ptr(rhs.block_ptr)
		{
			increase_use_count();
		}
		template <typename _OtherType>
		constexpr inline safe_ptr(const safe_ptr<_OtherType>& rhs) noexcept :
			safe_ptr(rhs.cast<_Class>())
		{
		}
		/// <summary>
		/// 복사 대입 연산시, 현재 ptr_block의 참조 갯수 감소와, 새로운 ptr_block에 대한 참조 갯수를 증가시킨다.
		/// </summary>
		/// <param name="rhs"></param>
		constexpr inline void operator= (const typename types::safe_ptr_type& rhs)
		{
			decrease_use_count();
			this->block_ptr = rhs.block_ptr;
			increase_use_count();
		}
		//template <typename _OtherType>
		//constexpr inline void operator= (const safe_ptr<_OtherType>& rhs) noexcept
		//{
		//	this->operator=(rhs.cast<_Class>());
		//}

		/// <summary>
		/// 이동 생성시 block_ptr값만을 옮긴다.
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		constexpr safe_ptr(typename types::safe_ptr_type&& rhs) noexcept :
			block_ptr(rhs.block_ptr)
		{
			rhs.block_ptr = nullptr;
		}

		/// <summary>
		/// 이동 대입 연산시, 현재 ptr_block에 대해서만 참조 갯수를 감소시킨다.
		/// </summary>
		/// <param name="rhs"></param>
		constexpr inline void operator= (typename types::safe_ptr_type&& rhs) noexcept
		{
			decrease_use_count();
			this->block_ptr = rhs.block_ptr;
			rhs.block_ptr = nullptr;
		}

		~safe_ptr() noexcept
		{
			decrease_use_count();
		}

		constexpr inline bool operator==(const typename types::safe_ptr_type& rhs) const noexcept
		{
			return this->ptr_block == rhs.ptr_block;
		}

		constexpr inline void reset() noexcept
		{
			decrease_use_count();
			this->block_ptr = nullptr;
		}

		constexpr inline bool has_block() const noexcept
		{
			return this->block_ptr != nullptr;
		}

		/// <summary>
		/// 주의. has_block의 반환값이 true가 아니라면 오류가 난다.
		/// </summary>
		/// <returns></returns>
		constexpr inline bool is_deleted() const noexcept
		{
			return block_ptr.instance_ptr != nullptr;
		}

		constexpr inline bool is_vaild() const noexcept
		{
			if (has_block() == false)		return false;
			if (is_deleted() == false)		return false;

			return true;
		}

		/// <summary>
		/// 주의. is_vaild의 반환값이 false일 경우, 오류가 난다.
		/// </summary>
		constexpr inline typename types::class_ptr_type unsafe_get() const noexcept
		{
			return block_ptr->instance_ptr;
		}

		/// <summary>
		/// ptr_block의 instance ptr을 반환한다.
		/// </summary>
		constexpr inline typename types::class_ptr_type get() const noexcept
		{
			return has_block() ? block_ptr->instance_ptr : nullptr;
		}

		/// <summary>
		/// 
		/// </summary>
		constexpr inline void unsafe_set(typename types::block_ptr_type block_ptr) noexcept
		{
			decrease_use_count();
			this->block_ptr = block_ptr;
			increase_use_count();
		}

		constexpr inline typename types::class_ptr_type operator->() const noexcept
		{
			return this->get();
		}
		
		/// <summary>
		/// dynamic_cast에 대해서만 cast메서드를 지원한다.
		/// </summary>
		template <typename _CastType>
		constexpr inline safe_ptr<_CastType> cast() const noexcept
		{
			safe_ptr<_CastType> result;

			// safe check
			if (has_block() == false) return result;

			auto p = dynamic_cast<_CastType*>(block_ptr->instance_ptr);
			if (p != nullptr)
			{
				result.unsafe_set(reinterpret_cast<ptr_block<_CastType>*>(this->block_ptr));
			}

			return result;
		}
	};

	template <typename _BeginClass>
	class use_safe_ptr
	{
		using types = safe_ptr_types<_BeginClass>;
		friend _BeginClass;

		safe_ptr<_BeginClass> this_safe_ptr;

		// use_safe_ptr은 _BeginClass를 가지는 safe_ptr을 만든다.
		use_safe_ptr() 
		{ 
			// use_safe_ptr은 public으로 상속받아야 한다.
			this_safe_ptr.create_ptr_block(static_cast<typename types::class_ptr_type>(this));
		}
		~use_safe_ptr() 
		{
			this_safe_ptr.block_ptr->instance_ptr = nullptr;
		}
	public:
		constexpr inline const safe_ptr<_BeginClass>& get_safe_ptr() const noexcept { return this_safe_ptr; }
		constexpr inline auto get_use_safe_ptr() const noexcept { return this; }

		/// <summary>
		/// 동일한 _BeginClass 인자에 대해서 대체할 수 있다.
		/// 
		/// 1. 참조 횟수가 변하지 않는다.
		/// 2. 다른 형에 대하여 캐스트 한 safe_ptr이 있는 경우, 오류가 발생 할 수 있다.
		/// </summary>
		constexpr inline void replace(use_safe_ptr<_BeginClass>& rhs) noexcept
		{
			// A_use_safe  B_use_safe
			// A { 3 &a }, B { 1 &b }
			// B { 1 &b }, A { 3 &a }
			// B { 1 &a }, A { 3 &b }

			// ptr_block을 스왑해준다.
			std::swap(this->this_safe_ptr.block_ptr, rhs.this_safe_ptr.block_ptr);
			std::swap(this->this_safe_ptr.block_ptr->instance_ptr, rhs.this_safe_ptr.block_ptr->instance_ptr);
		}
	};
}

namespace safe_ptr_test
{
	class Parent : public lstd::use_safe_ptr<Parent>
	{
	public:
		virtual ~Parent() {}
	};

	class Derived : public Parent
	{
	};

	void test_create_safe_ptr()
	{
		// parent생성후, safe_ptr구하기, 그리고 빈 safe_ptr에 대입하기.
		{
			lstd::safe_ptr<Parent> empty_safe_ptr;

			// Parent형 생성.
			Parent parent;
			auto parents_use_safe_ptr = parent.get_use_safe_ptr();
			auto parents_safe_ptr = parent.get_safe_ptr();

			empty_safe_ptr = parents_safe_ptr;

			// 총 3개의 safe_ptr이 생성되고, 제대로 3개의 safe_ptr의 use_count가 감소 후 삭제된다.
		}

		// 파생 클래스 생성 후, 부모 클래스로 형변환, 후 삭제 확인하기.
		{
			lstd::safe_ptr<Derived> derived_safe_ptr;
			{
				Derived derived;
				derived_safe_ptr = derived.get_safe_ptr();
				{
					auto parent_safe_ptr = derived.get_safe_ptr().cast<Parent>();
				}
			}
		}

		// 자동형변환에 대한 정의
		{
			Derived derived;
			lstd::safe_ptr<Derived> parent_safe_ptr = derived.get_safe_ptr();
			lstd::safe_ptr<Derived> parent_safe_ptr2;
			parent_safe_ptr2 = derived.get_safe_ptr();
		}

		// swap test
		{
			Derived derived_1;
			Derived derived_2;
			lstd::safe_ptr<Derived> p2 = derived_1.get_safe_ptr();

			derived_1.replace(derived_2);
		}
	}
}