#ifndef __ATLENC_BASE64_H__
#define __ATLENC_BASE64_H__

/*
int B64Encode(const BYTE* pInput, unsigned int nInputLen, LPTSTR buffEncoded, unsigned int nBuffLen)
{
	int nRet = K_B64_Code( EM_CODE, pInput, nInputLen, (BYTE*)buffEncoded, &nBuffLen );
	if(0 == nRet){
		buffEncoded[nBuffLen] = 0;
	}
	return nRet;
}

int B64Decode(LPCTSTR pInput, BYTE* pData, unsigned int& nDataLen)
{
	return K_B64_Code( EM_DECODE, (const BYTE*)pInput, strlen(pInput), pData, &nDataLen );
}
*/
//=======================================================================
// Base64Encode/Base64Decode
// compliant with RFC 2045
//=======================================================================
//
#define ATL_BASE64_FLAG_NONE	0
#define ATL_BASE64_FLAG_NOPAD	1
#define ATL_BASE64_FLAG_NOCRLF  2

inline int Base64EncodeGetRequiredLength(int nSrcLen, DWORD dwFlags=ATL_BASE64_FLAG_NONE)
{
	__int64 nSrcLen4=static_cast<__int64>(nSrcLen)*4;
	//ATLENSURE(nSrcLen4 <= INT_MAX);

	int nRet = static_cast<int>(nSrcLen4/3);

	if ((dwFlags & ATL_BASE64_FLAG_NOPAD) == 0)
		nRet += nSrcLen % 3;

	int nCRLFs = nRet / 76 + 1;
	int nOnLastLine = nRet % 76;

	if (nOnLastLine)
	{
		if (nOnLastLine % 4)
			nRet += 4-(nOnLastLine % 4);
	}

	nCRLFs *= 2;

	if ((dwFlags & ATL_BASE64_FLAG_NOCRLF) == 0)
		nRet += nCRLFs;

	return nRet;
}

inline int Base64DecodeGetRequiredLength(int nSrcLen) throw()
{
	return nSrcLen;
}

/*
inline BOOL Base64Encode(
	__in_ecount(nSrcLen) const BYTE *pbSrcData,
	__in int nSrcLen,
	__out_ecount_part_z(*pnDestLen, *pnDestLen) LPSTR szDest,
	__inout int *pnDestLen,
	__in DWORD dwFlags = ATL_BASE64_FLAG_NONE) throw()*/
inline BOOL Base64Encode(
	const BYTE *pbSrcData,
	int nSrcLen,
	LPSTR szDest,
	int *pnDestLen,
	DWORD dwFlags = ATL_BASE64_FLAG_NONE) throw()
{
	static const char s_chBase64EncodingTable[64] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
		'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',	'h',
		'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y',
		'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/' };

	if (!pbSrcData || !szDest || !pnDestLen)
	{
		return FALSE;
	}

	if(*pnDestLen < Base64EncodeGetRequiredLength(nSrcLen, dwFlags))
	{
		//ATLASSERT(FALSE);
		return FALSE;
	}

	int nWritten( 0 );
	int nLen1( (nSrcLen/3)*4 );
	int nLen2( nLen1/76 );
	int nLen3( 19 );

	for (int i=0; i<=nLen2; i++)
	{
		if (i==nLen2)
			nLen3 = (nLen1%76)/4;

		for (int j=0; j<nLen3; j++)
		{
			DWORD dwCurr(0);
			for (int n=0; n<3; n++)
			{
				dwCurr |= *pbSrcData++;
				dwCurr <<= 8;
			}
			for (int k=0; k<4; k++)
			{
				BYTE b = (BYTE)(dwCurr>>26);
				*szDest++ = s_chBase64EncodingTable[b];
				dwCurr <<= 6;
			}
		}
		nWritten+= nLen3*4;

		if ((dwFlags & ATL_BASE64_FLAG_NOCRLF)==0)
		{
			*szDest++ = '\r';
			*szDest++ = '\n';
			nWritten+= 2;
		}
	}

	if (nWritten && (dwFlags & ATL_BASE64_FLAG_NOCRLF)==0)
	{
		szDest-= 2;
		nWritten -= 2;
	}

	nLen2 = (nSrcLen%3) ? (nSrcLen%3 + 1) : 0;
	if (nLen2)
	{
		DWORD dwCurr(0);
		for (int n=0; n<3; n++)
		{
			if (n<(nSrcLen%3))
				dwCurr |= *pbSrcData++;
			dwCurr <<= 8;
		}
		for (int k=0; k<nLen2; k++)
		{
			BYTE b = (BYTE)(dwCurr>>26);
			*szDest++ = s_chBase64EncodingTable[b];
			dwCurr <<= 6;
		}
		nWritten+= nLen2;
		if ((dwFlags & ATL_BASE64_FLAG_NOPAD)==0)
		{
			nLen3 = nLen2 ? 4-nLen2 : 0;
			for (int j=0; j<nLen3; j++)
			{
				*szDest++ = '=';
			}
			nWritten+= nLen3;
		}
	}

	*pnDestLen = nWritten;
	return TRUE;
}

inline int DecodeBase64Char(unsigned int ch) throw()
{
	// returns -1 if the character is invalid
	// or should be skipped
	// otherwise, returns the 6-bit code for the character
	// from the encoding table
	if (ch >= 'A' && ch <= 'Z')
		return ch - 'A' + 0;	// 0 range starts at 'A'
	if (ch >= 'a' && ch <= 'z')
		return ch - 'a' + 26;	// 26 range starts at 'a'
	if (ch >= '0' && ch <= '9')
		return ch - '0' + 52;	// 52 range starts at '0'
	if (ch == '+')
		return 62;
	if (ch == '/')
		return 63;
	return -1;
}

inline BOOL Base64Decode(LPCSTR szSrc, int nSrcLen, BYTE *pbDest, int *pnDestLen) throw()
{
	// walk the source buffer
	// each four character sequence is converted to 3 bytes
	// CRLFs and =, and any characters not in the encoding table
	// are skiped

	if (szSrc == NULL || pnDestLen == NULL)
	{
		//ATLASSERT(FALSE);
		return FALSE;
	}
	
	LPCSTR szSrcEnd = szSrc + nSrcLen;
	int nWritten = 0;
	
	BOOL bOverflow = (pbDest == NULL) ? TRUE : FALSE;
	
	while (szSrc < szSrcEnd &&(*szSrc) != 0)
	{
		DWORD dwCurr = 0;
		int i;
		int nBits = 0;
		for (i=0; i<4; i++)
		{
			if (szSrc >= szSrcEnd)
				break;
			int nCh = DecodeBase64Char(*szSrc);
			szSrc++;
			if (nCh == -1)
			{
				// skip this char
				i--;
				continue;
			}
			dwCurr <<= 6;
			dwCurr |= nCh;
			nBits += 6;
		}

		if(!bOverflow && nWritten + (nBits/8) > (*pnDestLen))
			bOverflow = TRUE;

		// dwCurr has the 3 bytes to write to the output buffer
		// left to right
		dwCurr <<= 24-nBits;
		for (i=0; i<nBits/8; i++)
		{
			if(!bOverflow)
			{
				*pbDest = (BYTE) ((dwCurr & 0x00ff0000) >> 16);
				pbDest++;
			}
			dwCurr <<= 8;
			nWritten++;
		}

	}
	
	*pnDestLen = nWritten;
	
	if(bOverflow)
	{
		if(pbDest != NULL)
		{
			//ATLASSERT(FALSE);
		}
	
		return FALSE;
	}
	
	return TRUE;
}

#endif // __ATLENC_BASE64_H__
