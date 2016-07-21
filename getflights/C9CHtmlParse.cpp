#include "StdAfx.h"
#include "C9CHtmlParse.h"
#include "util.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int		C9CHtmlParse::m_iExtraAddPrice = 0;
C9CHtmlParse::C9CHtmlParse(void)
{
}


C9CHtmlParse::~C9CHtmlParse(void)
{
}

int C9CHtmlParse::ParseHtmlFlights(std::string& strHtmlData, list<PT9CFlightInfo>& listFlight)
{
	TidyDoc doc = tidyCreate();
	tidySetCharEncoding(doc,"raw");
	tidyParseString(doc,strHtmlData.c_str());
	TidyNode tnRoot = tidyGetRoot(doc);

	CStringA straFromCode,straToCode,straFromDate,straToDate;
	TidyNode tnFrom,tnTo;
	if (FindNode(tnRoot,"id","OriCityCode",tnFrom))
	{
		straFromCode.Format("%s",GetAttValue(tnFrom,"value"));
	}
	if (FindNode(tnRoot,"id","DestCityCode",tnTo))
	{
		straToCode.Format("%s",GetAttValue(tnTo,"value"));
	}
	if (FindNode(tnRoot,"id","FLY_TIME",tnTo))
	{
		straFromDate.Format("%s",GetAttValue(tnTo,"value"));
	}
	if (FindNode(tnRoot,"id","RETURN_TIME",tnTo))
	{
		straToDate.Format("%s",GetAttValue(tnTo,"value"));
	}
	CStringA straContent;
	int nMinHangPrice = 0;
	if (FindNode(tnRoot,"id","goMinHang",tnTo))
	{
		straContent = GetNodeContent(doc,tnTo);
		nMinHangPrice = ParsePrice(straContent);
	}

	TidyNode tnSearchresult;
	if (FindNode(tnRoot,"id","goFlightsShow",tnSearchresult))
	{
		//ѭ����������,goFlightsShow�µ�ÿһ��һ���ӽڵ㼴Ϊһ������
		TidyNode tnFlight;
		for ( tnFlight = tidyGetChild(tnSearchresult); tnFlight; tnFlight = tidyGetNext(tnFlight) )
		{
			TidyNode tnChild;
			int nIndex = 0;

			PT9CFlightInfo pInfo = new T9CFlightInfo;
			pInfo->straCompany = "9C";
			pInfo->straFromCityCode = straFromCode;
			pInfo->straToCityCode = straToCode;
			pInfo->straFromDate = straFromDate;
			pInfo->straToDate = straToDate;
			pInfo->nMinHangPrice = nMinHangPrice;

			for ( tnChild = tidyGetChild(tnFlight); tnChild; tnChild = tidyGetNext(tnChild) )
			{
				switch(nIndex)
				{
				case 0:
					{
						//�����
						if (GetChildSpanContent(doc,tnChild,straContent))
						{
							pInfo->straFlightNo = straContent;
						}
					}
					break;
				case 1:
					{
						//����ʱ��
						pInfo->straFromTime = GetNodeContent(doc,tnChild);
					}
					break;
				case 2:
					{
						//����ʱ��
						pInfo->straToTime = GetNodeContent(doc,tnChild);
					}
					break;
				case 3:
					{
						if (GetChildSpanContent(doc,tnChild,straContent))
						{
							if (0 == straContent.Left(2).Compare("--"))
							{
								pInfo->nPrice1 = 0;
							}
							else
							{
								pInfo->nPrice1 = ParsePrice(straContent);
							}
						}
					}
					break;
				case 4:
					{
						if (GetChildSpanContent(doc,tnChild,straContent))
						{
							if (0 == straContent.Left(2).Compare("--"))
							{
								pInfo->nPrice2 = 0;
							}
							else
							{
								pInfo->nPrice2 = ParsePrice(straContent);
							}
						}
					}
					break;
				case 5:
					{
						if (GetChildSpanContent(doc,tnChild,straContent))
						{
							if (0 == straContent.Left(2).Compare("--"))
							{
								pInfo->nPrice3 = 0;
							}
							else
							{
								pInfo->nPrice3 = ParsePrice(straContent);
							}
						}
					}
					break;
				}

				nIndex++;
			}

			pInfo->nMinPrice = GetMinPrice(pInfo->nPrice1,pInfo->nPrice2,pInfo->nPrice3);
			listFlight.push_back(pInfo);
		}
	}

	tidyRelease(doc);	

	return 0;
}

