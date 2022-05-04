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
	����. dynamic cast�� �̿��ϱ⿡, ��Ÿ�ӿ��� ����Ѵٰ� �����Ǵµ� constexpr�� �ʿ��ұ�?
	����. ptr_block -> class_ptr -> ref�� ������ �����Ƿ� stl�� �ٸ� ptr�� ���ؼ� �޸𸮸� ȣ���ϴµ� �־� 2���� ������带 �ʿ�� �Ѵ�.
		�ƹ��� �����ص� �����ص尡 2�谡 �Ǵ� ���� ��ĥ ���� ����.
	����. ��۸� �����͸� ó���ϱ� ���ؼ�, weak_ptr, shared_ptr�� �̿��� �� ������, safe_ptr�� use_safe_ptr���� swap����� �����Ѵ�.
	����. �׸��� weak_ptr�� ����Ƚ���� �����Ǵµ� ������ ��ģ��.
	����. �����Ͽ� �ʿ��� �ð��� ������ ���� �� �ִ� ����� �����ϱ�?
	����. unique_ptr�� Ȯ�������� ����ϸ� ���? uniqueó�� make_safe�� �����ϰ�, safe_ptr�� �������� ������.. �ƹ��� �����ص�
	���. ���ѱ��� ����ȭ �ؾ��ϴ� ��Ȳ������ �������� ������ ������ �����, �������� ����Ǿ�� �ϴ� ��Ȳ������ �����ϴٰ� �����ȴ�.
	����. ����,, weak_ptr���� swap����� ������ �� �ִٸ�, �׶��� �ǹ̰� ������ ��������.
	���. unique_ptr���� �޸� �ּ��� ��ü�� (swap) �ʿ�� �� �� (shared_ptr������ ������ ��) �ſ� ���ǹ��ϴٰ� �Ǵ�.
	����. shared_ptr�� weak_ptr�� ũ��� 8����Ʈ�̴�. (�޸𸮰����ϴ� �� ������, �޸� ������), safe_ptr�� �����ʹ� 4����Ʈ�̴�. (�޸� ������)

*/

namespace lstd
{
	/// <summary>
	/// 
	/// 1. ptr �޸𸮸� �����ϴ� ��.
	/// 2. �� ptr_block�� ��� ������ �������� use_count�� ������.
	/// 
	/// </summary>
	/// <typeparam name="Class">_Class�� �����͸� ������.</typeparam>
	template <typename _Class>
	class ptr_block;

	/// <summary>
	/// 
	/// 1. ptr_block�� �ּҸ� ������.
	/// 2. safe_ptr�� �ı��� �� ptr_��use_count�� 0�� �Ǹ� ptr_block�� �ı��Ѵ�. 
	/// 3. block_ptr�� nullptr�� ���, �����ߴ� ����� ���� ���� �ǹ��Ѵ�.
	/// 4. block_ptr�� class_ptr�� nullptr�� ���, �����ߴ� ����� �Ҹ�Ǿ��ٴ� ���� �ǹ��Ѵ�.
	/// 
	/// </summary>
	/// <typeparam name="Type">_Class ���ø� ���ڸ� ������ ptr_block�� ������.</typeparam>
	template <typename _Class>
	class safe_ptr;

	/// <summary>
	/// safe ptr�� ����ϱ� ���� ���,
	/// 
	/// 1. �ڱ� �ڽ��� safe_ptr�� ������ �ִ�.
	/// 2. �ν��Ͻ� ������, �ڱ� �ڽ��� safe_ptr�� �ʱ� ptr_block�� �����Ѵ�.
	/// 3. �ν��Ͻ� �ı���, safe_ptr�� use_count�� 0�� �ƴ϶��, ptr_block�� class_ptr�� nullptr�� �����Ѵ�.
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
		/// �� ptr_block�� ����ϴ� safe_ptr�� ������ ��Ÿ����.
		/// </summary>
		size_t use_count;
		/// <summary>
		/// �ν��Ͻ��� �ּҰ��� ������.
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
			// �޸� �������� �Ҵ��� �����ϴ� ����,, �����ϴ� ��Ȳ�� �ƴϴ�.
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
			// block_ptr�� nullptr�̶�� ��� �۾��� ���� �ʴ´�.
			if (this->block_ptr == nullptr) return;

