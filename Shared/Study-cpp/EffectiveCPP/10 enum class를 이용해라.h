#pragma once
#include <iostream>
#include <tuple>
#include <string>

using UserInfo = std::tuple<std::string, std::string, std::size_t>;
enum class UserInfoFields
{
    uiName, uiEmial, uiReputation,
};
// enum�� ������ ���⼭ enum class�� �ȵȴ�,,,
// enum�� UserInfoFields���� std::size_t���� �Ϲ��� ��ȯ�� ����ϱ� �����̴�.

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
    //auto t = std::get<UserInfoFields::uiEmial>(t); // enum���� �������� �� Ʃ�ÿ��� �ҷ����� ���.
    auto t = std::get<static_cast<std::size_t>(UserInfoFields::uiEmial)>(t); // enum class���� Ʃ���� �ҷ����� ���.
    // �̷��� �ۼ��ϸ� ������ ���߿� ����� �����ؾ� �Ѵ�.

    auto t = std::get<toUType(UserInfoFields::uiEmial)>(t);
    // ������ Ʃ�� Ÿ���� ������ ������ �𸥴�,,

}
