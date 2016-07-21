#ifndef Bigint_H
#define Bigint_H

/*
  
 * 1 ����Ҫ��¶�Ľӿ�����Ϊ private, ��Ҫ��¶�Ľӿ�����Ϊ public(�ӿ�)
 
 * 2 ���һ����������Ҫ����private��Ա����������ó�no-mem��no-friend�����������Ҫ����Private��Ա
 	 ����Ϊ��Ա������ �ǳ�Աfriend�����Է�װ�Ե�Ӱ����һ���ġ�����û�б�Ҫ����Ϊ�ǳ�Ա����
 
 * 3 ���飺�ٴμ����ʱ���ʺ�ȥ�����ֽ��򣬴�����ɺ���ת���ֽ���

 */

#include <string>
using std::string;

#ifdef BIGINT_EXPORT
#define API _declspec(dllexport)
#else
#define API _declspec(dllimport)
#endif

class /*API*/ Bigint
{
public:
	Bigint();

	/*explicit */Bigint(const char *pstr);

	Bigint(const Bigint &big);

	~Bigint();

	Bigint& operator = (const Bigint&);
	
	inline char* getptr() const
	{
		return m_pnum;
	}

	char &getindex (int nindex) const
	{
		return *(m_pnum + nindex);
	}

	void swap(Bigint& num)
	{
		char *temp = this->m_pnum;
		this->m_pnum = num.m_pnum;
		num.m_pnum = temp;
	}

	friend Bigint& ten(Bigint&);
	inline int getlength() const;

private:

	char *m_pnum;

};

Bigint operator+(const Bigint& num1, const Bigint& num2);
Bigint operator*(Bigint num1, Bigint num2);

int bigcmp(const Bigint& num1, const Bigint& num2);
bool operator >(const Bigint& num1, const Bigint& num2);
bool operator <(const Bigint& num1, const Bigint& num2);
bool operator ==(const Bigint& num1, const Bigint& num2);

#endif