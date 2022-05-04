#pragma once

/*

	STL

	std::vector
	std::list
	std::deque


C++ ǥ�� ���ø� ���̺귯�� ����

������ �����̳�(sequence container)
�ݺ��� (iterator)
���� ��� for �� (Range-based for loop)

*/

/*

��ǻ�� ���п��� ��� �۾��� ó�� �ӵ��� ���⵵(complexity) ��� �θ���, 
�� ���⵵�� Big OO ǥ����̶�� ������ ��Ÿ���ϴ�. �� ǥ�����, NN ���� �����Ͱ� �־��� ���� �� 
�� �۾��� �����ϱ� ���� �� ���� �۾��� �ʿ�� �ϴ��� NN �� ���� ������ ǥ���ϴ� ����Դϴ�. 
(�� ���⵵�� Ŭ ���� �۾��� ����Ǵµ� �ɸ��� �ð��� �þ������)
https://modoocode.com/223


vector ���� �����ϴ� �ݺ��ڷ� const_iterator �� �ֽ��ϴ�. 
�̴� ��ġ const �����͸� �����Ͻø� �˴ϴ�. 
��, const_iterator �� ��� ����Ű�� �ִ� ������ ���� �ٲ� �� �����ϴ�. 
// �̰� ���� �� ����� �߳�?

bool operator<(const Todo& t) const {
  if (priority == t.priority) {
	return job_desc < t.job_desc;
  }
  return priority > t.priority;
}
// �������� ����ϴ� operator�� ������ ������ �տ�������,
// �̸� Ȱ���� ���� �տ����� ������ true�� ��ȯ�ϵ���.

*/
