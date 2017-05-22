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
	DoInitENV(INIFILE,m_vecENV);
}

CENVData::~CENVData()
{

}


BOOL CENVData::DoInitENV(CString strFileName,vector<ENV>& vecInit)
{
	CIniFile cIniFile;
	vector<CString> vecSecData,vecSecName;
	vector<CString>::iterator iteVecData,iteVecName;
	struct ENV struInitENV;
//	vector<ENV>::iterator iteInit;
//	for(iteData=vecSecData.begin(),iteInit=vecInit.begin();iteData!=vecSecData.end();iteData++,iteInit++)
	cIniFile.GetSectionName(vecSecData,INIFILE);
	for(iteVecName=vecSecName.begin();iteVecName!=vecSecName.end();iteVecName++)
	{
		
		CString str=*iteVecName;
		cIniFile.GetSectionString(str,vecSecData,strFileName);
		iteVecData=vecSecData.begin;
		struInitENV.nCtrlID=_ttoi((*iteVecData).Right((*iteVecData).GetLength()-(*iteVecData).Find('=')));
		iteVecData++;
		struInitENV.strValue=(*iteVecData).Right((*iteVecData).GetLength()-(*iteVecData).Find('='));
		iteVecData++;
		struInitENV.strContent=(*iteVecData).Right((*iteVecData).GetLength()-(*iteVecData).Find('='));
		vecSecData.clear();	
		vecInit.push_back(struInitENV);
	}
	return TRUE;
}
/*	//	pstruENV=new ENV;
	TCHAR strPath[MAX_PATH];
	GetModuleFileName(NULL,strPath,MAX_PATH);
	CString strInitPath(strPath);
	strInitPath=strInitPath.Left(strInitPath.ReverseFind('\\')+1)+strFileName; 
	CFileFind file;
	if(!file.FindFile(strInitPath))
		CreatInitFile(strInitPath);

	ifstream _inFile(strInitPath,ios::in);
	if(!_inFile.good())
	{	
		_inFile.close();
		AfxMessageBox("设定档开启失败",MB_OK);
		return FALSE;
	}
	struct ENV struInitENV;
	TCHAR strBuf[MAX_PATH];			
	_inFile.getline(strBuf,MAX_PATH);
	while(!_inFile.eof())
	{
		CString strLine(strBuf);
		int nPos=0;
		strLine.TrimLeft('\'');struInitENV.nCtrlID=_ttoi(strLine.Left(nPos=strLine.Find('\'',1)));strLine=strLine.Right(strLine.GetLength()-nPos-2);
		strLine.TrimLeft('\'');struInitENV.strValue=strLine.Left(nPos=strLine.Find('\'',1));strLine=strLine.Right(strLine.GetLength()-nPos-2);
		strLine.TrimLeft('\'');strLine.TrimRight('\'');struInitENV.strContent=strLine;
		vecInit.push_back(struInitENV);
		_inFile.getline(strBuf,MAX_PATH);
	}
	_inFile.close();
	return TRUE;
}

void CENVData::CreatInitFile(CString strInitPath)
{

	ofstream _outFile(strInitPath,ios::out);
//	_outFile(strInitPath,ios::out);
	if(!_outFile.good()) 
	{
		AfxMessageBox("创建设定档失败",MB_OK);
	}
	else
	{
		_outFile<<'\''<<THUMBNAILWIDTH<<"\' \'200\' \'缩图宽度\'"<<endl;
		_outFile<<'\''<<AUDIOPREFIX<<"\' \'audio\' \'音档前置\'"<<endl;
		_outFile<<'\''<<FFMEPGPATH<<"\' \'C:\\ffmpeg.exe' \'FFMEPG档\'"<<endl;
		_outFile<<'\''<<IMAGEPREFIX<<"\' \'image\' \'图档前置\'"<<endl;
		_outFile<<'\''<<POSTERDIR<<"\' \'Poster\' \'海报目录\'"<<endl;
		_outFile<<'\''<<THUMBNAILDIR<<"\' \'Thumbnail\' \'缩图目录\'"<<endl;
		_outFile<<'\''<<VIDEOPREFIX<<"\' \'video\' \'视频前置\'"<<endl<<flush;
		_outFile.close();
	}
}
*/

