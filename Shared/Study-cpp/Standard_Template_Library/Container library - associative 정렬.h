#pragma once

/*

	C++ 17 기준
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

			Key는 Compare Functor에서 comp(a, b)를 지원해 줘야함.
			true, true, true, false일때 정렬

			겁색 제거 및 삽입은 로그 복잡성.
			일반적으로 레드-블랙 트리
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
		
			Key는 Compare Functor에서 comp(a, b)를 지원해 줘야함.
			true, true, true, false일때 정렬

			set과 달리 동일한 값을 가진 여러 키가 허용
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
			
			key, value의 대응쌍을 말함. 보통 레드 블랙 트리로 구현되어 있음.
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

			key, value의 대응쌍을 말함. 보통 레드 블랙 트리로 구현되어 있음.
		*/
		{
			std::multimap<int, int> multimap;
		}
	}
}