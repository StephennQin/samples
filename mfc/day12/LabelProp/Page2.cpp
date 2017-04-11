// Page2.cpp : implementation file
//

#include "stdafx.h"
#include "LabelProp.h"
#include "Page2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPage2 property page

IMPLEMENT_DYNCREATE(CPage2, CPropertyPage)

CPage2::CPage2() : CPropertyPage(CPage2::IDD)
{
	//{{AFX_DATA_INIT(CPage2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_Color=RGB(0,0,0);
}

CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CPage2)
	ON_BN_CLICKED(IDC_SET_COLOR, OnSetColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage2 message handlers
#include "LabelPropView.h"
BOOL CPage2::OnApply() 
{
	//����ɫ���ݸ���ͼ����ͼʹ���µ���ɫ�ػ�
	CLabelPropView *pView=(CLabelPropView*)
		((CFrameWnd*)(AfxGetMainWnd()))->GetActiveView();
	pView->m_Color=m_Color;
	//��ͼʹ���µ���ɫ�ػ�
	pView->Invalidate(TRUE);	
	return CPropertyPage::OnApply();
}

void CPage2::OnSetColor() 
{
	//��Ӧ�ð�ť����Ϊ����
	SetModified(TRUE);
	//������ɫ�Ի���
	CColorDialog dlg;
	if(dlg.DoModal()==IDCANCEL)return;
	/*��CPage2�������ɫ���͵ĳ�Ա������ʹ�øñ���
	  �������ɫ�Ի�����ѡ�����ɫ*/
	m_Color=dlg.GetColor();
}

BOOL CPage2::OnSetActive() 
{
	((CPropertySheet*)GetParent())->
		SetWizardButtons(PSWIZB_BACK|PSWIZB_FINISH);	
	return CPropertyPage::OnSetActive();
}
