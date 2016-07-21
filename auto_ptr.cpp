// auto_ptr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <memory>
#include <string>
#include "auto_ptr_array.h"
using std::cout;
using std::endl;

class People
{
public:
	People(const std::string &name = "default", int age = -1):
	  name (name), age(age)
	{
		cout<<"name:"<<name<<endl
			<<"age:"<<age<<endl;
	}

	~People()
	{
		cout<<"People destruct invoke"<<endl;
	}

private:
	std::string name;
	int age;
};

void test_ptr()
{
	//ԭʼ�ķ�ʽ������ڴ�й¶
	//People *ptr_old = new People;

	//ʹ��auto_ptr���ڲ��Ժ������������ͷţ����캯�������ã�
	std::auto_ptr<People> ptr_auto(new People("wanghao", 26));
	auto_array<People> ptr_auto_array(new People[3]);

	//����auto_ptrû���ṩ����ָ�룬���Կ������Լ���һ��
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_ptr();

	system("pause");
	return 0;
}

