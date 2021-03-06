#pragma once

/*

1. ��ȹ
	�ǻ��ڵ� �ۼ�
		����)
		1. �Ǹż��� ���Ե� ���� �� ����ϱ�
		1. ���� �� �����ϱ�
		2. ���� ������ �����ϱ�
		3. �Ǹż� = ���� �� * ������
		4. ���� = ���� + �Ǹż�
		5. ���� ǥ���ϱ�
		6. ����
	������ �ʹ� ũ�ٸ� ������ �����Ѵ�.

2. ����
	�ܼ��ϰ�, �ݺ�����, ������ ����

3. ����
	// ���� ����
	1. �ڽ��� �ڵ带 ���� �ǽ�.
	2. �ڽ��� �ڵ�� �ܺ� �ڵ尡 ������ ������ �ǽ�.
	3. �ܺ� ���̺귯���� �ǽ�.
	// ����� ���
	1. �׽�Ʈ ���̽��� ����� �߻� ���ɼ� Ž��
	2. ���� ���� �� �ϳ��� �����Ͽ� ������ ������� ������ Ž��
		�׽�Ʈ ���̽��� ����Ѵٸ�, ������ ���α׷��ӿ��� ��ħ�� �� �� �ִ�.
		?. ����ν� �׽�Ʈ ���̽��� ����� ������ ��ġ �׽�Ʈ ����� �𸥴�.

4. ���꼺 ���
	1. ������ ��ȹ�� ��ü����������
	2. �۵��� �ൿ�� ��������������
	3. �ڵ�� ���׸� 
	�ϰ� �ۼ��Ͽ� �����ϰ� ����� �� �ֵ���

	��ϰ� �ð��� �������� ��� �κ��� �������� �����ϰ� �н�
	�ݺ��Ǵ� �۾��� �ִٸ� ���׸�(�Ϲ�ȭ)�Ͽ� �ð��� ����

	�����ɸ��� �κ��� Ž���Ͽ� �ϳ��� ����ȭ �ϸ� �ȴ�.

�׿� ���� ��Ģ���� �ֱ�� ��.
https://insightcampus.co.kr/2021/02/08/%EF%BB%BF%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8D-%EC%9E%98%ED%95%98%EB%8A%94-5%EA%B0%80%EC%A7%80-%EB%B0%A9%EB%B2%95/

SOLID
https://mangsby.com/blog/programming/%EA%B0%9D%EC%B2%B4%EC%A7%80%ED%96%A5-5%EC%9B%90%EC%B9%99-solid%EC%9D%80-%EA%B5%AC%EC%8B%9C%EB%8C%80%EC%9D%98-%EC%9C%A0%EB%AC%BC%EC%9D%B8%EA%B0%80/
https://blog.siner.io/2020/06/18/solid-principles/

�������� ����,, 
1 ���� ������ ������ ������
2 ���� ���� ��� SOLID�� ������ ���� ���� ������.

���� å�� ��Ģ (Single Responsibility Principle)
���� ������ ����� �ڵ���� ������. �ٸ� ������ ����� �ڵ���� ����.
�� ��Ģ�� ����Ʈ���� ���߿� ���̻� �߿����� �ʴٴ� �� ����ϱ� ��Ƴ׿�. �츮�� GUI 
�ڵ�� ����Ͻ� ������ ��������� �ʽ��ϴ�. SQL ������ ��� ���������� ��������� �ʱ���. 
�츮�� �� �κ��� �������� �� �ٸ� �κп� ���װ� ������ �ʵ���, �ٸ� ������ ����� �ڵ���� 
�������ϴ�. �츮�� �ٸ� ������ ����� ���鳢�� �������� ������ �ʵ��� �մϴ�.

����-��� ��Ģ (Open-Closed Principle)
����� Ȯ�忡 �����ְ�, ���濡�� �����־�� �Ѵ�.
��� ��Ģ�� �߿�����, ������ �� ��Ģ�� �ǹ��� �����Ѵٴ� �� �츮 ����� �̷��� ��� 
���� ���� ������ ��Ƴֳ׿�. �翬�� �츮�� ���� �ڵ带 �������� �ʰ�� Ȯ���� �� �ִ� 
����� ������ �մϴ�. ����̽� �������� �������� �ʾƼ� ��ũ ���Ͽ� ����ϴ� ����� 
������, ȭ�� Ȥ�� �������� ����ϴ� ����� ������ �ٸ� �ý����� ����� �� �ֳ���? 
�׷� ���� ���׵��� �ϳ��ϳ� ó���Ϸ��� if ������ ����� �ڵ带 ���� �ͳ���?

�������� ġȯ ��Ģ (Liskov Substitution Principle)
� �������̽��� ����ϴ� ���α׷��� �� �������̽��� ����ü(implementation)�� ���� ������ ��������ϸ� �ȵȴ�.
������� (���� �����ؼ�) �� ��Ģ�� ��ӿ� ���� ���̶�� �Ǽ��߽��ϴ�. �ƴϿ���. 
�̰� ����Ÿ���ο� ���� �̴ϴ�. ��� �������̽����� ����ü����, � �� ���� �������̽��� 
����Ÿ���Դϴ�. ��� ��Ÿ�Ե���, � �� ���� �Ϲ��� �������̽��� ����Ÿ���Դϴ�. �׸��� 
��� ���̽� �������̽��� ����ڵ���, ������̰� �Ϲ����̰�, �������̽��� �ǹ̿� �����ؾ� �մϴ�. 
���� � �� ����ü�� ����ڸ� ȥ�������� �����, if/switch ���� �����ϰ� �� �̴ϴ�.

*������: �������� ġȯ ��Ģ�� �򰥷��ϴ� �е��� ���Ƽ�, �� ������ ���� ��� �����غ��ڽ��ϴ�. 
Ư�� ��θ� �����ϴ� �޼ҵ带 ���� ���Ͻý��� �������̽��� �ֽ��ϴ�. A ����ü�� ��ΰ� ���丮�̸� 
�����ϴµ�, B ����ü�� ��ΰ� ���丮���� ��°�� �����մϴ�. �� ����ü�� �������̽��� �ǹ̸� ȥ�������� 
����� ������, ����ڴ� �������̽��� ����ϱ� ���� if ������ ��ΰ� ���丮�� ��츦 ó������� �մϴ�. 
�̷� ��Ȳ�� �������� �������̽��� �������� ��쿡�� �����Ѵ١� Ȥ�� ���׳� �� �����Ѵ١� �� �� �ϳ��� 
�ǹ̸� ��Ȯ�� ������ �ϰ�, ��� ����ڵ��� �̷� �ǹ̸� ��ΰ� �����ϰ� �ν��ϰ� �־�� �Ѵ�. �� �ǹ̿� 
�����ؾ� �Ѵٴ� ���Դϴ�.

�������̽� �и� ��Ģ (Interface Segregation Principle)
����ڰ� �ʿ����� ���� �͵鿡 �����ϰ� ���� �ʵ���, �������̽��� �۰� �����϶�.
�츮�� ���� ������ �� ���ϴ�. �츮�� ���� � ������ �ٽ� �����ϵǰ� �ٽ� �����Ǿ�� ���� �����ϱ� 
���� ���� ���ڿ� �����մϴ�. �̷� ��� �Ʒ����� ��� A�� ������ Ÿ�ӿ� ��� B�� �����ϸ�, ��Ÿ�� �������� 
������ ��� B�� �������� �� ��� A�� ��������, ����� �ؾ��ϴ� ������ ���� �� �ۿ� �����ϴ�.

���� ���� ��Ģ (Dependency Inversion Principle)
�߻�ȭ�ϴ� �������� �����϶�. ���� ���� ����� ���� ���� ���� ���׿� �����ؼ��� �ȵȴ�.
�� ��Ģ�� �����ϰ� ���� �ʴ� ��Ű���ĸ� ���ø��� ��Ƴ׿�. �츮�� ���� ������ ����Ͻ� �������� ���� ���� 
���� ���׿� �����ϴ� ���� ������ �ʽ��ϴ�. �̰� ������ �翬�ϰ� ���������� ���ڳ׿�. �츮�� �츮���� ���� 
�����ִ� ������ SQL �̳� ���� ���� ����, ������ ������ ���������� ���� ������ �ʽ��ϴ�. ���� ������ 
�߻�ȭ�� ���� ������ ���� ������ �ݸ��Ǳ⸦ ������. �ݸ��� �ý����� ���� ���踦 �����ϰ� �����ؼ�, 
��� �ҽ� �ڵ� ���� ���谡 ���� ���� ���� ������ �ƴ� ���� ���� �߻�ȭ�� ���ϵ��� �ؼ� �̷� �� �ֽ��ϴ�. 
Ư�� �������� ���(architectural boundaries)�� �ѳ���� ��쿡��.

*/