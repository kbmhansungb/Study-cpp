#pragma once
#include <iostream>

template<typename T>
void processPointer(T* ptr)
{
	ptr++;
}

template<>
void processPointer<void>(void*) = delete;

template<>
void processPointer<char>(char*) = delete;

template<>
void processPointer<const void>(const void*) = delete;

template<>
void processPointer<const char>(const char*) = delete;

int main()
{
	int a = 0;
	processPointer(&a);

	//char b = 'a';
	//processPointer(&b);
}