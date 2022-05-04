#pragma once
#include <iostream>
#include <memory>

/// <summary>
/// 참고 1. unique_ptr을 이용해서 관리하도록 설계함.
/// </summary>
class Investment
{
public:
    Investment() = default;
    Investment(int a)
    {
    }
    virtual ~Investment() = default; // 소멸자는 기본적으로 noexcept다.

    // 복사 생성자를 허용하지 않는다.
    Investment(const Investment& rhs) = delete;
    // 이동 연산자를 허용하지 않는다.
    Investment(Investment&&) = delete;

    static void calc(int a) {}
};

class Stock : public Investment
{
public:
};

int main()
{
}