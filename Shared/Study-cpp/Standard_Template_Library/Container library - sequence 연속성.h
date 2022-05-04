#pragma once

/*

	2021 11 26
	C17기준 버전이 올라가면 또 바뀔듯 하다.
	https://en.cppreference.com/w/cpp/container/array
	보다 자세한 내용은 여기서 참고.

*/
#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
namespace c17_sequence
{
	void sequence_test()
	{
		/*
			template<
			    class T,
			    std::size_t N
			> struct array;

			C스타일 고정 배열, T[N]
		*/
		{
			std::array<int, 3> array;
			std::array<int, 3> other;
			
			decltype(array)::value_type					value_type;
			decltype(array)::size_type					size_type;
			decltype(array)::difference_type			difference_type;
			decltype(array)::reference					reference = value_type;
			decltype(array)::const_reference			const_reference = value_type;
			decltype(array)::pointer					pointer;
			decltype(array)::const_pointer				const_pointer;
			decltype(array)::iterator					iterator;
			decltype(array)::const_iterator				const_iterator;
			decltype(array)::reverse_iterator			reverse_iterator;
			decltype(array)::const_reverse_iterator		const_reverse_iterator;

			// 요소 접근
			array.at(0);
			array[0];
			array.front();
			array.back();
			array.data();

			// 이터레이터
			array.begin();
			array.cbegin();
			array.end();
			array.cend();
			array.rbegin();
			array.crbegin();
			array.rend();
			array.crend();

			// 캐파시티
			array.empty();
			array.size();
			array.max_size();

			// 연산
			array.fill(1);
			array.swap(other);

			std::get<0>(array);
			std::swap(array[0], array[1]);
		}

		/*
			template<
			    class T,
			    class Allocator = std::allocator<T>
			> class vector;
				
			namespace pmr {
			    template <class T>
			    using vector = std::vector<T, std::pmr::polymorphic_allocator<T>>;
			}

			가변 크기 배열

			allocator는 메모리를 흭득/해제하고 해당 메모리의 요소를 구성/파괴하는데 사용되는 할당자.

			Random access - constant 𝓞(1)
			Insertion or removal of elements at the end - amortized constant 𝓞(1)
			Insertion or removal of elements - linear in the distance to the end of the vector 𝓞(n)
		*/
		{
			//vecotr<bool>은 비트공간으로 전문화 되어 있음.
			std::vector<int> vector(3);
			std::vector<int> other;
			
			decltype(vector)::value_type					value_type;
			decltype(vector)::allocator_type				allocator_type;
			decltype(vector)::size_type						size_type;
			decltype(vector)::difference_type				difference_type;
			decltype(vector)::reference						reference = value_type;
			decltype(vector)::const_reference				const_reference = value_type;
			decltype(vector)::pointer						pointer;
			decltype(vector)::const_pointer					const_pointer;
			decltype(vector)::iterator						iterator;
			decltype(vector)::const_iterator				const_iterator;
			decltype(vector)::reverse_iterator				reverse_iterator;
			decltype(vector)::const_reverse_iterator		const_reverse_iterator;

			//
			vector.get_allocator();
			vector.assign(5, 1);		// 재할당함

			// 요소 접근
			vector.at(0);
			vector[0];
			vector.front();
			vector.back();
			vector.data();

			// 이터레이터
			vector.begin();
			vector.cbegin();
			vector.end();
			vector.cend();
			vector.rbegin();
			vector.crbegin();
			vector.rend();
			vector.crend();

			// 캐파시티
			vector.empty();
			vector.size();
			vector.max_size();
			vector.reserve(100);	// reserves storage, 케파시티를 조정함 // reverse가 뒤집다.
			vector.capacity();		// capacity크기를 받아옴
			vector.shrink_to_fit();	// 불필요한 메모리 제거, 캐파시티를 변경함

			// 조정
			vector.clear();
			vector.insert(vector.begin() + 3, 1);
			vector.emplace(vector.begin() + 1, 3);
			vector.erase(vector.begin() + 1);
			vector.push_back(3);
			vector.emplace_back(3);
			vector.pop_back();		// 마지막 인덱스 제거
			vector.resize(3);		// 크기 조정
			vector.swap(other);

			// 비 맴버 함수
			std::swap(vector[0], vector[1]);
		}

		/*
			template<
				class T,
				class Allocator = std::allocator<T>
			> class deque;
			
			namespace pmr {
				template <class T>
				using deque = std::deque<T, std::pmr::polymorphic_allocator<T>>;
			}

			시작과 끝접의 입력을 빠르게 하기 위한 블록형 가변 크기 배열
			
			데크의 스토리지는 필요에 따라 자동으로 확장 및 축소됩니다.
			데크의 확장은 기존 요소를 새 메모리 위치로 복사하는 것을 
			포함하지 않기 때문에 std::vector 의 확장보다 저렴합니다. 
			반면에 데크는 일반적으로 최소 메모리 비용이 큽니다. 하나의 
			요소만 보유하는 데크는 전체 내부 배열을 할당해야 합니다
			(예: 64비트 libstdc++에서는 개체 크기의 8배, 64비트 libc++에서는 
			개체 크기의 16배 또는 4096바이트 중 더 큰 값).

			allocator는 메모리를 흭득/해제하고 해당 메모리의 요소를 구성/파괴하는데 사용되는 할당자.

			Random access - constant O(1)
			Insertion or removal of elements at the end or beginning - constant O(1)
			Insertion or removal of elements - linear O(n)
		*/
		{
			//vecotr<bool>은 비트공간으로 전문화 되어 있음.
			std::deque<int> deque(3);
			std::deque<int> other;

			decltype(deque)::value_type					value_type;
			decltype(deque)::allocator_type				allocator_type;
			decltype(deque)::size_type					size_type;
			decltype(deque)::difference_type			difference_type;
			decltype(deque)::reference					reference = value_type;
			decltype(deque)::const_reference			const_reference = value_type;
			decltype(deque)::pointer					pointer;
			decltype(deque)::const_pointer				const_pointer;
			decltype(deque)::iterator					iterator;
			decltype(deque)::const_iterator				const_iterator;
			decltype(deque)::reverse_iterator			reverse_iterator;
			decltype(deque)::const_reverse_iterator		const_reverse_iterator;

			//
			deque.assign(5, 1);		// 재할당함
			deque.get_allocator();

			// 요소 접근
			deque.at(0);
			deque[0];
			deque.front();
			deque.back();

			// 이터레이터
			deque.begin();
			deque.cbegin();
			deque.end();
			deque.cend();
			deque.rbegin();
			deque.crbegin();
			deque.rend();
			deque.crend();

			// 캐파시티
			deque.empty();
			deque.size();
			deque.max_size();
			deque.shrink_to_fit();	// 불필요한 메모리 제거, 캐파시티를 변경함

			// 조정
			deque.clear();
			deque.insert(deque.begin() + 3, 1);
			deque.emplace(deque.begin() + 1, 3);
			deque.erase(deque.begin() + 1);
			deque.push_back(3);
			deque.emplace_back(3);
			deque.pop_front();
			deque.pop_back();		// 마지막 인덱스 제거
			deque.push_front(3);
			deque.emplace_front(3);
			deque.resize(3);		// 크기 조정
			deque.swap(other);

			// 비 맴버 함수
			std::swap(deque[0], deque[1]);
		}

		/*
			template<
			    class T,
			    class Allocator = std::allocator<T>
			> class forward_list;
			
			namespace pmr {
			    template <class T>
			    using forward_list = std::forward_list<T, std::pmr::polymorphic_allocator<T>>;
			}
			
			forward_list는 어느 곳에던지 빠르게 입력, 제거가 가능, 랜덤 접근은 지원하지 않음. 단방향 연결 리스트.

			allocator는 메모리를 흭득/해제하고 해당 메모리의 요소를 구성/파괴하는데 사용되는 할당자.
		*/
		{
			std::forward_list<int> list(3);
			std::forward_list<int> other;

			decltype(list)::value_type					value_type;
			decltype(list)::allocator_type				allocator_type;
			decltype(list)::size_type					size_type;
			decltype(list)::difference_type				difference_type;
			decltype(list)::reference					reference = value_type;
			decltype(list)::const_reference				const_reference = value_type;
			decltype(list)::pointer						pointer;
			decltype(list)::const_pointer				const_pointer;
			decltype(list)::iterator					iterator;
			decltype(list)::const_iterator				const_iterator;

			//
			list.assign(5, 1);		// 재할당함
			list.get_allocator();

			// 요소 접근
			list.front();

			// 이터레이터
			list.before_begin();
			list.cbefore_begin();
			list.begin();
			list.cbegin();
			list.end();
			list.cend();

			// 캐파시티
			list.empty();
			//list.size(); //사이즈를 가져오지 못한다.
			list.max_size();

			// 조정
			list.clear();
			list.insert_after(list.begin(), 1);
			list.emplace_after(list.begin(), 3);
			list.erase_after(list.begin());
			list.push_front(3);		
			list.emplace_front(3);
			list.pop_front();		// 맨앞 인덱스 제거
			list.resize(3);			// 크기 조정
			list.swap(other);

			list.merge(other);		// 리스트 병함.
			list.splice_after(list.begin(), other); // 분할 하기.

			// 내부적으로 구현되어있음. 즉... algorithm을 쓰는것보다 빠르다는 뜻?
			list.remove(3);
			list.remove_if([](int& val) { return val == 3; });
			list.reverse();
			list.unique();
			list.sort();

			// 비 맴버 함수
			std::swap(*list.begin(), *list.begin()); // ??..
		}

		/*
			template<
				class T,
				class Allocator = std::allocator<T>
			> class list;
			
			namespace pmr {
				template <class T>
				using list = std::list<T, std::pmr::polymorphic_allocator<T>>;
			}

			list는 양방향 연결 리스트,
			목록내에서 요소를 추가 제거 및 이동해도 반복자 또는 참조가 무효화 되지 않음.
			반복자는 해당 요소가 삭제된 경우에만 무효화.

			allocator는 메모리를 흭득/해제하고 해당 메모리의 요소를 구성/파괴하는데 사용되는 할당자.
		*/
		{
			std::list<int> list(3);
			std::list<int> other;

			decltype(list)::value_type					value_type;
			decltype(list)::allocator_type				allocator_type;
			decltype(list)::size_type					size_type;
			decltype(list)::difference_type				difference_type;
			decltype(list)::reference					reference = value_type;
			decltype(list)::const_reference				const_reference = value_type;
			decltype(list)::pointer						pointer;
			decltype(list)::const_pointer				const_pointer;
			decltype(list)::iterator					iterator;
			decltype(list)::const_iterator				const_iterator;

			//
			list.assign(5, 1);		// 재할당함
			list.get_allocator();

			// 요소 접근
			list.front();
			list.back();

			// 이터레이터
			list.begin();
			list.cbegin();
			list.end();
			list.cend();
			list.rbegin();
			list.crbegin();
			list.rend();
			list.crend();

			// 캐파시티
			list.empty();
			list.size();
			list.max_size();

			// 조정
			list.clear();
			list.insert(list.begin(), 1);
			list.emplace(list.begin(), 3);
			list.erase(list.begin());
			list.push_front(3);
			list.push_back(3);
			list.emplace_front(3);
			list.emplace_back(3);
			list.pop_front();		// 맨앞 인덱스 제거
			list.pop_back();
			list.resize(3);			// 크기 조정
			list.swap(other);

			list.merge(other);		// 리스트 병함.
			list.splice(list.begin(), other); // 분할 하기.
			// 내부적으로 구현되어있음. 즉... algorithm을 쓰는것보다 빠르다는 뜻?
			list.remove(3);
			list.remove_if([](int& val) { return val == 3; });
			list.reverse();	// 뒤집기
			list.unique();
			list.sort();

			// 비 맴버 함수
			std::swap(*list.begin(), *list.begin()); // ??..
		}
	}
}