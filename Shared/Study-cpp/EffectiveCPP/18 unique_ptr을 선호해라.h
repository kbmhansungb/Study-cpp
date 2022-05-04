#pragma once
#include <iostream>
#include <memory>

/// <summary>
/// ���� 1. unique_ptr�� �̿��ؼ� �����ϵ��� ������.
/// </summary>
class Investment
{
public:
    Investment() = default;
    Investment(int a)
    {
    }
    virtual ~Investment() = default; // �Ҹ��ڴ� �⺻������ noexcept��.

    // ���� �����ڸ� ������� �ʴ´�.
    Investment(const Investment& rhs) = delete;
    // �̵� �����ڸ� ������� �ʴ´�.
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