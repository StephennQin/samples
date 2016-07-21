// DlgConfig.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GetFlights.h"
#include "DlgConfig.h"
#include "afxdialogex.h"
#include "DataProcess.h"
#include "GetFlightsDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDlgConfig �Ի���

CTime CDlgConfig::m_tProcessStartTime;
CTime CDlgConfig::m_tProcessEndTime;

IMPLEMENT_DYNAMIC(CDlgConfig, CDialogEx)

CDlgConfig::CDlgConfig(CWnd* pParent /*=NULL*/)
: CDialogEx(CDlgConfig::IDD, pParent)
{
	m_bStarted = false;
}

CDlgConfig::~CDlgConfig()
{
}

void CDlgConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FROM, m_comboFrom);
	DDX_Control(pDX, IDC_COMBO_TO, m_comboTo);
	DDX_Control(pDX, IDC_DATE_START, m_dtStart);
	DDX_Control(pDX, IDC_DATE_END, m_dtEnd);
	DDX_Control(pDX, IDC_LIST_AIRLINE, m_listAirline);
	DDX_Control(pDX, IDC_LIST_AIRLINE_DATE, m_listAirlineDate);
	DDX_Control(pDX, IDC_LIST_LOG, m_listCtrlLog);
}


BEGIN_MESSAGE_MAP(CDlgConfig, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_AIRLINE_ADD, &CDlgConfig::OnBnClickedBtnAirlineAdd)
	ON_BN_CLICKED(IDC_BTN_AIRLINE_DEL, &CDlgConfig::OnBnClickedBtnAirlineDel)
	ON_BN_CLICKED(IDC_BTN_AIRLINE_ALL, &CDlgConfig::OnBnClickedBtnAirlineAll)
	ON_BN_CLICKED(IDC_BTN_AIRLINE_CANCEL, &CDlgConfig::OnBnClickedBtnAirlineCancel)
	ON_BN_CLICKED(IDC_BTN_AIRLINE_DATE_ADD, &CDlgConfig::OnBnClickedBtnAirlineDateAdd)
	ON_BN_CLICKED(IDC_BTN_AIRLINE_DATE_DEL, &CDlgConfig::OnBnClickedBtnAirlineDateDel)
	ON_BN_CLICKED(IDC_BTN_AIRLINE_DATE_DELALL, &CDlgConfig::OnBnClickedBtnAirlineDateDelall)
	ON_BN_CLICKED(IDC_LOAD_BTN, &CDlgConfig::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_SAVE_BTN, &CDlgConfig::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_START, &CDlgConfig::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_CLEAR_LOG, &CDlgConfig::OnBnClickedBtnClearLog)
	ON_BN_CLICKED(IDC_QUERY_LESS_CHANGE_FLIGHT_BTN, &CDlgConfig::OnBnClkQueryLessChangeFlightBtn)
	ON_MESSAGE(WM_PREPARE_PROXY_IP_PROGRESS, &CDlgConfig::OnPrepareProxyIpProgress)
END_MESSAGE_MAP()


// CDlgConfig ��Ϣ�������


