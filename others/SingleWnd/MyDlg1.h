#pragma once


// CMyDlg1 �Ի���
#define DOMAL 1

class CMyDlg1 : public CDialog
{
	DECLARE_DYNAMIC(CMyDlg1)

public:
	CMyDlg1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyDlg1();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	bool m_style;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