CString CENVData::GetENVVal(WORD nENVCtrlID)
{
	vector<ENV>::iterator ite;
	for (ite = m_vecENV.begin(); ite != m_vecENV.end();ite++)
	{
		if(ite->nCtrlID==nENVCtrlID)
		{
			return ite->strValue;
		}
	}
	return "";
}

BOOL CENVData::SetENVVal(WORD nENVCtrlID,CString strValue)
{
	vector<ENV>::iterator ite;

	for (ite = m_vecENV.begin(); ite != m_vecENV.end();ite++)
	{
		if(ite->nCtrlID==nENVCtrlID)
		{
			ite->strValue=strValue;
			CIniFile cIniFile;
//			cIniFile.WriteString(SECTIONA,nENVCtrlID,strValue);
			return TRUE;
		}
	}
	return FALSE;
}
/*
BOOL CENVData::SetAllENV(vector<ENV> &vecENV)
{

	return TRUE;
}

BOOL CENVData::GetAllENV(vector<ENV> &vecENV)
{

	return TRUE;
}

BOOL CENVData::LoadFile(CString const& strFile, vector<ENV> &vecENV)
{

	return TRUE;
}

BOOL CENVData::SaveToFile(CString strFile, vector<ENV> &vecENV)
{
	return TRUE;
}


BOOL CENVData::SaveToFile()
{
	//	pstruENV=new ENV;
	TCHAR strPath[MAX_PATH];
	GetModuleFileName(NULL,strPath,MAX_PATH);
	CString strInitPath(strPath);
	strInitPath=strInitPath.Left(strInitPath.ReverseFind('\\')+1)+SETUPFILE; 
	ofstream _outFile(strInitPath,ios::out);

	if(!_outFile.good()) 
	{
		_outFile.close();
		AfxMessageBox("创建设定档失败",MB_OK);
	}
	else
	{
		vector<ENV>::iterator ite;
		for (ite = m_vecENV.begin(); ite != m_vecENV.end();ite++)
		{
			CString strLine;
			strLine.Format("\'%d\' \'%s\' \'%s\'",ite->nCtrlID,ite->strValue,ite->strContent);
 			_outFile<<strLine.GetBuffer(strLine.GetLength())<<endl;
		}	
		_outFile.close();
	}
	return TRUE;
}

void CENVData::UpdateENV()
{
	TCHAR strPath[MAX_PATH];
	GetModuleFileName(NULL,strPath,MAX_PATH);
	CString strInitPath(strPath);
	strInitPath=strInitPath.Left(strInitPath.ReverseFind('\\')+1)+SETUPFILE; 
	ifstream _inFile(strInitPath,ios::in);
	if(!_inFile.good())
	{	
		_inFile.close();
		AfxMessageBox("设定档开启失败",MB_OK);
	}
	else
	{
		m_vecENV.clear();
		int nSize=m_vecENV.size();
		struct ENV struInitENV;
		TCHAR strBuf[MAX_PATH];			
		_inFile.getline(strBuf,MAX_PATH);
		while(!_inFile.eof())
		{
			CString strLine(strBuf);
			int nPos=0;
			strLine.TrimLeft('\'');struInitENV.nCtrlID=_ttoi(strLine.Left(nPos=strLine.Find('\'',1)));strLine=strLine.Right(strLine.GetLength()-nPos-2);
			strLine.TrimLeft('\'');struInitENV.strValue=strLine.Left(nPos=strLine.Find('\'',1));strLine=strLine.Right(strLine.GetLength()-nPos-2);
			strLine.TrimLeft('\'');strLine.TrimRight('\'');struInitENV.strContent=strLine;
			m_vecENV.push_back(struInitENV);
			_inFile.getline(strBuf,MAX_PATH);
		}
		_inFile.close();
	}
}
*/