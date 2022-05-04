#pragma once

/*
https://programmers.co.kr/learn/courses/30/lessons/67257

1. 연산문자는 +, -, *만 존재함.
2. 연산자중, 특정 연산자만을 먼저 계산하고 다음 연산자를 계산해야함.
	+, -, *
	+, *, -
	-, +, *
	-, *, +
	*, -, +
	*, +, -
	의 경우가 있음.
3. 0이상 999의 숫자라고 함.(양수만 있음)

16:40 시작
17:44 종료,,

나름 최적하에 집착하느라,, 시간을 많이 낭비했다.
뉴메릭 쓰지 말고,, 경우에수 직접 넣어서 만들껄,,, 6개 밖에 안되는데,, 그냥 할걸 그랬나.

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