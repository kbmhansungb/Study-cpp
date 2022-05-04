//
//#include <random>
//#include <iostream>
//#include <string>
//
//void quickSort(int array[], int min, int max)
//{
//	int leftIndex = min;
//	int rightIndex = max;
//	int pivot = array[(min + max) / 2];
//	//int pivot = array[max];
//
//	while (leftIndex <= rightIndex)
//	{
//		while (array[leftIndex] < pivot)
//		{
//			++leftIndex;
//		}
//		while (pivot < array[rightIndex])
//		{
//			--rightIndex;
//		}
//
//		if (leftIndex <= rightIndex)
//		{
//			std::swap(array[leftIndex], array[rightIndex]);
//			++leftIndex;
//			--rightIndex;
//		}
//	}
//
//	if (min < rightIndex)
//	{
//		quickSort(array, min, rightIndex);
//	}
//	if (leftIndex < max)
//	{
//		quickSort(array, leftIndex, max);
//	}
//}
//
//void setData(int array[], int arraySize)
//{
//	for (int i = 0; i < arraySize; i++)
//	{
//		array[i] = std::rand() % 1000;
//	}
//}
//
//void printData(int array[], int arraySize)
//{
//	for (int i = 0; i < arraySize; ++i)
//	{
//		std::cout << array[i] << ", ";
//	}
//}
//
//int main()
//{
//#define ARRAY_SIZE 10
//
//	std::string input;
//	while (std::cin >> input && input == "r")
//	{
//		int array[10];
//		setData(array, 10);
//		quickSort(array, 0, ARRAY_SIZE - 1);
//		printData(array, 10);
//	}
//
//	{
//		int array[10] = { 9, 4, 2, 2, 1, 3, 6, 7, 8, 5 };
//		quickSort(array, 0, 9);
//		printData(array, 10);
//	}
//
//	{
//		int array[10] = {1, 4, 2, 2, 2, 3, 6, 7, 8, 5};
//		quickSort(array, 0, 9);
//		printData(array, 10);
//	}
//#undef ARRAY_SIZE
//}


#include <stack>
#include <vector>
#include <iostream>

#define WIDTH 8
#define HEIGHT 8

int array[WIDTH][HEIGHT] =
{
	0, 0, 0, 1, 1, 0, 1, 0,
	1, 1, 0, 0, 0, 0, 1, 0,
	0, 1, 0, 1, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 1, 1, 1,
	1, 1, 0, 1, 0, 1, 0, 0,
	0, 0, 0, 1, 1, 1, 1, 0,
	0, 1, 0, 0, 0, 0, 0, 0,
	0, 1, 1, 1, 0, 1, 1, 0
};

bool search(int x, int y)
{
	// 갈수없으면 종료
	if (array[x][y] != 0)
	{
		return false;
	}
	array[x][y] = 3;

	// 도착했으면 종료
	if (x == 7 && y == 7)
	{
		array[x][y] = 2;
		return true;
	}

	// 갈수있으면 시도
	if (x > 0 && search(x - 1, y))
	{
		array[x][y] = 2;
		return true;
	}
	if (WIDTH - 1 > x && search(x + 1, y))
	{
		array[x][y] = 2;
		return true;
	}
	if (y > 0 && search(x, y - 1))
	{
		array[x][y] = 2;
		return true;
	}
	if (HEIGHT - 1 > y && search(x, y + 1))
	{
		array[x][y] = 2;
		return true;
	}
}

// 결론 논리가 부족하다. 한번에 머리속에 그리는게 어려우니.
// 종이의 도움을 빌리자.
void trace()
{
	for (int i = 0; i < WIDTH; ++i)
	{
		for (int j = 0; j < HEIGHT; ++j)
		{
			if (array[i][j] == 0)
			{
				std::cout << "○ ";
			}
			else if (array[i][j] == 1)
			{
				std::cout << "■ ";
			}
			else if (array[i][j] == 2)
			{
				std::cout << "● ";
			}
			else if (array[i][j] == 3)
			{
				std::cout << "□ ";
			}
		}
		std::cout << std::endl;
	}
}

#include <thread>
int main()
{
	std::thread;
	// 첫단계 도착을 목표로.
	search(0, 0);
	trace();
}