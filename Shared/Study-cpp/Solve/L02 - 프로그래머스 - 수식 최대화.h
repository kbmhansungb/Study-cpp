#pragma once

/*
https://programmers.co.kr/learn/courses/30/lessons/67257

1. ���깮�ڴ� +, -, *�� ������.
2. ��������, Ư�� �����ڸ��� ���� ����ϰ� ���� �����ڸ� ����ؾ���.
	+, -, *
	+, *, -
	-, +, *
	-, *, +
	*, -, +
	*, +, -
	�� ��찡 ����.
3. 0�̻� 999�� ���ڶ�� ��.(����� ����)

16:40 ����
17:44 ����,,

���� �����Ͽ� �����ϴ���,, �ð��� ���� �����ߴ�.
���޸� ���� ����,, ��쿡�� ���� �־ ���鲬,,, 6�� �ۿ� �ȵǴµ�,, �׳� �Ұ� �׷���.

*/

#include <string>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

enum class State
{
	END, ADD, SUB, MUL
};
struct Block
{
	long long num;
	State s;

	Block(long long num, State s) : num(num), s(s) {}
};
long long solution(string expression) {
	list<Block> sorted_expression;
	size_t num_start = 0;
	size_t index = 0;
	for (; index < expression.size(); ++index)
	{
		switch (expression[index])
		{
		case '+':
			sorted_expression.emplace_back(stoll(expression.substr(num_start, index - num_start)), State::ADD);
			num_start = index + 1;
			break;
		case '-':
			sorted_expression.emplace_back(stoll(expression.substr(num_start, index - num_start)), State::SUB);
			num_start = index + 1;
			break;
		case '*':
			sorted_expression.emplace_back(stoll(expression.substr(num_start, index - num_start)), State::MUL);
			num_start = index + 1;
			break;
		}
	}
	sorted_expression.emplace_back(stoll(expression.substr(num_start, index - num_start)), State::END);

	long long answer = -9223372036854775807 - 1;
	vector<int> states = { 1, 2, 3 };
	do
	{
		list<Block> copy_expression = sorted_expression;
		for (int i = 0; i < 3; ++i)
		{

			switch (states[i])
			{
			case 1: // Add
			{
				auto iter = copy_expression.begin();
				while (iter != copy_expression.end())
				{
					if (iter->s == State::ADD)
					{
						auto temp = iter->num;
						iter = copy_expression.erase(iter);
						iter->num += temp;
					}
					else
					{
						++iter;
					}
				}
			}
			break;
			case 2: // Sub
			{
				auto iter = copy_expression.begin();
				while (iter != copy_expression.end())
				{
					if (iter->s == State::SUB)
					{
						auto temp = iter->num;
						iter = copy_expression.erase(iter);
						iter->num = temp - iter->num;
					}
					else
					{
						++iter;
					}
				}
			}
			break;
			case 3: // Mul
			{
				auto iter = copy_expression.begin();
				while (iter != copy_expression.end())
				{
					if (iter->s == State::MUL)
					{
						auto temp = iter->num;
						iter = copy_expression.erase(iter);
						iter->num *= temp;
					}
					else
					{
						++iter;
					}
				}
			}
			break;
			}
		}
		copy_expression.begin()->num = abs(copy_expression.begin()->num);
		if (copy_expression.begin()->num > answer)
		{
			answer = copy_expression.begin()->num;
		}
	} while (next_permutation(states.begin(), states.end()));
	return answer;
}