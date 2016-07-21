
#include "stdafx.h"
#include "CCaHtmlParse.h"


CTime	CCaHtmlParse::m_tGetEndTime;
bool	CCaHtmlParse::m_bGetAllCaTuanFlight = true;
int		CCaHtmlParse::m_nMinTicketWarnNum = 2;

void dumpNode( TidyNode tnod, int indent );

CCaHtmlParse::CCaHtmlParse(void)
{

}

CCaHtmlParse::~CCaHtmlParse(void)
{

}

BOOL CCaHtmlParse::__IsFlightValid(const TidyNode & tdChild)
{
	BOOL bValid = TRUE;
	TidyNode tRadioNode;
	CStringA straValid;
	tRadioNode = tidyGetChild(tdChild);
	straValid.Format("%s", GetAttValue(tRadioNode, "disabled"));
	if (0 == straValid.CompareNoCase("disabled"))
		bValid = FALSE;

	return bValid;
}
int CCaHtmlParse::ParseCaHtmlFlights(std::list<SCaLowPriceFlightDetail*> & listFlight, const std::string& strHtmlData, const CStringA & straDCode, const CStringA & straACode, const SCaLowPriceFlightInfo*	pLowPriceFlightInfo)
{
	TidyDoc doc = tidyCreate();
	tidySetCharEncoding(doc,"raw");
	tidyParseString(doc,strHtmlData.c_str());
	TidyNode tnRoot = tidyGetRoot(doc);

	TidyNode tFlightTab;
	TidyNode tdChild;
	int nIndexTd = 0;

	CTime tCurrent = CTime::GetCurrentTime();
	SCaLowPriceFlightDetail *pfindFlight = NULL;
	if (FindNode(tnRoot,"class","CA_table mt_10 clear",tFlightTab))
	{
		//ѭ�����������,tblPolicy�µ�ÿһ���ӽڵ㼴Ϊһ���������Ϣ
		TidyNode trFlight;
		int nIndexTr = 0;
		BOOL bValid = FALSE;
		CStringA straDPortCode = straDCode;
		CStringA straAPortCode = straACode;
		CStringA straFlightNo("");
		CStringA straFlightStartDate("");
		CStringA straSaleEndDate("");
		CStringA straSaleEndTime("");
		CStringA straFlightStartTime("");

		UINT uPrice = 0;
		UINT uRemainTicket = 0;
		for ( trFlight = tidyGetChild(tFlightTab); trFlight; trFlight = tidyGetNext(trFlight) )
		{
			if (0 == nIndexTr)//������ͷ
			{
				nIndexTr++;
				continue;
			}

			nIndexTd = 0;
			bValid = FALSE;
			straFlightNo = "";
			straFlightStartDate = "";
			straSaleEndDate = "";
			straSaleEndTime = "";
			straFlightStartTime = "";
			uPrice = 0;
			uRemainTicket = 0;
			for ( tdChild = tidyGetChild(trFlight); tdChild; tdChild = tidyGetNext(tdChild) )
			{
				switch(nIndexTd)
				{
				case 0:
					{
						//ѡ���Ƿ�Ϊdisabled
						bValid = __IsFlightValid(tdChild);
						TRACE(_T("Flight valid:%d-"), bValid);
						
					}
					break;
				case 1:
					{
						//����/�����
						//dumpNode(tdChild, 0);
						//TRACE(_T("\r\n"));
						__GetFlightNoAndFlightStartDate(straFlightNo, straFlightStartDate, doc, tdChild);
						TRACE("date:%s, no:%s-", straFlightStartDate, straFlightNo);
						 //TRACE("%s\r\n", GetNodeContent(doc, tdChild));
					}
					break;
				case 2:
					{
						//��ʱ��
						//dumpNode(tdChild, 0);
						//TRACE(_T("\r\n"));
						 //TRACE("%s\r\n", GetNodeContent(doc, tdChild));
						__GetFlightStartTime(straFlightStartTime, doc, tdChild);
					}
					break;
				case 3:
					{
						//����
						//dumpNode(tdChild, 0);
						//TRACE(_T("\r\n"));
						 //TRACE("%s\r\n", GetNodeContent(doc, tdChild));
						if (__IsTwoAirPort(straDCode, straACode))
						{
							__GetAirPortCode(straDPortCode, straAPortCode, doc, tdChild);
							if(straDPortCode.IsEmpty())
								straDPortCode = straDCode;
							if(straAPortCode.IsEmpty())
								straAPortCode = straACode;
							TRACE("%s->%s-", straDPortCode, straAPortCode);
						}

					}
					break;
				case 4:
					{
						//���۽�������,ʱ��
						//dumpNode(tdChild, 0);
						//TRACE(_T("\r\n"));
						//TRACE("%s\r\n", GetNodeContent(doc, tdChild));
						__GetSaleEndDate(straSaleEndDate, straSaleEndTime, doc, tdChild);
						TRACE("sale end date:%s, %s-", straSaleEndDate, straSaleEndTime);
					}
					break;
				case 5:
					{
						//�Ź���
						//dumpNode(tdChild, 0);
						//TRACE(_T("\r\n"));
						//TRACE("%s\r\n", GetNodeContent(doc, tdChild));
						//CStringA straSetPrice = GetNodeContent(doc, tdChild);

						//double fSetPrice = atof(straSetPrice.GetBuffer(0));
						//straSetPrice.ReleaseBuffer();
						//tidyRelease(doc);
						//return fSetPrice;
						__GetPriceAndRamainTicket(&uPrice, &uRemainTicket, doc, tdChild);
						TRACE("price:%d, remain %d seats", uPrice, uRemainTicket);
					}
					break;
				}

				nIndexTd++;
			}
			TRACE(_T("\r\n"));

			//��������֮��ĺ��಻ץȡ
			//�õ��������
			int nFlightStartYear = 2014;
			int nFlightStartMonth = 12;
			int nFlightStartDay = 12;
			GetYearMonthDay(straFlightStartDate, &nFlightStartYear, &nFlightStartMonth, &nFlightStartDay);
			
			CTime tStart(nFlightStartYear, nFlightStartMonth, nFlightStartDay, 0, 0, 0);
			//if (!m_bGetAllCaTuanFlight)
			//{
			//	if (tStart > m_tGetEndTime)
			//		continue;
			//}
			//
			
			//double d6 = pLowPriceFlightInfo->iMinHangPrice * 0.6;
			//UINT u6 = (UINT)d6;
			////6��������ͨ�Ź��˸�ǩҪ�շѣ��ͼ����벻�����ƣ������Բ���
			//if (uPrice > d6 && CA_TUAN_PRODUCT == pLowPriceFlightInfo->iProductType)
			//{
			//	bValid = FALSE;
			//	uRemainTicket = 0;
			//	continue;
			//}
			//��ͬ���ڡ�ʱ�䡢��εĺ��ֻ࣬ȡ��ͼ�
			BOOL bFind = __findCaFlight(&pfindFlight, straFlightStartDate, straDPortCode, straAPortCode, straFlightNo, listFlight);
			if (bFind)
			{
				int nCurPrice = (int)uPrice;
				//��ǰ��������������ϴν������ı���
				if(pfindFlight->nPrice > nCurPrice)
				{
					if (uRemainTicket > m_nMinTicketWarnNum)
					{
						//��ǰƱ����������ʱ���õ�ǰƱ�����������ϴν�����������
						pfindFlight->nRemainSeat = uRemainTicket;
						pfindFlight->nPrice = nCurPrice;
						pfindFlight = NULL;
					}
				}
				else //(pfindFlight->nPrice <= nCurPrice)
				{
					if(pfindFlight->nRemainSeat <= m_nMinTicketWarnNum)
					{
						pfindFlight->nRemainSeat = uRemainTicket;
						pfindFlight->nPrice = nCurPrice;
						pfindFlight = NULL;
					}
				}

				continue;
			}

			//������������ĺ�����Ϣ,�����߸����ͷ��ڴ�
			if (bValid)
			{
				SCaLowPriceFlightDetail* pDetail = new SCaLowPriceFlightDetail;
				pDetail->straCompany = "CA";	
				pDetail->straFromCityCode = straDPortCode;	
				pDetail->straToCityCode = straAPortCode;	
				pDetail->straFlightNo = straFlightNo;		
				pDetail->straFromDate = straFlightStartDate;	
				//����Я�̶���������Ҫһ����ʱ�䣬�����°�16��00�°࣬���Ե����Ʊ,��2��12:00֮ǰ��Ʊ�����۽���ʱ����ǰ30���ӣ�	
				//ȡ���ۼ��
				int nSaleEndYear = 2014;
				int nSaleEndMonth = 12;
				int nSaleEndDay = 12;
				GetYearMonthDay(straSaleEndDate, &nSaleEndYear, &nSaleEndMonth, &nSaleEndDay);
				int nSaleEndHour = 12;
				int nSaleEndMin = 0;
				GetHourMinSec(straSaleEndTime, &nSaleEndHour, &nSaleEndMin);
				CTime tSaleEndDate(nSaleEndYear, nSaleEndMonth, nSaleEndDay, nSaleEndHour, nSaleEndMin, 0);
				CTimeSpan tSpan = tSaleEndDate - tCurrent;
				//end ȡ���ۼ��
				//�õ����ʱ��
				int nFlightStartHour = 12;
				int nFlightStartMin = 0;
				GetHourMinSec(straFlightStartTime, &nFlightStartHour, &nFlightStartMin);
				CTime tFlightStartTime(nFlightStartYear, nFlightStartMonth, nFlightStartDay, nFlightStartHour, nFlightStartMin, 0);
				CTime tTimeKey(nFlightStartYear, nFlightStartMonth, nFlightStartDay, 12, 0, 0);
				//end �õ����ʱ��
	
				//��������ġ����ʱ����12��֮ǰ�����ǵͼ�����ģ����۽���ʱ��Ϊ ǰһ��Ĺ������۽�����ǰ30����
				if ((CA_TUAN_LOW_PRICE_APPLY_PRODUT == pLowPriceFlightInfo->iProductType) && (1 == tSpan.GetDays()))//����ĵĵͼ�����
				{	
					if(tFlightStartTime <= tTimeKey)//����12��ɵĵͼ�����, ��������3��25ǰ��Ч������4���°ࣩ
					{
						pDetail->straSaleEndDate.Format("%d-%02d-%02d", tCurrent.GetYear(), tCurrent.GetMonth(), tCurrent.GetDay());
						CTime tSaleEnd(tCurrent.GetYear(), tCurrent.GetMonth(), tCurrent.GetDay(), 15, 25, 0);
						pDetail->straSaleEndTime.Format("%02d:%02d:%02d", tSaleEnd.GetHour(), tSaleEnd.GetMinute(), 0);	
					}
					else//����12����ɵĵͼ����룬������Գ�Ʊ
					{
						pDetail->straSaleEndDate = straSaleEndDate;
						pDetail->straSaleEndTime.Format("%02d:%02d:%02d", nSaleEndHour, nSaleEndMin, 0);
					}
				}
				else if ((CA_TUAN_LOW_PRICE_APPLY_PRODUT == pLowPriceFlightInfo->iProductType) && (tSpan.GetDays() < 1))//����ĵĵͼ����룬��������3��30ǰ��Ч������4���°ࣩ
				{
					pDetail->straSaleEndDate.Format("%d-%02d-%02d", tCurrent.GetYear(), tCurrent.GetMonth(), tCurrent.GetDay());
					CTime tSaleEnd(tCurrent.GetYear(), tCurrent.GetMonth(), tCurrent.GetDay(), 15, 30, 0);
					pDetail->straSaleEndTime.Format("%02d:%02d:%02d", tSaleEnd.GetHour(), tSaleEnd.GetMinute(), 0);	
				}
				else//��ͨ�Ź������켰�Ժ�ĵͼ�����
				{
					pDetail->straSaleEndDate = straSaleEndDate;
					pDetail->straSaleEndTime.Format("%02d:%02d:%02d", nSaleEndHour, nSaleEndMin, 0);
				}

				//��������ʱ�䵽��ɾ������
				GetYearMonthDay(pDetail->straSaleEndDate,  &nSaleEndYear, &nSaleEndMonth, &nSaleEndDay);
				int nSaleEndSec = 0;
				GetHourMinSec(pDetail->straSaleEndTime, &nSaleEndHour, &nSaleEndMin, &nSaleEndSec);
				CTime tPolicyDeleteTime(nSaleEndYear, nSaleEndMonth, nSaleEndDay, nSaleEndHour, nSaleEndMin, nSaleEndSec);
				if (tCurrent >= tPolicyDeleteTime)
					uRemainTicket = 0;

				pDetail->nPrice = uPrice;				
				pDetail->nProductId = pLowPriceFlightInfo->iProductId;			
				pDetail->nRemainSeat = uRemainTicket;	
				pDetail->nProductType = pLowPriceFlightInfo->iProductType;

				listFlight.push_back(pDetail);
			}
		}
	}

	tidyRelease(doc);	

	return -1.0;
}

