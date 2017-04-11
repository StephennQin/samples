// Page1.cpp : implementation file
//

#include "stdafx.h"
#include "LabelProp.h"
#include "Page1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPage1 property page

IMPLEMENT_DYNCREATE(CPage1, CPropertyPage)

CPage1::CPage1() : CPropertyPage(CPage1::IDD)
{
	//{{AFX_DATA_INIT(CPage1)
	m_nLineWidth = 0;
	//}}AFX_DATA_INIT
}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage1)
	DDX_Text(pDX, IDC_LINE_WIDTH, m_nLineWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CPage1)
	ON_EN_CHANGE(IDC_LINE_WIDTH, OnChangeLineWidth)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage1 message handlers

void CPage1::OnChangeLineWidth() 
{
	//���Ƚ�Ӧ�ð�ť����Ϊ����
	SetModified(TRUE);
}
#include "LabelPropView.h"
BOOL CPage1::OnApply() 
{
	UpdateData(TRUE);
	//���ı����е��߿��ݸ���ͼ
	//��ȡ��ǰ��ͼ
	CLabelPropView *pView=(CLabelPropView*)
	((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	//��ֵ
	pView->m_nWidth=m_nLineWidth;
	//��ͼʹ���µ��߿��ػ�
	pView->Invalidate(TRUE);
	return CPropertyPage::OnApply();
}

BOOL CPage1::OnSetActive() 
{
	((CPropertySheet*)GetParent())->
		SetWizardButtons(PSWIZB_NEXT);
	return CPropertyPage::OnSetActive();
}
