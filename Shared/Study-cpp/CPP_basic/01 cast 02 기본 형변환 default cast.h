#pragma once

/*

	2021 11 26

	static_cast			: �츮�� ���� �����ϴ�, ����� �������� �����ϴ� �Ϲ����� Ÿ�� ��ȯ �Ϲ������� ��ĳ����

						  ���� Ŭ������ ������ �� ������ �����͸� ���� Ŭ������ ������ �� ������ �����ͷ� �Ӹ� �ƴ϶�,
						  ���� Ŭ������ ������ �� ������ �����͵� ���� Ŭ������ ������ �� ������ �����ͷ�
						  �ƹ��� ���� ���� �� ��ȯ����������, �׿� ���� å���� ���α׷��Ӱ� ���� �Ѵ�.

	dynamic_cast		: �Ļ� Ŭ���� ���̿����� ĳ����
						  ����. ������ �Ǵ� �����̰ų� void*�̿��� �Ѵ�.
						  ����. dynamic_cast�� ����� �ڷ����� ���� Ŭ���� �����̿��� �Ѵ�.
						  ������ �ð��� �ƴ� ��Ÿ�ӿ� �������� �˻��ϵ��� �����Ϸ��� ���̳ʸ� �ڵ带 ����

	const_cast			: ��ü�� �����(const)�� ���ִ� Ÿ�� ��ȯ,
						  ex) const *int -> *int
						  const cast�� ��ü ���Ŀ� ���� ������, ����, �ɹ� �������� ��쿡�� ������.

	reinterpret_cast	: ������ �����ϰ� �ϴ� ĳ�������� ���� ������ ���� �����͵� ������ ĳ����,

						  reinterpret_cast<new_type>(expression)
						  expression�� �ش��ϴ� ���� new_type���� ��Ʈ������ �ٲٴ� �� �Դϴ�.
						  ����. �����͸� �����ϴ�.


	https://musket-ade.tistory.com/entry/C-C-%ED%98%95-%EB%B3%80%ED%99%98-%EC%97%B0%EC%82%B0%EC%9E%90-staticcast-constcast-dynamiccast-reinterpretcast
	https://blockdmask.tistory.com/242

*/

namespace C17_default_cast
{
	// �θ� Ŭ����
	class Parent
	{
	public:
		char parent[7] = "parent";
		// dynamic cast�� �����ϱ� ���ؼ��� ������ Ŭ���������Ѵ�.
		// �ƴ� ��� ������ ��ü�� �ȵȴ�.
		virtual ~Parent() = default;
	};
	// �ڽ� Ŭ����
	class Child : public Parent // private���� Ȯ���ϴ� ���
								// ����ȯ�� : ������ �� �� ���� �⺻ Ŭ���� ...���� ������ ����ȯ�� ������� �ʴ´�.
								// ������ ��ü�� �ȵȴ�.
	{
	public:
		char child[6] = "child";
	};


	void cast_test()
	{
		Parent p;
		Child c;
		Parent* pp = &p;
		Child* pc = &c;

		//////
		// �θ𿡼� �ڽ����� ����ȯ (�ٿ� ĳ����)
		// Parent -> Child

		// ���� ����ȯ�� ���
		// Child p_to_c_s = static_cast<Child>(p); // ����ȯ�� ����� �������� �����Ƿ� ������ ��ü�� �ȵȴ�.

		// ���� ����ȯ�� ���
		// Child p_to_c_d = dynamic_cast<Child>(p); // ������, ����, void*�� �ƴϹǷ� ������ ��ü�� �ȵȴ�.

		//////
		// �ڽĿ��� �θ�� ����ȯ (�� ĳ����)
		// Child -> Parent

		// ���� ����ȯ�� ���
		Parent c_to_p_s = static_cast<Parent>(c);

		// ���� ����ȯ�� ���
		// Parent c_to_p_d = dynamic_cast<Parent>(c); // ������, ����, void*�� �ƴϹǷ� ������ ��ü�� �ȵȴ�.

		//////
		// �θ� �����Ϳ��� �ڽ� �����ͷ� ����ȯ (�ٿ� ĳ����)
		// Parent ptr -> Child ptr

		// ���� ����ȯ�� ���
		Child* pp_to_c_s = static_cast<Child*>(pp); // �Ǳ�� �ϳ� ������ ����ϸ� ������ �߻���Ų��. 
													//(���������� �۵� �� ���� ������, �Ұ��� �� ������ �����ؾ���)

		// ���� ����ȯ�� ���
		Child* pp_to_c_d = dynamic_cast<Child*>(pp); // ĳ������ ������ ��� nullptr�� �ƴ� ���� ��ȯ�ϰ� �Ұ��� �ϴٸ� nullptr�� ��ȯ�Ѵ�.

		//////
		// �ڽ� �����Ϳ��� �θ� �����ͷ� ����ȯ (�� ĳ����)
		// Child ptr -> Parent ptr

		// ���� ����ȯ�� ���
		Parent* pc_to_p_s = static_cast<Parent*>(pc); // ����

		// ���� ����ȯ�� ���
		Parent* pc_to_p_d = dynamic_cast<Parent*>(pc); // ����


		//////
		// const cast

		const int const_int = 3;
		//const_cast<int>(const_int) = 3;			// const cast�� ��ü ���Ŀ� ���� ������, ����, �ɹ� �������� ��쿡�� ������.
		(*const_cast<int*>(&const_int)) = 3;

		//////
		// reinterpret cast
		int rint = 3;
		float* prfloat = reinterpret_cast<float*>(&rint);
	}
}