BOOL CDlgConfig::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_dtStart.SetFormat(_T("yyyy-MM-dd"));
	m_dtEnd.SetFormat(_T("yyyy-MM-dd"));

	m_comboFrom.ModifyACBStyle( 0, ACBS_AUTOSUGGEST);
	m_comboTo.ModifyACBStyle( 0, ACBS_AUTOSUGGEST);

	CDataProcess::GetInstance()->LoadCityCodes();
	map<CString,CString>::iterator itmap;
	for (itmap = CDataProcess::GetInstance()->m_mapCityCodes.begin(); itmap != CDataProcess::GetInstance()->m_mapCityCodes.end();itmap++)  
	{ 
		m_comboFrom.AddString(itmap->second);
		m_comboTo.AddString(itmap->second);
	}

	m_imageList.Create(IDB_BMP_AIR,32,10,ILC_COLOR32);
	m_listAirline.SetImageList(&m_imageList,LVSIL_NORMAL);
	m_listAirlineDate.SetExtendedStyle(m_listAirlineDate.GetExtendedStyle()|LVS_EX_FLATSB|LVS_EX_SUBITEMIMAGES|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	//������
	m_listAirlineDate.InsertColumn(0,_T("��������"),LVCFMT_CENTER,100);
	m_listAirlineDate.InsertColumn(1,_T("�������"),LVCFMT_CENTER,100);
	m_listAirlineDate.InsertColumn(2,_T("��ʼ����"),LVCFMT_CENTER,100);
	m_listAirlineDate.InsertColumn(3,_T("��������"),LVCFMT_CENTER,100);	

	m_listCtrlLog.SetExtendedStyle(m_listCtrlLog.GetExtendedStyle()|LVS_EX_FLATSB|LVS_EX_SUBITEMIMAGES|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_listCtrlLog.InsertColumn(0,_T("ʱ��"),LVCFMT_CENTER,60);
	m_listCtrlLog.InsertColumn(1,_T("����"),LVCFMT_LEFT,250);
	//	AddLog(_T("�½�|8835|PFV|ADE|2013-12-12"));

	list<PTAirLineInfo> listAirline;
	if (CDataProcess::GetInstance()->LoadAirlinesFromXml(listAirline))
	{
		list<PTAirLineInfo>::iterator it;  
		int nIndex = 0;
		PTAirLineInfo pInfo = NULL;
		for (it = listAirline.begin(); it != listAirline.end();it++)  
		{  
			pInfo = *it;
			nIndex = m_listAirline.InsertItem(m_listAirline.GetItemCount(),pInfo->strFromCity + _T("-") + pInfo->strToCity,0);
			m_listAirline.SetItemData(nIndex,(DWORD)pInfo);
		}
	}

	//list<PTAirLineDateInfo> listAirDate1;
	//listAirDate1.clear();
	//if (CDataProcess::GetInstance()->LoadAirlineDateFromXml(listAirDate1))
	//{
	//	CDataProcess::GetInstance()->GenAirLine(listAirDate1);
	//}

	list<PTAirLineDateInfo> listAirDate;
	if (CDataProcess::GetInstance()->LoadAirlineDateFromXml(listAirDate))
	{
		__SetListAirDateDataListCtl(listAirDate);
	}

	GetDlgItem(IDC_PROCESS_OK_LAB)->SetWindowText(_T(""));

#ifndef CEAIR_MOBILE_E
	__EnableStartBtn(FALSE);
#endif

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgConfig::OnBnClickedBtnAirlineAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFrom,strTo,strAirLine;
	m_comboFrom.GetText(strFrom);
	m_comboTo.GetText(strTo);
	strFrom.Trim();
	strTo.Trim();
	if (strFrom.GetLength() <= 0 || CDataProcess::GetInstance()->IsCityExist(strFrom))
	{
		MessageBox(_T("�������в����ڣ�"));
		return;
	}
	if (strTo.GetLength() <= 0 || CDataProcess::GetInstance()->IsCityExist(strTo))
	{
		MessageBox(_T("������в����ڣ�"));
		return;
	}

	if (0 == strFrom.Compare(strTo))
	{
		MessageBox(_T("�������к͵�����в�����ͬ��"));
		return;
	}
	strAirLine = strFrom + "-" + strTo;

	int nCount = m_listAirline.GetItemCount();

	CString strText;
	for (int nIndex = 0; nIndex < nCount; nIndex++)
	{
		strText = m_listAirline.GetItemText(nIndex,0);
		if (0 == strAirLine.Compare(strText))
		{
			MessageBox(_T("�ú����Ѿ����ڣ�"));
			return;
		}
	}

	int nNewIndex = m_listAirline.InsertItem(nCount,strAirLine,0);
	if ( nNewIndex >= 0)
	{
		PTAirLineInfo pAirline = new TAirLineInfo;
		pAirline->strFromCity = strFrom;
		pAirline->strFromCityCode = CDataProcess::GetInstance()->GetCityCodeByName(strFrom);
		pAirline->strToCity = strTo;
		pAirline->strToCityCode = CDataProcess::GetInstance()->GetCityCodeByName(strTo);

		m_listAirline.SetItemData(nNewIndex,(DWORD)pAirline);
	}
}


void CDlgConfig::OnBnClickedBtnAirlineDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nCount = m_listAirline.GetItemCount();
	for(int nIndex = nCount - 1; nIndex >= 0; nIndex--)
	{
		if( m_listAirline.GetItemState(nIndex, LVIS_SELECTED) == LVIS_SELECTED )
		{
			PTAirLineInfo pAirline = (PTAirLineInfo)m_listAirline.GetItemData(nIndex);
			m_listAirline.DeleteItem(nIndex);
			delete pAirline;
		}
	}
}


