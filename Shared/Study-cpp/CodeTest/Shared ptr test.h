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

    // 1 안
//    friend void std::_Construct_in_place(TestClass&, std::string&&);
//    //friend std::shared_ptr<TestClass> std::make_shared<TestClass>();
//public:
//    static auto create(std::string&& str)
//    {
//        return std::make_shared<TestClass>(std::forward<std::string>(str));
//    }
// 
    // 2안
    // 이렇게 하면 friend를 호출하지 않고 사용할 수 있다.
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

    // use safe ptr이 의미가 없지는 않았네..
    // shared_ptr의 swap은 shared_ptr이 가르키는 ptr을 swap하는 거지 shared_ptr들이 가르키는 것을 교체하지 않는다.

    // use safe ptr의 node에서 카운터를 없애고
    // 객체가 소멸되었을 때만 파악할 수 있게 하고.
    // use safe ptr의 replace는 차조하는 모든 개체를 바꾸는 식으로 만들자.

    // shared ptr은 피지칭 자원의 소유권 공유에는 참여하지 않기 때문.

    auto c = TestClass::create("c");
    std::weak_ptr<TestClass> w_c = c;
    auto d = TestClass::create("d");
    std::swap(c, d);
    //c.reset();
    // weak ptr은 인스턴스의 소멸을 감지할 수 는 있으나, 참고하는 인스턴스의 교체는 불가능 하다.
    // 여전히 safe ptr은 유의미 하다.

    // 쓰레드에서 사용할 수 있게, lock을 건단 말이지...
    auto e = TestClass::create("e");
    std::weak_ptr<TestClass> w_e = e;
    TestClass::recreate(e, "new e");

}