// Account.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Serialize.h"
#include "Account.h"


// CAccount
IMPLEMENT_SERIAL(CAccount, CObject, 1)

CAccount::CAccount()
{
}
CAccount::CAccount(CString age, CString name)
:m_age(age), m_name(name)
{
}

CAccount::~CAccount()
{
}


// CAccount ��Ա����

void CAccount::Serialize(CArchive& ar)
{
	CObject::Serialize (ar);
	if (ar.IsStoring())
	{	
		ar<<m_age<<m_name;
	}
	else
	{	// loading code
		ar>>m_age>>m_name;
	}
}
