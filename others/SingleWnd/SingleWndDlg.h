
// SingleWndDlg.h : ͷ�ļ�
//

#pragma once

#define WM_USER_NOTIFY  WM_USER +1
// CSingleWndDlg �Ի���
class CSingleWndDlg : public CDialog
{
// ����
public:
	CSingleWndDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SINGLEWND_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnNotifyMsg(WPARAM wparam,LPARAM lparam);
public:
	CDialog *m_pDlg;
	NOTIFYICONDATA m_NotifyIcon;
	afx_msg void OnPopupExit();
	afx_msg void OnPopupDlg1();
	afx_msg void OnPopupDlg2();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	CDialog *m_pDlgShowing;
	bool HasShowingDlg(void);
	afx_msg void OnPopupNoModal();
};