void CDlgConfig::OnBnClickedBtnAirlineAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nCount = m_listAirline.GetItemCount();
	for (int nIndex = 0; nIndex < nCount; nIndex++)
	{
		m_listAirline.SetItemState(nIndex, LVIS_FOCUSED | LVIS_SELECTED,LVIS_FOCUSED | LVIS_SELECTED);   //ѡ����
		//		m_listAirline.SetSelectionMark(nIndex);
	}
	m_listAirline.SetFocus();
}


void CDlgConfig::OnBnClickedBtnAirlineCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_listAirline.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		while (pos)
		{
			int nItem = m_listAirline.GetNextSelectedItem(pos);
			m_listAirline.SetItemState(nItem, 0, LVIS_SELECTED);
		}
	}
}


void CDlgConfig::OnBnClickedBtnAirlineDateAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTime tStart,tEnd;
	m_dtStart.GetTime(tStart);
	m_dtEnd.GetTime(tEnd);

	CTimeSpan ts = tEnd - tStart;
	if (ts.GetDays() < 0)
	{
		MessageBox(_T("��ʼ���ڲ��ܴ��ڽ������ڣ�"));
		return;
	}

	POSITION pos = m_listAirline.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		CString strDate;
		while (pos)
		{
			int nItem = m_listAirline.GetNextSelectedItem(pos);
			PTAirLineInfo pAirline = (PTAirLineInfo)m_listAirline.GetItemData(nItem);
			if (NULL != pAirline)
			{
				int nNewItem = m_listAirlineDate.InsertItem(0,pAirline->strFromCity);
				m_listAirlineDate.SetItemText(nNewItem,1,pAirline->strToCity);
				strDate.Format(_T("%d-%02d-%02d"),tStart.GetYear(),tStart.GetMonth(),tStart.GetDay());
				m_listAirlineDate.SetItemText(nNewItem,2,strDate);
				strDate.Format(_T("%d-%02d-%02d"),tEnd.GetYear(),tEnd.GetMonth(),tEnd.GetDay());
				m_listAirlineDate.SetItemText(nNewItem,3,strDate);

				PTAirLineDateInfo pAirDateInfo = new TAirLineDateInfo;
				pAirDateInfo->_airInfo = *pAirline;
				pAirDateInfo->tStart = tStart;
				pAirDateInfo->tEnd = tEnd;

				m_listAirlineDate.SetItemData(nNewItem,(DWORD)pAirDateInfo);
			}
		}
	}
}


void CDlgConfig::OnBnClickedBtnAirlineDateDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nIndex = m_listAirlineDate.GetSelectionMark();
	if (nIndex >= 0)
	{
		PTAirLineDateInfo pInfo = (PTAirLineDateInfo)m_listAirlineDate.GetItemData(nIndex);
		m_listAirlineDate.DeleteItem(nIndex);
		delete pInfo;
	}
}


void CDlgConfig::OnBnClickedBtnAirlineDateDelall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DeleteAllAirlineDates();
}

// ɾ���б������еĺ�����Ϣ
void CDlgConfig::DeleteAllAirline(void)
{
	int nCount = m_listAirline.GetItemCount();
	for (int nIndex = nCount - 1; nIndex >=0 ; nIndex--)
	{
		PTAirLineInfo pAirline = (PTAirLineInfo)m_listAirline.GetItemData(nIndex);
		m_listAirline.DeleteItem(nIndex);
		delete pAirline;
	}
}

