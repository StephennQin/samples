
// GetFlightsDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "DlgConfig.h"
//#include "DlgGetFlights.h"
//#include "DlgBrowsers.h"
#include "DlgShowFlights.h"
#include "CeairMobileEConst.h"
#include <map>

#ifndef GET_KN_FLIGHT
	#ifndef GET_CA_FLIGHT
		#ifndef GET_AQ_FLIGHT
			#ifdef CEAIR_MOBILE_E
				#define ThreadCount	(1)//15
			#else
				#if (SSS_CLIENT_NUM == SSS_1_CLIENT)
					#define ThreadCount	(1)//10
				#else
					#define ThreadCount	(15)
				#endif
			#endif
		#else//#define GET_AQ_FLIGHT
			#define ThreadCount (20) //20
		#endif
	#else //#ifdef GET_CA_FLIGHT
		#define ThreadCount	(10)
	#endif
#else
	#if ( GET_FLIGHT_TYPE == 0 )
		#define ThreadCount (5)
	#elif( GET_FLIGHT_TYPE == 1 )
		#define ThreadCount (10)
	#else
		#define ThreadCount (1)//10
	#endif
#endif
//Ҫ���������(һ������ݱ�����һ��)
typedef struct AirLineDateProcess
{
	CTime				tDate;		//����
	CDialogEx*			pDlg;
	list<PTAirLineInfo>	listAirLine;
}TAirLineDateProcess,*PTAirLineDateProcess;

typedef struct AirLineDetailProcess
{
	CDialogEx*			pDlg;
	list<PAirLineDetailInfo>	listAirLine;
}TAirLineDetailProcess,*PTAirLineDetailProcess;

// CGetFlightsDlg �Ի���
class CGetFlightsDlg : public CDialogEx
{
// ����
public:
	CGetFlightsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GETFLIGHTS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public:
	static HWND GetDlgConfigHwnd() { return m_hDlgConfigHwnd;};

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
	CTabCtrl m_tab;

	bool	m_bCloseClicked;
	bool	m_bStart;

	CDlgConfig* m_pDlgConfig;
	CDlgShowFlights*	m_pDlgShowFlights;

	std::list<PAirLineDetailInfo>	m_allLineList;

	map<UINT, PTAirLineDetailProcess> m_client1MapProcess;
	map<CString, PTAirLineDateProcess> m_mapProcess;


	virtual BOOL DestroyWindow();
	void LayoutCtrls(void);
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	int Start(bool bLoop);
	int Client1Start(bool bLoop);//���к�����1���ͻ�������
	int CaClientStart(bool bLoop);//�����ͻ���
	int ClientMobileEStart(bool bLoop);//�����ƶ�E
	int KnClientStart(bool bLoop);//�����ͻ���

	void AddLog(CString strLog);

	void ClearAllLineList();
	// ����map
	int ClearProcessMap(map<CString,PTAirLineDateProcess>& mapProcess);
	//�̴߳�����,һ������һ���߳�
	static void ThreadProcessKn( LPVOID pParam );
	static void ThreadProcess( LPVOID pParam );
	static void ThreadProcessClient1( LPVOID pParam );
	static void __ThreadAqFlightProcess( LPVOID pParam );
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void Stop(void);

	//��Ϣ��Ӧ�����������߳��Ѿ�����
	LRESULT OnProcessThreadEnd(WPARAM wParam, LPARAM lParam);

	LRESULT OnUpdateFlight(WPARAM wParam, LPARAM lParam);
	LRESULT OnQueryLessChangeFlightOk(WPARAM wParam, LPARAM lParam);

	UINT	m_nThreadEndCount;
	MUINT	m_uThreadCount;
	afx_msg void OnClose();

	//����6���¼�
	static HANDLE   m_h6Second;
	static HANDLE   m_h6Second2;
	//�˳�����¼�
	static HANDLE	m_hExitEvt;
	//����ִ���¼�
	static HANDLE	m_hContinueDoEvt;
	static CGetFlightsDlg*	m_pThis;
	static HWND		m_hDlgConfigHwnd;

	//��������̳߳�
	static UINT __ThreadInsertKnJobToThreadPool(void* pParam);
	static UINT __ThreadInsertJobToThreadPool( void* pParam );
	static UINT __ThreadInsertJobToThreadPoolClient1(void * pParam );
	//�ȴ��̳߳��е�����������ɣ��̳߳��е�����ִ�о��������ԣ���ֹ��Щ����ִ�д��������Щ����ִ�еĴ����٣�
	static void __WailAllJobFinished(bool bWaitAll=true);