			this->block_ptr->use_count -= 1;

			// use_count�� 0�̶�� ptr_block�� �ı��Ѵ�.
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
			// block_ptr�� nullptr�̶�� ��� �۾��� ���� �ʴ´�.
			if (this->block_ptr == nullptr) return;

			this->block_ptr->use_count += 1;
		}

	public:
		/// <summary>
		/// �� safe_ptr�� �����, ����Ű�� ����� �����Ƿ� block_ptr�� nullptr�̴�.
		/// </summary>
		constexpr safe_ptr() noexcept : block_ptr(nullptr) {}
		
		/// <summary>
		/// use safe ptr�κ��� safe ptr�� ����� ���� ������ �ʴ´�.
		/// safe ptr�� ���� �����ؾ� �Ѵ�.
		/// </summary>
		/// <param name="class_ptr"></param>
		safe_ptr(typename types::use_safe_ptr_ptr_type class_ptr) = delete;

		/// <summary>
		/// ���� ������ ���� ������ ������Ų��.
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
		/// ���� ���� �����, ���� ptr_block�� ���� ���� ���ҿ�, ���ο� ptr_block�� ���� ���� ������ ������Ų��.
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
		/// �̵� ������ block_ptr������ �ű��.
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		constexpr safe_ptr(typename types::safe_ptr_type&& rhs) noexcept :
			block_ptr(rhs.block_ptr)
		{
			rhs.block_ptr = nullptr;
		}

		/// <summary>
		/// �̵� ���� �����, ���� ptr_block�� ���ؼ��� ���� ������ ���ҽ�Ų��.
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
		/// ����. has_block�� ��ȯ���� true�� �ƴ϶�� ������ ����.
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
		/// ����. is_vaild�� ��ȯ���� false�� ���, ������ ����.
		/// </summary>
		constexpr inline typename types::class_ptr_type unsafe_get() const noexcept
		{
			return block_ptr->instance_ptr;
		}

		/// <summary>
		/// ptr_block�� instance ptr�� ��ȯ�Ѵ�.
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
		/// dynamic_cast�� ���ؼ��� cast�޼��带 �����Ѵ�.
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

		// use_safe_ptr�� _BeginClass�� ������ safe_ptr�� �����.
		use_safe_ptr() 
		{ 
			// use_safe_ptr�� public���� ��ӹ޾ƾ� �Ѵ�.
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
		/// ������ _BeginClass ���ڿ� ���ؼ� ��ü�� �� �ִ�.
		/// 
		/// 1. ���� Ƚ���� ������ �ʴ´�.
		/// 2. �ٸ� ���� ���Ͽ� ĳ��Ʈ �� safe_ptr�� �ִ� ���, ������ �߻� �� �� �ִ�.
		/// </summary>
		constexpr inline void replace(use_safe_ptr<_BeginClass>& rhs) noexcept
		{
			// A_use_safe  B_use_safe
			// A { 3 &a }, B { 1 &b }
			// B { 1 &b }, A { 3 &a }
			// B { 1 &a }, A { 3 &b }

			// ptr_block�� �������ش�.
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
		// parent������, safe_ptr���ϱ�, �׸��� �� safe_ptr�� �����ϱ�.
		{
			lstd::safe_ptr<Parent> empty_safe_ptr;

			// Parent�� ����.
			Parent parent;
			auto parents_use_safe_ptr = parent.get_use_safe_ptr();
			auto parents_safe_ptr = parent.get_safe_ptr();

			empty_safe_ptr = parents_safe_ptr;

			// �� 3���� safe_ptr�� �����ǰ�, ����� 3���� safe_ptr�� use_count�� ���� �� �����ȴ�.
		}

		// �Ļ� Ŭ���� ���� ��, �θ� Ŭ������ ����ȯ, �� ���� Ȯ���ϱ�.
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

		// �ڵ�����ȯ�� ���� ����
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