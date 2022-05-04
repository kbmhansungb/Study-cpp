#pragma once

/*
	2021 11 30

	21:03 ���� ����
	21:32 ����� ����
	21:45 �׽�Ʈ ���̽����� ����.
		�۵������� ��Ȯ�� �𸣴� ����ȭ�� �ڵ�� �׽�Ʈ ���̽� ���� ������.
		���� ������ ���� ��������.
		goto�� �ݺ���, ������� �����ؾ� �ϴ� ���ΰ�. goto ���� �����ؼ� ����.
		goto���� �� ����, �ߺ��ڵ� �Ǵ� �ڵ带 ������ �����ϰ� �� �� �ִ�.
*/

#include <string>
#include <vector>

using namespace std;

bool compare(const string& s, int a_begin, int b_begin, int compare_size)
{
	for (int i = 0; i < compare_size; ++i, ++a_begin, ++b_begin)
	{
		if (s[a_begin] != s[b_begin]) 
			return false;
	}
	return true;
}
int solution(string s) {
	// 1. �ּ� ���� 1���� ���� ������ ũ�� n��ŭ �˻��Ѵ�. n�� �ִ� ũ��� n.size()/2�̴�.
	//	���� [1, n.size()/2]��ŭ �˻��ؾ� �Ѵ�.
	int min_compress_length = s.size();
	int max_compress_size = s.size() / 2;
	for (int n = 1; n <= max_compress_size; ++n)
	{
		// ��� ���൵ �Ұ����ϴٸ� ������� size = (���ڿ��� ����) �̴�.
		// ����)	 ���� �ε����� ��������, ���� ������ ũ�⸸ŭ �����Ѵ�.
		//			(���ڿ� ������ ��ȭ) = (�ߺ��Ǵ� ���ڿ��� ���� �ڸ��� ũ��) - (�ߺ��Ǵ� ���ڿ��� ��) * n �̴�.
		//			(���� ����Ű�� �ִ� �ε����� �̵�ũ��) = (�ߺ��Ǵ� ���ڿ��� ��) * n + n�̴�.
		// n ũ��� ������ ���� ������ �˻��� ũ�⺸�� �۴ٸ� �� �۰� ������ �� �ִٴ� ���̴�.
		int now_compress_size = s.size();

		int compare_index = 0;
		int repeat_size = 1;
		
		int now_index = 0;
	ALLOW_COMPRES_SIZE:
		now_index += n;
		// 1. ���� �� ������ �������� ��ŭ �ߺ��� �� �ִ��� �˻��Ѵ�.
		//	���� �� �Ұ��� �ϴٸ� ������Ʈ �ؾ� �Ѵ�.
		if (now_index >= s.size())
			goto UPDATE_MIN_COMPRESS_LENGTH;

		if (compare(s, compare_index, now_index, n))
			goto IS_REPEATED;
		else
			goto NEW_COMPARE_STATE;

	IS_REPEATED:
		repeat_size += 1;
		goto ALLOW_COMPRES_SIZE; // ���� ���ǿ� ������ �� ���� �˻縦 ����Ѵ�.

	NEW_COMPARE_STATE:

		// �������� �� ���ڿ��� ��ȭ�� ����Ѵ�.
		now_compress_size -= (repeat_size - 1) * n; // �ߺ��Ǵ� ũ�⸸ŭ ���� �� �ִ�.
		while (repeat_size > 1)
		{
			repeat_size /= 10;
			now_compress_size += 1;
		}

		// ���ڿ��� �ٸ��ٸ� ������ �ߺ� �˻� ���ʹ� ���� �ε��� ���� �˻��ϰ� �ȴ�.
		compare_index = now_index;
		repeat_size = 1;

		goto ALLOW_COMPRES_SIZE; // ���� ���ǿ� ������ �� ���� �˻縦 ����Ѵ�.

	UPDATE_MIN_COMPRESS_LENGTH:

		// �������� �� ���ڿ��� ��ȭ�� ����Ѵ�.
		now_compress_size -= (repeat_size - 1) * n; // �ߺ��Ǵ� ũ�⸸ŭ ���� �� �ִ�.
		while (repeat_size > 1)
		{
			repeat_size /= 10;
			now_compress_size += 1;
		}

		if (min_compress_length > now_compress_size)
			min_compress_length = now_compress_size;
	}
	return min_compress_length;
}
/*
	2021 11 30
	https://programmers.co.kr/learn/courses/30/lessons/60057
	
	17:00 ����
	17:19 �޽�
	18:08 �ٽ� ����
	18:30 �˰��� ����� ����.
	18:34 ���� ���� �̻��ϴ�.

	�߶� �ߺ��Ǵ� ���� Ȯ���Ѵ�.
	���ڸ� ���ϸ� �Ǵѱ�..

//	1. 1~size()/2���� n�� �����.
//		1. n�� �̿�, n������� �������� �� �󸶳� ���� �� �� �ִ��� Ȯ���Ѵ�.
//			1. ���� �ε�����, ���� �ε����� �ߺ��� �˻��Ѵ�. (���⼭ ������ �Ǵ� �ε����� �����Ѵ�.)
//				1. ���� ���� �ε�����, ���� �ε�����  n ũ�⸸ŭ ���ٸ�, ������ �� �ִ� ���̴�.
//				2. ������ �� �ִٸ� ������ �� �ִ� ī���͸� ������Ų��.
//				3. ������ �� ���ٸ�, ������ �� �ִ� ���� 0�� �ƴҶ� �տ� ���ڸ� �Է��ؾ� �Ѵ�.
//				4. �ٸ� ��� n / 10�� �̿��Ͽ�, ���ڿ����� ��ŭ �ڸ��� �����ϴ� �� ���Ѵ�.
//		2. ���� ������ �� �ִ� ����� ���� ��ȯ�Ѵ�.
//	2. ����� ��ȯ�Ѵ�.

2��°�� § �˰��򿡴� ���װ� �ִ�.
���׸� ��� ����� �� �����ΰ�? ������ �׽�Ʈ ���̽��� �� �� ����.
2��°�� �ξ� ������� �ϴ�. �����ϰ� �ϴ� ��� ����??
���ΰ� �ʹ� ������ ���� goto������ ��������..
while������ ���ͷ����͸� ������Ű�� ��ĺ��ٴ� goto���� �����ϴ�. ���¸ӽŰ��� ����ϴ�. �ٸ� �Լ� �ȿ����� ����.

*/

