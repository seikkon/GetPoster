// ENVData.cpp: implementation of the CENVData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "getposter.h"
#include "ENVData.h"
#include "IniFile.h"
#include <fstream>

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CENVData::CENVData()
{
	UpdateAllENV(INIFILE);
}

CENVData::~CENVData()
{

}


BOOL CENVData::UpdateAllENV(CString const& strFileName)
{
	CIniFile cIniFile;
	vector<CString> vecSecData,vecSecName;
	vector<CString>::iterator iteVecData,iteVecName;
	struct ENV struInitENV;
	//	vector<ENV>::iterator iteInit;
	//	for(iteData=vecSecData.begin(),iteInit=vecInit.begin();iteData!=vecSecData.end();iteData++,iteInit++)
	cIniFile.GetSectionName(vecSecName,INIFILE);
	for(iteVecName=vecSecName.begin();iteVecName!=vecSecName.end();iteVecName++)
	{
		
		CString strName=*iteVecName;
		cIniFile.GetSectionString(strName,vecSecData,strFileName);
		struInitENV.strSection=strName;
		iteVecData=vecSecData.begin();
		CString strData=*iteVecData;
		struInitENV.nCtrlID=_ttoi(strData.Right(strData.GetLength()-strData.Find('=')-1));
		iteVecData++;strData=*iteVecData;
		struInitENV.strValue=strData.Right(strData.GetLength()-strData.Find('=')-1);
		iteVecData++;strData=*iteVecData;
		struInitENV.strContent=strData.Right(strData.GetLength()-strData.Find('=')-1);
		vecSecData.clear();	
		m_vecENV.push_back(struInitENV);
	}
	return TRUE;
}

CString CENVData::GetENVVal(WORD const& nCtrlID)
{
	vector<ENV>::iterator ite;
	for (ite = m_vecENV.begin(); ite != m_vecENV.end();ite++)
	{
		if(ite->nCtrlID==nCtrlID)
		{
			return ite->strValue;
		}
	}
	return "";
}

BOOL CENVData::UpdateENVVal(WORD const& nCtrlID)
{
	vector<ENV>::iterator ite;
	CString strValue;

	for (ite = m_vecENV.begin(); ite != m_vecENV.end();ite++)
	{
		if(ite->nCtrlID==nCtrlID)
		{

			CIniFile cIniFile;
			cIniFile.ReadString(ite->strSection,VALUE,strValue,INIFILE);
			ite->strValue=strValue;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CENVData::SetENVINIVal(WORD const& nCtrlID,CString& strValue)
{
	vector<ENV>::iterator ite;

	for (ite = m_vecENV.begin(); ite != m_vecENV.end();ite++)
	{
		if(ite->nCtrlID==nCtrlID)
		{
			ite->strValue=strValue;
			CIniFile cIniFile;
 			cIniFile.WriteString(ite->strSection,VALUE,strValue,INIFILE);
			return TRUE;
		}
	}
	return FALSE;
}

