#pragma once

//���ø��� ����� �̱��� ������ �ۼ�
template<typename T>
class singletonBase
{
protected:
	//�̱��� �ν��Ͻ��� �ϳ� ����
	static T* singleton;

	singletonBase() {}
	~singletonBase() {}
	
public:
	//�̱��� ��������
	static T* getSingleton();
	//�̱��� ����
	void releaseSingleton();
};

//�̱��� �ʱ�ȭ
template<typename T>
T* singletonBase<T>::singleton = 0;

//�̱��� ��������
template<typename T>
T* singletonBase<T>::getSingleton()
{
	//���� �̱����� ���ٸ� ���� �������ֱ�
	if (!singleton)
	{
		singleton = new T;
	}
	return singleton;
}

//�̱��� ����
template<typename T>
void singletonBase<T>::releaseSingleton()
{
	if (singleton)
	{
		delete singleton;
		singleton = 0;
	}
}


//�Լ� ���ø�(Function Template)
/*
	- �Լ��� ���� ����(�����ε�)�ϴ� ������ �����ϱ�?
	  �� �����(����)�� ���Ǽ��� Ȯ�强�� ����Ű�� �����̴�.

	- ����ڸ� ���ϰ� ���ָ� ���� ����,
	   �����ڴ� ���� ���� ���� �� �ݺ��ؾ߸� �Ѵ�.

	- ���࿡ ���� ���� �ϴ� �ڵ尡 ���� ���ǵ� ä�� �����ϴµ�,
	   �� �ڵ�� 5���� �����Ѵ�. �׷��� �� �߿��� ���� ������ �߻��ߴ�?
	     �� �����ڴ� ��� 5���� �ڵ带 �����ؾ� �Ѵ�.

	
	[�Լ� ���ø��� ����]
	template <typename T>
	T �Լ��� (�Ű�����)
	{
		���๮
	}

	- typename T ��� Ű�����
	   ���� ��ü������ �������� ���� �ڷ���
	- ȣ���ڰ� � ������ �μ��� ����ִ��Ŀ� ����
	   �Լ��� ���� Ÿ���� ����� �� ���.

	   #include <iostream>

	   using namespace std;

	   template <typename T>
	   T testFunc(T a, T b)
	   {
		   T result = a + b;
		   return result;
	   }

	   int main()
	   {
		   cout << testFunc(10, 20) << endl;
		   cout << testFunc(1.1, 3.2) << endl;

		   return 0;
	   }
*/