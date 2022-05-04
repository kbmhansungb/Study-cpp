#pragma once

/*

	C++ 17 ����
	https://en.cppreference.com/w/cpp/container/set

*/
#include <set> // set, multiset
#include <map> // map, multimap
namespace c17_associative
{
	void associative_test()
	{
		/*
			template<
			    class Key,
			    class Compare = std::less<Key>,
			    class Allocator = std::allocator<Key>
			> class set;
			
			namespace pmr {
			    template <class Key, class Compare = std::less<Key>>
			    using set = std::set<Key, Compare, std::pmr::polymorphic_allocator<Key>>;
			}

			Key�� Compare Functor���� comp(a, b)�� ������ �����.
			true, true, true, false�϶� ����

			�̻� ���� �� ������ �α� ���⼺.
			�Ϲ������� ����-�� Ʈ��
		*/
		{
			std::set<int> set;
		}

		/*
			template<
			    class Key,
			    class Compare = std::less<Key>,
			    class Allocator = std::allocator<Key>
			> class multiset;
			
			namespace pmr {
			    template <class Key, class Compare = std::less<Key>>
			    using multiset = std::multiset<Key, Compare,
			                                   std::pmr::polymorphic_allocator<Key>>;
			}
		
			Key�� Compare Functor���� comp(a, b)�� ������ �����.
			true, true, true, false�϶� ����

			set�� �޸� ������ ���� ���� ���� Ű�� ���
		*/
		{
			std::multiset<int> multiset;
		}

		/*
			template<
			    class Key,
			    class T,
			    class Compare = std::less<Key>,
			    class Allocator = std::allocator<std::pair<const Key, T> >
			> class map;
				
			namespace pmr {
			    template <class Key, class T, class Compare = std::less<Key>>
			    using map = std::map<Key, T, Compare,
			                         std::pmr::polymorphic_allocator<std::pair<const Key,T>>>
			}
			
			key, value�� �������� ����. ���� ���� �� Ʈ���� �����Ǿ� ����.
		*/
		{
			std::map<int, int> map;
		}

		/*
			template<
			    class Key,
			    class T,
			    class Compare = std::less<Key>,
			    class Allocator = std::allocator<std::pair<const Key, T> >
			> class multimap;
			
			namespace pmr {
			    template <class Key, class T, class Compare = std::less<Key>>
			    using multimap = std::multimap<Key, T, Compare,
			                                  std::pmr::polymorphic_allocator<std::pair<const Key,T>>>;
			}

			key, value�� �������� ����. ���� ���� �� Ʈ���� �����Ǿ� ����.
		*/
		{
			std::multimap<int, int> multimap;
		}
	}
}