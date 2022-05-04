#pragma once

/*
	2021 11 30

	21:03 새로 시작
	21:32 디버그 시작
	21:45 테스트 케이스에서 막힘.
		작동원리를 정확히 모르는 최적화된 코드는 테스트 케이스 에서 막힌다.
		분할 정복을 몸에 습득하자.
		goto와 반복문, 어느것을 선택해야 하는 것인가. goto 문을 조심해서 쓰자.
		goto문을 잘 쓰면, 중복코드 또는 코드를 굉장히 간략하게 할 수 있다.
*/

#include <string>
#include <vector>

using namespace std;

bool compare(const string& s, int a_begin, int b_begin, int compare_size)
{
	for (int i = 0; i < compare_size; ++i, ++a_begin, ++b_begin)
	{
		if (s[a_begin] != s[b_begin]) 
			return false;
	}
	return true;
}
int solution(string s) {
	// 1. 최소 단위 1에서 부터 압축의 크기 n만큼 검사한다. n의 최대 크기는 n.size()/2이다.
	//	따라서 [1, n.size()/2]만큼 검사해야 한다.
	int min_compress_length = s.size();
	int max_compress_size = s.size() / 2;
	for (int n = 1; n <= max_compress_size; ++n)
	{
		// 어떠한 압축도 불가능하다면 사이즈는 size = (문자열의 길이) 이다.
		// 개요)	 현재 인덱스를 기준으로, 압축 가능한 크기만큼 압축한다.
		//			(문자열 길이의 변화) = (중복되는 문자열의 수의 자리수 크기) - (중복되는 문자열의 수) * n 이다.
		//			(현재 가리키고 있는 인덱스의 이동크기) = (중복되는 문자열의 수) * n + n이다.
		// n 크기로 압축한 값이 이전에 검사한 크기보다 작다면 더 작게 압축할 수 있다는 뜻이다.
		int now_compress_size = s.size();

		int compare_index = 0;
		int repeat_size = 1;
		
		int now_index = 0;
	ALLOW_COMPRES_SIZE:
		now_index += n;
		// 1. 현재 비교 시점을 기준으로 얼만큼 중복할 수 있는지 검사한다.
		//	만일 비교 불가능 하다면 업데이트 해야 한다.
		if (now_index >= s.size())
			goto UPDATE_MIN_COMPRESS_LENGTH;

		if (compare(s, compare_index, now_index, n))
			goto IS_REPEATED;
		else
			goto NEW_COMPARE_STATE;

	IS_REPEATED:
		repeat_size += 1;
		goto ALLOW_COMPRES_SIZE; // 종료 조건에 부합할 때 까지 검사를 계속한다.

	NEW_COMPARE_STATE:

		// 압축했을 시 문자열의 변화를 기록한다.
		now_compress_size -= (repeat_size - 1) * n; // 중복되는 크기만큼 줄일 수 있다.
		while (repeat_size > 1)
		{
			repeat_size /= 10;
			now_compress_size += 1;
		}

		// 문자열이 다르다면 다음번 중복 검사 부터는 현재 인덱스 부터 검사하게 된다.
		compare_index = now_index;
		repeat_size = 1;

		goto ALLOW_COMPRES_SIZE; // 종료 조건에 부합할 때 까지 검사를 계속한다.

	UPDATE_MIN_COMPRESS_LENGTH:

		// 압축했을 시 문자열의 변화를 기록한다.
		now_compress_size -= (repeat_size - 1) * n; // 중복되는 크기만큼 줄일 수 있다.
		while (repeat_size > 1)
		{
			repeat_size /= 10;
			now_compress_size += 1;
		}

		if (min_compress_length > now_compress_size)
			min_compress_length = now_compress_size;
	}
	return min_compress_length;
}
/*
	2021 11 30
	https://programmers.co.kr/learn/courses/30/lessons/60057
	
	17:00 시작
	17:19 휴식
	18:08 다시 시작
	18:30 알고리즘 디버그 시작.
	18:34 무언가 많이 이상하다.

	잘라서 중복되는 것을 확인한다.
	숫자만 구하면 되닌까..

//	1. 1~size()/2까지 n을 만든다.
//		1. n을 이용, n사이즈로 나누었을 때 얼마나 압축 할 수 있는지 확인한다.
//			1. 기준 인덱스와, 현재 인덱스의 중복을 검사한다. (여기서 기준이 되는 인덱스는 생략한다.)
//				1. 만일 기준 인덱스와, 현재 인덱스의  n 크기만큼 같다면, 압축할 수 있는 것이다.
//				2. 압축할 수 있다면 압축할 수 있는 카운터를 증가시킨다.
//				3. 압축할 수 없다면, 압축할 수 있는 수가 0이 아닐때 앞에 숫자를 입력해야 한다.
//				4. 다를 경우 n / 10을 이용하여, 문자열에서 얼만큼 자리를 차지하는 지 구한다.
//		2. 가장 압축할 수 있는 경우의 수를 반환한다.
//	2. 결과를 반환한다.

2번째로 짠 알고리즘에는 버그가 있다.
버그를 잡는 방법은 또 무엇인가? 심지어 테스트 케이스로 알 수 없다.
2번째가 훨씬 빠르기는 하다. 가능하게 하는 방법 없나??
내부가 너무 복잡할 때는 goto문으로 정리하자..
while문으로 이터레이터를 증가시키는 방식보다는 goto문이 속편하다. 상태머신과도 비슷하다. 다만 함수 안에서만 쓰자.

*/

