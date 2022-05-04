#pragma once
#include <iostream>
#include <tuple>
#include <string>

using UserInfo = std::tuple<std::string, std::string, std::size_t>;
enum class UserInfoFields
{
    uiName, uiEmial, uiReputation,
};
// enum은 되지만 여기서 enum class는 안된다,,,
// enum은 UserInfoFields에서 std::size_t로의 암묵적 변환을 허용하기 때문이다.

//template <typename E>
//constexpr typename std::underlying_type<E>::type
//toUType(E enumerator) //noexcept
//{
//    return
//        static_cast<typename std::underlying_type<E>::type>(enumerator);
//}

template <typename E>
constexpr std::underlying_type_t<E>
toUType(E enumerator) noexcept
{
    return static_cast<std::underlying_type_t<E>>(enumerator);
}

int main()
{
    std::cout << "Hello World!\n";

    std::tuple<int, int, size_t, int> t;
    //auto t = std::get<UserInfoFields::uiEmial>(t); // enum으로 정의했을 때 튜플에서 불러오는 방법.
    auto t = std::get<static_cast<std::size_t>(UserInfoFields::uiEmial)>(t); // enum class에서 튜플을 불러오는 방법.
    // 이렇게 작성하면 컴파일 도중에 결과를 산출해야 한다.

    auto t = std::get<toUType(UserInfoFields::uiEmial)>(t);
    // 하지만 튜플 타입이 뭔지는 여전히 모른다,,

}
