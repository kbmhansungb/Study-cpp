#pragma once
#include <iostream>
#include <string>

#include <functional>

void func(int a, const std::string& b)
{
    std::cout << a << ", " << b << std::endl;
}
void test()
{
    std::function<void(int, const std::string&)> func1 = func; 
    // void
}