// staticMem.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "MyClass.h"


int _tmain(int argc, _TCHAR* argv[])
{
	//��̬��Ա �տ�ʼ�ͱ���ʼ��
	printf("static m_mem1 = %d\n", MyClass::m_mem1);
	//���� ֻ����ʱ�ű���ʼ����
	MyClass::BuildOjbect().m_mem1 += 1;
	printf("static m_mem1 = %d\n", MyClass::m_mem1);

	return 0;
}