// ɾ�����еĺ���������Ϣ
void CDlgConfig::DeleteAllAirlineDates(void)
{
	int nCount = m_listAirlineDate.GetItemCount();
	for (int nIndex = nCount - 1; nIndex >=0 ; nIndex--)
	{
		PTAirLineDateInfo pInfo = (PTAirLineDateInfo)m_listAirlineDate.GetItemData(nIndex);
		m_listAirlineDate.DeleteItem(nIndex);
		delete pInfo;
	}
}

BOOL CDlgConfig::DestroyWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	DeleteAllAirlineDates();
	DeleteAllAirline();

	return CDialogEx::DestroyWindow();
}


void CDlgConfig::OnBnClickedBtnStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_bStarted)
	{
		((CGetFlightsDlg*)AfxGetMainWnd())->Start(false);
		GetDlgItem(IDC_BTN_START)->SetWindowText(_T("��  ʼ"));
		m_bStarted = false;

		return;
	}


	GetDlgItem(IDC_BTN_START)->SetWindowText(_T("ͣ  ֹ"));
	m_bStarted = true;
	m_tProcessStartTime = CTime::GetCurrentTime();

	SaveAirlines();

	__GetCurListAirDateData(m_listAirDateData);

	CDataProcess::GetInstance()->SaveAirlineDateToXml(m_listAirDateData);
#ifndef GET_KN_FLIGHT
	#ifndef GET_CA_FLIGHT
	#ifndef GET_AQ_FLIGHT
		#ifdef CEAIR_MOBILE_E
			((CGetFlightsDlg*)AfxGetMainWnd())->ClientMobileEStart(false);
		#else
			#if (SSS_CLIENT_NUM == SSS_1_CLIENT)
				((CGetFlightsDlg*)AfxGetMainWnd())->Client1Start(false);
			#else
				((CGetFlightsDlg*)AfxGetMainWnd())->Start(false);
			#endif
		#endif
	#else //#define GET_AQ_FLIGHT
		((CGetFlightsDlg*)AfxGetMainWnd())->Client1Start(false);
	#endif
	#else //#ifdef GET_CA_FLIGHT
		((CGetFlightsDlg*)AfxGetMainWnd())->CaClientStart(false);
	#endif
#else
	((CGetFlightsDlg*)AfxGetMainWnd())->KnClientStart(false);
#endif
}

// ���溽����Ϣ
BOOL CDlgConfig::SaveAirlines(void)
{
	list<PTAirLineInfo> listAirline;
	int nCount = m_listAirline.GetItemCount();
	PTAirLineInfo pInfo = NULL;
	for (int nIndex = 0; nIndex < nCount; nIndex++)
	{
		pInfo = (PTAirLineInfo)m_listAirline.GetItemData(nIndex);
		listAirline.push_back(pInfo);
	}

	return CDataProcess::GetInstance()->SaveAirlinesToXml(listAirline);
}

// �����־��Ϣ
void CDlgConfig::AddLog(CString strLog)
{
	CTime t = CTime::GetCurrentTime();
	CString strTime;
	strTime.Format(_T("%02d:%02d:%02d"),t.GetHour(),t.GetMinute(),t.GetSecond());
	int nIndex = m_listCtrlLog.InsertItem(0,strTime);
	m_listCtrlLog.SetItemText(nIndex,1,strLog);
}

void CDlgConfig::AddProcessTime(void)
{
	m_tProcessEndTime = CTime::GetCurrentTime();
	CTimeSpan ts = m_tProcessEndTime - m_tProcessStartTime;
	CString str;
	str.Format(_T("һ��������%d:%d:%d�������,��ʱ��%d��%d��"), m_tProcessEndTime.GetHour(), m_tProcessEndTime.GetMinute()
		, m_tProcessEndTime.GetSecond(), ts.GetMinutes(), ts.GetSeconds());
	GetDlgItem(IDC_PROCESS_OK_LAB)->SetWindowText(str);
	m_tProcessStartTime = m_tProcessEndTime;
}

void CDlgConfig::OnBnClickedBtnClearLog()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_listCtrlLog.DeleteAllItems();
}

void CDlgConfig::EnableCtrls(BOOL bEnable)
{
	if (bEnable)
	{
		GetDlgItem(IDC_BTN_START)->SetWindowText(_T("��  ʼ"));
	}
	else
	{
		GetDlgItem(IDC_BTN_START)->SetWindowText(_T("ͣ  ֹ"));
	}
}

