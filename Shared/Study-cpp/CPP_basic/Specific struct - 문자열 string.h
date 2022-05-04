#pragma once

#include <string>
#include <iostream>
namespace c17_literal_expend
{
	void literal_expend_test()
	{
		char; char16_t; char32_t; wchar_t;
		/*
			������ ���ǻ���
				string�� ���Ǹ� ���Ͽ� �ۼ���. ��� string�� ���� const char* ������ ��ȯ ����
				c++���� �⺻ ó���� utf-8�̴�. (ȯ�漳���� ���� ����� �� �ֵ��� ������. Ȯ���ʿ�)
		*/

		std::string str = "" "" ""; // �̷������� �ۼ��ص� �ȴ�.. ���� ���.
		std::string raw_string 
			= R"( �̾ȿ� �ִ� ��� ���� ���ڿ��� ó���� 
���� �̻����� ����...)";

		std::string u8_str = "UTF - 8 ���ڿ�";			// ���ڸ� 1~4����Ʈ�� ǥ���Ѵ�.
		std::u16string u16_str = u"UTF - 16 ���ڿ�";	// ���ڸ� 2,4����Ʈ�� ǥ���Ѵ�.
		std::u32string u32_str = U"UTF - 32 ���ڿ�";	// ���ڸ� 4����Ʈ�� ǥ���Ѵ�.
		std::wstring wstr = L"world wide ���ڿ�";		// Linux���� wchar_t�� 4 ����Ʈ�̰� Windows������ 2 ����Ʈ�Դϴ�.

#pragma message (__FILE__ "(" _CRT_STRINGIZE(__LINE__) ")" ": warning: ���ڿ� Ÿ�԰� ����ȯ ����� �ñ�.")
		/*
		
			https://github.com/nemtrif/utfcpp
			utf���� ��ȯ ���̺귯��
		
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
		
			string_view�� �����͸� �������� �ʰ� �б⸸ �ϴ� �ڷ�����.
			string_view�� sub_str�� string_view�� ��ȯ��.
			�ٸ� �̶��� �����͸� �������� �ʱ� ������ ������ �ı��Ǹ� �̸� �̿��� ��� string_view�� ������.
		
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