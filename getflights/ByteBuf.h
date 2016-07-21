

#pragma once

class CByteBuf
{
public:
	CByteBuf(BOOL bNullTerminate=FALSE);
	~CByteBuf();
public:
	//Resize���ƻ��Ѵ���buf�е�����
	void	Resize(size_t iSize);
	BYTE*	GetBufPtr(void){return m_pBuf;}
	size_t Size(void) {return m_uBufByteLen;}

private:
	CByteBuf(const CByteBuf&); //not implement
	CByteBuf& operator=(const CByteBuf&);//not implement

	size_t			m_uBufByteLen;
	BYTE*			m_pBuf;
	BOOL			m_bNullTerminateStr;
};
