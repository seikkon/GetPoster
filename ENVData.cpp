// ENVData.cpp: implementation of the CENVData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "getposter.h"
#include "ENVData.h"
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
	DoInitENV(INITEFILE,m_vecENV);
}

CENVData::~CENVData()
{

}
BOOL CENVData::DoInitENV(CString strFileName,vector<ENV>& vecInit)
{
	//	pstruENV=new ENV;
	TCHAR strPath[MAX_PATH];
	GetModuleFileName(NULL,strPath,MAX_PATH);
	CString strInitPath(strPath);
	strInitPath=strInitPath.Left(strInitPath.ReverseFind('\\')+1)+strFileName; 
	
	ifstream _inFile;
	_inFile.open(strInitPath,ios::in);
	if(!_inFile.good())
	{	
		_inFile.close();
		CreatInitFile(strFileName,vecInit);
		_inFile.open(strInitPath,ios::in);
	}
	
	TCHAR strBuf[MAX_PATH];			
	struct ENV struInitENV;
	while(!_inFile.eof())
	{
		_inFile.getline(strBuf,MAX_PATH);
		CString strLine(strBuf);
		int nPos=0;
		strLine.TrimLeft('\'');struInitENV.strCtrlID=strLine.Left(nPos=strLine.Find('\'',1));strLine=strLine.Right(strLine.GetLength()-nPos-2);
		strLine.TrimLeft('\'');struInitENV.strValue=strLine.Left(nPos=strLine.Find('\'',1));strLine=strLine.Right(strLine.GetLength()-nPos-2);
		strLine.TrimLeft('\'');strLine.TrimRight('\'');struInitENV.strContent=strLine;
		vecInit.push_back(struInitENV);
	}
	_inFile.close();
	
	return TRUE;
}

void CENVData::CreatInitFile(CString strFileName,vector<ENV>& vecInit)
{
	TCHAR strPath[MAX_PATH];
	GetModuleFileName(NULL,strPath,MAX_PATH);
	CString strInitFile(strPath);
	strInitFile=strInitFile.Left(strInitFile.ReverseFind('\\')+1)+strFileName; 
	
	ofstream _outFile;
	if(!_outFile.good()) 
	{
		AfxMessageBox("�����趨��ʧ��",MB_OK);
	}
	else
	{
		_outFile<<"\'THUMBNAILWIDTH\' \'200\' \'��ͼ���\'"<<endl;
		_outFile<<"\'AUDIOPREFIX\' \'audio\' \'����ǰ��\'"<<endl;
		_outFile<<"\'FFMEPGPATH\' \'C:\' \'FFMEPG��\'"<<endl;
		_outFile<<"\'IMAGEPREFIX\' \'image\' \'ͼ��ǰ��\'"<<endl;
		_outFile<<"\'POSTERDIR\' \'Poster\' \'����Ŀ¼\'"<<endl;
		_outFile<<"\'THUMBNAILDIR\' \'Thumbnail\' \'��ͼĿ¼\'"<<endl;
		_outFile<<"\'VIDEOPREFIX\' \'video\' \'��Ƶǰ��\'"<<endl<<flush;
		_outFile.close();
	}
}

CString CENVData::GetENVVal(CString strENVCtrlID)
{
	vector<ENV>::iterator ite;
	for (ite = m_vecENV.begin(); ite != m_vecENV.end();ite++)
	{
		if(ite->strCtrlID==strENVCtrlID)
		{
			return ite->strValue;
		}
	}
	return "";
}

BOOL CENVData::SetENVVal(CString strENVCtrlID,CString strValue)
{
	vector<ENV>::iterator ite;
	for (ite = m_vecENV.begin(); ite != m_vecENV.end();ite++)
	{
		if(ite->strCtrlID==strENVCtrlID)
		{
			ite->strValue=strValue;
		}
	}
	return TRUE;
}

BOOL CENVData::SetAllENV(vector<ENV> &vecENV)
{

	return TRUE;
}

BOOL CENVData::GetAllENV(vector<ENV> &vecENV)
{

	return TRUE;
}

BOOL CENVData::LoadFile(CString strFile, vector<ENV> &vecENV)
{

	return TRUE;
}

BOOL CENVData::SaveData(CString strFile, vector<ENV> &vecENV)
{
	return TRUE;
}