	void	__Reset9CFlightInfoList(list<PT9CFlightInfo> &flightList);
	PT9CFlightInfo	__Find9CFlight(list<PT9CFlightInfo> &flightList, PT9CFlightInfo pKey, BOOL *pbFind);
	void	__Merge9CFlightInfoList(list<PT9CFlightInfo> & fromFlightList, list<PT9CFlightInfo> & toFlightList);
	void	__Free9CFlightInfoList(list<PT9CFlightInfo> &flightList);
	void	__SetCurThreadCount(UINT u);
	UINT	__GetCurThreadCount(void);
	static BOOL	__IsJsonFlightDataOk(list<PT9CFlightInfo>& listFlight);
	//�Ӵ���ץȡһ��������Ϣ
	static BOOL __GetSssFlight(BOOL bChangeProxy, CString strFromCityCode,CString strToCityCode, 
		CStringA straStartDate, CStringA straEndDate, wstring& httpResponseContent);
	//�Ӿ�Ԫץȡһ��������Ϣ
	static BOOL __GetAqFlightFromSite(BOOL bChangeProxy, CString & strFromCityCode,CString & strToCityCode, 
		CStringA & straStartDate, wstring& httpResponseContent);
	//�Ӵ���ץȡһ��������Ϣ
	static BOOL	__GetKnFlight(BOOL bChangeProxy, CString & strFromCityCode,CString & strToCityCode, 
		CStringA & straStartDate, wstring& httpResponseContent);
	static BOOL __GetSssFlightFromNewSite(BOOL bChangeProxy, CString & strFromCityCode,CString & strToCityCode, 
		CStringA & straStartDate, wstring& httpResponseContent);
	static std::string	__GetCityNameUrlCode(CString & strCityCode);

	static BOOL		m_bNoChangeFlightPoll;//��������ĺ����Ƿ��Ѿ���ѯ���


private:
	map<UINT, SCaAirLineDetailProcess*> m_caMapProcess;//ÿ���̴߳���Ҫ����ĺ����б�map�е�key��Ϊ���
	//map<int, std::list<UINT>> m_caProductFlightMap;//ÿ����Ʒ�İ����ĺ����б�һ��ҳ���ϵ�һ������ͼƬΪһ����Ʒ
	std::list<SCaLowPriceFlightInfo*>	m_caLowPriceAirLineList;
	void	__ReleaseCaLowPriceFlightList();
	void	__LoadCaLowPriceAirLineList();
	static BOOL	__GetCaLowPriceFlight(BOOL bChangeProxy, int iCityCode, const CString & strCity, wstring& httpResponseContent);
	//��������̳߳�
	static UINT __ThreadInsertCaJobToThreadPool( void* pParam );
	static UINT __ThreadInsertAqJobToThreadPool( void* pParam );
	//�̴߳�����,һ���̴߳�������
	static void __ThreadCaLowPriceFlightProcess( LPVOID pParam );

	
	static UINT __ThreadInsertMobileEJobToThreadPool( LPVOID pParam );
	static void __CeairMobileEThreadProcess( LPVOID pParam );

	template <class T>
	void	__FreeFlightList(list<T*> &flightList)
	{
		list<T*>::iterator it;
		T* pFlight = NULL;

		if (flightList.empty())
			return;
		for (it = flightList.begin(); it != flightList.end(); it++)
		{
			pFlight = *it;
			delete pFlight;
			pFlight = NULL;
		}
		flightList.clear();
	}
	void	__ResetCaTuanFlightInfoList(list<SCaLowPriceFlightDetail*> &flightList);
	void	__MergeCaTuanFlightInfoList(list<SCaLowPriceFlightDetail*> & fromFlightList, list<SCaLowPriceFlightDetail*> & toFlightList);
	SCaLowPriceFlightDetail*	__FindCaTuanFlight(list<SCaLowPriceFlightDetail*>  &flightList, SCaLowPriceFlightDetail* pKey, BOOL *pbFind);

	//�����ƶ�E
	void	__ResetCeairMEFlightInfoList(list<SCeairFlightInfo*> &flightList);
	void	__MergeCeairMEFlightInfoList(list<SCeairFlightInfo*> & fromFlightList, list<SCeairFlightInfo*> & toFlightList);
	SCeairFlightInfo*	__FindCeairMEFlight(list<SCeairFlightInfo*>  &flightList, SCeairFlightInfo* pKey, BOOL *pbFind);

public:

	static CStringA CityCode2CityNameCode(CStringA straCityCode)
	{
		CStringA CityNameCode;
		if(straCityCode == "NAY")
			CityNameCode = "BJS";
		else if(straCityCode == "PVG")
			CityNameCode = "SHA";
		else if(straCityCode == "PEK")
			CityNameCode = "BJS";
		else 
			CityNameCode = straCityCode;
		return CityNameCode;
	}
};