int C9CHtmlParse::GetMinPrice(int nPrice1, int nPrice2, int nPrice3)
{
	int nMinPrice = 0;
	if (nPrice1 != 0)
	{
		nMinPrice = nPrice1;
	}
	if (nPrice2 != 0)
	{
		if (nMinPrice == 0 || nMinPrice > nPrice2)
		{
			nMinPrice = nPrice2;
		}
	}
	if (nPrice3 != 0)
	{
		if (nMinPrice == 0 || nMinPrice > nPrice3)
		{
			nMinPrice = nPrice3;
		}
	}

	return nMinPrice;
}

int C9CHtmlParse::ParsePrice(CStringA stra)
{
	int nPrice = 0;
	int n = sizeof('��');
	int nPos = stra.Find("��");
	if (nPos >= 0)
	{
	//	stra = stra.Left(stra)
		int nLength = stra.GetLength();
	//	stra = "�񺽹����ۣ���1260";
	//	nLength = stra.GetLength();
		CStringA str = stra.Mid(nPos + 2,nLength - nPos - n);
		nPrice = atoi(str.GetBuffer(0));
	}

	return nPrice;
}
//ץȡ��������վ��������
int C9CHtmlParse::ParseNewSiteJsonFlights(std::string& strHtmlData, list<PT9CFlightInfo>& listFlight, UINT uMinHangPrice, const CTime & tSel9Start, const CTime & tSel9End, BOOL bIgnoreP4Ticket, BOOL bIgnoreP5Ticket, BOOL bSelSpecialPriceTicket, int nP4SpecialPrice)
{
	int nCount = 0;
	Json::Reader reader;
	Json::Value jRoot;
	CTime tCur = CTime::GetCurrentTime();
	listFlight.clear();
	if (reader.parse(strHtmlData,jRoot))
	{
		if(jRoot.isNull() || !jRoot.isObject())
			return 0;
		Json::Value fligtsPackage = jRoot["Packages"];
		//ѭ��ÿ������
		int iFightCount = fligtsPackage.size();
		for (int i = 0; i < iFightCount; i++)
		{
			int k = 0;
			Json::Value flights = fligtsPackage[i];
			PT9CFlightInfo pInfo = new T9CFlightInfo;

			//�����
			pInfo->straCompany = "9C";
			CStringA straFlightNo;
			straFlightNo.Format("%s",flights[k]["No"].asCString());
			pInfo->straFlightNo = straFlightNo.Right(straFlightNo.GetLength()-2);

			//�����������룬����������
			CStringA straAirPortCode("");
			CStringA straAirPortName("");
			straAirPortCode.Format("%s",flights[k]["DepartureCode"].asCString());
			straAirPortName.Format("%s",flights[k]["DepartureStation"].asCString());
			//�Ϻ��������������°���վ���ص�ȫ��SHA��
			if (0 == straAirPortCode.CompareNoCase("SHA"))
			{
				if(-1 != straAirPortName.Find("����"))
					pInfo->straFromCityCode = "SHA";
				else
					pInfo->straFromCityCode = "PVG";
			}
			else
			{
				pInfo->straFromCityCode = straAirPortCode;
			}
			//����վ���ص���������������SIA��λ�˼������г���ǿ�Ƹ�ΪXIY
			if (0 == straAirPortCode.CompareNoCase("SIA"))
			{
				pInfo->straFromCityCode = "XIY";
			}

			//����������룬���������
			straAirPortCode.Format("%s",flights[k]["ArrivalCode"].asCString());
			straAirPortName.Format("%s",flights[k]["ArrivalStation"].asCString());
			if (0 == straAirPortCode.CompareNoCase("SHA"))
			{
				if(-1 != straAirPortName.Find("����"))
					pInfo->straToCityCode = "SHA";
				else
					pInfo->straToCityCode = "PVG";
			}
			else
			{
				pInfo->straToCityCode = straAirPortCode;
			}
			//����վ���ص���������������SIA��λ�˼������г���ǿ�Ƹ�ΪXIY
			if (0 == straAirPortCode.CompareNoCase("SIA"))
			{
				pInfo->straToCityCode = "XIY";
			}
			
			pInfo->nMinHangPrice = uMinHangPrice;

			//��������
			CStringA straDateTime;
			straDateTime.Format("%s",flights[k]["DepartureTime"].asCString());
			pInfo->straFromDate = straDateTime.Left(10);
			//straDateTime.Format("%s",flights[k]["ArrivalTime"].asCString());
			//pInfo->straToDate = straDateTime.Left(10);
			//����ĺ��࣬��ʱ�����߸��µ�ʱ�����Щ����
			pInfo->straToDate = pInfo->straFromDate;
			pInfo->straFromTime = "";
			pInfo->straToTime = "";

			pInfo->nPrice1 = pInfo->nPrice2 = pInfo->nPrice3 = 0;

			Json::Value cabinInfo = flights[k]["CabinInfos"];
			int ncabinCount = cabinInfo.size();

			if (ncabinCount >0)
			{
				//����
				int iCabinId = 0;
				if (bIgnoreP5Ticket)
					pInfo->nPrice1 = 0;
				else
				{
					Json::Value bestCabin = cabinInfo[iCabinId]["Cabins"];
					if (bestCabin.size() > 0)
					{
						int iBestCabinId = 0;
						pInfo->nPrice1 = bestCabin[iBestCabinId]["CabinPrice"].asUInt();
					}
					else
					{
						pInfo->nPrice1 = 0;
					}
				}

				//����
				iCabinId = 1;
				if (bIgnoreP5Ticket)
					pInfo->nPrice2 = 0;
				else
				{
					Json::Value midCabin = cabinInfo[iCabinId]["Cabins"];
					if (midCabin.size() > 0)
					{
						int iMidCabinId = 0;
						pInfo->nPrice2 = midCabin[iMidCabinId]["CabinPrice"].asUInt();
					}
					else
					{
						pInfo->nPrice2 = 0;
					}
				}


				//4������
				if (bIgnoreP4Ticket)
					pInfo->nPrice3 = 0;//����4�����µ�Ʊ
				else
				{
					//��4�����µ�Ʊ
					iCabinId = 2;
					Json::Value normalCabin = cabinInfo[iCabinId]["Cabins"];
					if (normalCabin.size() > 0)
					{
						int iNorCabinId = 0;
						pInfo->nPrice3 = normalCabin[iNorCabinId]["CabinPrice"].asUInt();
					}
					else
					{
						pInfo->nPrice3 = 0;
					}

					int nGw = pInfo->nPrice3 % 10;
					if (bSelSpecialPriceTicket)
					{
						//ֻ��ָ����ʱ�䷶Χ����4�����µ�Ʊ
						if (9 == nGw)
						{
							//�����涨��ʱ�䷶Χ�ˣ�����
							if (tCur < tSel9Start || tCur >= tSel9End)
							{
								pInfo->nPrice3 = 0;
							}
						}
					}
					else //(!bSelSpecialPriceTicket)
					{
						//���´�9��Ʊ����
						//4�����£�600������ĩβ��9��Ʊ���ϣ����ڲ���ͨ���绰����
						if (9 == nGw)
						{
							if (pInfo->nPrice3 < nP4SpecialPrice)
							{
								pInfo->nPrice3 = 0;
							}
						}
					}
				}
			}
			//����ȫ��飬ȥ��9��59�������ؼۻ�Ʊ��Ʊ���٣��������գ��˴�ǿ����0
			int nMinSafePrice = 60;
			if (pInfo->nPrice1 < nMinSafePrice )
			{
				pInfo->nPrice1 = 0;
			}
			if (pInfo->nPrice2 < nMinSafePrice )
			{
				pInfo->nPrice2 = 0;
			}
			if (pInfo->nPrice3 < nMinSafePrice )
			{
				pInfo->nPrice3 = 0;
			}
			//end ����ȫ��飬ȥ��9��59�������ؼۻ�Ʊ��Ʊ���٣��������գ��˴�ǿ����0

			pInfo->nMinPrice = GetMinPrice(pInfo->nPrice1,pInfo->nPrice2,pInfo->nPrice3);
			if (pInfo->nMinHangPrice < 0)
				pInfo->nMinPrice = 0;

			//����Ӽۣ�Ӧ�Դ���ϵͳά��ʱ
			if (0 != pInfo->nMinPrice)
			{
				pInfo->nMinPrice = pInfo->nMinPrice + m_iExtraAddPrice;
				if(pInfo->nMinPrice > pInfo->nMinHangPrice)
					pInfo->nMinPrice = pInfo->nMinPrice -1;
			}
			//end ����Ӽۣ�Ӧ�Դ���ϵͳά��ʱ

			listFlight.push_back(pInfo);
			nCount++;
		}
	}

	return nCount;
}