void CDlgConfig::__SetListAirDateDataListCtl(list<PTAirLineDateInfo> &listAirDate)
{
	list<PTAirLineDateInfo>::iterator it;  
	int nIndex = 0;
	PTAirLineDateInfo pInfo = NULL;
	CString strDate;
	for (it = listAirDate.begin(); it != listAirDate.end();it++)  
	{  
		pInfo = *it;
		nIndex = m_listAirlineDate.InsertItem(m_listAirlineDate.GetItemCount(),pInfo->_airInfo.strFromCity);
		m_listAirlineDate.SetItemText(nIndex,1,pInfo->_airInfo.strToCity);
		strDate.Format(_T("%d-%02d-%02d"),pInfo->tStart.GetYear(),pInfo->tStart.GetMonth(),pInfo->tStart.GetDay());
		m_listAirlineDate.SetItemText(nIndex,2,strDate);
		strDate.Format(_T("%d-%02d-%02d"),pInfo->tEnd.GetYear(),pInfo->tEnd.GetMonth(),pInfo->tEnd.GetDay());
		m_listAirlineDate.SetItemText(nIndex,3,strDate);

		m_listAirlineDate.SetItemData(nIndex,(DWORD)pInfo);
	}
}
void CDlgConfig::__GetCurListAirDateData(list<PTAirLineDateInfo> & listAirDateData)
{
	listAirDateData.clear();
	int nCount = m_listAirlineDate.GetItemCount();
	PTAirLineDateInfo pInfo = NULL;
	for (int nIndex = 0; nIndex < nCount; nIndex++)
	{
		pInfo = (PTAirLineDateInfo)m_listAirlineDate.GetItemData(nIndex);
		listAirDateData.push_back(pInfo);
	}
}
void CDlgConfig::OnBnClickedBtnLoad()
{
	CString strPath;
	CFileDialog dlg(TRUE,_T("xml"),_T("*.xml"), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT
		, _T("xml File(*.xml)|*.xml||"));

	if(dlg.DoModal()!=IDOK)
		return;

	strPath = dlg.GetPathName();

	m_listAirlineDate.DeleteAllItems();
	list<PTAirLineDateInfo> listAirDate;
	if (CDataProcess::GetInstance()->LoadAirlineDateFromXml(listAirDate, strPath))
	{
		__SetListAirDateDataListCtl(listAirDate);
	}
}
void CDlgConfig::OnBnClickedBtnSave()
{
	CFileDialog dlg(FALSE,_T("xml"),_T("*.xml"), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, _T("xml File(*.xml)|*.xml||"));
	if(dlg.DoModal() !=IDOK)
		return;
	CString strPath = dlg.GetPathName();
	__GetCurListAirDateData(m_listAirDateData);
	CDataProcess::GetInstance()->SaveAirlineDateToXml(m_listAirDateData, strPath);
}

void CDlgConfig::OnBnClkQueryLessChangeFlightBtn()
{
	// TODO: Add your control notification handler code here
	EnabeleQueryLessChangeFlightBtn(FALSE);
}

void CDlgConfig::EnabeleQueryLessChangeFlightBtn(BOOL bEnable)
{
	GetDlgItem(IDC_QUERY_LESS_CHANGE_FLIGHT_BTN)->EnableWindow(bEnable);
}
void CDlgConfig::__EnableStartBtn(BOOL bEnable, int nCount)
{
	CString str = _T("����Ԥ�������IP�����Ե�3��4����");
	CString strCount;
	if (bEnable)
		str = _T("");
	else
	{
		strCount.Format(_T(",����%d��"),nCount);
		str = str + strCount;
	}
	GetDlgItem(IDC_PROCESS_OK_LAB)->SetWindowText(str);
	GetDlgItem(IDC_BTN_START)->EnableWindow(bEnable);
}
LRESULT CDlgConfig::OnPrepareProxyIpProgress(WPARAM wParam, LPARAM lParam)
{
	BOOL bOk = (BOOL)wParam;
	int nCount = (int)lParam;
	__EnableStartBtn(bOk, nCount);
	return 0L;
}