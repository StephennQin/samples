

#pragma once
#include "HtmlParse.h"


class CCaHtmlParse :
	public CHtmlParse
{
public:
	CCaHtmlParse(void);
	~CCaHtmlParse(void);
public:
	static void SetCaTuanGetFlightEndDate(const CTime & endTime){m_tGetEndTime = endTime;};//ץȡ��������Ľ�������
	static void SetAllCaTuanFlightFlag(bool bGet){m_bGetAllCaTuanFlight = bGet;};//�Ƿ�ץȡ�Ź�ҳ���ϵ����к���
	static void	SetCaTuanMinTicketNumWarnNum(int nMinTicketWarnNum){m_nMinTicketWarnNum = nMinTicketWarnNum;};//���Ʊ�������������ֵ����Ϊû

public:
	int ParseCaHtmlFlights(std::list<SCaLowPriceFlightDetail*> & listFlight, const std::string& strHtmlData, const CStringA & straDCode, const CStringA & straACode, const SCaLowPriceFlightInfo* pLowPriceFlightInfo);

private:
	BOOL	__IsFlightValid(const TidyNode & tdChild);
	void	__GetFlightNoAndFlightStartDate(CStringA & strFlightNo, CStringA & strFlightStartDate, const TidyDoc & tdoc, const TidyNode & tdNode);
	void	__GetSaleEndDate(CStringA & straEndDate, CStringA & straEndTime, const TidyDoc & tdoc, const TidyNode & tdNode);
	void	__GetAirPortCode(CStringA & straDCode, CStringA & straACode, const TidyDoc & tdoc, const TidyNode & tdNode);
	void	__GetPriceAndRamainTicket(UINT *pPrice, UINT *pRemainTicket, const TidyDoc & tdoc, const TidyNode & tdNode);
	BOOL	__IsTwoAirPort(const CStringA & straCode1, const CStringA & straCode2);
	void	__GetFlightStartTime(CStringA & strFlightStartTime, const TidyDoc & tdoc, const TidyNode & tdNode);
	BOOL	__findCaFlight(SCaLowPriceFlightDetail** pFind, const CStringA & straFlightStartDate, const CStringA & straDPortCode
		, const CStringA & straAPortCode, const CStringA & straFlightNo, const std::list<SCaLowPriceFlightDetail*> & listFlight);

	static	CTime	m_tGetEndTime;
	static	bool	m_bGetAllCaTuanFlight;
	static	int		m_nMinTicketWarnNum;

};

