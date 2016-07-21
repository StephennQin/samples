#pragma once

#include <list>
#include <map>
#include "common/WinHttpClient.h"

#define	 MAX_PROXY_IP_OBJ		(2)
#define	 PROXY_IP_MAX_CHAR		(30)

#define SSS_1_CLIENT		(1)
#define SSS_MULTI_CLIENT		(2)

//��3��ĺ��ࣺGET_FLIGHT_TYPE = 0
//�ӵ�4�쿪ʼ7���ڵĺ��� GET_FLIGHT_TYPE = 1;
//�ӵ�11�쿪ʼ�ĺ��� GET_FLIGHT_TYPE = 2;
//��ǰ���ĺ��� GET_FLIGHT_TYPE = 3;

#define GET_FLIGHT_TYPE	(1)

#if (0 == GET_FLIGHT_TYPE || 1 ==  GET_FLIGHT_TYPE)
	#define SSS_CLIENT_NUM	(1)
	#define MAX_CLIENT_NUM	(1)
#elif(2 ==  GET_FLIGHT_TYPE)
	#define SSS_CLIENT_NUM	(2)
	#define MAX_CLIENT_NUM	(5)
#else//(3 ==  GET_FLIGHT_TYPE)
	#define SSS_CLIENT_NUM	(1)
	#define MAX_CLIENT_NUM	(2)
#endif

//#define  GET_CA_FLIGHT

//#define CEAIR_MOBILE_E

//#define GET_AQ_FLIGHT

//#define GET_KN_FLIGHT

#ifndef GET_KN_FLIGHT
	#ifndef GET_CA_FLIGHT
		#ifndef GET_AQ_FLIGHT
			#ifdef CEAIR_MOBILE_E
				#define	 PROXY_IP_BUF_MAX_COUNT		(5)
			#else
				#if (SSS_CLIENT_NUM == SSS_1_CLIENT)
					#define		GET_FLIGHT_FROM_NEW_SITE
					#define	 PROXY_IP_BUF_MAX_COUNT		(20)//10
				#else //(SSS_CLIENT_NUM == SSS_2_CLIENT)
					#define		GET_FLIGHT_FROM_NEW_SITE
					#define	 PROXY_IP_BUF_MAX_COUNT		(30)
				#endif
			#endif
		#else//#define GET_AQ_FLIGHT
			#define MAX_CLIENT_NUM (1)
			#define PROXY_IP_BUF_MAX_COUNT (20)
		#endif
	#else //#ifdef GET_CA_FLIGHT
		#define MAX_CLIENT_NUM	(1)
		#define	 PROXY_IP_BUF_MAX_COUNT		(20)
	#endif
#else
	#define MAX_CLIENT_NUM (1)
	#if (GET_FLIGHT_TYPE == 0)
		#define PROXY_IP_BUF_MAX_COUNT (20)
	#elif (GET_FLIGHT_TYPE == 1)
		#define PROXY_IP_BUF_MAX_COUNT (20)
	#else 
		#define PROXY_IP_BUF_MAX_COUNT (20)
	#endif
#endif

using namespace std;

//�½����޸����߳ɹ����ʹ���Ϣ����ʾ���½���
#define WM_CTRIP_FLIGHT		(WM_USER + 110)

enum
{
	CA_TUAN_PRODUCT = 0,
	CA_TUAN_LOW_PRICE_APPLY_PRODUT
};
//���д�����Ϣ
typedef struct CityCode
{
	CString strName;
	CString strCode;
}TCityCode,*PTCityCode;

//������Ϣ
typedef struct AirLineInfo
{
	CString strFromCity;
	CString strToCity;
	CString strFromCityCode;
	CString strToCityCode;
	UINT	uMinHangPrice;

	AirLineInfo& operator=(AirLineInfo& value)
	{
		strFromCity = value.strFromCity;
		strFromCityCode = value.strFromCityCode;
		strToCity = value.strToCity;
		strToCityCode = value.strToCityCode;
		uMinHangPrice = value.uMinHangPrice;

		return *this;
	}
}TAirLineInfo,*PTAirLineInfo;

//����������Ϣ�����ڶΣ�
typedef struct AirLineDateInfo
{
	TAirLineInfo	_airInfo;
	CTime			tStart;
	CTime			tEnd;
}TAirLineDateInfo,*PTAirLineDateInfo;

