#pragma once

/*

	STL

	std::vector
	std::list
	std::deque


C++ 표준 템플릿 라이브러리 개요

시퀀스 컨테이너(sequence container)
반복자 (iterator)
범위 기반 for 문 (Range-based for loop)

*/

/*

컴퓨터 공학에선 어떠한 작업의 처리 속도를 복잡도(complexity) 라고 부르고, 
그 복잡도를 Big OO 표기법이라는 것으로 나타냅니다. 이 표기법은, NN 개의 데이터가 주어져 있을 때 
그 작업을 수행하기 위해 몇 번의 작업을 필요로 하는지 NN 에 대한 식으로 표현하는 방식입니다. 
(즉 복잡도가 클 수록 작업이 수행되는데 걸리는 시간이 늘어나겠지요)
https://modoocode.com/223


vector 에서 지원하는 반복자로 const_iterator 가 있습니다. 
이는 마치 const 포인터를 생각하시면 됩니다. 
즉, const_iterator 의 경우 가리키고 있는 원소의 값을 바꿀 수 없습니다. 
// 이걸 몰라서 그 고생을 했나?

bool operator<(const Todo& t) const {
  if (priority == t.priority) {
	return job_desc < t.job_desc;
  }
  return priority > t.priority;
}
// 정리에서 사용하는 operator의 개념은 작은게 앞에오도록,
// 이를 활용할 때는 앞에오고 싶은게 true를 반환하도록.

*/