BOOL CCaHtmlParse::__findCaFlight(SCaLowPriceFlightDetail** pFind, const CStringA & straFlightStartDate, const CStringA & straDPortCode
	, const CStringA & straAPortCode, const CStringA & straFlightNo, const std::list<SCaLowPriceFlightDetail*> & listFlight)
{
	*pFind = NULL;
	BOOL bFind = FALSE;
	SCaLowPriceFlightDetail* pCur = NULL;
	for (std::list<SCaLowPriceFlightDetail*>::const_iterator it = listFlight.begin(); it != listFlight.end();  it++)
	{
		pCur = *it;
		if (0 == straFlightNo.CompareNoCase(pCur->straFlightNo) && 0 == straDPortCode.CompareNoCase(pCur->straFromCityCode)
			&& 0 == straAPortCode.CompareNoCase(pCur->straToCityCode) && 0 == straFlightStartDate.CompareNoCase(pCur->straFromDate))
		{
			bFind = TRUE;
			*pFind = pCur;
			break;
		}
	}
	return bFind;
}
void CCaHtmlParse::__GetFlightStartTime(CStringA & strFlightStartTime, const TidyDoc & tdoc, const TidyNode & tdNode)
{
	CStringA straRet;
	strFlightStartTime = "";

	TidyBuffer text = {0};
	tidyBufInit(&text);
	TidyNodeType type = tidyNodeGetType(tdNode);
	tidyNodeGetText(tdoc, tdNode, &text);
	straRet.Format("%s",text.bp);

	CStringA straKey("\">");
	int iStartPos = straRet.Find(straKey);
	int iEndPos = straRet.Find("</strong>");
	iStartPos = iStartPos+straKey.GetLength();
	strFlightStartTime = straRet.Mid(iStartPos, iEndPos-iStartPos);

	tidyBufFree(&text);
}
BOOL CCaHtmlParse::__IsTwoAirPort(const CStringA & straCode1, const CStringA & straCode2)
{
	BOOL bRet = FALSE;
	if (0 == straCode1.CompareNoCase("SHA") || 0 == straCode1.CompareNoCase("PVG") || 0 == straCode1.CompareNoCase("PEK") || 0 == straCode1.CompareNoCase("NAY")
		|| 0 == straCode2.CompareNoCase("SHA") || 0 == straCode2.CompareNoCase("PVG") || 0 == straCode2.CompareNoCase("PEK") || 0 == straCode2.CompareNoCase("NAY"))
	{
		bRet = TRUE;
	}
	return bRet;
}
void CCaHtmlParse::__GetFlightNoAndFlightStartDate(CStringA & strFlightNo, CStringA & strFlightStartDate, const TidyDoc & tdoc, const TidyNode & tdNode)
{
	CStringA straRet;
	strFlightNo = "";
	strFlightStartDate = "";

	TidyBuffer text = {0};
	tidyBufInit(&text);
	TidyNodeType type = tidyNodeGetType(tdNode);
	tidyNodeGetText(tdoc, tdNode, &text);
	straRet.Format("%s",text.bp);
	straRet.TrimLeft();
	strFlightStartDate = straRet.Mid(4, 10);
	int iStartPos = straRet.Find('C');//ƥ��CA��ca��Ca��cA��<br />������س����з���
	if(-1 == iStartPos)//û�ҵ���дC��ƥ��Сдc
		iStartPos = straRet.Find('c');
	int iEndPos = straRet.Find("</");
	strFlightNo = straRet.Mid(iStartPos, iEndPos-iStartPos);//�����������3λ�ģ�����4λ��
	strFlightNo = strFlightNo.MakeUpper();
	strFlightNo = strFlightNo.Mid(2);//ȥ��CA

	tidyBufFree(&text);
}

