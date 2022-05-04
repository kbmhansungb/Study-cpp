#pragma once

#include <string>
#include <iostream>
namespace c17_literal_expend
{
	void literal_expend_test()
	{
		char; char16_t; char32_t; wchar_t;
		/*
			읽을때 주의사항
				string은 편의를 위하여 작성함. 모든 string은 위의 const char* 형으로 변환 가능
				c++에서 기본 처리는 utf-8이다. (환경설정에 따라 변경될 수 있도고 생각됨. 확인필요)
		*/

		std::string str = "" "" ""; // 이런식으로 작성해도 된다.. 놀라운 사실.
		std::string raw_string 
			= R"( 이안에 있는 모든 것이 문자열로 처리됨 
보기 이쁘지는 않음...)";

		std::string u8_str = "UTF - 8 문자열";			// 문자를 1~4바이트로 표현한다.
		std::u16string u16_str = u"UTF - 16 문자열";	// 문자를 2,4바이트로 표현한다.
		std::u32string u32_str = U"UTF - 32 문자열";	// 문자를 4바이트로 표현한다.
		std::wstring wstr = L"world wide 문자열";		// Linux에서 wchar_t는 4 바이트이고 Windows에서는 2 바이트입니다.

#pragma message (__FILE__ "(" _CRT_STRINGIZE(__LINE__) ")" ": warning: 문자열 타입간 형변환 방법이 궁금.")
		/*
		
			https://github.com/nemtrif/utfcpp
			utf간의 변환 라이브러리
		
		*/
		// to utf-8 
		{
			std::cout << "to utf - 8" << std::endl;

			std::string from_u8		(u8_str.begin(), u8_str.end());
			std::string from_u16	(u16_str.begin(), u16_str.end());
			std::string from_u32	(u32_str.begin(), u32_str.end());
			std::string from_w		(wstr.begin(), wstr.end());

			std::cout << from_u8.c_str() << std::endl;
			std::cout << from_u16.c_str() << std::endl;
			std::cout << from_u32.c_str() << std::endl;
			std::cout << from_w.c_str() << std::endl;
		}
		// to utf-16 
		{
			std::cout << "to utf - 16" << std::endl;

			std::u16string from_u8(u8_str.begin(), u8_str.end());
			std::u16string from_u16(u16_str.begin(), u16_str.end());
			std::u16string from_u32(u32_str.begin(), u32_str.end());
			std::u16string from_w(wstr.begin(), wstr.end());

			std::cout << from_u8.c_str() << std::endl;
			std::cout << from_u16.c_str() << std::endl;
			std::cout << from_u32.c_str() << std::endl;
			std::cout << from_w.c_str() << std::endl;
		}
		// to utf-32
		{
			std::cout << "to utf - 32" << std::endl;

			std::u32string from_u8(u8_str.begin(), u8_str.end());
			std::u32string from_u16(u16_str.begin(), u16_str.end());
			std::u32string from_u32(u32_str.begin(), u32_str.end());
			std::u32string from_w(wstr.begin(), wstr.end());

			std::cout << from_u8.c_str() << std::endl;
			std::cout << from_u16.c_str() << std::endl;
			std::cout << from_u32.c_str() << std::endl;
			std::cout << from_w.c_str() << std::endl;
		}
		// to world wide
		{
			std::cout << "to world wide" << std::endl;

			std::wstring from_u8(u8_str.begin(), u8_str.end());
			std::wstring from_u16(u16_str.begin(), u16_str.end());
			std::wstring from_u32(u32_str.begin(), u32_str.end());
			std::wstring from_w(wstr.begin(), wstr.end());

			std::cout << from_u8.c_str() << std::endl;
			std::cout << from_u16.c_str() << std::endl;
			std::cout << from_u32.c_str() << std::endl;
			std::cout << from_w.c_str() << std::endl;
		}


		/*
		
			string_view는 데이터를 생성하지 않고 읽기만 하는 자료형임.
			string_view의 sub_str는 string_view를 반환함.
			다만 이때도 데이터를 생성하지 않기 때문에 원본이 파괴되면 이를 이용한 모든 string_view가 망가짐.
		
		*/
		{
			const char* text = "test";
			std::string_view sv = text;
			std::u16string_view;
			std::u32string_view;
			std::wstring_view;
		}
	}
}