#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <xmemory>

// typedef보다 별칭 선언(alias declaration)을 선호하라

//typedef void (*FP) (int, const std::string&);
//using FP = void (*)(int, const std::string&);
// 위의 두가지 의미는 같은 의미이다.
// 별칭을 사용해야 되는 이유는 템플릿에 있다.

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

// template 안에서 typedef를 사용하려 한다면
template<typename T>
class Widget2
{
private:
    std::list<T, MyAlloc<T>> list0;
    typename MyAlloc<T>::type list; //의존적 형식(dependent type)이기 때문에 의존적 형식 앞에는 typename을 붙여야 한다.
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