//����������Ϣ
typedef struct AirLineDetailInfo
{
	TAirLineInfo	_airInfo;
	CTime			tStart;
}TAirLineDetailInfo,*PAirLineDetailInfo;

//����������Ϣ�����죩
typedef struct AirLineDateSingle
{
	TAirLineInfo	_airInfo;
	CTime			tDate;
}TAirLineDateSingle,*PTAirLineDateSingle;

typedef struct FlightInfo
{

}TFlightInfo,*PTFlightInfo;



//������Ϣ
typedef struct t9CFlightInfo 
{
	CStringA	straCompany;		//���չ�˾
	CStringA	straFromCityCode;	//�������д���
	CStringA	straToCityCode;		//������д���
	CStringA	straFlightNo;		//�����
	CStringA	straFromDate;		//��������
	CStringA	straToDate;			//��������
	CStringA	straFromTime;		//����ʱ��
	CStringA	straToTime;			//����ʱ��
	int			nMinHangPrice;		//�񺽼�
	int			nPrice1;			//�۸�1
	int			nPrice2;			//�۸�2
	int			nPrice3;			//�۸�3
	int			nMinPrice;			//��ͼ�
	bool		bHavePolicy;		//�Ƿ��ж�Ӧ����������

	CStringA	straPrice1Json;
	CStringA	straPrice2Json;
	CStringA	straPrice3Json;

	t9CFlightInfo()
	{
		straCompany = "9C";
		nMinHangPrice = 0;
		nMinPrice = 0;
		nPrice1 = 0;
		nPrice2 = 0;
		nPrice3 = 0;
		bHavePolicy = false;

		straPrice1Json = "";
		straPrice2Json = "";
		straPrice3Json = "";
	}

	t9CFlightInfo & operator=(const t9CFlightInfo & flight)
	{
		this->straCompany = flight.straCompany;	
		this->straFromCityCode = flight.straFromCityCode;
		this->straToCityCode = flight.straToCityCode;	
		this->straFlightNo = flight.straFlightNo;	
		this->straFromDate = flight.straFromDate;	
		this->straToDate = flight.straToDate;		
		this->straFromTime = flight.straFromTime;		
		this->straToTime = flight.straToTime;	
		this->straCompany = flight.straCompany;
		this->nMinHangPrice = flight.nMinHangPrice;
		this->nMinPrice = flight.nMinPrice;
		this->nPrice1 = flight.nPrice1;
		this->nPrice2 = flight.nPrice2;
		this->nPrice3 = flight.nPrice3;
		this->bHavePolicy = flight.bHavePolicy;
		this->straPrice1Json = flight.straPrice1Json;
		this->straPrice2Json = flight.straPrice2Json;
		this->straPrice3Json = flight.straPrice3Json;

		return *this;
	}

}T9CFlightInfo,*PT9CFlightInfo;

typedef struct _tagTimePara
{
	BYTE u8Hour:8;	//0��7
	BYTE u8Minute:8;//8��15
	BYTE u8Sec:8;	//16��23
	BYTE uReserved:8;//24��31
}STimePara;
typedef union _tagUTimePara
{
	STimePara	sTime;
	UINT		u32;
}UTimePara;

typedef struct _tagDatePara
{
	WORD wYear:16;	//0��15
	BYTE u8Month:5;//16��20
	BYTE u8Day:6;	//21��26
	BYTE uReserved:5;//27��31
}SDatePara;
typedef union _tagUDatePara
{
	SDatePara	sDate;
	UINT		u32;
}UDatePara;