int C9CHtmlParse::ParseJsonFlights(std::string& strHtmlData, list<PT9CFlightInfo>& listFlight, BOOL bIgnoreP4Ticket, BOOL bIgnoreP5Ticket, BOOL bSelSpecialPriceTicket, int nP4SpecialPrice)
{
	int nCount = 0;
	Json::Reader reader;
	Json::Value jRoot;
	if (reader.parse(strHtmlData,jRoot))
	{
		Json::Value fligts = jRoot["Flights"];
		//ѭ��ÿ������
		for (int i = 0; i < fligts.size(); i++)
		{
			PT9CFlightInfo pInfo = new T9CFlightInfo;
			pInfo->straCompany.Format("%s",fligts[i]["CompanyCode"].asCString());
			pInfo->nMinHangPrice = fligts[i]["Price"].asInt();
			CStringA straFlightNo;
			straFlightNo.Format("%s",fligts[i]["FlightNo"].asCString());
			pInfo->straFlightNo = straFlightNo.Right(straFlightNo.GetLength()-2);
			pInfo->straFromCityCode.Format("%s",fligts[i]["OriAirportCode"].asCString());
			pInfo->straToCityCode.Format("%s",fligts[i]["DestAirportCode"].asCString());
			pInfo->straFromDate.Format("%s",fligts[i]["FlightDateBJ"].asCString());
			pInfo->straToDate.Format("%s",fligts[i]["FlightDateBJ"].asCString());
			pInfo->straFromTime.Format("%s",fligts[i]["OriTimeBJ"].asCString());
			pInfo->straToTime.Format("%s",fligts[i]["DestTimeBJ"].asCString());
			
			Json::Value rates = fligts[i]["RoteOfLate"];
			int nsize = rates.size();
			if (rates.size()>=2)
			{
				int nTmp = 0;
				double  dRate = 0;
				if (bIgnoreP5Ticket)
					pInfo->nPrice2 = 0;
				else
				{
					dRate = rates[nTmp].asDouble();
					char szRate[65]={0};
					sprintf_s(szRate,sizeof(szRate),"%0lf",dRate);
					int nPrice = fligts[i]["MinSeatAPriceWeb"].asInt();
					char szPrice[65]={0};
					//itoa(nPrice,szPrice,10);
					//_itoa_s(nPrice, szPrice, 65, 10);
					sprintf_s(szPrice,sizeof(szPrice),"%d",nPrice);
					string strRate(szRate);
					string strPrice(szPrice);
					pInfo->straPrice2Json.Format("%s_%s", strRate.c_str(), strPrice.c_str());
					pInfo->nPrice2 = CalcJsonPrice2(strRate.c_str(), strPrice.c_str());
				}

				if (bIgnoreP4Ticket)
					pInfo->nPrice3 = 0;
				else
				{
					nTmp = 1;
					dRate = rates[nTmp].asDouble();
					char szRate2[65]={0};
					sprintf_s(szRate2,sizeof(szRate2),"%0lf",dRate);
					int nPrice2 = fligts[i]["MinSeatBPriceWeb"].asInt();
					char szPrice2[65]={0};
					//itoa(nPrice,szPrice2,10);
					//_itoa_s(nPrice2, szPrice2, 65, 10);
					sprintf_s(szPrice2,sizeof(szPrice2),"%d",nPrice2);
					string strRate3(szRate2);
					string strPrice3(szPrice2);
					pInfo->straPrice3Json.Format("%s_%s", strRate3.c_str(), strPrice3.c_str());
					pInfo->nPrice3 = CalcJsonPrice2(strRate3.c_str(), strPrice3.c_str());

					if (!bSelSpecialPriceTicket)
					{
						//4�����£�600������ĩβ��9��Ʊ���ϣ����ڲ���ͨ���绰����
						if (pInfo->nPrice3 < nP4SpecialPrice)
						{
							int nGw = pInfo->nPrice3 % 10;
							if (9 == nGw)
							{
								pInfo->nPrice3 = 0;
							}
						}
						//
					}
				}			
			}
			Json::Value supers = fligts[i]["lSuperSeatInfo"];
			if (bIgnoreP5Ticket)
				pInfo->nPrice1 = 0;
			else
			{
				if (supers.size() > 0)
				{
					int nTmp = 0;
					int nPrice1 = supers[nTmp]["superSeatsPrice"].asInt();
					char szPrice1[65]={0};
					//itoa(nPrice,szPrice,10);
					//_itoa_s(nPrice1, szPrice1, 65, 10);
					sprintf_s(szPrice1,sizeof(szPrice1),"%d",nPrice1);
					string strRate1 = supers[nTmp]["RoteOfLate"].asString();
					string strPrice1(szPrice1);
					pInfo->straPrice1Json.Format("%s_%s_%d", strRate1.c_str(), strPrice1.c_str(), supers[nTmp]["subProdPrice"].asInt());
					pInfo->nPrice1 = CalcJsonPrice2(strRate1.c_str(), strPrice1.c_str()) + supers[nTmp]["subProdPrice"].asInt();
				}
			}

			//����ȫ��飬ȥ��9��59�������ؼۻ�Ʊ��Ʊ���٣��������գ��˴�ǿ����0
			int nMinSafePrice = 90;
			if (pInfo->nPrice1 < nMinSafePrice )
			{
				pInfo->nPrice1 = 0;
			}
			if (pInfo->nPrice2 < nMinSafePrice )
			{
				pInfo->nPrice2 = 0;
			}
			if (pInfo->nPrice3 < nMinSafePrice )
			{
				pInfo->nPrice3 = 0;
			}
			//end ����ȫ��飬ȥ��9��59�������ؼۻ�Ʊ��Ʊ���٣��������գ��˴�ǿ����0

			pInfo->nMinPrice = GetMinPrice(pInfo->nPrice1,pInfo->nPrice2,pInfo->nPrice3);

			//CString strlog;
			//strlog.Format(_T("minhang:%d,min:%d,p1=%d,p2=%d,p3=%d"), pInfo->nMinHangPrice, pInfo->nMinPrice, pInfo->nPrice1, pInfo->nPrice2, pInfo->nPrice3);
			//OutputDebugString(strlog);

			listFlight.push_back(pInfo);
			nCount++;
		}
	}

	return nCount;
}

