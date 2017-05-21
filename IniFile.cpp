// IniFile.cpp: implementation of the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <Afx.H>
#include "getposter.h"
#include "IniFile.h"
#include <FSTREAM>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIniFile::CIniFile()
{
	
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL,szPath,MAX_PATH);
	CString strIniPathName(szPath);
	strIniPathName=strIniPathName.Left(strIniPathName.ReverseFind('\\')+1);
	strIniPathName += INIFILE;
	m_strIniPathName=strIniPathName;
	CFileFind cFile;
	if(!cFile.FindFile(m_strIniPathName))
		MakeIniFile(m_strIniPathName);
}

CIniFile::~CIniFile()
{

}


void CIniFile::MakeIniFile(CString strIniPathName)
{

	
	CFileFind cFile;
	if(cFile.FindFile(strIniPathName))
		if(AfxMessageBox("��ʼ���������ڣ��Ƿ񸲸ǣ�",MB_OK|MB_OKCANCEL)==IDCANCEL)
			return;
		
		ofstream _outFile(strIniPathName,ios::out);
		_outFile.close();
		
		CString strData;
		CString arrayCtrlID[7]={"THUMBNAILWIDTH=1024","AUDIOPREFIX=1018","FFMEPGPATH=1011","IMAGEPREFIX=1019","POSTERDIR=1013","THUMBNAILDIR=1012","VIDEOPREFIX=1017"};
		CString arrayVal[7]={"THUMBNAILWIDTH=200","AUDIOPREFIX=audio","FFMEPGPATH=C:\\ffmpeg.exe","IMAGEPREFIX=image","POSTERDIR=Poster","THUMBNAILDIR=Thumbnail","VIDEOPREFIX=video"};
		CString arrayContent[7]={"THUMBNAILWIDTH=��ͼ���","AUDIOPREFIX=����ǰ��","FFMEPGPATH=FFMEPG��","IMAGEPREFIX=ͼ��ǰ��","POSTERDIR=����Ŀ¼","THUMBNAILDIR=��ͼĿ¼","VIDEOPREFIX=��Ƶǰ��"};
		for(int i=0;i<7;i++)
		{
			strData+=arrayCtrlID[i];
			strData+='\0';
		}
		::WritePrivateProfileSection(SECTIONA,strData.GetBuffer(strData.GetLength()),strIniPathName.GetBuffer(strIniPathName.GetLength()));
		for(int i=0;i<7;i++)
		{
			strData+=arrayVal[i];
			strData+='\0';
		}
		::WritePrivateProfileSection(SECTIONB,strData.GetBuffer(strData.GetLength()),strIniPathName.GetBuffer(strIniPathName.GetLength()));
		for(int i=0;i<7;i++)
		{
			strData+=arrayContent[i];
			strData+='\0';
		}
		::WritePrivateProfileSection(SECTIONC,strData.GetBuffer(strData.GetLength()),strIniPathName.GetBuffer(strIniPathName.GetLength()));
}

BOOL CIniFile::WriteString(CString strSection, CString strKey, CString& strAdd)
{

    return ::WritePrivateProfileString(strSection.GetBuffer(strSection.GetLength()),strKey.GetBuffer(strKey.GetLength()),strAdd.GetBuffer(strAdd.GetLength()),m_strIniPathName.GetBuffer(m_strIniPathName.GetLength())); 
}


DWORD CIniFile::ReadString(CString strSection,CString strKey,CString& strRead)
{
	
    return ::GetPrivateProfileString(strSection.GetBuffer(strSection.GetLength()), strKey.GetBuffer(strKey.GetLength()),NULL,strRead.GetBuffer(MAX_PATH),MAX_PATH,m_strIniPathName.GetBuffer(m_strIniPathName.GetLength()));  
}
/*

BOOL CIniFile::WriteString(CString strSection,int nKey, CString& strAdd)
{
// 	CString strIniPathName;
// 	GetModuleFileName(NULL,strIniPathName.GetBuffer(MAX_PATH),MAX_PATH);
// 	strIniPathName.SetAt(strIniPathName.ReverseFind('\\')+1,'\0');
// 	strIniPathName=strIniPathName +strIniFileName;
	CString strKey;
	strKey.Format("%d",nKey);
    return ::WritePrivateProfileString(strSection.GetBuffer(strSection.GetLength()),strKey.GetBuffer(strKey.GetLength()),strAdd.GetBuffer(strAdd.GetLength()),m_strIniPathName.GetBuffer(m_strIniPathName.GetLength())); 
}

DWORD CIniFile::ReadString(CString strSection,int nKey,CString& strRead)
{

	CString strKey,strBuff;
	strKey.Format("%d",nKey);
	DWORD nRet= ::GetPrivateProfileString(strSection.GetBuffer(strSection.GetLength()), strKey.GetBuffer(strKey.GetLength()),NULL,strBuff.GetBuffer(MAX_PATH),MAX_PATH,m_strIniPathName.GetBuffer(m_strIniPathName.GetLength()));  
	strRead=strBuff;
	
    return nRet;
}
*/

DWORD CIniFile::GetSectionString(CString strSection, vector<CString>& vecSecData)
{

	const int BUFFSIZE=2048;
	CHAR szBuff[BUFFSIZE];
	DWORD nRet= ::GetPrivateProfileSection(strSection.GetBuffer(strSection.GetLength()),szBuff,BUFFSIZE,m_strIniPathName.GetBuffer(m_strIniPathName.GetLength()));  
	CHAR *pBuff=szBuff;
	size_t size=strlen(pBuff);
	int i=0; //i��¼����������
	while(size) //��ȡ�����г��Ȳ�Ϊ0ʱ��˵�����д��ڣ�����ȡֵ
	{
		CString str=pBuff;
		vecSecData.push_back(str);
		pBuff+=size+1;
		size=strlen(pBuff);
		i++;
	} 
	
    return nRet;
}