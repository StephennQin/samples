#pragma once

#include "../tidyinclude/tidy.h"
#include "../tidyinclude/buffio.h"
#include "common/CStringToolEx.h"
#include "DataProcess.h"

#include <list>

using namespace std;


class CHtmlParse
{
public:
	CHtmlParse(void);
	virtual ~CHtmlParse(void);
	virtual int ParseHtmlFlights(std::string& strHtmlData, list<PT9CFlightInfo>& listFlight);
	static bool FindNode(TidyNode tnod, ctmbstr stratt, ctmbstr strvalue, TidyNode& tnOut);
	static bool IsHaveThisAttr(TidyNode tnod,ctmbstr stratt, ctmbstr strvalue);
	// �õ�����ֵ
	static ctmbstr GetAttValue(TidyNode tnod, ctmbstr stratt);

	//�����ӽڵ��µ�span�ڵ���ı�����
	static bool GetChildSpanContent(TidyDoc tdoc, TidyNode tnod,CStringA& straRet);

	// �õ��ڵ��ı�����
	static CStringA GetNodeContent(TidyDoc tdoc,TidyNode tnod);
	// ���ݽڵ����ݲ��ҽڵ�
	static bool FindNodeByContent(TidyDoc tdoc, TidyNode tnod, ctmbstr strContent,TidyNode& tnRet);

public:
	//ȡ�������ַ����е������գ����������ַ�����ʽ��2014-10-29
	void GetYearMonthDay(const CStringA & straDate, int *piYear, int *piMonth, int *piDay);
	//ȡ��ʱ���ַ����е�ʱ��,����ʱ���ַ�����ʽ��00:00
	void GetHourMinSec(const CStringA & straTime, int *piHour, int *piMin);
	//ȡ��ʱ���ַ����е�ʱ��,����ʱ���ַ�����ʽ��00:00:00
	void GetHourMinSec(const CStringA & straTime, int *piHour, int *piMin, int *piSec);
};

