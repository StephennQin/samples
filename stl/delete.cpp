/*
 ��effective stl������7
  stl�������������ָ�룬��Ҫ�ֶ��ͷţ����ʹ��forѭ��������̫���㣬����ʹ��for_each,��for_each��ʹ����Ҫע��
  һЩ����...
 */
 
#include <vector>
#include <algorithm>
#include <vld.h>
using namespace std;

/*
	���T�����Ǽ̳ж����ģ����׳������⣨base class δ������������Ϊ�麯����������������Ǹ��ࣩ��
	�ʿ��Խ�ģ�廯���ӡ�
	����Ȼ���쳣��ȫ���⡣�������ʹ������ָ����档
	unary_functionָ�� operator()ֻ��һ������
	��һ��������Operator()�ĵ�һ���������ڶ����������䷵��ֵ���͡�
	ʹ��unary_function��Ϊ����ʹ�ú���������(notl, not2, bind1st, bind2nd)
 */

//C++ �º���
 //template<typename T>
 struct deleteobj //����40������Ϊʲô �����и��̳�
	// :public unary_function<const T*, void>
 {
	 //��ģ�廯��������
	 template<typename T>
	 void operator() (const T* ptr) const
	 {
		 delete ptr;
	 }
 };
 
 class people
 {};

 int main()
 {
	people *p;
	std::vector<people*> temp;
	for (int i = 0; i < 10; i++)
	{
		p = new people;
		temp.push_back(p);
	}
	//ʹ��for_each�� forѭ��Ҫ����
	for_each(temp.begin(), temp.end(), deleteobj());
	 
	return 0;
 }