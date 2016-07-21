/*
 *	����ģʽ�ǽ��ȫ�ֶ���Ĵ��������⣬ ����ģʽ�ǽ���ֲ�����Ĵ�������
	���������ڴ��������ʱ�򲻽���Ҫ���ǵ����������󣬻��д���ʱ��һЩ��ʼ���Ĳ������������������캯�����г�ʼ���ֲ�����Ҳ��
	�������������������ʸ��������Լ������һЩ�����ڶ��󴴽�ʱ�����ã�Ϊ�˷���ͳһ��ʹ�ù���ģʽ����������C++���ģʽ��
	������������ԭ��
 */

#include <stdlib.h>
#include <iostream>
using namespace std;

class student
{
public:
	student(){}
	//��ʼ��һ���ѧ��
	void initstudent()
	{
		m_age = 18;
		strcpy(m_szname, "student");
	}
	//��ʼ����ѧ��
	void initcollege()
	{
		m_age = 20;
		strcpy(m_szname, "college");
	}
	void print()
	{
		cout<<"age "<<m_age<<endl<<"name "<<m_szname<<endl;
	}
private:
	int m_age;
	char m_szname[128];
};

class people
{
public:
	void initpeople()
	{
		//Ĭ��Ϊ����
		m_bman = true;
	}
public:
	void print()
	{
		cout<<"people's sex "<<(m_bman?("male"):("famale"))<<endl;
	}
private:
	bool m_bman;
};


class factory
{
public:
	student *createstudent()
	{
		student *pstu =
		new student();
		pstu->initstudent();
		return pstu;
	}
	student *createcollege()
	{
		student *pstu = new student();
		pstu->initcollege();
		return pstu;
	}
	people *createpeople()
	{
		people *ppel = new people();
		ppel->initpeople();
		return ppel;
	}

};

int main()
{
	factory fc;
	fc.createstudent()->print();
	fc.createcollege()->print();
	fc.createpeople()->print();
	system("pause");
	return 0;
}