//������Ϣ
typedef struct ConfigInfo
{
	CStringA strDbHost;
	CStringA strDbUser;
	CStringA strDbPwd;
	CStringA strDbName;
	UINT	nDbPort;
	UINT	uClientId;

	CTime	tNoChangeFlightPoll;
	CTime	tLessChangeFlightPoll;
	BOOL	bAutoModDate;
	BOOL	bSelP4Ticket;	//�Ƿ���4�ۼ����µ�Ʊ
	BOOL	bSelP5Ticket;	//�Ƿ���4�����ϵ�Ʊ
	BOOL	bSelSpecialPriceTicket;	//�Ƿ���4�����µ��ؼ�Ʊ��9��99��199��299Ԫ����
	int		nP4SpecialPrice;	//����4�� nP4SpecialPrice�۸�����������ĩβ��9��Ʊ����
	UTimePara uSel9Start;
	UTimePara uSel9End;

	ConfigInfo()
	{
		strDbHost	= _T("127.0.0.1");
		strDbUser	= _T("root");
		strDbPwd	= _T("hifb@2014");
		strDbName	= _T("hifb");
		nDbPort		= 3306;
		bSelP4Ticket = TRUE;
		bSelP5Ticket = TRUE;
		bSelSpecialPriceTicket = TRUE;
		nP4SpecialPrice = 800;
		uSel9Start.u32 = 0;
		uSel9End.u32 = 0;
	}
}TConfigInfo,*PTConfigInfo;

typedef struct _tagGetIp
{
	char	szIpBuf[PROXY_IP_MAX_CHAR+1];
	int		iRowId;
	_tagGetIp()
	{
		SecureZeroMemory(szIpBuf, sizeof(szIpBuf));
		szIpBuf[0] = '\0';
		iRowId = 1;
	}
}SGetIp;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//����
typedef struct _tagSCaLowPriceFlightInfo
{
	int iProductId;
	int	iProductType;	//��ͨ�Ź����ͼ������Ź�	CA_TUAN_PRODUCT = 0, CA_TUAN_LOW_PRICE_APPLY_PRODUT
	int iMinHangPrice;	//�񺽼�
	CStringA straDCityCode;
	CStringA straACityCode;
	int	 iCityCode;
	CStringA straCity;

	_tagSCaLowPriceFlightInfo & operator=(_tagSCaLowPriceFlightInfo & info)
	{
		this->iProductId = info.iProductId;
		this->iProductType = info.iProductType;
		this->straDCityCode = info.straDCityCode;
		this->straACityCode = info.straACityCode;
		this->iCityCode = info.iCityCode;
		this->straCity = info.straCity;

		return *this;
	}
}SCaLowPriceFlightInfo;

typedef struct _tagSCaAirLineDetailProcess
{
	CDialogEx*			pDlg;
	std::list<SCaLowPriceFlightInfo*> lowPriceFlightList;
}SCaAirLineDetailProcess,*PSCaAirLineDetailProcess;


//������Ϣ
typedef struct _tagCaLowPriceFlightDetail 
{
	CStringA	straCompany;		//���չ�˾
	CStringA	straFromCityCode;	//�������д���
	CStringA	straToCityCode;		//������д���
	CStringA	straFlightNo;		//�����
	CStringA	straFromDate;		//��������
	CStringA	straSaleEndDate;	//���۽�������
	CStringA	straSaleEndTime;	//���۽���ʱ��
	int			nPrice;				//�۸�
	int			nProductId;			//������Ʒ���
	int			nRemainSeat;		//��Ʊ
	int			nProductType;		//������Ʒ����,CA_TUAN_PRODUCT;	CA_TUAN_LOW_PRICE_APPLY_PRODUT

	_tagCaLowPriceFlightDetail()
	{
		straCompany = "CA";		//���չ�˾
		straFromCityCode = "";	//�������д���
		straToCityCode = "";	//������д���
		straFlightNo = "";		//�����
		straFromDate = "";		//��������
		straSaleEndDate = "";	//���۽�������
		straSaleEndTime = "";	//���۽���ʱ��
		nPrice = 0;				//�۸�
		nProductId = 0;			//������Ʒ���
		nRemainSeat = 0;		//��Ʊ
		nProductType = CA_TUAN_PRODUCT;
	}

	_tagCaLowPriceFlightDetail & operator=(const _tagCaLowPriceFlightDetail & det)
	{
		this->straCompany = det.straCompany;	
		this->straFromCityCode = det.straFromCityCode;	
		this->straToCityCode = det.straToCityCode;	
		this->straFlightNo = det.straFlightNo;		
		this->straFromDate = det.straFromDate;	
		this->straSaleEndDate = det.straSaleEndDate;	
		this->straSaleEndTime = det.straSaleEndTime;	
		this->nPrice = det.nPrice;				
		this->nProductId = det.nProductId;			
		this->nRemainSeat = det.nRemainSeat;	
		this->nProductType = det.nProductType;

		return *this;
	}
}SCaLowPriceFlightDetail ,*PCaLowPriceFlightDetail;

