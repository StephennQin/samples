#include "stdio.h"

//�����������cpp������֣�����.def�������
_declspec(dllimport)int CPPdll_add(int add1,int add2);
_declspec(dllimport)int CPPdll_sub(int sub1,int sub2);
_declspec(dllimport)int CPPdll_sub(int sub1,int sub2,int sub3);

//.lib�ļ������Ƕ���ʱ�ĺ������뵼����ʵ�ʺ������Ķ��ձ�
#pragma comment(lib,"../lib/CPPdll.lib")
int main()
{
	int sum = CPPdll_add(5,3);
	int sub = CPPdll_sub(5,3);
	int sub2 = CPPdll_sub(5, 3, 1);
	printf("sum=%d,sub=%d,sub2=%d\n",sum,sub,sub2);
	return 0;
}