void CCaHtmlParse::__GetSaleEndDate(CStringA & straEndDate, CStringA & straEndTime, const TidyDoc & tdoc, const TidyNode & tdNode)
{
	CStringA straRet;
	straEndDate = "";
	straEndTime = "";

	TidyBuffer text = {0};
	tidyBufInit(&text);
	TidyNodeType type = tidyNodeGetType(tdNode);
	tidyNodeGetText(tdoc, tdNode, &text);
	straRet.Format("%s",text.bp);
	straRet.TrimLeft();

	int iPos = straRet.Find("<br");
	straRet = straRet.Mid(4, iPos-4);
	straEndDate = straRet.Left(10);
	straEndTime = straRet.Mid(11);
	straEndTime.Trim();

	tidyBufFree(&text);
}

void CCaHtmlParse::__GetAirPortCode(CStringA & straDCode, CStringA & straACode, const TidyDoc & tdoc, const TidyNode & tdNode)
{
	CStringA straRet;
	CStringA straSha("�Ϻ�����");
	CStringA straPvg("�Ϻ��ֶ�");
	CStringA straPek("�����׶�");
	CStringA straNay("������Է");

	straDCode = "";
	straACode = "";

	TidyBuffer text = {0};
	tidyBufInit(&text);
	TidyNodeType type = tidyNodeGetType(tdNode);
	tidyNodeGetText(tdoc, tdNode, &text);
	straRet.Format("%s",text.bp);
	straRet.TrimLeft();

	CStringA straKey("<br />");//<br />���лس����з�
	int iPos = straRet.Find(straKey);
	CStringA straDCity = straRet.Mid(4, iPos-4);
	if (-1 != straDCity.Find(straSha))
		straDCode = "SHA";
	else if (-1 != straDCity.Find(straPvg))
		straDCode = "PVG";
	else if (-1 != straDCity.Find(straPek))
		straDCode = "PEK";
	else if(-1 != straDCity.Find(straNay))
		straDCode = "NAY";
	else
	{

	}

	//ȡ���������<br />���лس����з�
	straRet = straRet.Mid(iPos+straKey.GetLength());
	straRet.Remove(0x0d);//ȥ���س�
	straRet.Remove(0x0a);//ȥ������
	int iEndPos = straRet.Find("</td>");
	CStringA straACity = straRet.Left(iEndPos);
	if (-1 != straACity.Find(straSha))
		straACode = "SHA";
	else if (-1 != straACity.Find(straPvg))
		straACode = "PVG";
	else if (-1 != straACity.Find(straPek))
		straACode = "PEK";
	else if(-1 != straACity.Find(straNay))
		straACode = "NAY";
	else
	{

	}

	tidyBufFree(&text);
}
void CCaHtmlParse::__GetPriceAndRamainTicket(UINT *pPrice, UINT *pRemainTicket, const TidyDoc & tdoc, const TidyNode & tdNode)
{
	CStringA straRet;
	*pPrice = 0;
	*pRemainTicket = 0;

	TidyBuffer text = {0};
	tidyBufInit(&text);
	TidyNodeType type = tidyNodeGetType(tdNode);
	tidyNodeGetText(tdoc, tdNode, &text);
	straRet.Format("%s",text.bp);
	straRet.TrimLeft();

	CStringA straKey("</font>");
	int iPos = straRet.Find(straKey);
	int iEndPos = straRet.Find("</strong>");
	int iStartPos = iPos+straKey.GetLength();
	CStringA straPrice = straRet.Mid(iStartPos, iEndPos-iStartPos);
	straPrice.Remove(0x0d);//ȥ���س�
	straPrice.Remove(0x0a);//ȥ������
	*pPrice = atoi(straPrice.GetBuffer(0));
	straPrice.ReleaseBuffer();

	//ʣ����λ
	straKey = "��";
	iPos = straRet.Find(straKey);
	iEndPos = straRet.Find("</td>");
	iStartPos = iPos+straKey.GetLength();
	CStringA straRemainSeat = straRet.Mid(iStartPos, iEndPos-iStartPos);
	*pRemainTicket = atoi(straRemainSeat.GetBuffer(0));
	straRemainSeat.ReleaseBuffer();

	tidyBufFree(&text);
}
void dumpNode( TidyNode tnod, int indent )
{
	TidyNode child;

	for ( child = tidyGetChild(tnod); child; child = tidyGetNext(child) )
	{
		ctmbstr name;
		switch ( tidyNodeGetType(child) )
		{
		case TidyNode_Root:       name = "Root";                    break;
		case TidyNode_DocType:    name = "DOCTYPE";                 break;
		case TidyNode_Comment:    name = "Comment";                 break;
		case TidyNode_ProcIns:    name = "Processing Instruction";  break;
		case TidyNode_Text:       name = "Text";                    break;
		case TidyNode_CDATA:      name = "CDATA";                   break;
		case TidyNode_Section:    name = "XML Section";             break;
		case TidyNode_Asp:        name = "ASP";                     break;
		case TidyNode_Jste:       name = "JSTE";                    break;
		case TidyNode_Php:        name = "PHP";                     break;
		case TidyNode_XmlDecl:    name = "XML Declaration";         break;

		case TidyNode_Start:
		case TidyNode_End:
		case TidyNode_StartEnd:
		default:
			name = tidyNodeGetName( child );
			break;
		}
		assert( name != NULL );
		TRACE( "------%d,%d, %s,%s", indent, indent, " ", name );
		dumpNode( child, indent + 4 );
	}
}