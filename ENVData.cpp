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
	CFileFind file;
	if(!file.FindFile(strInitPath))
		CreatInitFile(strInitPath);

	ifstream _inFile(strInitPath,ios::in);
	if(!_inFile.good())
	{	
		_inFile.close();
		AfxMessageBox("�趨������ʧ��",MB_OK);
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
		AfxMessageBox("�����趨��ʧ��",MB_OK);
	}
	else
	{
		_outFile<<'\''<<THUMBNAILWIDTH<<"\' \'200\' \'��ͼ���\'"<<endl;
		_outFile<<'\''<<AUDIOPREFIX<<"\' \'audio\' \'����ǰ��\'"<<endl;
		_outFile<<'\''<<FFMEPGPATH<<"\' \'C:\' \'FFMEPG��\'"<<endl;
		_outFile<<'\''<<IMAGEPREFIX<<"\' \'image\' \'ͼ��ǰ��\'"<<endl;
		_outFile<<'\''<<POSTERDIR<<"\' \'Poster\' \'����Ŀ¼\'"<<endl;
		_outFile<<'\''<<THUMBNAILDIR<<"\' \'Thumbnail\' \'��ͼĿ¼\'"<<endl;
		_outFile<<'\''<<VIDEOPREFIX<<"\' \'video\' \'��Ƶǰ��\'"<<endl<<flush;
		_outFile.close();
	}
}

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
/*
BOOL CENVData::SaveToFile(CString strFile, vector<ENV> &vecENV)
{
	return TRUE;
}
*/

BOOL CENVData::SaveToData()
{
	//	pstruENV=new ENV;
	TCHAR strPath[MAX_PATH];
	GetModuleFileName(NULL,strPath,MAX_PATH);
	CString strInitPath(strPath);
	strInitPath=strInitPath.Left(strInitPath.ReverseFind('\\')+1)+INITEFILE; 
	ofstream _outFile(strInitPath,ios::out);

	if(!_outFile.good()) 
	{
		_outFile.close();
		AfxMessageBox("�����趨��ʧ��",MB_OK);
	}
	else
	{
		vector<ENV>::iterator ite;
		int nSize=m_vecENV.size();
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
