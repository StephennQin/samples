/*
 * 1 ��Ҫ�ṩһ�������Ľӿڣ� ����������-����ķ������������Թ��캯�������ǹ��е�
 * 2 ��Ҫ�ṩһ�ֻ�ȡ�����ķ�������ȫ�ֶ���ʹ�ã��ʿ���ʹ����ľ�̬��Ա�ķ�ʽȥ�����ͻ�ȡ�������

 * 3 ʹ�õ���ģʽ��ȡʵ����ԭ��ֻ��һ��ʵ���������ʵ�����ڱ�����
	 ����һ��ԭ����effective c++���н��ܣ�ȷ�������Ĵ���ʱ������Ϊȫ�ֶ��󴴽���ʱ��Ҫ��һ���Ĵ��򣬵�ȫ�ֶ���Ĵ�����ʽȴû��
	 �����������ʿ���ʹ�õ���ģʽ���������ȥeffective c++�в鿴��
 */

#include <stdlib.h>
#include <iostream>
using namespace std;

class single
{
	//���ʹ��ȫ�ֺ����ķ�ʽ����Ҫ����Ϊ��Ա���Ա��ܵ��ù��캯��
	friend single getinstance();
	//friend single* getinstance();
private:
	single() {}
public:
	//����ط���һ��Ҫʹ����ľ�̬�����ķ�ʽ����Ϊ������Ҫ����2����ȫ�ֺ���Ҳ����ʵ��
#if 0
	static single* getinstance()
	{
		static single* m_pinstance;
		if (m_pinstance == NULL)//����ǵ�һ�ε��ã���Ҫ����
		{
			m_pinstance = new single();
		}
		return m_pinstance;
	}
#endif
	void fun()
	{
		cout<<"fun invoke"<<endl;
	}
};

#if 0
single* getinstance()
{
	//Ҳ���Բ�ʹ��ָ��ķ�ʽ����ȡ���������ֱ���ö���Ҳ����
	static single *pinstance;
	if(pinstance == NULL) pinstance = new single();
	return pinstance;
}
#endif

single getinstance()
{
	//Ҳ���Բ�ʹ��ָ��ķ�ʽ����ȡ���������ֱ���ö���Ҳ����
	static single pinstance;
	return pinstance;
}

int main()
{
	//single::getinstance()->fun();
	//getinstance()->fun();
	getinstance().fun();
	system("pause");
	return 0;
}