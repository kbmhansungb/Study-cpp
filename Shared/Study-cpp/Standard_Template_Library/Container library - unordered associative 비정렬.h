#pragma once

/*

	C++ 17 기준
	https://en.cppreference.com/w/cpp/container/set

*/
#include <unordered_set> // set, multiset
#include <unordered_map> // map, multimap
namespace c17_associative
{
	void associative_test()
	{
		/*
			template<
				class Key,
				class Hash = std::hash<Key>,
				class KeyEqual = std::equal_to<Key>,
				class Allocator = std::allocator<Key>
			> class unordered_set;
			
			namespace pmr {
				template <class Key,
						  class Hash = std::hash<Key>,
						  class Pred = std::equal_to<Key>>
				using unordered_set = std::unordered_set<Key, Hash, Pred,
														 std::pmr::polymorphic_allocator<Key>>;
			}

			hash맵으로 정렬, 해쉬 값이 같을 경우를 대비해, key가 같은지 검사하는 functor가 있음.
		*/
		{
			std::unordered_set<int> unordered_set;
		}

		/*
			template<
				class Key,
				class Hash = std::hash<Key>,
				class KeyEqual = std::equal_to<Key>,
				class Allocator = std::allocator<Key>
			> class unordered_set;

			namespace pmr {
				template <class Key,
						  class Hash = std::hash<Key>,
						  class Pred = std::equal_to<Key>>
				using unordered_set = std::unordered_set<Key, Hash, Pred,
														 std::pmr::polymorphic_allocator<Key>>;
			}

			hash맵으로 정렬, 해쉬 값이 같을 경우를 대비해, key가 같은지 검사하는 functor가 있음.
		*/
		{
			std::unordered_multiset<int> unordered_multiset;
		}

		/*
			template<
				class Key,
				class Hash = std::hash<Key>,
				class KeyEqual = std::equal_to<Key>,
				class Allocator = std::allocator<Key>
			> class unordered_set;

			namespace pmr {
				template <class Key,
						  class Hash = std::hash<Key>,
						  class Pred = std::equal_to<Key>>
				using unordered_set = std::unordered_set<Key, Hash, Pred,
														 std::pmr::polymorphic_allocator<Key>>;
			}

			hash맵으로 정렬, 해쉬 값이 같을 경우를 대비해, key가 같은지 검사하는 functor가 있음.
		*/
		{
			std::unordered_map<int, int> unordered_map;
		}

		/*
			template<
				class Key,
				class Hash = std::hash<Key>,
				class KeyEqual = std::equal_to<Key>,
				class Allocator = std::allocator<Key>
			> class unordered_set;

			namespace pmr {
				template <class Key,
						  class Hash = std::hash<Key>,
						  class Pred = std::equal_to<Key>>
				using unordered_set = std::unordered_set<Key, Hash, Pred,
														 std::pmr::polymorphic_allocator<Key>>;
			}

			hash맵으로 정렬, 해쉬 값이 같을 경우를 대비해, key가 같은지 검사하는 functor가 있음.
		*/
		{
			std::unordered_multimap<int, int> unordered_multimap;
		}
	}
}