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

������ �ٲ۴ٸ�? 

�����Ϸ��� ������ ����.
C++ �����Ϸ��� �Լ��� ������ �ÿ�, �ڽ��� �տ� ���ǵǾ� �ִ� 
�Լ��� �ۿ� ���� ���ϱ� �����Դϴ�. ���� void print(T arg, Types... args) �� 
�Լ��� ������ �� ��, void print(T arg) �� �Լ��� �������� �𸣴� ��������.

�׷��� �ȴٸ�, �������� print("abc") �� �����ε��� ã�� ��, 
�Ķ���� ���� �ִ� �Լ��� ���ϰ� �Ǵµ�, �� ��� �� �Լ� �ȿ��� 
print() �� ȣ���� �˴ϴ�. ������ �츮�� print() �� �������� �ʾұ⿡ 
�����Ϸ��� �� �Լ��� ã�� �� ���ٰ� ������ �ջ� �ϰ� �Ǵ� ���Դϴ�.
*/

void variadic_template()
{
	print_t(1, 2, 3);
}

/*

������ ������ ���ڿ��� ��ġ�� �Լ�
���� ���� ���ø��� Ȱ���� �� �ٸ� ���÷� ������ ������ ���ڿ��� �����ִ� �Լ��� �� �� �ֽ��ϴ�. ���� �� std::string ���� ���ڿ��� ��ġ�� ���ؼ���

�䱸�ϴ� �ý���
std::string concat;
concat.reserve(s1.size() + s2.size() + s3.size());  // ���⼭ �Ҵ� 1 �� ����
concat.append(s1);
concat.append(s2);
concat.append(s3);

// ���� ¥���� �Ƿ��� �ð� ������,,

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
		append_to_string(concat_str, strs...);		// �̷��� �ص� Ȯ���� �Ǵ±���,,
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
C++ 11 ���� ���Ե� ���� ���� ���ø��� �ſ� �������� 
�� ���� ������ �ֽ��ϴ�. ��� �Լ� ���·� �����ؾ� �ϱ� ������,
�ݵ�� ��� ȣ�� ���Ḧ ���� �Լ��� ���� ������ �Ѵٴ� ��������.

���� ���� ��� �Լ� ȣ���� �����ϱ� ���� ���̽� ���̽��� 
�� �������� �Ѵٴ� ���Դϴ�. �̴� �ڵ��� ���⵵�� �������� �ø��� �˴ϴ�.
������ C++ 17 �� ���� ���Ե� Fold ������ ����Ѵٸ� �̸� �ξ� �����ϰ� ǥ���� �� �ֽ��ϴ�.

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

���� ���� ���¸� ���� ���� Fold (Unary left fold)��� �θ��ϴ�. 
C++ 17 ���� �����ϴ� Fold ����� ������ �Ʒ� ǥ�� ���� �� 4 ������ �ֽ��ϴ�. 
����� I �� �ʱⰪ�� �ǹ��ϸ� �Ķ���� ���� �ƴմϴ�.

(E op ...)			���� ���� Fold		(E1 op (... op (EN-1 op EN))...)
(... op E)			���� ���� Fold		((...(E1 op E2) op ...) op EN)
(E op ... op I)		���� ���� Fold		(E1 op (... op(EN-1 op (EN op I))...))
(I op ... op E)		���� ���� Fold		((...((I op E1) op E2) op ... ) op EN

�� ���� �߿��� ���� Fold ���� �� �� �� () �� ������� �Ѵٴ� ���Դϴ�.
C++ 17 �ɼ��� ����� �Ѵ�.

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