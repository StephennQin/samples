// ������������� Microsoft Visual C++ ������ IDispatch ��װ��

// ע��: ��Ҫ�޸Ĵ��ļ������ݡ����������
//  Microsoft Visual C++ �������ɣ������޸Ľ������ǡ�


#include "stdafx.h"
#include "explorer1.h"

/////////////////////////////////////////////////////////////////////////////
// CExplorer1

IMPLEMENT_DYNCREATE(CExplorer1, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CExplorer1 ����

/////////////////////////////////////////////////////////////////////////////
// CExplorer1 ����
void CExplorer1::Navigate(LPCTSTR URL)
{
	CString		url(URL);

	m_strUrl = url;

	_variant_t	flags(0L,VT_I4);
	_variant_t	target_frame_name("");
	_variant_t	post_data("");
	_variant_t	headers("");

	Navigate(url.AllocSysString(),
		&flags,
		&target_frame_name,
		&post_data,
		&headers);
}

IHTMLDocument2 * CExplorer1::GetDocument()
{
	IHTMLDocument2 *document = NULL;

	// get browser document's dispatch interface

	IDispatch *document_dispatch = get_Document();

	if (document_dispatch != NULL) {

		// get the actual document interface

		document_dispatch->QueryInterface(IID_IHTMLDocument2,
			(void **)&document);

		// release dispatch interface

		document_dispatch->Release();
	}

	return document;
}