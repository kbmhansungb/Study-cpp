#pragma once
#include <memory>

/*
    c++ 14 v
    Data를 생성자의 호출 전에 초기화 하는 방법.
*/

//int main()
//{
//    //// when construct
//    //After* mptr = (After*)malloc(sizeof(After));
//    //Before::initialize_before_construct(mptr, 1);
//    //new(mptr) After();
//
//    //// when destruct
//    //mptr->~After();
//    //Before::uninitialize_before_deconstruct(mptr);
//    //free(mptr);
//}