#pragma once

#include "common/AdvComboBox.h"
#include "afxcmn.h"
#include <list>
#include "DataProcess.h"
#include "common/xgmvar.h"

using namespace std;

// CDlgConfig �Ի���

class CDlgConfig : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgConfig)

public:
	CDlgConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgConfig();

// �Ի�������
	enum { IDD = IDD_DLG_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CAdvComboBox m_comboFrom;
	CAdvComboBox m_comboTo;
	CDateTimeCtrl m_dtStart;
	CDateTimeCtrl m_dtEnd;
	CListCtrl m_listAirline;
	CListCtrl m_listAirlineDate;
	virtual BOOL OnInitDialog();
	CListCtrl m_listCtrlLog;

	list<PTAirLineDateInfo> m_listAirDateData;
	bool		m_bStarted;

	CImageList	m_imageList;
	afx_msg void OnBnClickedBtnAirlineAdd();
	afx_msg void OnBnClickedBtnAirlineDel();
	afx_msg void OnBnClickedBtnAirlineAll();
	afx_msg void OnBnClickedBtnAirlineCancel();
	afx_msg void OnBnClickedBtnAirlineDateAdd();
	afx_msg void OnBnClickedBtnAirlineDateDel();
	afx_msg void OnBnClickedBtnAirlineDateDelall();

	// ɾ���б������еĺ�����Ϣ
	void DeleteAllAirline(void);
	// ɾ�����еĺ���������Ϣ
	void DeleteAllAirlineDates(void);
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedBtnStart();
	// ���溽����Ϣ
	BOOL SaveAirlines(void);

	void AddLog(CString strLog);
	void AddProcessTime(void);
	afx_msg void OnBnClickedBtnClearLog();
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnBnClickedBtnSave();
	LRESULT OnPrepareProxyIpProgress(WPARAM wParam, LPARAM lParam);

	void EnableCtrls(BOOL bEnable);
	void EnabeleQueryLessChangeFlightBtn(BOOL bEnable);

private:
	void	__SetListAirDateDataListCtl(list<PTAirLineDateInfo> &listAirDate);
	void	__GetCurListAirDateData(list<PTAirLineDateInfo> & listAirDateData);
	void	__EnableStartBtn(BOOL bEnable, int nCount=0);

	static CTime m_tProcessStartTime;
	static CTime m_tProcessEndTime;

public:
	afx_msg void OnBnClkQueryLessChangeFlightBtn();
};