//#include <string>
//#include <vector>
//
//using namespace std;
//
//int solution(string s) {
//	int min_size = s.size();
//	//	1. 1~size()/2���� n�� �����.
//	int allowed_max_compress_size = s.size() / 2;
//	for (int n = 1; n <= allowed_max_compress_size; ++n)
//	{
//		// 1. n�� �̿�, n������� �������� �� �󸶳� ���� �� �� �ִ��� Ȯ���Ѵ�.
//		// �ʱ� ������ 0�� �ε����� ��������, n��°�� ���ϰ� �ִ� ��Ȳ���� �Ѵ�.
//		int allow_count = 0;
//		int now_size = s.size();
//
//		int compare_index = 0;
//		int now_index = n;
//
//		while (now_index < s.size())
//		{
//			// 1. ���� �ε�����, ���� �ε����� �ߺ��� �˻��Ѵ�. (���⼭ ������ �Ǵ� �ε����� �����Ѵ�.)
//			bool is_same = true;
//			for (int index_offset = 0; index_offset < n; ++index_offset)
//			{
//				if (s[compare_index + index_offset] != s[now_index + index_offset])
//				{
//					is_same = false;
//					break;
//				}
//			}
//
//			// 1. ���� ���� �ε�����, ���� �ε�����  n ũ�⸸ŭ ���ٸ�, ������ �� �ִ� ���̴�.
//			// 2. ������ �� �ִٸ� ������ �� �ִ� ī���͸� ������Ų��.
//			if (is_same)
//			{
//				now_size -= n;
//				allow_count += 1;
//			}
//			// 3. ������ �� ���ٸ�, �ٸ� ���ڿ��̹Ƿ� ���ϴ� �ε����� ������Ʈ �ؾ��Ѵ�.
//			// 4. now_size�� ��Ʈ�� �ڸ����� n / 10�� �̿��Ͽ�, ���ڿ����� ��ŭ �ڸ��� �����ϴ� �� ���Ѵ�.
//			else
//			{
//				compare_index = now_index;
//				while (allow_count > 0)
//				{
//					allow_count /= 10;
//					now_size += 1;
//				}
//			}
//
//			// Ž�� ������ �ε����� ������Ų��.
//			now_index += n;
//		}
//		while (allow_count > 0)
//		{
//			allow_count /= 10;
//			now_size += 1;
//		}
//		// �� �ܼ��ϰ� © �� �ִ� ����� ����?
//		
//	//		2. ���� ������ �� �ִ� ����� ���� ��ȯ�Ѵ�.
//		min_size = min(min_size, now_size);
//	}
//	//	2. ����� ��ȯ�Ѵ�.
//	return min_size;
//}

/*
	2021 11 30 ����
*/
//#include <string>
//#include <vector>
//
//using namespace std;
//
//struct Compress
//{
//    int compress_size;
//    string result;
//
//    Compress(int compress_size, string input)
//    {
//        if (compress_size < 1)
//        {
//            this->compress_size = 1;
//            result = input;
//            return;
//        }
//
//        size_t index = 0;
//        while (input.size() >= index + compress_size)    // ��Ʈ���� ũ�⺸�� ������ �ݺ��Ѵ�.
//        {
//            size_t loop_size = 0;
//            size_t compare_index = index + compress_size;
//
//            while (compare(input, index, compare_index, compress_size))
//            {
//                compare_index += compress_size;
//                loop_size += 1;
//            }
//
//            if (loop_size != 0)
//            {
//                string num_str = to_string(loop_size + 1);
//                input.erase(index + compress_size, compare_index - index - compress_size); //
//                input.insert(index, num_str);
//
//                index += num_str.size() + compress_size;
//            }
//            else
//            {
//                ++index;
//            }
//        }
//
//        this->compress_size = compress_size;
//        result = input;
//    }
//
//    static bool compare(const string& input, int a_s, int b_s, int size)
//    {
//        for (int i = 0; i < size; ++i, ++a_s, ++b_s)
//        {
//            if (input[a_s] != input[b_s]) 
//                return false;
//        }
//        return true;
//    }
//};
//
//// https://programmers.co.kr/learn/courses/30/lessons/60057
//void solution() 
//{
//    auto c1 = Compress(1, "aabbaccc");
//    auto c2 = Compress(8, "ababcdcdababcdcd");
//}