#pragma once

#include <iostream>

template <typename T>
void print_t(T arg)
{
	std::cout << arg << ", ";
}

template <typename T, typename... Types>
void print_t(T arg, Types... args)
{
	std::cout << arg << ", ";
	print_t(args...);
}

/*

https://modoocode.com/290

순서를 바꾼다면? 

컴파일러는 오류를 낸다.
C++ 컴파일러는 함수를 컴파일 시에, 자신의 앞에 정의되어 있는 
함수들 밖에 보지 못하기 때문입니다. 따라서 void print(T arg, Types... args) 이 
함수를 컴파일 할 때, void print(T arg) 이 함수가 존재함을 모르는 셈이지요.

그렇게 된다면, 마지막에 print("abc") 의 오버로딩을 찾을 때, 
파라미터 팩이 있는 함수를 택하게 되는데, 그 경우 그 함수 안에서 
print() 가 호출이 됩니다. 하지만 우리는 print() 를 정의하지 않았기에 
컴파일러가 이 함수를 찾을 수 없다고 오류를 뿜뿜 하게 되는 것입니다.
*/

void variadic_template()
{
	print_t(1, 2, 3);
}

/*

임의의 개수의 문자열을 합치는 함수
가변 길이 템플릿을 활용한 또 다른 예시로 임의의 길이의 문자열을 합쳐주는 함수를 들 수 있습니다. 예를 들어서 std::string 에서 문자열을 합치기 위해서는

요구하는 시스템
std::string concat;
concat.reserve(s1.size() + s2.size() + s3.size());  // 여기서 할당 1 번 수행
concat.append(s1);
concat.append(s2);
concat.append(s3);

// 직접 짜봐야 실력이 늘거 같은데,,

*/

#include <iostream>
#include <string>


// get size in here
namespace
{
	size_t get_size(const char* s) { return strlen(s); }
	size_t get_size(const std::string& s) { return s.size(); }

	template <typename String, typename... Strings>
	size_t get_size(const String& s, Strings... strs)
	{
		return get_size(s) + get_size(strs...);
	}
}

// append in here
namespace
{
	void append_to_string(std::string* concat_str) { return; }

	template <typename String, typename... Strings>
	void append_to_string(std::string* concat_str, const String& s, Strings... strs)
	{
		concat_str->append(s);
		append_to_string(concat_str, strs...);		// 이렇게 해도 확장이 되는구나,,
	}
}

template <typename Str, typename... Strs>
std::string StrCat(const Str& s, Strs... strs)
{
	size_t total_size = get_size(s, strs...);

	std::string concat_str;
	concat_str.reserve(total_size);

	concat_str = s;
	append_to_string(&concat_str, strs...);
	
	return concat_str;
}

void test()
{
	std::string This = "this";
	std::cout << StrCat(This, " ", "is", " ", "a", " ", std::string("sentence"));
}

/*

Fold Expression
C++ 11 에서 도입된 가변 길이 템플릿은 매우 편리하지만 
한 가지 단점이 있습니다. 재귀 함수 형태로 구성해야 하기 때문에,
반드시 재귀 호출 종료를 위한 함수를 따로 만들어야 한다는 것이지요.

위와 같이 재귀 함수 호출을 종료하기 위해 베이스 케이스를 
꼭 만들어줘야 한다는 점입니다. 이는 코드의 복잡도를 쓸데없이 늘리게 됩니다.
하지만 C++ 17 에 새로 도입된 Fold 형식을 사용한다면 이를 훨씬 간단하게 표현할 수 있습니다.

*/

#include <iostream>

template <typename... Ints>
int sum_all(Ints... nums) 
{
	return (... + nums);
}

void fold_expression()
{
	std::cout << sum_all(1, 4, 2, 3, 10) << std::endl;
}

/*

위와 같은 형태를 단항 좌측 Fold (Unary left fold)라고 부릅니다. 
C++ 17 에서 지원하는 Fold 방식의 종류로 아래 표와 같이 총 4 가지가 있습니다. 
참고로 I 는 초기값을 의미하며 파라미터 팩이 아닙니다.

(E op ...)			단항 우측 Fold		(E1 op (... op (EN-1 op EN))...)
(... op E)			단항 좌측 Fold		((...(E1 op E2) op ...) op EN)
(E op ... op I)		이항 우측 Fold		(E1 op (... op(EN-1 op (EN op I))...))
(I op ... op E)		이항 좌측 Fold		((...((I op E1) op E2) op ... ) op EN

한 가지 중요한 점은 Fold 식을 쓸 때 꼭 () 로 감싸줘야 한다는 점입니다.
C++ 17 옵션을 켜줘야 한다.

*/

#include <vector>
template <typename... T>
int vector_sum(std::vector<int>& index, T... N)
{
	return (... + index[N]);
}

void fold_expression2()
{
	std::vector<int> vec = { 0,1,2,3,4,5 };
	std::cout << vector_sum(vec, 0, 1, 2, 3) << std::endl;
}