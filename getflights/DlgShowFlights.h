#pragma once


// CDlgShowFlights �Ի���

class CDlgShowFlights : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShowFlights)

public:
	CDlgShowFlights(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgShowFlights();

// �Ի�������
	enum { IDD = IDD_DLG_SHOW_FLIGHTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
