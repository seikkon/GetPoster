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
	

	CFileFind cFile;
	if(!cFile.FindFile(GetIniPathName(INIFILE)))
		MakeIniFile(INIFILE);
//	MakeIniFile("test.ini");
}

CIniFile::~CIniFile()
{

}


void CIniFile::MakeIniFile(CString const& strIniFileName)
{
	CString strIniPathName=GetIniPathName(strIniFileName);
	CFileFind cFile;
	if(cFile.FindFile(GetIniPathName(strIniPathName)))
		if(AfxMessageBox("初始化档案存在！是否覆盖？",MB_OK|MB_OKCANCEL)==IDCANCEL)
			return;
		
		ofstream _outFile(strIniPathName,ios::out);
		_outFile.close();
		

		CString arraySection[7]={_T("FFMEPGPATH"),_T("THUMBNAILWIDTH"),_T("POSTERDIR"),_T("THUMBNAILDIR"),_T("IMAGEPREFIX"),_T("VIDEOPREFIX"),_T("AUDIOPREFIX")};
		CString arrayCtrlID[7]={_T("1011"),_T("1024"),_T("1013"),_T("1012"),_T("1019"),_T("1017"),_T("1018")};
		CString arrayVal[7]={_T("C:\\ffmpeg.exe"),_T("200"),_T("Poster"),_T("Thumbnail"),_T("image"),_T("video"),_T("audio")};
		CString arrayContent[7]={_T("FFMEPG档"),_T("缩图宽度"),_T("海报目录"),_T("缩图目录"),_T("图档前置"),_T("视频前置"),_T("音档前置")};
		for(int i=0;i<7;i++)
		{   
			const int BUFFSIZE=255;
			TCHAR szBuff[BUFFSIZE]={0};
			CString strData=_T("");
			strData+=_T("CtrlID=")+_T(arrayCtrlID[i])+_T("\r\n");
			strData+=_T("Value=")+_T(arrayVal[i])+_T("\r\n");
			strData+=_T("Content=")+_T(arrayContent[i]);
			strcat(szBuff,strData.GetBuffer(strData.GetLength()));
			::WritePrivateProfileSection(arraySection[i],szBuff,strIniPathName);
		}
}

BOOL CIniFile::WriteString(CString const& strSection, CString const& strKey, CString& strAdd,CString const& strIniFileName)
{
	CString strIniPathName;
	strIniPathName=GetIniPathName(strIniFileName);
//    return ::WritePrivateProfileString(strSection.GetBuffer(strSection.GetLength()),strKey.GetBuffer(strKey.GetLength()),strAdd.GetBuffer(strAdd.GetLength()),strIniPathName.GetBuffer(strIniPathName.GetLength())); 
	return ::WritePrivateProfileString(strSection,strKey,strAdd,strIniPathName); 

}


DWORD CIniFile::ReadString(CString const& strSection,CString const& strKey,CString& strRead,CString const& strIniFileName)
{
	CString strIniPathName;
	strIniPathName=GetIniPathName(strIniFileName);	
//    return ::GetPrivateProfileString(strSection.GetBuffer(strSection.GetLength()), strKey.GetBuffer(strKey.GetLength()),NULL,strRead.GetBuffer(MAX_PATH),MAX_PATH,strIniPathName.GetBuffer(strIniPathName.GetLength()));  
	TCHAR szBuff[MAX_PATH]={0};
	DWORD nRet=::GetPrivateProfileString(strSection, strKey,NULL,szBuff,MAX_PATH,strIniPathName); 
	strRead.Format("%s",szBuff);

	return nRet;
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

DWORD CIniFile::GetSectionString(CString const& strSection, vector<CString>& vecSecData,CString const& strIniFileName)
{

	CString strIniPathName;
	strIniPathName=GetIniPathName(strIniFileName);

	const int BUFFSIZE=255;
	CHAR szBuff[BUFFSIZE]={0};
	DWORD nRet= ::GetPrivateProfileSection(strSection,szBuff,BUFFSIZE,strIniPathName);  
	CHAR *pBuff=szBuff;
	size_t size=strlen(pBuff);
	int i=0; //i记录总数据行数
	while(size) //当取到的行长度不为0时，说明此行存在，继续取值
	{
		CString str=pBuff;
		vecSecData.push_back(str);
		pBuff+=size+1;
		size=strlen(pBuff);
		i++;
	} 
	
    return nRet;
}

BOOL CIniFile::GetSectionName(vector<CString>& vecSecName,CString const& strIniFileName)
{
	CString strIniPathName;
	strIniPathName=GetIniPathName(strIniFileName);

	const int BUFFSIZE=255;
	CHAR szBuff[BUFFSIZE];
	DWORD nRet= ::GetPrivateProfileSectionNames(szBuff,BUFFSIZE,strIniPathName.GetBuffer(strIniPathName.GetLength()));  
	CHAR *pBuff=szBuff;

	size_t size=strlen(pBuff);
	for(int i=0;size!=0;i++) //i记录总数据行数,当取到的行长度不为0时，说明此行存在，继续取值
	{
		CString str=pBuff;
		vecSecName.push_back(str);
		pBuff+=size+1;
		size=strlen(pBuff);
	} 
	
    return nRet;

}

CString CIniFile::GetIniPathName(CString const& strIniFileName)
{
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL,szPath,MAX_PATH);
	CString strIniPathName(szPath);
	strIniPathName=strIniPathName.Left(strIniPathName.ReverseFind('\\')+1);
	strIniPathName += strIniFileName;
	return strIniPathName;
}