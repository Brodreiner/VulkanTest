#include <iostream>
#include <memory>
#include <string>


class myClass
{
	std::string& m_s;
public:
	myClass(std::string& s) :m_s(s)
	{

	}
	~myClass()
	{
		std::cout << m_s << std::endl;
	}

};

int main()
{
	std::cout << "STAGE 1" << std::endl;
	std::string test = "Test";
	std::cout << "STAGE 2" << std::endl;
	{
		myClass asdf(test);
		test = "Was neues!";
	}
	std::cout << "STAGE 3" << std::endl;

}