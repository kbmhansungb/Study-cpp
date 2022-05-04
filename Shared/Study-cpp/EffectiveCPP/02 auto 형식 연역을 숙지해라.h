#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>

template<typename It>
void dwim(It b, It e) // dwim�� "do what I mean"����
					  // DWIM (�� ����� ��) ��ǻ�� �ý����� ������� ��� �������� ���������� �߸��� �Է��� 
					  // �͸������� �������� �ʰ� ����� ������ �ڵ����� �����Ͽ� ����ڰ��Ϸ��� �۾��� �����Ϸ��� �õ��մϴ�.
{
	for (; b != e; ++b)
	{
		//typename std::iterator_traits<It>::value_type	 // �� Ÿ�Ը��� �̿��ϴ� ���� ���� �ʴ�.
		//	currValue = *b;

		auto currValue = *b; // auto �� ���ؼ� �ܼ�ȭ ��ų �� �ִ�. �� auto�� ���Ŀ����� �̿��Ѵ�. 

	}
}

void processWidget(bool priority)
{

}

class Widget
{
public:
	//int z(0);
};

class Widget2
{
public:
	Widget2(int i, bool b) {}
	Widget2(std::initializer_list<bool> il) {}
};

//class Widget3
//{
//public:
//	Widget3() {};
//	Widget3(std::initializer_list<int> il) {};
//};
//
//Widget3 w31;
//Widget3 w32{};
//Widget3 w33(); // �Լ� ������ �ǹ�����,

int main()
{
	// 1.
	std::vector<int> vec_dwim;
	dwim(vec_dwim.begin(), vec_dwim.end());

	// 2.
	// auto�� ���� ������ ����ϹǷ� �����Ϸ��� �˴� ������ ������ �� �ִ�.
	// ���� ǥ�ǽ��� �Ű��������� auto�� ������ �� �ִ�.
	auto dereLess
		= [](
			const auto& p1,
			const auto& p2
			)
	{
		return *p1 < *p2;
	};
	// �̷��� ¥�� �۵��� �ǳ�???

	std::vector<int> vec = { 0, 1 };
	bool result = dereLess(vec.begin() + 0, vec.begin() + 1);

	std::function<bool(const std::vector<int>::iterator&, const std::vector<int>::iterator)> func;
	func = dereLess;
	// �̷��� ���ٽ��� �����ؾ� �Ǵ� �κп��� auto�� ����� ������ �����ϴ�.

	// 
	// 	   auto�� ��� ������ �� Ŭ������ ���� �����̸�, ���� �� Ŭ������ �䱸�Ǵ� ��ŭ�� �޸𸮸� ����Ѵ�.
	// 
	// 	   std::function���� ����� ������ ������ std::function���ø��� �� �ν��Ͻ��̸�, �� ũ��� ������ �־��� ���� ���� �����Ǿ� �ִ�.
	// 	   �׷��� �� ũ�Ⱑ �䱸�� Ŭ������ �����ϱ⿡ ������ ���� ������, �׷� ��� std::function�� �� �޸𸮸� �Ҵ��ؼ� Ŭ������ �����Ѵ�.
	//
	// 	   ��������� std::function ��ü�� ��ü�� auto�� ����� ��ü���� �޸𸮸� �� ���� �Һ��Ѵ�.
	//
	//	   https://lunchballer.com/archives/284
	//

	std::vector<int> v;
	unsigned sz_u = v.size();
	// 32��Ʈ�� ��� ���� ������, 64��Ʈ�� ��� ������ �߻��Ѵ�.
	// auto�� ���ؼ� �̷��� ������ �ذ� �� �� �ִ�.
	auto sz_a = v.size();

	std::unordered_map<std::string, int> m;
	for (const std::pair<std::string, int>& p : m)
	{
		// p�� ������ ����
		// 

	}
	// �� �ڵ��� �������� for���� ����� �� ����
	// std::pair<std::string, int> -> const std::pair<std::string, int>&
	// �ϰ� �Ǵ� ���������� �ſ캹���� �۾��� ��ġ�� �ȴ�.
	// auto�� ���Ͽ� ���� ������ �ذ� �� �� �ִ�.
	for (const auto& p : m)
	{
		// p�� ���𰡸� ����.
	}

	// auto�� ��ġ �ʴ� �������� ������ ������ ����� ������ �ʱ�ġ�� ����϶�.
	std::vector<bool> features = { true };
	auto highPriority_0 = features[0];
	bool highPriority_1 = features[0];
	// auto�� bool�� ����Ű�� ���� �ƴ�, std::vector<bool>::reference�� ���� �ȴ�.

	// ����� ���� ������(dangling pointer)
	processWidget(highPriority_0); // reference�� �����ϴ� ������ �ذ��ϱ� ���� ����ϴ� ���� '���� ��� �ʱ�ġ ���뱸'�̴�.

	// ????
	auto highPriority_2 = static_cast<bool>(features[0]);

	Widget w1;		// �⺻ �����ڸ� ȣ��
	Widget w2 = w1;	// ������ �ƴ�; ���� �����ڸ� ȣ��
	w1 = w2;		// ����; ���� ���� ������ (operator =)�� ȣ��

	//int z(0);

	//Widget2 wi2{10, 5.0f}; // 
	//Widget2 wi2 = {10, 5.0f}; // 
	// initializer_list<VALTYPE> �� �������� �Լ��� ���� ��� �߰�ȣ �ʱ��ڴ� �ֿ켱���� �� �����ڸ� �̿��Ѵ�.
}