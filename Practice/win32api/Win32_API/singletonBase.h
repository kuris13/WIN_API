#pragma once

//템플릿에 기반한 싱글톤 패턴을 작성
template<typename T>
class singletonBase
{
protected:
	//싱글톤 인스턴스를 하나 선언
	static T* singleton;

	singletonBase() {}
	~singletonBase() {}
	
public:
	//싱글톤 가져오기
	static T* getSingleton();
	//싱글톤 해제
	void releaseSingleton();
};

//싱글톤 초기화
template<typename T>
T* singletonBase<T>::singleton = 0;

//싱글톤 가져오기
template<typename T>
T* singletonBase<T>::getSingleton()
{
	//만약 싱글톤이 없다면 새로 생성해주기
	if (!singleton)
	{
		singleton = new T;
	}
	return singleton;
}

//싱글톤 해제
template<typename T>
void singletonBase<T>::releaseSingleton()
{
	if (singleton)
	{
		delete singleton;
		singleton = 0;
	}
}


//함수 템플릿(Function Template)
/*
	- 함수를 다중 정의(오버로딩)하는 이유는 무엇일까?
	  → 사용자(유저)의 편의성과 확장성을 향상시키기 위함이다.

	- 사용자를 편하게 해주면 해줄 수록,
	   개발자는 같은 일을 여러 번 반복해야만 한다.

	- 만약에 같은 일을 하는 코드가 다중 정의된 채로 존재하는데,
	   이 코드는 5개가 존재한다. 그런데 이 중에서 논리적 결함이 발생했다?
	     → 개발자는 적어도 5곳의 코드를 수정해야 한다.

	
	[함수 템플릿의 사용법]
	template <typename T>
	T 함수명 (매개변수)
	{
		실행문
	}

	- typename T 라는 키워드는
	   아직 구체적으로 정해지지 않은 자료형
	- 호출자가 어떤 형태의 인수를 집어넣느냐에 따라
	   함수의 리턴 타입이 변경된 후 출력.

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