#pragma once
#include <iostream>
#include <memory>
#include <string>

class TestClass : public std::enable_shared_from_this<TestClass>
{
    std::string str;
private:
    TestClass(std::string&& str) : str(str)
    {
    };

    // 1 ��
//    friend void std::_Construct_in_place(TestClass&, std::string&&);
//    //friend std::shared_ptr<TestClass> std::make_shared<TestClass>();
//public:
//    static auto create(std::string&& str)
//    {
//        return std::make_shared<TestClass>(std::forward<std::string>(str));
//    }
// 
    // 2��
    // �̷��� �ϸ� friend�� ȣ������ �ʰ� ����� �� �ִ�.
public:
    static auto create(std::string&& str)
    {
        return std::shared_ptr<TestClass>(new TestClass(std::forward<std::string>(str)));
    }
    static auto recreate(std::shared_ptr<TestClass>& sptr, std::string&& str)
    {
        sptr.reset(new TestClass(std::forward<std::string>(str)));
    }
};

int main()
{
    auto a = TestClass::create("a");
    auto p_a = a->shared_from_this();
    auto b = TestClass::create("b");
    auto p_b = b->shared_from_this();
    std::swap(a, b);
    a.reset();
    auto ptr = p_a.get();

    // use safe ptr�� �ǹ̰� ������ �ʾҳ�..
    // shared_ptr�� swap�� shared_ptr�� ����Ű�� ptr�� swap�ϴ� ���� shared_ptr���� ����Ű�� ���� ��ü���� �ʴ´�.

    // use safe ptr�� node���� ī���͸� ���ְ�
    // ��ü�� �Ҹ�Ǿ��� ���� �ľ��� �� �ְ� �ϰ�.
    // use safe ptr�� replace�� �����ϴ� ��� ��ü�� �ٲٴ� ������ ������.

    // shared ptr�� ����Ī �ڿ��� ������ �������� �������� �ʱ� ����.

    auto c = TestClass::create("c");
    std::weak_ptr<TestClass> w_c = c;
    auto d = TestClass::create("d");
    std::swap(c, d);
    //c.reset();
    // weak ptr�� �ν��Ͻ��� �Ҹ��� ������ �� �� ������, �����ϴ� �ν��Ͻ��� ��ü�� �Ұ��� �ϴ�.
    // ������ safe ptr�� ���ǹ� �ϴ�.

    // �����忡�� ����� �� �ְ�, lock�� �Ǵ� ������...
    auto e = TestClass::create("e");
    std::weak_ptr<TestClass> w_e = e;
    TestClass::recreate(e, "new e");

}