//end����
/////////////////////////////////////////////////////////////////////////////////////////////////////////

class CDataProcess
{
public:
	CDataProcess(void);
	~CDataProcess(void);

	bool	m_bStarting;	//���ڿ����̵߳Ĺر�

	static CString	m_strXmlFile;

	map<CString,CString>	m_mapCityCodes;
	TConfigInfo				m_configInfo;
	UDatePara				m_uCaTuanGetFlightEndDate;//ץȡ�����Ź��ĺ����������
	bool					m_bGetAllCaTuanFlight;//�Ƿ�ץȡ���е��Ź�����

	int						m_iExtraAddPrice;
	BOOL					m_bOutCeairLog;	//��������ƶ�E��־���ļ�,�����Ƹ�ʽ���ļ���Ϊceairlog.log

	//����������Ϣ
	bool	LoadConfigFromXml();
	//����������Ϣ
	bool	SaveConfigToini();
	//�����񺽼۸�
	BOOL	LoadMinHangPrice();
	//�õ����ߵ��񺽼۸񣬲���ʼ�����������м�ĺ����񺽼۸��ǹ̶���
	UINT	GetMinHangPrice(std::map<CString, UINT> & priceMap, CString & strCity1Code, CString & strCity2Code);

	//���治ͬ��ѯʱ������ִ�����
	void	SaveNoChangeFlightPollTime();
	void	LoadNoChangeFlightPollTime();
	BOOL	NeedNoChangeFlightPoll();//�Ƿ���Ҫ��ѯ��������ĺ���

	void	SaveLessChangeFlightPollTime();
	void	LoadLessChangeFlightPollTime();
	BOOL	NeedLessChangeFlightPoll();//�Ƿ���Ҫ��ѯ���ٱ�ĺ���

	static void DateStrToCTime(CString strDate, CTime& t);
	static CTime	GetQueryStartTime(){return m_queryStartTime;};
	

	// ͨ���������Ƶõ����д���
	CString GetCityCodeByName(CString& strCityName);

	// ͨ�����д���õ���������
	CString GetCityNameByCode(CString& strCityCode);
	// ���溽����Ϣ��xml�ļ�
	BOOL SaveAirlinesToXml(list<PTAirLineInfo>& listAirline);
	// �õ���ǰexe�ļ�����·��
	CString GetExePath(void);
	// ��xml�ļ��м��غ�����Ϣ
	BOOL LoadAirlinesFromXml(list<PTAirLineInfo>& listAirline);
	// �������ڵȺ�����Ϣ��xml�ļ���
	BOOL SaveAirlineDateToXml(list<PTAirLineDateInfo>& listAirDate, CString strFullPath = _T(""));
	// ��xml�ļ��м��غ���������Ϣ
	BOOL LoadAirlineDateFromXml(list<PTAirLineDateInfo>& listAirDate, CString strFullPath = _T(""));
	// �жϳ����Ƿ����
	BOOL IsCityExist(CString& strCity);
	// �õ����ݴ����Ψһʵ��
	static CDataProcess* GetInstance(void);

	static std::string Unicode2Ansi(const wchar_t* wstr);
	//ȡ�ú�������ĸ
	static CString GetFirstLetter(LPCTSTR strName);
	
	// �õ��µ����ߴ���
	static CString GetNewPolicyCode(void);
	// ���س��д���
	bool LoadCityCodes(void);

	int ChangeProxy(WinHttpClient& httpClient);

	void GenAirLine(list<PTAirLineDateInfo>& listAirDate);
	BOOL __FindKeyInMap(std::map<CString, int> & mp, CString & strKey);

	CStringA ConvertCtripTo9C(CStringA & straCode);

private:
	static CString m_strIniFileName;

	static CTime	m_queryStartTime;
	static BOOL		m_bqueryStartTimeOk;

	std::map<CString, UINT>	m_minHangPriceMap;
	void			__GenMinHangPriceXml();
};

#define _DataProcess CDataProcess::GetInstance();
