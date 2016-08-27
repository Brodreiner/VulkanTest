#include <iostream>
#include <memory>

class ObjectA
{
	int m_number;
public:
	ObjectA(int number):m_number(number)
	{
		std::cout << "ObjectA " << m_number << "construct" << std::endl;
	}
	~ObjectA()
	{
		std::cout << "ObjectA " << m_number << "destructed" << std::endl;
	}
};


class ObjectB
{
	std::unique_ptr<ObjectA> objectA;
	int m_number;
public:
	ObjectB(int number)
	{
		m_number = number;
		std::cout << "ObjectB " << m_number << "construct" << std::endl;
		objectA.reset(new ObjectA(number));
	}
	~ObjectB()
	{
		std::cout << "ObjectB " << m_number << "destructed" << std::endl;
		//delete objectA;
	}
	ObjectB& operator= (ObjectB&& source)
	{
		objectA = std::move(source.objectA);
		m_number = source.m_number;
	}
};


int main()
{
	std::cout << "STAGE 1" << std::endl;
	{
		ObjectB objectB1(1);
		std::cout << "STAGE 2" << std::endl;
		ObjectB objectB2(2);
		std::cout << "STAGE 3" << std::endl;
		//objectB1 = std::move(objectB2);
		std::cout << "STAGE 4" << std::endl;
	}
	std::cout << "STAGE 2" << std::endl;


	std::cout << "Before Test" << std::endl;
	{
		std::unique_ptr<ObjectA> myUniquePtr;
		myUniquePtr.reset(new ObjectA(123));
		std::cout << "After Test1" << std::endl;
		std::unique_ptr<ObjectA> myUniquePtr2;
		myUniquePtr2 = std::move(myUniquePtr);

		std::cout << "After Test2" << std::endl;
	}
	std::cout << "After Brackets" << std::endl;

}