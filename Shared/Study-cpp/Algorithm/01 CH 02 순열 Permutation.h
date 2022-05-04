#pragma once

/*

	2021 11 25
	<Algorithm>의 next_permutation을 이용할 수 있다.
	
	https://eocoding.tistory.com/58

*/

#include <Algorithm>

namespace
{
	auto next_permutation_test()
	{
		int permutation[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
		bool is_permutation = std::next_permutation(permutation, permutation + 8);
		/*
			true, { 0, 1, 2, 3, 4, 5, 6, 7 }
			true, { 0, 1, 2, 3, 4, 5, 7, 6 }
			true, { 0, 1, 2, 3, 4, 6, 5, 7 }
			true, { 0, 1, 2, 3, 4, 6, 7, 6 }
			... 오름차순으로 순열 반환
			true, { 7, 6, 5, 4, 3, 2, 1, 0 }
			false, {...}
		*/
		int permutation2[] = { 7, 6, 5, 4, 3, 2, 1, 0 };
		bool is_permutation = std::prev_permutation(permutation2, permutation2 + 8);
		/*
			내림차순으로 순열 반환
		*/
	}
}
