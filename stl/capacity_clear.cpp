/*
 *  vector �����ڴ���ͷ�
 *  ������size��capacity��ӳ�������ݵĴ�С�������Ĵ�С����Щ������erase.clear����ȻsizeΪ0����ʵ�ʻ���ռ��һ���ռ���ڴ�
 *  �Ϳ���ͨ��capacity����.����ڴ���˷ѡ���ʱ��Ϳ���ͨ��swap��������ȫ�ͷţ���capacityҲ���0
 *  note: �������е�����clear�������ͷţ�ʹ��ʱҪ������������
 */

#include <stdio.h>
#include <vector>

using std::vector;

int main()
{
	vector<int> temp;
	for (int i = 0 ; i < 10; i++)
	{
		temp.push_back(i);
	}
	printf("capacity:%d|size:%d\n", temp.capacity(), temp.size());
#if 1
	//temp.clear();
	temp.erase(temp.begin());
#else
	vector<int>().swap(temp);
#endif
	printf("capacity:%d|size:%d\n", temp.capacity(), temp.size());
	
}