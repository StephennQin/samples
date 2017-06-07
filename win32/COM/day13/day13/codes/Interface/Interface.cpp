// Interface.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <objbase.h>
//����ӿ�
interface IMath
{
public:
	virtual int Add(int nAdd1,int nAdd2)=0;
	virtual int Sub(int nSub1,int nSub2)=0;
};
//���������ʵ����
class CImpMath:public IMath
{
public:
	virtual int Add(int nAdd1,int nAdd2);
	virtual int Sub(int nSub1,int nSub2);
};
int CImpMath::Add(int nAdd1,int nAdd2)
{
	return nAdd1+nAdd2;
}
int CImpMath::Sub(int nSub1,int nSub2)
{
	return nSub1-nSub2;
}
//��������ĵڶ���ʵ����
class CImpMath2:public IMath
{
public:
	virtual int Add(int nAdd1,int nAdd2);
	virtual int Sub(int nSub1,int nSub2);
};
int CImpMath2::Add(int nAdd1,int nAdd2)
{
	return nAdd1+nAdd2+100;
}
int CImpMath2::Sub(int nSub1,int nSub2)
{
	return nSub1-nSub2-100;
}
//����һ����������ĺ�����ʹ�ýӿڷ���
IMath* CreateInstance()
{
	return new CImpMath2;
} 
//���ܵ��ṩ�ߣ��ṩAdd/Sub����
////////////////////////////////////////

//�����ǹ��ܵ�ʹ����
int main(int argc, char* argv[])
{
	//1 ��ͨ���ӿڣ�ʹ��Add/Sub����
    CImpMath2 math;
	int nAdd=math.Add(100,100);

	//2 ʹ�ýӿڵ���Add/Sub����
    IMath *pMath=CreateInstance();
	nAdd=pMath->Add(100,100);


	printf("nAdd=%d\n",nAdd);
	return 0;
}

