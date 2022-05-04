#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <xmemory>

// typedef���� ��Ī ����(alias declaration)�� ��ȣ�϶�

//typedef void (*FP) (int, const std::string&);
//using FP = void (*)(int, const std::string&);
// ���� �ΰ��� �ǹ̴� ���� �ǹ��̴�.
// ��Ī�� ����ؾ� �Ǵ� ������ ���ø��� �ִ�.

class Widget
{
public:
};

template<typename T>
class MyAlloc : public std::allocator<T>
{
public:
};

template<typename T>
using MyAllocList = std::list<T, MyAlloc<T>>;


MyAllocList<Widget> lw;

// template �ȿ��� typedef�� ����Ϸ� �Ѵٸ�
template<typename T>
class Widget2
{
private:
    std::list<T, MyAlloc<T>> list0;
    typename MyAlloc<T>::type list; //������ ����(dependent type)�̱� ������ ������ ���� �տ��� typename�� �ٿ��� �Ѵ�.
    MyAllocList<T> list2;
    void t()
    {
        list;
    }
};

#include <string>

int main()
{
    std::string text = "Test text";
    const std::string& const_ref = text;
}