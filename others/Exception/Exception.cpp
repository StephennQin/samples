// Exception.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "exception.h"

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		int a, b ;
		puts("input a, b:");
		scanf("%d%d", &a, &b);
		if(!b)
			throw ClientException("�쳣");
	}
	catch(exception &ex)
	{
		printf("%s\n", ex.what());
	}
	return 0;
}