int C9CHtmlParse::CalcJsonPrice(const char* pstrRate, const char* pstrPrice)
{
	int nPrice = 0;
	std::string strRateTmp(pstrRate);
	std::string strPriceTmp(pstrPrice);
	if (strRateTmp.empty() || strPriceTmp.empty())
		return 0;
	for (int n = strPriceTmp.length() - 1; n >= 0; n--)
	{
		char a = strPriceTmp.at(n);
		//int nPos = atoi(&a);//�˴�����a�ĵ�ֱַ������\��0�������ַ�������������atoi(&a)�����bug��a��ַָ����ַ����ǲ����ģ����Գ�����Ҳ����
		int nPos =  a - '0';

		string::iterator it;
		int nPostmp = 0;
		for (it = strRateTmp.begin(); it != strRateTmp.end(); it++)
		{
			if (nPostmp == nPos)
			{
				char c = *it;
				int nTmp = c - '0';
				for (int i = 0; i < strPriceTmp.length() - 1 - n; i++)
				{
					nTmp *= 10;
				}
				nPrice += nTmp;

				strRateTmp.erase(it);
			}
			nPostmp++;
		}
	}

	return nPrice;
}

int C9CHtmlParse::CalcJsonPrice2(const char* pstrRate, const char* pstrPrice)
{
	int nPrice = 0;
	int nPriceStrLength = strlen(pstrPrice);
	char szRate[50] = {0};
	char szTmp[50] = {0};
	sprintf_s(szRate, sizeof(szRate), "%s", pstrRate);

	for (int n = nPriceStrLength - 1; n >= 0; n--)
	{
		char a = *(pstrPrice + n);
		int nPos =  a - '0';
		int nStrRateLen = strlen(szRate);
		for (int k = 0; k < nStrRateLen; k++)
		{
			if (k == nPos)
			{
				char c = szRate[k];
				int nTmp = c - '0';
				for (int i = 0; i < nPriceStrLength - 1 - n; i++)
				{
					nTmp *= 10;
				}
				nPrice += nTmp;

				//�Ƴ���ǰ�ַ�
				SecureZeroMemory(szTmp, sizeof(szTmp));
				sprintf_s(szTmp, sizeof(szTmp), "%s", szRate);
				//nStrRateLen-k-1Ϊ�Ӻ���ǰ�ƶ�Ԫ�صĸ���
				for (int j = 0; j < nStrRateLen-k-1; j++)
				{
					//�����Ԫ��ǰ��
					szTmp[j+k] = szTmp[j+k+1];
				}
				//�ַ�������һ���ַ��������ַ���������־
				szTmp[nStrRateLen-1] = '\0';
				//���Ƴ���ǰ�ַ�����ַ������浽ԭ�ַ������´δ���
				sprintf_s(szRate, sizeof(szRate), "%s", szTmp);
				break;
			}
		}
	}

	//CStringA stralog;
	//stralog.Format("%s_%s, nPriceStrLength=%d, nPrice=%d", pstrRate, pstrPrice, nPriceStrLength, nPrice);
	//OutputDebugStringA(stralog);

	return nPrice;
}