//#include <string>
//#include <vector>
//
//using namespace std;
//
//int solution(string s) {
//	int min_size = s.size();
//	//	1. 1~size()/2까지 n을 만든다.
//	int allowed_max_compress_size = s.size() / 2;
//	for (int n = 1; n <= allowed_max_compress_size; ++n)
//	{
//		// 1. n을 이용, n사이즈로 나누었을 때 얼마나 압축 할 수 있는지 확인한다.
//		// 초기 설정은 0번 인덱스를 기준으로, n번째를 비교하고 있는 상황으로 한다.
//		int allow_count = 0;
//		int now_size = s.size();
//
//		int compare_index = 0;
//		int now_index = n;
//
//		while (now_index < s.size())
//		{
//			// 1. 기준 인덱스와, 현재 인덱스의 중복을 검사한다. (여기서 기준이 되는 인덱스는 생략한다.)
//			bool is_same = true;
//			for (int index_offset = 0; index_offset < n; ++index_offset)
//			{
//				if (s[compare_index + index_offset] != s[now_index + index_offset])
//				{
//					is_same = false;
//					break;
//				}
//			}
//
//			// 1. 만일 기준 인덱스와, 현재 인덱스의  n 크기만큼 같다면, 압축할 수 있는 것이다.
//			// 2. 압축할 수 있다면 압축할 수 있는 카운터를 증가시킨다.
//			if (is_same)
//			{
//				now_size -= n;
//				allow_count += 1;
//			}
//			// 3. 압축할 수 없다면, 다른 문자열이므로 비교하는 인덱스를 업데이트 해야한다.
//			// 4. now_size의 스트링 자리수는 n / 10을 이용하여, 문자열에서 얼만큼 자리를 차지하는 지 구한다.
//			else
//			{
//				compare_index = now_index;
//				while (allow_count > 0)
//				{
//					allow_count /= 10;
//					now_size += 1;
//				}
//			}
//
//			// 탐색 시점의 인덱스를 증가시킨다.
//			now_index += n;
//		}
//		while (allow_count > 0)
//		{
//			allow_count /= 10;
//			now_size += 1;
//		}
//		// 더 단순하게 짤 수 있는 방법이 없나?
//		
//	//		2. 가장 압축할 수 있는 경우의 수를 반환한다.
//		min_size = min(min_size, now_size);
//	}
//	//	2. 결과를 반환한다.
//	return min_size;
//}

/*
	2021 11 30 이전
*/
//#include <string>
//#include <vector>
//
//using namespace std;
//
//struct Compress
//{
//    int compress_size;
//    string result;
//
//    Compress(int compress_size, string input)
//    {
//        if (compress_size < 1)
//        {
//            this->compress_size = 1;
//            result = input;
//            return;
//        }
//
//        size_t index = 0;
//        while (input.size() >= index + compress_size)    // 스트링의 크기보다 작은한 반복한다.
//        {
//            size_t loop_size = 0;
//            size_t compare_index = index + compress_size;
//
//            while (compare(input, index, compare_index, compress_size))
//            {
//                compare_index += compress_size;
//                loop_size += 1;
//            }
//
//            if (loop_size != 0)
//            {
//                string num_str = to_string(loop_size + 1);
//                input.erase(index + compress_size, compare_index - index - compress_size); //
//                input.insert(index, num_str);
//
//                index += num_str.size() + compress_size;
//            }
//            else
//            {
//                ++index;
//            }
//        }
//
//        this->compress_size = compress_size;
//        result = input;
//    }
//
//    static bool compare(const string& input, int a_s, int b_s, int size)
//    {
//        for (int i = 0; i < size; ++i, ++a_s, ++b_s)
//        {
//            if (input[a_s] != input[b_s]) 
//                return false;
//        }
//        return true;
//    }
//};
//
//// https://programmers.co.kr/learn/courses/30/lessons/60057
//void solution() 
//{
//    auto c1 = Compress(1, "aabbaccc");
//    auto c2 = Compress(8, "ababcdcdababcdcd");
//}